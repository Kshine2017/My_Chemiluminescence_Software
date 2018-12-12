/**
  *  @brief    自定义校准确定按钮代理
  *  @file     calibration_okbtndelegate.h
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-10-10
  */
#ifndef CALIBRATION_OKBTNDELEGATE_H
#define CALIBRATION_OKBTNDELEGATE_H
#include <QStyledItemDelegate>
#include <QPushButton>
/**
 * @brief 按钮代理
 */
class calibration_okBtnDelegate:public QStyledItemDelegate
{
public:
        Q_OBJECT

public:
    explicit calibration_okBtnDelegate(QObject *parent = 0);

private:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

public:

  QMap<int, QStyleOptionButton*> Display_btns;
signals:
    /// \brief 按钮点击信号
    ///
    /// \param QModelIndex   包含点击位置信息(表的行列)
    /// \return       void
    /// \see 无
    void btnClicked(const QModelIndex&);

};

#endif // CALIBRATION_OKBTNDELEGATE_H
