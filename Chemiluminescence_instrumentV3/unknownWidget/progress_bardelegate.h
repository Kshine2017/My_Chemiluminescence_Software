#ifndef PROGRESS_BARDELEGATE_H
#define PROGRESS_BARDELEGATE_H

#include <QStyledItemDelegate>
#include <QProgressBar>
#include <QStyleOptionProgressBar>
#include <QApplication>
class progress_BarDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:

    explicit progress_BarDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex  &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;

};

#endif // PROGRESS_BARDELEGATE_H
