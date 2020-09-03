#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "olap/cubewidget.h"
#include "instockwidget.h"
#include "presencewidget.h"
#include "infoshipwidget.h"
#include "reportwidget.h"
#include "shipwidget.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    
private:
    Ui::MainWidget *ui;
    InStockWidget *instock;
    PresenceWidget *presence;
    InfoShipWidget *infoShip;
    CubeWidget *pStock;
    CubeWidget *pShip;
    ReportWidget *reportWidget;
    ShipWidget *shipWidget;

private slots:
};

#endif // MAINWIDGET_H
