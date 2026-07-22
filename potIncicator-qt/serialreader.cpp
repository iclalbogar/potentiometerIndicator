#include "serialreader.h"
#include <QDebug>

static const quint8 POT_STX = 0xAA;
static const quint8 POT_ETX = 0x55;
static const quint8 POT_MSG_ID_VALUE = 0x01;

SerialReader::SerialReader(QObject *parent)
    : QObject(parent), serial(new QSerialPort(this))
{
}

bool SerialReader::openPort(const QString &portName, qint32 baudRate)
{
    serial->setPortName(portName);
    serial->setBaudRate(baudRate);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (!serial->open(QIODevice::ReadOnly))
        return false;

    connect(serial, &QSerialPort::readyRead, this, &SerialReader::onReadyRead);
    return true;
}

void SerialReader::onReadyRead()
{
    const QByteArray data = serial->readAll();
    qDebug() << "RX:" << data.toHex(' ');
    for (const char c : data)
        processByte(static_cast<quint8>(c));
}

void SerialReader::processByte(quint8 byte)
{
    switch (state)
    {
    case WAIT_STX:
        if (byte == POT_STX)
            state = WAIT_MSG_ID;
        break;

    case WAIT_MSG_ID:
        msgId = byte;
        state = WAIT_LEN;
        break;

    case WAIT_LEN:
        payloadLen = byte;
        payload.clear();
        state = (payloadLen > 0) ? WAIT_PAYLOAD : WAIT_CHECKSUM;
        break;

    case WAIT_PAYLOAD:
        payload.append(static_cast<char>(byte));
        if (payload.size() >= payloadLen)
            state = WAIT_CHECKSUM;
        break;

    case WAIT_CHECKSUM:
        checksum = byte;
        state = WAIT_ETX;
        break;

    case WAIT_ETX:
        if (byte == POT_ETX)
        {
            quint8 calc = msgId ^ payloadLen;
            for (const char b : payload)
                calc ^= static_cast<quint8>(b);

            if (calc == checksum && msgId == POT_MSG_ID_VALUE && payload.size() == 2)
            {
                quint16 value = (static_cast<quint8>(payload[0]) << 8)
                               |  static_cast<quint8>(payload[1]);
                emit potValueReceived(value);
            }
        }
        state = WAIT_STX;
        break;
    }
}
