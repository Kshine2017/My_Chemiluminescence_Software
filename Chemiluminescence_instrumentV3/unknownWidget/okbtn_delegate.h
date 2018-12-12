#ifndef OKBTN_DELEGATE_H
#define OKBTN_DELEGATE_H
#include <QStyledItemDelegate>
#include <QPushButton>
#include <QIcon>
#include <QPalette>
#include <QFont>
#include <QEvent>
#include <QStyleOptionButton>
class okbtn_Delegate : public QStyledItemDelegate
{
    Q_OBJECT
  public:
    explicit  okbtn_Delegate(QObject *parent = 0 );

  private:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

 public:
    QMap<int, QStyleOptionButton*> OK_btns;

  signals:
    /// \brief 按钮点击信号
    ///
    /// \param QModelIndex   包含点击位置信息(表的行列)
    /// \return       void
    /// \see 无
    void OkBtnClicked(const QModelIndex &);
};
#endif // OKBTN_DELEGATE_H
