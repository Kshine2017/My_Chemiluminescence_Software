/**
  *  @brief    试剂前序混匀次数
  *  @file
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-10-17
  */
#ifndef STANDARDPROGRAME_BEFORECOUNTDELEGATE_H
#define STANDARDPROGRAME_BEFORECOUNTDELEGATE_H

#include <QStyledItemDelegate>
#include <QComboBox>
#include <QStyleOptionComboBox>

class standardPrograme_beforeCountDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit standardPrograme_beforeCountDelegate(QWidget *parent = 0);
protected:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex  &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;
signals:

public slots:
};

#endif // STANDARDPROGRAME_BEFORECOUNTDELEGATE_H
