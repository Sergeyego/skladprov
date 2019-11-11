#include "chdatewidget.h"
#include "ui_chdatewidget.h"
#include <QCalendarWidget>

ChDateWidget::ChDateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChDateWidget)
{
    ui->setupUi(this);
    ui->cmd_upd->setIcon(QIcon(QApplication::style()->standardIcon(QStyle::SP_BrowserReload)));
    QCalendarWidget *begCalendarWidget = new QCalendarWidget(this);
    begCalendarWidget->setFirstDayOfWeek(Qt::Monday);
    ui->dateEdit_beg->setCalendarWidget(begCalendarWidget);
    QDate date;
    date.setDate(QDate::currentDate().year(),1,1);
    ui->dateEdit_beg->setDate(date);
    QCalendarWidget *endCalendarWidget = new QCalendarWidget(this);
    endCalendarWidget->setFirstDayOfWeek(Qt::Monday);
    ui->dateEdit_end->setCalendarWidget(endCalendarWidget);
    ui->dateEdit_end->setDate(QDate::currentDate());
    connect(ui->cmd_upd,SIGNAL(clicked()),this,SLOT(cmdUpdSlot()));
}

ChDateWidget::~ChDateWidget()
{
    delete ui;
}

QDate ChDateWidget::begDate()
{
    return ui->dateEdit_beg->date();
}

QDate ChDateWidget::endDate()
{
    return ui->dateEdit_end->date();
}

void ChDateWidget::setDate(QDate beg, QDate end)
{
    ui->dateEdit_beg->setDate(beg);
    ui->dateEdit_end->setDate(end);
}

void ChDateWidget::cmdUpdSlot()
{
    emit sigUpd();
}
