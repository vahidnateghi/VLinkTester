#ifndef MNG_SETTINGS_H
#define MNG_SETTINGS_H

#include <QObject>
#include <QJsonDocument>
#include <VLink_Infos/Serial_Info.h>
#include <VLink_Infos/UDP_Info.h>
#include <Components/CompPack.h>

class Mng_Settings : public QObject
{
    Q_OBJECT
public:
    static Mng_Settings* Instance()
    {
        if( instance == NULL )
            instance = new Mng_Settings();
        return instance;
    }
    void ImportPacks(QString FileName, QList<CompLinePack*> packComps);
    void ExportPacks(QString FileName, const QList<CompLinePack *> packComps );
    void SavePacksDefault(const QList<CompLinePack *> packComps);
    void LoadPackDefault(QList<CompLinePack *> packComps);


    void ImportLinkConfigs(QString FileName, Serial_Info *serial, UDP_Info *udp);
    void ExportLinkConfigs(QString FileName, Serial_Info *serial, UDP_Info *udp);
    void SaveLinkConfigDefault(Serial_Info *serial, UDP_Info *udp );
    void LoadLinkConfigDefault(Serial_Info *serial, UDP_Info *udp);

private:
    static Mng_Settings* instance;
    explicit Mng_Settings(QObject *parent = nullptr);
};

#endif // MNG_SETTINGS_H
