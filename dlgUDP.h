#ifndef DLGUDP_H
#define DLGUDP_H

#include <QDialog>

namespace Ui {
class dlgUDP;
}

class dlgUDP : public QDialog
{
    Q_OBJECT

public:
    explicit dlgUDP(QWidget *parent = nullptr);
    ~dlgUDP();

    void SetConfig( QString IP, int TxPort, int RxPort );

private slots:
    void on_buttonBox_accepted();


private:
    Ui::dlgUDP *ui;
};

#endif // DLGUDP_H
