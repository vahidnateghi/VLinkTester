#ifndef MNG_SYSTEM_H
#define MNG_SYSTEM_H

#include <QObject>
#include <VLink_Communication.h>
#include <QVector>

class Mng_System : public QObject
{
    Q_OBJECT
public:
    static Mng_System* Instance()
    {
        if( instance == NULL )
            instance = new Mng_System();
        return instance;
    }

    int UDPCommID() const;

    int SerialCommID() const;

    int UDPLinkID() const;
    void setUDPLinkID(int UDPLinkID);

    int SerialLinkID() const;
    void setSerialLinkID(int SerialLinkID);

private:
    explicit Mng_System(QObject *parent = nullptr);
    static Mng_System* instance;

    int m_UDPCommID;
    int m_UDPLinkID;


    int m_SerialCommID;
    int m_SerialLinkID;

signals:
    void SgNewBytes(ShrdPtrByteArray, Qt::GlobalColor);
    void SgUDPStarted();
    void SgUDPStopped();
    void SgSerialStarted();
    void SgSerialStopped();

};

#endif // MNG_SYSTEM_H
