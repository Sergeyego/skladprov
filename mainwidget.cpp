#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    instock = new InStockWidget();
    presence = new PresenceWidget();
    infoShip = new InfoShipWidget();
    pStock = new CubeWidget(21);
    pShip = new CubeWidget(22);
    reportWidget = new ReportWidget();
    shipWidget = new ShipWidget();

    connect(ui->cmd_in_stock,SIGNAL(clicked()),instock,SLOT(show()));
    connect(ui->cmd_presence,SIGNAL(clicked()),presence,SLOT(show()));
    connect(ui->cmd_infoShip,SIGNAL(clicked()),infoShip,SLOT(show()));
    connect(ui->cmd_AnStock,SIGNAL(clicked()),pStock,SLOT(show()));
    connect(ui->cmd_AnShip,SIGNAL(clicked()),pShip,SLOT(show()));
    connect(ui->cmd_Report,SIGNAL(clicked()),reportWidget,SLOT(show()));
    connect(ui->cmd_Ship,SIGNAL(clicked()),shipWidget,SLOT(show()));
}

MainWidget::~MainWidget()
{
    delete instock;
    delete presence;
    delete infoShip;
    delete pStock;
    delete pShip;
    delete reportWidget;
    delete shipWidget;

    delete ui;
}
