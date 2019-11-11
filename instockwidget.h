#ifndef INSTOCKWIDGET_H
#define INSTOCKWIDGET_H

#include <QWidget>
#include "modelnakl.h"
#include "modelnaklitem.h"
//#include "cbrelationdelegate.h"
#include "chdatewidget.h"
#include "db/dbmapper.h"
#include <QTcpSocket>

namespace Ui {
class InStockWidget;
}

class InStockWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit InStockWidget(QWidget *parent = 0);
    ~InStockWidget();
    
private:
    Ui::InStockWidget *ui;
    ModelNakl *naklModel;
    ModelNaklItem *naklItemModel;
    ChDateWidget *dateWidget;
    DbMapper *naklMapper;

private slots:
    void updateNakl();    
    void updateNaklItem(int index);
    void setFlt(int index);
    void printNakl();
};

#endif // INSTOCKWIDGET_H
