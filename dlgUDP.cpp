#include "dlgUDP.h"
#include "ui_dlgUDP.h"
#include <Management/Mng_System.h>
#include <Mng_Connection.h>
#include <VLink_Links/UDP_VLink.h>
#include <VLink_Infos/UDP_Info.h>

dlgUDP::dlgUDP(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgUDP)
{
    ui->setupUi(this);

    on_buttonBox_accepted();
}

dlgUDP::~dlgUDP()
{
    delete ui;
}

void dlgUDP::SetConfig(QString IP, int TxPort, int RxPort)
{
    this->ui->txtPeerIP->setText( IP );
    this->ui->numudTxPort->setValue( TxPort );
    this->ui->numudRxPort->setValue( RxPort );
}

void dlgUDP::on_buttonBox_accepted()
{
    ShrdPtrComm Comm = Mng_Connection::Instance()->Communication( Mng_System::Instance()->UDPCommID() );

    ShrdPtrInfo info = Comm.data()->LinkInfo( Mng_System::Instance()->UDPLinkID() );
    ((UDP_Info*)info.data())->m_PeerIP = this->ui->txtPeerIP->text();
    ((UDP_Info*)info.data())->m_RxPort = this->ui->numudRxPort->value();
    ((UDP_Info*)info.data())->m_TxPort = this->ui->numudTxPort->value();
}
