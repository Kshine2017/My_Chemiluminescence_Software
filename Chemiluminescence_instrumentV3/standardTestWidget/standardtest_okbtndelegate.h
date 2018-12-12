/**
  *  @brief    标准品测试tableView进度条
  *  @file     standtest_progressdelegate.h
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-10-12
  */
#ifndef STANDARDTEXT_OKBTNDELEGATE_H
#define STANDARDTEXT_OKBTNDELEGATE_H
#include <QStyledItemDelegate>

class standardText_okBtnDelegate:public QStyledItemDelegate
{
public:
        Q_OBJECT
public:
    explicit standardText_okBtnDelegate(QObject *parent = 0);

protected:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

public:
    QMap<int, QStyleOptionButton*> okBtn_btns;

signals:
    /// \brief 按钮点击信号
    /// \param QModelIndex   包含点击位置信息(表的行列)
    /// \return       void
    /// \see 无
    void OkBtnClicked(const QModelIndex& );
};

#endif // STANDARDTEXT_OKBTNDELEGATE_H
