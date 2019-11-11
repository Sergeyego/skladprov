#ifndef MODELNAKLITEM_H
#define MODELNAKLITEM_H
#include "db/dbtablemodel.h"

class ModelNaklItem : public DbTableModel
{
    Q_OBJECT
public:
    ModelNaklItem(QObject *parent = 0);
    void refresh(int id_nakl);
    bool submitRow();
private:
    DbRelation *partRelation;
public slots:
    void refresh_part();
};

#endif // MODELNAKLITEM_H
