#ifndef COMPLINEPACK_H
#define COMPLINEPACK_H

#include <QWidget>
#include <QTimer>
#include "defines.h"
#include <VLink_Defines.h>
#include "defines.h"

namespace Ui {
class CompLinePack;
}

class CompLinePack : public QWidget
{
    Q_OBJECT

private:
    Ui::CompLinePack *ui;

    QTimer* m_SendTimer;
    QString m_FileName;
    ShrdPtrByteArray m_SendBytes;

    void PrepareSendPack();

public:
    explicit CompLinePack(QWidget *parent = nullptr);
    ~CompLinePack();

    void GetData(QString& Text, Enum_PackSendType &SendType, bool &SendFile, QString &FilePath, bool &Timer, int &TimerInterval );
    void SetData(const QString &Text, const Enum_PackSendType &SendType, const bool &SendFile, const QString &FilePath, const bool &Timer, const int &TimerInterval );

public slots:
    void SltPuSendPack();

private slots:
    void on_btnSend_clicked(bool checked);

    void on_btnFile_clicked();

signals:
    void SgSendBytes(ShrdPtrByteArray);
};

#endif // COMPLINEPACK_H
