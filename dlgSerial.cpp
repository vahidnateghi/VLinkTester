#include "dlgSerial.h"
#include "ui_dlgSerial.h"

#include <Management/Mng_System.h>
#include <Mng_Connection.h>
#include <VLink_Links/Serial_VLink.h>
#include <VLink_Infos/Serial_Info.h>
#include <QSerialPortInfo>

dlgSerial::dlgSerial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgSerial)
{
    ui->setupUi(this);

    on_btnRefresh_clicked();
}

dlgSerial::~dlgSerial()
{
    delete ui;
}

void dlgSerial::setConfig(QString PortName, int BaudRate, QSerialPort::Parity Parity, QSerialPort::StopBits StopBits, QSerialPort::DataBits DataBits)
{
    this->ui->cmbxPortName->setCurrentText( PortName );
    this->ui->numudBaudrate->setValue( BaudRate );
    SetCurrentParity( Parity );
    SetCurrentStopBits( StopBits );
    SetCurrentDataBits( DataBits );
}

void dlgSerial::on_buttonBox_accepted()
{
    ShrdPtrComm Comm = Mng_Connection::Instance()->Communication( Mng_System::Instance()->SerialCommID() );

    ShrdPtrInfo info = Comm.data()->LinkInfo( Mng_System::Instance()->SerialLinkID() );
    ((Serial_Info*)info.data())->setPortName( this->ui->cmbxPortName->currentText() );
    ((Serial_Info*)info.data())->setBaudRate( this->ui->numudBaudrate->value() );
    ((Serial_Info*)info.data())->setParity( CurrentParity() );
    ((Serial_Info*)info.data())->setStopBit( CurrentStopBits() );
    ((Serial_Info*)info.data())->setDataBits( CurrentDatabits() );
    this->hide();
}

void dlgSerial::on_btnRefresh_clicked()
{
    this->ui->cmbxPortName->clear();
    QList<QSerialPortInfo> List = QSerialPortInfo::availablePorts();
    for( int i = 0 ; i < List.size(); i++ )
        this->ui->cmbxPortName->addItem( List.at(i).portName() );
}

void dlgSerial::showEvent(QShowEvent *)
{

}

QSerialPort::Parity dlgSerial::CurrentParity()
{
    if( this->ui->cmbxParity->currentText() == "Odd" ) return QSerialPort::OddParity;
    if( this->ui->cmbxParity->currentText() == "Even" ) return QSerialPort::EvenParity;
    if( this->ui->cmbxParity->currentText() == "NoParity" ) return QSerialPort::NoParity;
    if( this->ui->cmbxParity->currentText() == "SpaceParity" ) return QSerialPort::SpaceParity;
    if( this->ui->cmbxParity->currentText() == "MarkParity" ) return QSerialPort::MarkParity;
    if( this->ui->cmbxParity->currentText() == "UnknownParity" ) return QSerialPort::UnknownParity;

    return QSerialPort::UnknownParity;
}

void dlgSerial::SetCurrentParity(QSerialPort::Parity parity)
{
    if( parity == QSerialPort::Parity::OddParity ) this->ui->cmbxParity->setCurrentText( "Odd" );
    else if( parity == QSerialPort::Parity::EvenParity ) this->ui->cmbxParity->setCurrentText( "Even" );
    else if( parity == QSerialPort::Parity::NoParity ) this->ui->cmbxParity->setCurrentText( "NoParity" );
    else if( parity == QSerialPort::Parity::SpaceParity ) this->ui->cmbxParity->setCurrentText( "SpaceParity" );
    else if( parity == QSerialPort::Parity::MarkParity ) this->ui->cmbxParity->setCurrentText( "MarkParity" );
    else if( parity == QSerialPort::Parity::UnknownParity ) this->ui->cmbxParity->setCurrentText( "UnknownParity" );
}

QSerialPort::DataBits dlgSerial::CurrentDatabits()
{
    if( this->ui->cmbxDataBits->currentText() == "Data 5" ) return QSerialPort::Data5;
    if( this->ui->cmbxDataBits->currentText() == "Data 6" ) return QSerialPort::Data6;
    if( this->ui->cmbxDataBits->currentText() == "Data 7" ) return QSerialPort::Data7;
    if( this->ui->cmbxDataBits->currentText() == "Data 8" ) return QSerialPort::Data8;
    if( this->ui->cmbxDataBits->currentText() == "Unknown" ) return QSerialPort::UnknownDataBits;
}

void dlgSerial::SetCurrentDataBits(QSerialPort::DataBits dataBits)
{
    if( dataBits == QSerialPort::DataBits::Data5 ) this->ui->cmbxDataBits->setCurrentText( "Data 5" );
    else if( dataBits == QSerialPort::DataBits::Data6 ) this->ui->cmbxDataBits->setCurrentText( "Data 6" );
    else if( dataBits == QSerialPort::DataBits::Data7 ) this->ui->cmbxDataBits->setCurrentText( "Data 7" );
    else if( dataBits == QSerialPort::DataBits::Data8 ) this->ui->cmbxDataBits->setCurrentText( "Data 8" );
    else if( dataBits == QSerialPort::DataBits::UnknownDataBits ) this->ui->cmbxDataBits->setCurrentText( "Unknown" );
}

QSerialPort::StopBits dlgSerial::CurrentStopBits()
{
    if( this->ui->cmbxStopBit->currentText() == "One" ) return QSerialPort::StopBits::OneStop;
    if( this->ui->cmbxStopBit->currentText() == "One And Half" ) return QSerialPort::StopBits::OneAndHalfStop;
    if( this->ui->cmbxStopBit->currentText() == "Two" ) return QSerialPort::StopBits::TwoStop;
    if( this->ui->cmbxStopBit->currentText() == "Unknown" ) return QSerialPort::StopBits::UnknownStopBits;
}

void dlgSerial::SetCurrentStopBits(QSerialPort::StopBits stopBits)
{
    if( stopBits == QSerialPort::StopBits::OneStop ) this->ui->cmbxStopBit->setCurrentText( "One" );
    else if( stopBits == QSerialPort::StopBits::OneAndHalfStop ) this->ui->cmbxStopBit->setCurrentText( "One And Half" );
    else if( stopBits == QSerialPort::StopBits::TwoStop ) this->ui->cmbxStopBit->setCurrentText( "Two" );
    else if( stopBits == QSerialPort::StopBits::UnknownStopBits ) this->ui->cmbxStopBit->setCurrentText( "Unknown" );
}
