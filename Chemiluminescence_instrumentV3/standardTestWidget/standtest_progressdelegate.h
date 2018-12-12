/**
  *  @brief    标准品测试tableView进度条
  *  @file     standtest_progressdelegate.h
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-10-12
  */
#ifndef STANDTEST_PROGRESSDELEGATE_H
#define STANDTEST_PROGRESSDELEGATE_H
#include <QStyledItemDelegate>

class standTest_ProgressDelegate:public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit standTest_ProgressDelegate(QObject *parent = 0);

protected:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex  &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;
signals:
    void OkBtnClicked(const QModelIndex &);
};

#endif // STANDTEST_PROGRESSDELEGATE_H
