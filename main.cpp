#include "VLinkTester.h"
#include <QApplication>
#include <QStyleFactory>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VLink_Tester w;
    w.show();

    QApplication::setStyle( "Fusion" );

    qDebug() << QStyleFactory::keys();

    return a.exec();
}
