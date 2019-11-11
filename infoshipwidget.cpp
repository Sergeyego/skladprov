#include "infoshipwidget.h"
#include "ui_infoshipwidget.h"
#include <QMessageBox>

InfoShipWidget::InfoShipWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoShipWidget)
{
    ui->setupUi(this);

    chDate = new ChDateWidget(this);
    ui->verticalLayout_Date->addWidget(chDate);

    poluchModel = new QSqlQueryModel(this);
    poluchModel->setQuery("select id, short from poluch order by short");
    if (poluchModel->lastError().isValid()){
        QMessageBox::critical(this,"Error",poluchModel->lastError().text(),QMessageBox::Ok);
    }

    ui->listViewPoluch->setModel(poluchModel);
    ui->listViewPoluch->setModelColumn(1);
    ui->listViewPoluch->setCurrentIndex(ui->listViewPoluch->model()->index(0,1));

    shipModel = new ModelShip(this);
    shipAllDataModel = new ModelShipAllData(this);
    shipDataModel = new ModelShipData(this);
    updShip();

    ui->tableViewTotalChip->setModel(shipAllDataModel);
    ui->tableViewTotalChip->setColumnHidden(0,true);
    ui->tableViewTotalChip->setColumnWidth(1,120);
    ui->tableViewTotalChip->setColumnWidth(2,35);
    ui->tableViewTotalChip->setColumnWidth(3,110);
    ui->tableViewTotalChip->setColumnWidth(4,70);

    ui->tableViewShip->setModel(shipModel);
    ui->tableViewShip->setColumnHidden(0,true);
    ui->tableViewShip->setColumnWidth(1,80);
    ui->tableViewShip->setColumnWidth(2,80);
    ui->tableViewShip->setColumnWidth(3,80);

    updShipData();
    ui->tableViewDataShip->setModel(shipDataModel);
    ui->tableViewDataShip->setColumnHidden(0,true);
    ui->tableViewDataShip->setColumnWidth(1,110);
    ui->tableViewDataShip->setColumnWidth(2,30);
    ui->tableViewDataShip->setColumnWidth(3,110);
    ui->tableViewDataShip->setColumnWidth(4,55);
    ui->tableViewDataShip->setColumnWidth(5,70);

    connect(chDate,SIGNAL(sigUpd()),this,SLOT(updShip()));
    connect(ui->listViewPoluch->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(updShip()));
    connect(ui->tableViewShip->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(updShipData()));
}

InfoShipWidget::~InfoShipWidget()
{
    delete ui;
}

void InfoShipWidget::updShip()
{
    int id_pol= poluchModel->data(poluchModel->index(ui->listViewPoluch->currentIndex().row(),0)).toInt();
    shipModel->refresh(chDate->begDate(),chDate->endDate(),id_pol);
    shipAllDataModel->refresh(chDate->begDate(),chDate->endDate(),id_pol);
    ui->tableViewShip->resizeToContents();
    ui->tableViewTotalChip->resizeToContents();
    updShipData();
}

void InfoShipWidget::updShipData()
{
    int id_ship= shipModel->data(shipModel->index(ui->tableViewShip->currentIndex().row(),0)).toInt();
    shipDataModel->refresh(id_ship);
    ui->tableViewDataShip->resizeToContents();
}

