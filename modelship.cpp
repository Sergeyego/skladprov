#include "modelship.h"
#include <QMessageBox>

ModelShip::ModelShip(QObject *parent) :
    QSqlQueryModel(parent)
{
}

void ModelShip::refresh(QDate dbeg, QDate dend, int id_pol)
{
    setQuery("select s.id, s.nom_s, s.dat_vid, sum(m_netto) from wire_shipment_consist w "
             "inner join sertifikat s on s.id=w.id_ship "
             "where s.id_pol= "+QString::number(id_pol)+
             "and s.dat_vid between '"+dbeg.toString("yyyy.MM.dd")+"' and '"+dend.toString("yyyy.MM.dd")+
             "' group by s.id, s.nom_s, s.dat_vid "
             "order by s.dat_vid, s.nom_s");
    if (lastError().isValid()){
        QMessageBox::critical(NULL,"Error",lastError().text(),QMessageBox::Cancel);
    } else {
        setHeaderData(1, Qt::Horizontal,tr("Номер"));
        setHeaderData(2, Qt::Horizontal,tr("Дата"));
        setHeaderData(3, Qt::Horizontal,tr("Кг"));
        emit sigUpd();
    }
}

QVariant ModelShip::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    switch (role) {
     case Qt::DisplayRole: // Данные для отображения
        if(index.column() == 2) return value.toDate().toString("dd.MM.yy");
        if(index.column() == 3) return QString::number(value.toDouble(),0,2);
        break;
     case Qt::TextAlignmentRole: // Выравнивание
         if(index.column() == 3)
             return int(Qt::AlignRight | Qt::AlignVCenter);
         else return int(Qt::AlignLeft | Qt::AlignVCenter);
        break;
    }
    return value;
}


ModelViewShip::ModelViewShip(QObject *parent) :
    QSqlQueryModel(parent)
{
}

void ModelViewShip::refresh(QDate dbeg, QDate dend)
{
    setQuery("select s.id, s.nom_s, s.dat_vid, p.short, t.nam from sertifikat s "
             "inner join poluch p on s.id_pol=p.id "
             "inner join sert_type t on s.id_type=t.id "
             "inner join (select distinct id_ship from wire_shipment_consist) w on w.id_ship=s.id "
             "where s.dat_vid between '"+dbeg.toString("yyyy.MM.dd")+"' and '"+dend.toString("yyyy.MM.dd")+
             "' order by s.dat_vid, s.nom_s");
    if (lastError().isValid()){
        QMessageBox::critical(NULL,"Error",lastError().text(),QMessageBox::Cancel);
    } else {
        setHeaderData(1, Qt::Horizontal,tr("Номер"));
        setHeaderData(2, Qt::Horizontal,tr("Дата"));
        setHeaderData(3, Qt::Horizontal,tr("Получатель"));
        setHeaderData(4, Qt::Horizontal,tr("Тип отгрузки"));
        emit sigUpd();
    }
}

QVariant ModelViewShip::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    if (role==Qt::DisplayRole && index.column()==2){
        return value.toDate().toString("dd.MM.yy");
    } else {
        return value;
    }
}
