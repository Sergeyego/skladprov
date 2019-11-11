#ifndef REPORTWIDGET_H
#define REPORTWIDGET_H

#include <QWidget>
#include "chdatewidget.h"
#include "modelpresence.h"

namespace Ui {
class ReportWidget;
}

class ReportWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ReportWidget(QWidget *parent = 0);
    ~ReportWidget();
    
private:
    Ui::ReportWidget *ui;
    ChDateWidget *chDate;
    ModelReport *modelReport;

private slots:
    void updSlot();
    void save();
};

#endif // REPORTWIDGET_H
