#include "qmysqlquerymodel.h"
/**
 * @brief QMySQlQueryModel::QMySQlQueryModel
 * 重写data方法让文本居中---tableView
 */
QMySQlQueryModel::QMySQlQueryModel()
{

}

QVariant QMySQlQueryModel::data(const QModelIndex &item, int role) const
{
    QVariant value = QSqlQueryModel::data(item, role);
    if(role ==  Qt::TextAlignmentRole )
    {
        value   =   (Qt::AlignCenter);
        return value;
    }
    return value;
}
