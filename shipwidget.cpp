#include "shipwidget.h"
#include "ui_shipwidget.h"

ShipWidget::ShipWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShipWidget)
{
    ui->setupUi(this);
    chDate = new ChDateWidget(this);
    ui->verticalLayout_Date->addWidget(chDate);
    modelShip = new ModelViewShip(this);
    modelShipData = new ModelShipData(this);
    updSlot();
    ui->tableView_Ship->setModel(modelShip);
    ui->tableView_Ship->setColumnHidden(0,true);
    ui->tableView_Ship->setColumnWidth(1,70);
    ui->tableView_Ship->setColumnWidth(2,70);
    ui->tableView_Ship->setColumnWidth(3,200);
    ui->tableView_Ship->resizeRowsToContents();
    updShipData();
    ui->tableView_ShipData->setModel(modelShipData);
    ui->tableView_ShipData->setColumnHidden(0,true);
    ui->tableView_ShipData->setColumnWidth(1,110);
    ui->tableView_ShipData->setColumnWidth(2,30);
    ui->tableView_ShipData->setColumnWidth(3,110);
    ui->tableView_ShipData->setColumnWidth(4,55);
    ui->tableView_ShipData->setColumnWidth(5,70);

    connect(chDate,SIGNAL(sigUpd()),this,SLOT(updSlot()));
    connect(ui->tableView_Ship->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(updShipData()));
}

ShipWidget::~ShipWidget()
{
    delete ui;
}

void ShipWidget::updSlot()
{
    modelShip->refresh(chDate->begDate(),chDate->endDate());
    ui->tableView_Ship->resizeToContents();
}

void ShipWidget::updShipData()
{
    int id_ship= modelShip->data(modelShip->index(ui->tableView_Ship->currentIndex().row(),0)).toInt();
    modelShipData->refresh(id_ship);
    ui->tableView_ShipData->resizeToContents();
}
