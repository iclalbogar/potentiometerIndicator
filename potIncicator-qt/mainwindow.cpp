#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts())
        ui->portCombo->addItem(info.portName());

    ui->progressBar->setRange(0, 4095);
    ui->valueSlider->setRange(0, 4095);
    ui->valueSlider->setEnabled(false);

    reader = new SerialReader(this);
    connect(reader, &SerialReader::potValueReceived, this, &MainWindow::onPotValue);
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::onConnectClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onConnectClicked()
{
    const QString port = ui->portCombo->currentText();
    if (reader->openPort(port, 115200))
    {
        ui->connectButton->setEnabled(false);
        ui->connectButton->setText("Bağlandı");
    }
    else
    {
        ui->valueLabel->setText("Bağlantı hatası");
    }
}

void MainWindow::onPotValue(quint16 value)
{
    const double voltage = (value * 3.3) / 4095.0;

    ui->progressBar->setValue(value);
    ui->valueSlider->setValue(value);
    ui->valueLabel->setText(QString("%1 V").arg(voltage, 0, 'f', 2));
}
