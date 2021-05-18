#ifndef VLINK_TESTER_H
#define VLINK_TESTER_H

#include <QMainWindow>
#include <VLink_Defines.h>
#include "defines.h"
#include "dlgUDP.h"
#include "dlgSerial.h"
#include <QLabel>
#include <Components/CompPack.h>

namespace Ui {
class VLinkTester;
}

class VLink_Tester : public QMainWindow
{
    Q_OBJECT

public:
    explicit VLink_Tester(QWidget *parent = nullptr);
    ~VLink_Tester();

private:
    Ui::VLinkTester *ui;

    dlgUDP* m_dlgUDP;
    dlgSerial * m_dlgSerial;
    QLabel* m_StatusLabel;

    QList<CompLinePack*> GetPackPointers();

private slots:
    void SltPrSendBytes(ShrdPtrByteArray Sent);
    void SltPrReceivedBytes(ShrdPtrByteArray Received, Qt::GlobalColor color);
    void on_actionUDP_triggered();
    void on_actionSerial_triggered();
    void on_actionUDPStart_triggered(bool checked);
    void on_actionSerialStart_triggered(bool checked);
    void on_actionExit_triggered();
    void on_actionExport_Packs_triggered();
    void on_actionImport_Packs_triggered();
    void on_actionExport_Link_Configs_triggered();
    void on_actionImport_Link_Configs_triggered();
    void on_actionSave_Packs_as_Default_triggered();
    void on_actionSave_Link_Configs_as_Default_triggered();
};

#endif // VLINK_TESTER_H
