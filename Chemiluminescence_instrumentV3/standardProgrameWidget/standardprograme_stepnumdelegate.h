/**
  *  @brief    更改步骤号代理
  *  @file
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-10-17
  */
#ifndef STANDARDPROGRAME_STEPNUMDELEGATE_H
#define STANDARDPROGRAME_STEPNUMDELEGATE_H

#include <QWidget>
#include <QStyleOptionViewItem>
#include <QStyledItemDelegate>
class standardprograme_stepNumDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit standardprograme_stepNumDelegate(QWidget *parent = 0);
protected:
     void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
     void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
signals:

public slots:
};

#endif // STANDARDPROGRAME_STEPNUMDELEGATE_H
