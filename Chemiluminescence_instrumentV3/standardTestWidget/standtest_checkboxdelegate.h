#ifndef STANDTEST_CHECKBOXDELEGATE_H
#define STANDTEST_CHECKBOXDELEGATE_H

#include <QStyledItemDelegate>
class standtest_checkBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit standtest_checkBoxDelegate(QObject *parent = 0);

protected:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex  &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;
private:
    QMap< QModelIndex, QStyleOptionButton*> CheckBox;
};

#endif // STANDTEST_CHECKBOXDELEGATE_H
