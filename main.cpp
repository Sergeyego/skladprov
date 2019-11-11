#include <QApplication>
#include "mainwidget.h"
#include "db/dblogin.h"
#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication a( argc, argv );
    a.setWindowIcon(QIcon(":/images/icon.ico"));

    QPixmap logo(":/images/simb_labl.png");
    DbLogin d(QObject::tr("Склад проволоки"),logo);
    if (d.exec()!=QDialog::Accepted) exit(1);

    MainWidget w;
    w.show();

    return a.exec();
}
