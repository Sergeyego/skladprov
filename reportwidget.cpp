#include "reportwidget.h"
#include "ui_reportwidget.h"

ReportWidget::ReportWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReportWidget)
{
    ui->setupUi(this);
    ui->cmd_save->setIcon(QIcon(QApplication::style()->standardIcon(QStyle::SP_DialogSaveButton)));
    chDate = new ChDateWidget(this);
    chDate->setDate(QDate::currentDate().addDays(-QDate::currentDate().day()+1),QDate::currentDate());
    ui->verticalLayout_Date->addWidget(chDate);
    modelReport = new ModelReport(this);
    ui->tableView->setModel(modelReport);
    connect(chDate,SIGNAL(sigUpd()),this,SLOT(updSlot()));
    connect(ui->cmd_save,SIGNAL(clicked()),this,SLOT(save()));
}

ReportWidget::~ReportWidget()
{
    delete ui;
}

void ReportWidget::updSlot()
{
   modelReport->refresh(chDate->begDate().addDays(-1),chDate->endDate());
   ui->tableView->resizeToContents();
}

void ReportWidget::save()
{
    QString tit=tr("Отчет по проволоке ООО СЗСМ с ")+chDate->begDate().toString("dd.MM.yyyy")+tr(" по ")+chDate->endDate().toString("dd.MM.yyyy");
    ui->tableView->save(tit,2,true,Qt::LandscapeOrientation);
}
