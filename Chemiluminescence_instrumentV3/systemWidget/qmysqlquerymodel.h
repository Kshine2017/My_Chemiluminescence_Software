#ifndef QMYSQLQUERYMODEL_H
#define QMYSQLQUERYMODEL_H
#include<QSqlQueryModel>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class QMySQlQueryModel : public QSqlQueryModel
{
public:
    explicit  QMySQlQueryModel();
public:
    QVariant data(const QModelIndex &index, int role) const;

};

#endif // QMYSQLQUERYMODEL_H
