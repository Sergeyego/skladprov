#ifndef MODELSHIP_H
#define MODELSHIP_H

#include <QSqlQueryModel>
#include <QtSql>

class ModelShip : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit ModelShip(QObject *parent = 0);
    void refresh(QDate dbeg, QDate dend, int id_pol);
    QVariant data(const QModelIndex &index,int role = Qt::DisplayRole) const;
    
signals:
    void sigUpd();
    
public slots:
    
};

class ModelViewShip : public QSqlQueryModel
{
    Q_OBJECT
public:
    ModelViewShip(QObject *parent = 0);
    void refresh(QDate dbeg, QDate dend);
    QVariant data(const QModelIndex &index,int role = Qt::DisplayRole) const;
signals:
    void sigUpd();
};

#endif // MODELSHIP_H
