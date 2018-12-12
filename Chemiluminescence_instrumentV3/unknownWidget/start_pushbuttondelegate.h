#ifndef START_PUSHBUTTONDELEGATE_H
#define START_PUSHBUTTONDELEGATE_H

#include <QStyledItemDelegate>
#include <QPushButton>
#include <QIcon>
#include <QPalette>
#include <QFont>
#include <QEvent>
#include <QStyleOptionButton>
class start_PushButtonDelegate : public QStyledItemDelegate
{
    Q_OBJECT
  public:
    explicit start_PushButtonDelegate(QObject *parent = 0 );
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

  public:
    QMap<int, QStyleOptionButton*> m_btns; //储存按钮状态


public slots:

signals:
  /// \brief 按钮点击信号
  ///
  /// \param QModelIndex   包含点击位置信息(表的行列)
  /// \return       void
  /// \see 无
  void startBtnClicked(const QModelIndex &);
};

#endif // START_PUSHBUTTONDELEGATE_H
