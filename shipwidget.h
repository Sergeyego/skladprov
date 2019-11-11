#ifndef SHIPWIDGET_H
#define SHIPWIDGET_H

#include <QWidget>
#include "chdatewidget.h"
#include "modelship.h"
#include "modelshipdata.h"

namespace Ui {
class ShipWidget;
}

class ShipWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ShipWidget(QWidget *parent = 0);
    ~ShipWidget();
    
private:
    Ui::ShipWidget *ui;
    ChDateWidget * chDate;
    ModelViewShip *modelShip;
    ModelShipData *modelShipData;
private slots:
    void updSlot();
    void updShipData();
};

#endif // SHIPWIDGET_H
