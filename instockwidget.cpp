#include "instockwidget.h"
#include "ui_instockwidget.h"
#include <QtGui>

InStockWidget::InStockWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InStockWidget)
{
    ui->setupUi(this);
    ui->cmdPartUpd->setIcon(QIcon(QApplication::style()->standardIcon(QStyle::SP_BrowserReload)));

    ui->comboBoxFlt->addItem(tr("начиная с текущего года"));
    ui->comboBoxFlt->addItem(tr("начиная с прошлого года"));
    ui->comboBoxFlt->addItem(tr("за всё время"));
    ui->comboBoxFlt->setCurrentIndex(1);

    dateWidget = new ChDateWidget(this);
    ui->horizontalLayoutDate->insertWidget(0,dateWidget);

    QSqlQueryModel *typeModel = new QSqlQueryModel(this);
    typeModel->setQuery("select id, nam from wire_way_bill_type where (id=3 or id=4 or id=5 or id=7) order by id");
    if (typeModel->lastError().isValid()){
        QMessageBox::critical(this,"Error",typeModel->lastError().text(),QMessageBox::Ok);
    } else {
        ui->comboBoxType->setModel(typeModel);
        ui->comboBoxType->setModelColumn(1);
    }

    naklModel = new ModelNakl(this);
    ui->tableViewNakl->setModel(naklModel);
    ui->tableViewNakl->setColumnHidden(0,true);
    ui->tableViewNakl->setColumnWidth(1,80);
    ui->tableViewNakl->setColumnWidth(2,80);
    ui->tableViewNakl->setColumnHidden(3,true);
    ui->tableViewNakl->selectRow(0);

    naklMapper = new DbMapper(ui->tableViewNakl,this);
    ui->horizontalLayoutMap->insertWidget(0,naklMapper);
    naklMapper->addMapping(ui->lineEditNum,1);
    naklMapper->addMapping(ui->dateEdit,2);
    naklMapper->addEmptyLock(ui->tableViewNaklItem);
    naklMapper->addLock(dateWidget);
    naklMapper->addLock(ui->comboBoxType);
    naklMapper->addLock(ui->cmdPartUpd);
    naklMapper->addLock(ui->cmdNakl);

    naklItemModel=new ModelNaklItem(this);
    ui->tableViewNaklItem->setModel(naklItemModel);
    ui->tableViewNaklItem->setColumnHidden(0,true);
    ui->tableViewNaklItem->setColumnHidden(1,true);
    ui->tableViewNaklItem->setColumnWidth(2,490);
    ui->tableViewNaklItem->setColumnWidth(3,80);

    connect(naklMapper,SIGNAL(currentIndexChanged(int)),this,SLOT(updateNaklItem(int)));
    connect(ui->comboBoxType,SIGNAL(currentIndexChanged(int)),this,SLOT(updateNakl()));
    connect(ui->cmdPartUpd,SIGNAL(clicked()),naklItemModel,SLOT(refresh_part()));
    connect(dateWidget,SIGNAL(sigUpd()),this,SLOT(updateNakl()));
    connect(ui->comboBoxFlt,SIGNAL(currentIndexChanged(int)),this,SLOT(setFlt(int)));
    connect(ui->cmdNakl,SIGNAL(clicked(bool)),this,SLOT(printNakl()));

    updateNakl();
}

InStockWidget::~InStockWidget()
{
    delete ui;
}

void InStockWidget::updateNakl()
{
    int id_type=ui->comboBoxType->model()->data(ui->comboBoxType->model()->index(ui->comboBoxType->currentIndex(),0)).toInt();
    naklModel->refresh(id_type,dateWidget->begDate(),dateWidget->endDate());
}

void InStockWidget::updateNaklItem(int index)
{
    int id_nakl=naklModel->data(naklModel->index(index,0),Qt::EditRole).toInt();
    naklItemModel->refresh(id_nakl);
}

void InStockWidget::setFlt(int index)
{
    int year=QDate::currentDate().year();
    QString pattern=QString();
    if (index==0){
        pattern=QString::number(year);
    } else if (index==1){
        pattern=QString::number(year-1)+"|"+QString::number(year);
    }
    if (naklItemModel->relation(2)){
        naklItemModel->relation(2)->proxyModel()->setFilterRegExp(pattern);
    }
}

void InStockWidget::printNakl()
{
    int id_nakl=naklModel->data(naklModel->index(naklMapper->currentIndex(),0),Qt::EditRole).toInt();
    int id_type=naklModel->data(naklModel->index(naklMapper->currentIndex(),3),Qt::EditRole).toInt();
    QTcpSocket tcpSocket;
    tcpSocket.connectToHost("127.0.0.1", 5555);
    if (tcpSocket.waitForConnected()) {
        tcpSocket.write((QString("%1:%2:%3:%4").arg(1).arg(1).arg(id_nakl).arg(id_type)).toLocal8Bit().data());
        tcpSocket.waitForBytesWritten();
        tcpSocket.disconnectFromHost();
    } else {
        QMessageBox::critical(this,tr("Ошибка"),tcpSocket.errorString(),QMessageBox::Ok);
    }
}


