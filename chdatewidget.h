#ifndef CHDATEWIDGET_H
#define CHDATEWIDGET_H

#include <QWidget>
#include <QDate>
#include <QStyle>

namespace Ui {
class ChDateWidget;
}

class ChDateWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ChDateWidget(QWidget *parent = 0);
    ~ChDateWidget();
    QDate begDate();
    QDate endDate();
    void setDate(QDate beg, QDate end);
    
private:
    Ui::ChDateWidget *ui;

private slots:
    void cmdUpdSlot();

signals:
    void sigUpd();
};

#endif // CHDATEWIDGET_H
