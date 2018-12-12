/**
  *  @brief    试剂船动作选择代理
  *  @file
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-10-17
  */
#ifndef STANDARDPROGRAME_ACTIONCHECKDELEGATE_H
#define STANDARDPROGRAME_ACTIONCHECKDELEGATE_H
#include <QStyledItemDelegate>
#include <QComboBox>
#include <QStyleOptionComboBox>
class standardprograme_actionCheckDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit standardprograme_actionCheckDelegate(QWidget *parent = 0);

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

#endif // STANDARDPROGRAME_ACTIONCHECKDELEGATE_H
