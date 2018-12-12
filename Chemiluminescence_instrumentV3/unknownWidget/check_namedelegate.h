#ifndef CHECK_NAMEDELEGATE_H
#define CHECK_NAMEDELEGATE_H

#include <QWidget>
#include <QStyledItemDelegate>
#include <QLabel>
class check_nameDelegate :public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit check_nameDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent,const QStyleOptionViewItem &/*option*/,const QModelIndex &/*index*/) const;
    void setEditorData(QWidget *editor,const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const;

signals:

public slots:
};

#endif // CHECK_NAMEDELEGATE_H
