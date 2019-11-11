#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "instockwidget.h"
#include "presencewidget.h"
#include "infoshipwidget.h"
#include "reportwidget.h"
#include "shipwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    InStockWidget *instock = new InStockWidget(NULL);
    PresenceWidget *presence = new PresenceWidget(NULL);
    InfoShipWidget *infoShip = new InfoShipWidget(NULL);
    QStringList axesStock;
    axesStock.push_back(tr("Источник"));
    axesStock.push_back(tr("Тип поступления"));
    axesStock.push_back(tr("Марка"));
    axesStock.push_back(tr("Диаметр"));
    axesStock.push_back(tr("Катушка"));
    axesStock.push_back(tr("Партия"));
    axesStock.push_back(tr("Год"));
    axesStock.push_back(tr("Месяц"));
    axesStock.push_back(tr("День"));
    QString queryStock="select s.nam, wt.nam, pr.nam, d.sdim, k.short, m.n_s||'-'||date_part('year',m.dat), "
            "substr(cast(wb.dat as char(32)),1,4) as yr, "
            "substr(cast(wb.dat as char(32)),1,7) as mn, "
            "substr(cast(wb.dat as char(32)),1,10) as dy, w.m_netto "
            "from wire_warehouse w "
            "inner join wire_whs_waybill wb on w.id_waybill=wb.id "
            "inner join wire_way_bill_type wt on wt.id=wb.id_type "
            "inner join wire_parti p on w.id_wparti=p.id "
            "inner join wire_parti_m m on p.id_m=m.id "
            "inner join provol pr on pr.id=m.id_provol "
            "inner join diam d on d.id=m.id_diam "
            "inner join wire_pack_kind k on p.id_pack=k.id "
            "inner join wire_source s on m.id_source=s.id "
            "where wb.dat between :d1 and :d2 and wt.koef=1 ";
    CubeWidget *pStock = new CubeWidget(tr("Поступление проволоки на склад"),axesStock,queryStock,2);

    QStringList axesShip;
    axesShip.push_back(tr("Марка"));
    axesShip.push_back(tr("Диаметр"));
    axesShip.push_back(tr("Катушка"));
    axesShip.push_back(tr("Партия"));
    axesShip.push_back(tr("Категория"));
    axesShip.push_back(tr("Получатель"));
    axesShip.push_back(tr("Год"));
    axesShip.push_back(tr("Месяц"));
    axesShip.push_back(tr("День"));

    QString queryShip="select pr.nam, d.sdim, k.short, m.n_s||'-'||date_part('year',m.dat), pk.nam, pl.short, "
            "substr(cast(o.dat_vid as char(32)),1,4) as yr, "
            "substr(cast(o.dat_vid as char(32)),1,7) as mn, "
            "substr(cast(o.dat_vid as char(32)),1,10) as dy, w.m_netto "
            "from wire_shipment_consist w "
            "inner join sertifikat o on w.id_ship=o.id "
            "inner join wire_parti p on w.id_wparti=p.id "
            "inner join wire_parti_m m on p.id_m=m.id "
            "inner join provol pr on pr.id=m.id_provol "
            "inner join diam d on d.id=m.id_diam "
            "inner join wire_pack_kind k on p.id_pack=k.id "
            "inner join wire_source s on m.id_source=s.id "
            "inner join poluch pl on o.id_pol=pl.id "
            "inner join pol_kat pk on pl.id_kat=pk.id "
            "where o.dat_vid between :d1 and :d2";

    CubeWidget *pShip = new CubeWidget(tr("Отгрузка проволоки"),axesShip,queryShip,2);

    ReportWidget *reportWidget = new ReportWidget(NULL);
    ShipWidget *shipWidget = new ShipWidget(NULL);

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
    delete ui;
}
