#include "Mng_System.h"
#include <VLink_Links/UDP_VLink.h>
#include <VLink_Links/Serial_VLink.h>
#include <Mng_Connection.h>

Mng_System* Mng_System::instance = NULL;

Mng_System::Mng_System(QObject *parent) : QObject(parent)
{
    m_UDPCommID = Mng_Connection::Instance()->AddNewCommunication();
    ShrdPtrComm CommUdp = Mng_Connection::Instance()->Communication( m_UDPCommID );
    ShrdPtrInfo udpInfo (new UDP_Info());
    CommUdp.data()->setSendNewBytesSignal( true );
    connect( CommUdp.data(), &VLink_Communication::SgNewBytes, [this](ShrdPtrByteArray Bytes)
    {
        emit SgNewBytes( Bytes, Qt::red );
    });
    connect( CommUdp.data(), &VLink_Communication::SgLinkStarted, [this]()
    {
        emit SgUDPStarted();
    });
    connect( CommUdp.data(), &VLink_Communication::SgLinkStopped, [this]()
    {
        emit SgUDPStopped();
    });

    m_UDPLinkID = CommUdp.data()->AddLink( LinkType::Link_UDP, udpInfo );
    // ---------

    m_SerialCommID = Mng_Connection::Instance()->AddNewCommunication();
    ShrdPtrComm CommSerial = Mng_Connection::Instance()->Communication( m_SerialCommID );
    ShrdPtrInfo serialInfo (new Serial_Info());
    CommSerial.data()->setSendNewBytesSignal( true );
    connect( CommSerial.data(), &VLink_Communication::SgNewBytes, [this](ShrdPtrByteArray Bytes)
    {
        emit SgNewBytes( Bytes, Qt::blue );
    });
    connect( CommSerial.data(), &VLink_Communication::SgLinkStarted, [this]()
    {
        emit SgSerialStarted();
    });
    connect( CommSerial.data(), &VLink_Communication::SgLinkStopped, [this]()
    {
        emit SgSerialStopped();
    });

    m_SerialLinkID =  CommSerial.data()->AddLink( LinkType::Link_Serial, serialInfo );
    // ---------
}

int Mng_System::SerialLinkID() const
{
    return m_SerialLinkID;
}

void Mng_System::setSerialLinkID(int SerialLinkID)
{
    m_SerialLinkID = SerialLinkID;
}

int Mng_System::UDPLinkID() const
{
    return m_UDPLinkID;
}

void Mng_System::setUDPLinkID(int UDPLinkID)
{
    m_UDPLinkID = UDPLinkID;
}

int Mng_System::SerialCommID() const
{
    return m_SerialCommID;
}

int Mng_System::UDPCommID() const
{
    return m_UDPCommID;
}
