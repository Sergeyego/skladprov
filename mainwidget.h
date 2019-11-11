#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "olap/cubewidget.h"

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

private slots:
};

#endif // MAINWIDGET_H
