#ifndef DLGSERIAL_H
#define DLGSERIAL_H

#include <QDialog>
#include <QSerialPort>

namespace Ui {
class dlgSerial;
}

class dlgSerial : public QDialog
{
    Q_OBJECT

public:
    explicit dlgSerial(QWidget *parent = nullptr);
    ~dlgSerial();

    void setConfig( QString PortName, int BaudRate, QSerialPort::Parity Parity, QSerialPort::StopBits StopBits, QSerialPort::DataBits DataBits );

private slots:
    void on_buttonBox_accepted();

    void on_btnRefresh_clicked();

protected:
    void showEvent(QShowEvent* );

private:
    Ui::dlgSerial *ui;

    QSerialPort::Parity CurrentParity();
    void SetCurrentParity(QSerialPort::Parity parity);

    QSerialPort::DataBits CurrentDatabits();
    void SetCurrentDataBits(QSerialPort::DataBits dataBits);

    QSerialPort::StopBits CurrentStopBits();
    void SetCurrentStopBits(QSerialPort::StopBits stopBits);
};

#endif // DLGSERIAL_H
