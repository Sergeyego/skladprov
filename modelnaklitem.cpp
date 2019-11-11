#include "modelnaklitem.h"

ModelNaklItem::ModelNaklItem(QObject *parent) : DbTableModel("wire_warehouse",parent)
{
    partRelation = new DbRelation(new DbRelationalModel("select p.id, m.n_s||' '||cast(m.dat as varchar(96))||' '||pr.nam||' "+tr("ф")+"'||d.sdim||' '||k.short||' '||s.nam, date_part('year',m.dat) "
                                                        "from wire_parti as p "
                                                        "inner join wire_parti_m as m on p.id_m=m.id "
                                                        "inner join provol as pr on pr.id=m.id_provol "
                                                        "inner join diam as d on d.id=m.id_diam "
                                                        "inner join wire_pack_kind as k on p.id_pack=k.id "
                                                        "inner join wire_source as s on m.id_source=s.id "
                                                        "order by m.dat desc, m.n_s, pr.nam, d.sdim",this),0,1,this);
    int year=QDate::currentDate().year();
    partRelation->proxyModel()->setFilterKeyColumn(2);
    partRelation->proxyModel()->setFilterRegExp(QRegExp(QString::number(year-1)+"|"+QString::number(year)));

    addColumn("id",tr("id"),true,TYPE_INT);
    addColumn("id_waybill",tr("id_waybill"),false,TYPE_INT);
    addColumn("id_wparti",tr("Партия"),false,TYPE_STRING,NULL,partRelation);
    addColumn("m_netto",tr("Кол-во, кг"),false,TYPE_DOUBLE,new QDoubleValidator(-999999999,999999999,2,this));
    setSort("wire_warehouse.id");
}

void ModelNaklItem::refresh(int id_nakl)
{
    setFilter("wire_warehouse.id_waybill = "+QString::number(id_nakl));
    setDefaultValue(1,id_nakl);
    select();
}

bool ModelNaklItem::submitRow()
{
    bool ok=false;
    if (this->isEdt()){
        int id_nakl=this->data(this->index(currentEdtRow(),1),Qt::EditRole).toInt();
        int id_part=this->data(this->index(currentEdtRow(),2),Qt::EditRole).toInt();
        double kvo=this->data(this->index(currentEdtRow(),3),Qt::EditRole).toDouble();
        QSqlQuery query;
        query.prepare("select dat, id_type from wire_whs_waybill where id = :id_n");
        query.bindValue(":id_n",id_nakl);
        QDate date;
        int type;
        if (query.exec()){
            while (query.next()){
                date=query.value(0).toDate();
                type=query.value(1).toInt();
            }
        } else {
            QMessageBox::critical(NULL,"Error",query.lastError().text(),QMessageBox::Cancel);
        }
        if (type==5){
            query.clear();
            query.prepare("select st from wire_calc_stock(:date) where id_wparti = :id_part ");
            query.bindValue(":date",date);
            query.bindValue(":id_part",id_part);
            if (query.exec()){
                double m;
                while (query.next()){
                    m=query.value(0).toDouble();
                }
                if (kvo>0 && m>=kvo){
                    ok=DbTableModel::submitRow();
                } else {
                    QMessageBox::critical(NULL,tr("Ошибка"),tr("На складе на ")+date.toString("dd.MM.yy")+tr(" числится ")+
                                          QLocale().toString(m,'f',2)+tr(" кг проволоки этой партии. Масса передачи должна быть положительной и не больше, чем числится на складе."),QMessageBox::Cancel);
                }

            } else {
                QMessageBox::critical(NULL,"Error",query.lastError().text(),QMessageBox::Cancel);
            }
        } else {
            if (type==7 || kvo>0){
                ok=DbTableModel::submitRow();
            } else {
                QMessageBox::critical(NULL,tr("Ошибка"),tr("Масса должна быть больше нуля."),QMessageBox::Cancel);
            }
        }
    }
    return ok;
}

void ModelNaklItem::refresh_part()
{
    partRelation->model()->refresh();
}
