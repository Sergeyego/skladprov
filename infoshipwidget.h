#ifndef INFOSHIPWIDGET_H
#define INFOSHIPWIDGET_H

#include <QWidget>
#include <QtSql>
#include "modelship.h"
#include "modelshipdata.h"
#include "chdatewidget.h"

namespace Ui {
class InfoShipWidget;
}

class InfoShipWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit InfoShipWidget(QWidget *parent = 0);
    ~InfoShipWidget();
    
private:
    Ui::InfoShipWidget *ui;
    ChDateWidget *chDate;
    QSqlQueryModel *poluchModel;
    ModelShip *shipModel;
    ModelShipData *shipDataModel;
    ModelShipAllData *shipAllDataModel;

private slots:
    void updShip();
    void updShipData();
};

#endif // INFOSHIPWIDGET_H
