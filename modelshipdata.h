#ifndef MODELSHIPDATA_H
#define MODELSHIPDATA_H

#include <QSqlQueryModel>
#include <QtSql>

class ModelShipData : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit ModelShipData(QObject *parent = 0);
    void refresh(int id_ship);
    QVariant data(const QModelIndex &index,int role = Qt::DisplayRole) const;
    
signals:
    void sigUpd();
    
public slots:
    
};

class ModelShipAllData : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit ModelShipAllData(QObject *parent = 0);
    void refresh(QDate dbeg, QDate dend, int id_pol);
    QVariant data(const QModelIndex &index,int role = Qt::DisplayRole) const;

signals:
    void sigUpd();

public slots:

};

#endif // MODELSHIPDATA_H
