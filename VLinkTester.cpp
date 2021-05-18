#include "VLinkTester.h"
#include "ui_VLinkTester.h"
#include <Mng_Connection.h>
#include <Management/Mng_System.h>
#include <QFileDialog>
#include "Management/Mng_Settings.h"

VLink_Tester::VLink_Tester(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VLinkTester)
{
    ui->setupUi(this);

    m_dlgUDP = new dlgUDP( this );

    m_dlgSerial = new dlgSerial( this );

    m_StatusLabel = new QLabel();
    m_StatusLabel->setText( "------------" );
    this->ui->statusBar->addWidget( m_StatusLabel );

    QList<CompLinePack*> packs = GetPackPointers();
    Mng_Settings::Instance()->LoadPackDefault( packs );

    Serial_Info* serialInfo = (Serial_Info*)Mng_Connection::Instance()->Communication( Mng_System::Instance()->SerialCommID() ).data()->LinkInfo( Mng_System::Instance()->SerialLinkID() ).data();
    UDP_Info* udpInfo = (UDP_Info*)Mng_Connection::Instance()->Communication( Mng_System::Instance()->UDPCommID() ).data()->LinkInfo( Mng_System::Instance()->UDPLinkID() ).data();

    Mng_Settings::Instance()->LoadLinkConfigDefault(
                serialInfo,
                udpInfo);

    m_dlgSerial->setConfig( serialInfo->PortName(), serialInfo->BaudRate(), serialInfo->Parity(), serialInfo->StopBit(), serialInfo->DataBits() );
    m_dlgUDP->SetConfig( udpInfo->m_PeerIP, udpInfo->m_TxPort, udpInfo->m_RxPort );

    connect( this->ui->wgPack1, &CompLinePack::SgSendBytes, this, &VLink_Tester::SltPrSendBytes );
    connect( this->ui->wgPack2, &CompLinePack::SgSendBytes, this, &VLink_Tester::SltPrSendBytes );
    connect( this->ui->wgPack3, &CompLinePack::SgSendBytes, this, &VLink_Tester::SltPrSendBytes );
    connect( this->ui->wgPack4, &CompLinePack::SgSendBytes, this, &VLink_Tester::SltPrSendBytes );

    connect( Mng_System::Instance(), &Mng_System::SgNewBytes, this, &VLink_Tester::SltPrReceivedBytes );
    connect( Mng_System::Instance(), &Mng_System::SgUDPStarted, [this]() { m_StatusLabel->setText( "UDP Started!" );});
    connect( Mng_System::Instance(), &Mng_System::SgUDPStopped, [this]() { m_StatusLabel->setText( "UDP Stopped!" );});
    connect( Mng_System::Instance(), &Mng_System::SgSerialStarted, [this]() { m_StatusLabel->setText( "Serial Started!" );});
    connect( Mng_System::Instance(), &Mng_System::SgSerialStopped, [this]() { m_StatusLabel->setText( "Serial Stopped!" );});
}

VLink_Tester::~VLink_Tester()
{
    delete ui;
}

QList<CompLinePack *> VLink_Tester::GetPackPointers()
{
    QList<CompLinePack*> packs;
    packs.append( this->ui->wgPack1 );
    packs.append( this->ui->wgPack2 );
    packs.append( this->ui->wgPack3 );
    packs.append( this->ui->wgPack4 );

    return packs;
}

void VLink_Tester::SltPrSendBytes(ShrdPtrByteArray Sent)
{
    if( Sent.data()->size() == 0 )
        return;

    Mng_Connection::Instance()->Communication( Mng_System::Instance()->UDPCommID() ).data()->SendBytes( Sent );
    Mng_Connection::Instance()->Communication( Mng_System::Instance()->SerialCommID() ).data()->SendBytes( Sent );

    if( !this->ui->chbxShowSentBytes->isChecked() )
        return;

    this->ui->txtSent->setTextColor( Qt::blue );
    this->ui->txtSent->append( QString( Sent.data()->toHex(':').toUpper() ) + tr(":") );
}

void VLink_Tester::SltPrReceivedBytes(ShrdPtrByteArray Received, Qt::GlobalColor color)
{
    if( !this->ui->chbxShowRxBytes->isChecked() )
        return;

    this->ui->txtReceived->setTextColor( color );
    this->ui->txtReceived->insertPlainText( QString( Received.data()->toHex(':').toUpper() ) + tr("::") );
}

void VLink_Tester::on_actionUDP_triggered()
{
    m_dlgUDP->show();
}

void VLink_Tester::on_actionSerial_triggered()
{
    m_dlgSerial->show();
}

void VLink_Tester::on_actionUDPStart_triggered(bool checked)
{
    if( checked )
        Mng_Connection::Instance()->Communication( Mng_System::Instance()->UDPCommID() ).data()->Start();
    else
        Mng_Connection::Instance()->Communication( Mng_System::Instance()->UDPCommID() ).data()->Stop();
}

void VLink_Tester::on_actionSerialStart_triggered(bool checked)
{
    if( checked )
        Mng_Connection::Instance()->Communication( Mng_System::Instance()->SerialCommID() ).data()->Start();
    else
        Mng_Connection::Instance()->Communication( Mng_System::Instance()->SerialCommID() ).data()->Stop();
}

void VLink_Tester::on_actionExit_triggered()
{
    QApplication::exit();
}

void VLink_Tester::on_actionExport_Packs_triggered()
{
    QString FileName = QFileDialog::getSaveFileName( this, "Pack File", "", "Pack File (*.vpkg)" );

    QList<CompLinePack*> packs = GetPackPointers();

    Mng_Settings::Instance()->ExportPacks( FileName, packs );
}

void VLink_Tester::on_actionImport_Packs_triggered()
{
    QString FileName = QFileDialog::getOpenFileName( this, "Pack File", "", "Pack File (*.vpkg)" );

    QList<CompLinePack*> packs = GetPackPointers();

    Mng_Settings::Instance()->ImportPacks( FileName, packs );
}

void VLink_Tester::on_actionExport_Link_Configs_triggered()
{
    QString FileName = QFileDialog::getSaveFileName( this, "Link Config File", "", "Pack File (*.vconf)" );

    Mng_Settings::Instance()->ExportLinkConfigs(
                FileName,
                (Serial_Info*)Mng_Connection::Instance()->Communication( Mng_System::Instance()->SerialCommID() ).data()->LinkInfo( Mng_System::Instance()->SerialLinkID() ).data(),
                (UDP_Info*)Mng_Connection::Instance()->Communication( Mng_System::Instance()->UDPCommID() ).data()->LinkInfo( Mng_System::Instance()->UDPLinkID() ).data());
}

void VLink_Tester::on_actionImport_Link_Configs_triggered()
{
    QString FileName = QFileDialog::getOpenFileName( this, "Pack File", "", "Link Config File (*.vconf)" );

    Serial_Info* serialInfo = (Serial_Info*)Mng_Connection::Instance()->Communication( Mng_System::Instance()->SerialCommID() ).data()->LinkInfo( Mng_System::Instance()->SerialLinkID() ).data();
    UDP_Info* udpInfo = (UDP_Info*)Mng_Connection::Instance()->Communication( Mng_System::Instance()->UDPCommID() ).data()->LinkInfo( Mng_System::Instance()->UDPLinkID() ).data();

    Mng_Settings::Instance()->ImportLinkConfigs(
                FileName,
                serialInfo,
                udpInfo);

    m_dlgSerial->setConfig( serialInfo->PortName(), serialInfo->BaudRate(), serialInfo->Parity(), serialInfo->StopBit(), serialInfo->DataBits() );
    m_dlgUDP->SetConfig( udpInfo->m_PeerIP, udpInfo->m_TxPort, udpInfo->m_RxPort );
}

void VLink_Tester::on_actionSave_Link_Configs_as_Default_triggered()
{
    Mng_Settings::Instance()->SaveLinkConfigDefault(
                (Serial_Info*)Mng_Connection::Instance()->Communication( Mng_System::Instance()->SerialCommID() ).data()->LinkInfo( Mng_System::Instance()->SerialLinkID() ).data(),
                (UDP_Info*)Mng_Connection::Instance()->Communication( Mng_System::Instance()->UDPCommID() ).data()->LinkInfo( Mng_System::Instance()->UDPLinkID() ).data() );
}

void VLink_Tester::on_actionSave_Packs_as_Default_triggered()
{
    QList<CompLinePack*> packs = GetPackPointers();

    Mng_Settings::Instance()->SavePacksDefault( packs );
}
