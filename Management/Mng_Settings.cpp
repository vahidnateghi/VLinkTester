#include "Mng_Settings.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#define MAX_PACK_SIZE 20

Mng_Settings* Mng_Settings::instance = NULL;

Mng_Settings::Mng_Settings(QObject *parent) : QObject(parent)
{

}

////////////////////////////

void Mng_Settings::ImportPacks( QString FileName, QList<CompLinePack*> packComps )
{
    QFile file( FileName );
    if( !file.open( QIODevice::ReadOnly ) )
        return;

    QJsonDocument jdoc = QJsonDocument::fromJson( file.readAll() );
    for( int i = 0; i < MAX_PACK_SIZE; i++ )
    {
        if( !jdoc.object().contains( tr("Pack_") + QString::number(i) + tr("_SendType") ) )
            break;
        if( i >= packComps.size() )
            break;
        QString Text; Enum_PackSendType SendType; bool SendFile; QString FileName; bool Timer; int TimerInterval;
        Text = jdoc.object()[tr("Pack_") + QString::number(i) + tr("_Text")].toString();
        SendType = (Enum_PackSendType)jdoc.object()[tr("Pack_") + QString::number(i) + tr("_SendType")].toInt();
        SendFile = jdoc.object()[tr("Pack_") + QString::number(i) + tr("_SendFile")].toBool();
        FileName = jdoc.object()[tr("Pack_") + QString::number(i) + tr("_FileName")].toString();
        Timer = jdoc.object()[tr("Pack_") + QString::number(i) + tr("_Timer")].toBool();
        TimerInterval = jdoc.object()[tr("Pack_") + QString::number(i) + tr("_TimerInterval")].toInt();
        packComps.at(i)->SetData( Text, SendType, SendFile, FileName, Timer, TimerInterval );
    }
}

void Mng_Settings::ExportPacks( QString FileName, const QList<CompLinePack*> packComps )
{
    QFile file( FileName );
    if( !file.open( QIODevice::WriteOnly ) )
        return;

    QJsonObject obj;
    for( int i = 0; i < packComps.size(); i++ )
    {
        QString Text; Enum_PackSendType SendType; bool SendFile; QString FileName; bool Timer; int TimerInterval;
        packComps.at(i)->GetData( Text, SendType, SendFile, FileName, Timer, TimerInterval );
        obj.insert(tr("Pack_") + QString::number(i) + tr("_Text"), Text );
        obj.insert(tr("Pack_") + QString::number(i) + tr("_SendType"), (int)SendType );
        obj.insert(tr("Pack_") + QString::number(i) + tr("_SendFile"), SendFile );
        obj.insert(tr("Pack_") + QString::number(i) + tr("_FileName"), FileName );
        obj.insert(tr("Pack_") + QString::number(i) + tr("_Timer"), Timer );
        obj.insert(tr("Pack_") + QString::number(i) + tr("_TimerInterval"), TimerInterval );
    }

    QJsonDocument jdoc( obj );

    file.write( jdoc.toJson() );
    file.close();
}

void Mng_Settings::SavePacksDefault( const QList<CompLinePack*> packComps )
{
    ExportPacks( "PacksDefault.vpkg", packComps );
}

void Mng_Settings::LoadPackDefault( QList<CompLinePack*> packComps )
{
    ImportPacks( "PacksDefault.vpkg", packComps );
}

////////////////////////////

void Mng_Settings::ImportLinkConfigs( QString FileName, Serial_Info* serial, UDP_Info* udp )
{
    QFile file( FileName );
    if( !file.open( QIODevice::ReadOnly ) )
        return;

    QJsonParseError error;
    QJsonDocument jdoc = QJsonDocument::fromJson( file.readAll(), &error );
    if( jdoc.isNull()  )
        return;

    udp->m_PeerIP = jdoc.object()["UDP_IP"].toString();
    udp->m_RxPort = jdoc.object()["UDP_RxPort"].toInt();
    udp->m_TxPort = jdoc.object()["UDP_TxPort"].toInt();

    serial->setPortName( jdoc.object()["Serial_PortName"].toString() );
    serial->setBaudRate( jdoc.object()["Serial_Baudrate"].toInt() );
    serial->setParity( (QSerialPort::Parity)jdoc.object()["Serial_Parity"].toInt() );
    serial->setStopBit( (QSerialPort::StopBits)jdoc.object()["Serial_StopBits"].toInt() );
    serial->setDataBits( (QSerialPort::DataBits)jdoc.object()["Serial_DataBits"].toInt() );
}

void Mng_Settings::ExportLinkConfigs( QString FileName, Serial_Info* serial, UDP_Info* udp )
{
    QFile file( FileName );
    if( !file.open( QIODevice::WriteOnly ) )
        return;

    QJsonParseError error;

    QJsonObject obj;
    obj.insert( "UDP_IP", udp->m_PeerIP );
    obj.insert( "UDP_RxPort", udp->m_RxPort );
    obj.insert( "UDP_TxPort", udp->m_TxPort );

    obj.insert( "Serial_PortName", serial->PortName() );
    obj.insert( "Serial_Baudrate", serial->BaudRate() );
    obj.insert( "Serial_Parity", (int)serial->Parity() );
    obj.insert( "Serial_StopBits", (int)serial->StopBit() );
    obj.insert( "Serial_DataBits", (int)serial->DataBits() );

    QJsonDocument jdoc( obj );

    file.write( jdoc.toJson() );
    file.close();
}

void Mng_Settings::SaveLinkConfigDefault( Serial_Info* serial, UDP_Info* udp )
{
    ExportLinkConfigs( "LinkConfigDefaults.vconf", serial, udp );
}

void Mng_Settings::LoadLinkConfigDefault( Serial_Info* serial, UDP_Info* udp )
{
    ImportLinkConfigs( "LinkConfigDefaults.vconf", serial, udp );
}
