#ifndef SERIALREADER_H
#define SERIALREADER_H

#include <QObject>
#include <QSerialPort>
#include <QByteArray>

class SerialReader : public QObject
{
    Q_OBJECT
public:
    explicit SerialReader(QObject *parent = nullptr);
    bool openPort(const QString &portName, qint32 baudRate = 115200);

signals:
    void potValueReceived(quint16 value);

private slots:
    void onReadyRead();

private:
    enum State { WAIT_STX, WAIT_MSG_ID, WAIT_LEN, WAIT_PAYLOAD, WAIT_CHECKSUM, WAIT_ETX };

    QSerialPort *serial;
    State   state = WAIT_STX;
    quint8  msgId = 0;
    quint8  payloadLen = 0;
    QByteArray payload;
    quint8  checksum = 0;

    void processByte(quint8 byte);
};

#endif // SERIALREADER_H
