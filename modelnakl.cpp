#include "modelnakl.h"

ModelNakl::ModelNakl(QObject *parent) :
    DbTableModel("wire_whs_waybill",parent)
{
    addColumn("id",tr("id"),true,TYPE_INT);
    addColumn("num",tr("Номер"),false,TYPE_STRING);
    addColumn("dat",tr("Дата"),false,TYPE_DATE);
    addColumn("id_type",tr("id_type"),false,TYPE_INT);
    setSort("dat, num");
}

void ModelNakl::refresh(int id_type, QDate begDate, QDate endDate)
{
    setFilter("wire_whs_waybill.dat between '"+begDate.toString("yyyy.MM.dd")+"' and '"+
              endDate.toString("yyyy.MM.dd")+
              "' and wire_whs_waybill.id_type= "+QString::number(id_type));
    type=id_type;
    setDefaultValue(3,type);
    select();
}

bool ModelNakl::insertRow(int row, const QModelIndex &parent)
{
    bool b = DbTableModel::insertRow(row,parent);
    if (b && rowCount()>1){
        int n_s = data(index(rowCount()-2,1)).toInt();
        n_s++;
        setData(index(rowCount()-1,1),QString("%1").arg(n_s,4,'d',0,QChar('0')),Qt::EditRole);
    }
    return b;
}

