/**
  *  @brief    开始位置选择代理
  *  @file
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-10-17
  */
#ifndef STANDARDPROGRAME_STARTPOSTIONDELEGATE_H
#define STANDARDPROGRAME_STARTPOSTIONDELEGATE_H

#include <QStyledItemDelegate>
#include <QComboBox>
#include <QStyleOptionComboBox>

class standardPrograme_startPostionDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit standardPrograme_startPostionDelegate(QWidget *parent = 0);
protected:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex  &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

private:
     QMap<QModelIndex, QStyleOptionButton*> Btns;
signals:

    /// \brief 按钮点击信号
    ///
    /// \param QModelIndex   包含点击位置信息(表的行列)
    /// \return       void
    /// \see 无
    void stepRnBtnClicked(const QModelIndex&);

public slots:
};

#endif // STANDARDPROGRAME_STARTPOSTIONDELEGATE_H
