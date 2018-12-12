#ifndef SERIAL_NUMDELEGATE_H
#define SERIAL_NUMDELEGATE_H

#include <QWidget>
#include <QStyledItemDelegate>
class serial_numDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit serial_numDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex  &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
signals:

public slots:
};

#endif // SERIAL_NUMDELEGATE_H
