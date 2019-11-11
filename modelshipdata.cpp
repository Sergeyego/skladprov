#include "modelshipdata.h"
#include <QMessageBox>

ModelShipData::ModelShipData(QObject *parent) :
    QSqlQueryModel(parent)
{
}

void ModelShipData::refresh(int id_ship)
{
    setQuery("select w.id, pr.nam, d.sdim, k.nam, m.n_s, w.m_netto "
             "from wire_shipment_consist w "
             "inner join wire_parti p on p.id=w.id_wparti "
             "inner join wire_parti_m as m on p.id_m=m.id "
             "inner join provol pr on pr.id=m.id_provol "
             "inner join diam d on d.id=m.id_diam "
             "inner join wire_pack_kind k on p.id_pack=k.id "
             "where w.id_ship= "+QString::number(id_ship)+
             " order by pr.nam, d.sdim, k.nam, p.n_s");
    if (lastError().isValid()){
        QMessageBox::critical(NULL,"Error",lastError().text(),QMessageBox::Cancel);
    } else {
        setHeaderData(1, Qt::Horizontal,tr("Марка"));
        setHeaderData(2, Qt::Horizontal,tr("Ф"));
        setHeaderData(3, Qt::Horizontal,tr("Катушка"));
        setHeaderData(4, Qt::Horizontal,tr("Партия"));
        setHeaderData(5, Qt::Horizontal,tr("Кг"));
        emit sigUpd();
    }
}

QVariant ModelShipData::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    switch (role) {
     case Qt::DisplayRole: // Данные для отображения
        if(index.column() == 5) return QString::number(value.toDouble(),0,2);
            else
                return value;

     case Qt::EditRole:    // Данные для редактирования
         return value;

     case Qt::TextAlignmentRole: // Выравнивание
         if(index.column() == 5)
             return int(Qt::AlignRight | Qt::AlignVCenter);
         else return int(Qt::AlignLeft | Qt::AlignVCenter);

    }
    return value;
}


ModelShipAllData::ModelShipAllData(QObject *parent) :
    QSqlQueryModel(parent)
{
}

void ModelShipAllData::refresh(QDate dbeg, QDate dend, int id_pol)
{
    setQuery("select s.id, pr.nam, d.sdim, k.nam, w.m_netto "
             "from sertifikat s "
             "inner join wire_shipment_consist w on w.id_ship=s.id "
             "inner join wire_parti p on p.id=w.id_wparti "
             "inner join wire_parti_m as m on p.id_m=m.id "
             "inner join provol pr on pr.id=m.id_provol "
             "inner join diam d on d.id=m.id_diam "
             "inner join wire_pack_kind k on p.id_pack=k.id "
             "where s.id_pol= "+QString::number(id_pol)+
             "and s.dat_vid between '"+dbeg.toString("yyyy.MM.dd")+"' and '"+dend.toString("yyyy.MM.dd")+
             "' order by pr.nam, d.sdim, k.nam, p.n_s");
    if (lastError().isValid()){
        QMessageBox::critical(NULL,"Error",lastError().text(),QMessageBox::Cancel);
    } else {
        setHeaderData(1, Qt::Horizontal,tr("Марка"));
        setHeaderData(2, Qt::Horizontal,tr("Ф"));
        setHeaderData(3, Qt::Horizontal,tr("Катушка"));
        setHeaderData(4, Qt::Horizontal,tr("Кг"));
        emit sigUpd();
    }
}

QVariant ModelShipAllData::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    switch (role) {
     case Qt::DisplayRole: // Данные для отображения
        if(index.column() == 4) return QString::number(value.toDouble(),0,2);
            else
                return value;

     case Qt::EditRole:    // Данные для редактирования
         return value;

     case Qt::TextAlignmentRole: // Выравнивание
         if(index.column() == 4)
             return int(Qt::AlignRight | Qt::AlignVCenter);
         else return int(Qt::AlignLeft | Qt::AlignVCenter);

    }
    return value;
}
