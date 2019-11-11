#ifndef MODELNAKL_H
#define MODELNAKL_H

#include "db/dbtablemodel.h"

class ModelNakl : public DbTableModel
{
    Q_OBJECT

public:
    explicit ModelNakl(QObject *parent = 0);
    void refresh(int id_type, QDate begDate, QDate endDate);
    bool insertRow(int row, const QModelIndex &parent=QModelIndex());

private:
    int type;
};

#endif // MODELNAKL_H
