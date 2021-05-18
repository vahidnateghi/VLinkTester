#include "CompPack.h"
#include "ui_CompPack.h"
#include <iostream>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QChar>
#include <QFileDialog>

CompLinePack::CompLinePack(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CompLinePack)
{
    ui->setupUi(this);

    m_SendBytes = ShrdPtrByteArray(new QByteArray());

    m_SendTimer = new QTimer();
    connect( m_SendTimer, &QTimer::timeout, this, &CompLinePack::SltPuSendPack );
}

CompLinePack::~CompLinePack()
{
    delete ui;
}

void CompLinePack::GetData(QString &Text, Enum_PackSendType &SendType, bool &SendFile, QString &FilePath, bool &Timer, int &TimerInterval)
{
    Text = this->ui->txtSendText->text();

    if( this->ui->rdbDecimal->isChecked() ) SendType = SendType_Decimal;
    else if( this->ui->rdbHex->isChecked() ) SendType = SendType_Hex;
    else if( this->ui->rdbASCII->isChecked() ) SendType = SendType_ASCII;

    SendFile = this->ui->chbxFile->isChecked();

    FilePath = m_FileName;

    Timer = this->ui->chbxTimer->isChecked();

    TimerInterval = this->ui->numudInterval->value();
}

void CompLinePack::SetData(const QString& Text, const Enum_PackSendType &SendType, const bool &SendFile, const QString &FilePath, const bool &Timer, const int &TimerInterval)
{
    this->ui->txtSendText->setText( Text );

    if( SendType == SendType_Decimal ) this->ui->rdbDecimal->setChecked( true );
    else if( SendType == SendType_Hex ) this->ui->rdbHex->setChecked( true );
    else if( SendType == SendType_ASCII ) this->ui->rdbASCII->setChecked( true );

    this->ui->chbxFile->setChecked( SendFile );

    m_FileName = FilePath;
    this->ui->lblFileName->setText( m_FileName.split("/").last() );

    this->ui->chbxTimer->setChecked( Timer );

    this->ui->numudInterval->setValue( TimerInterval );
}

void CompLinePack::SltPuSendPack()
{
    std::cout << "SendBytes:" << std::endl;
    std::cout << "Count: " << m_SendBytes.data()->count() << std::endl;
    for( int i = 0; i < m_SendBytes.data()->size(); i++ )
        std::cout << (uint)m_SendBytes.data()->at(i) << ", ";
    std::cout << std::endl << "=============" << std::endl;

    emit SgSendBytes( m_SendBytes );
}

void CompLinePack::on_btnSend_clicked(bool checked)
{
    if( this->ui->chbxTimer->isChecked() && !checked )
    {
        m_SendTimer->stop();
        this->ui->btnSend->setText( "Send" );
        this->ui->chbxTimer->setEnabled( true );
        return;
    }

    if( this->ui->chbxTimer->isChecked() && checked )
    {
        this->ui->btnSend->setCheckable( true );
        this->ui->btnSend->setChecked( true );
        this->ui->btnSend->setText( "Stop" );
        this->ui->chbxTimer->setEnabled( false );

        PrepareSendPack();

        m_SendTimer->setInterval( this->ui->numudInterval->value() );
        m_SendTimer->start();
        return;
    }

    if( !this->ui->chbxTimer->isChecked() && checked )
    {
        PrepareSendPack();
        SltPuSendPack();
        this->ui->btnSend->setChecked( false );
        return;
    }
}

void CompLinePack::PrepareSendPack()
{
    QString SendText;
    if( this->ui->chbxFile->isChecked() )
    {
        QFile inFile(m_FileName);
        inFile.open( QIODevice::ReadOnly );
        SendText = QString( inFile.readAll() );
        inFile.close();
    }
    else
    {
        SendText = this->ui->txtSendText->text();
    }

    m_SendBytes.data()->clear();

    if( this->ui->rdbDecimal->isChecked() )
    {
        QStringList Values = SendText.split( " " );
        for( int i = 0; i < Values.size(); i++ )
        {
            bool ok;
            char tVal = (char)Values.at(i).toInt(&ok, 10);
            if( ok )
                m_SendBytes.data()->append( 1, tVal );
        }
    }
    else if( this->ui->rdbHex->isChecked() )
    {
        QStringList Values = SendText.split( " " );
        for( int i = 0; i < Values.size(); i++ )
        {
            bool ok;
            char tVal = (char)Values.at(i).toInt(&ok, 16);
            if( ok )
                m_SendBytes.data()->append( 1, tVal );
        }
    }
    else if( this->ui->rdbASCII->isChecked() )
    {
        for( int i = 0; i < SendText.size(); i++ )
        {
            m_SendBytes.data()->append( 1, SendText.at(i).toLatin1() );
        }
    }
}

void CompLinePack::on_btnFile_clicked()
{
    QString FilePath = QFileDialog::getOpenFileName( this, "Open Text File", "", "Text File (*.txt)" );
    if( !FilePath.isEmpty() )
    {
        this->ui->lblFileName->setText( FilePath.split("/").last() );
        m_FileName = FilePath;
    }
}
