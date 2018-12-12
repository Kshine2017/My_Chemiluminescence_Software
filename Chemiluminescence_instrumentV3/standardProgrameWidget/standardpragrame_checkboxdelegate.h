#ifndef STANDARDPRAGRAME_CHECKBOXDELEGATE_H
#define STANDARDPRAGRAME_CHECKBOXDELEGATE_H

#include <QWidget>
#include <QStyledItemDelegate>
#include <QAbstractTableModel>
#include <QCheckBox>
#include <QVariant>
#include <QMap>
#include <QStyledItemDelegate>
#include <QPushButton>
#include <QEvent>
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>

class standardpragrame_checkBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit standardpragrame_checkBoxDelegate(QWidget *parent = 0);

protected:

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
private:

  QMap<QModelIndex, QStyleOptionButton*> Btns;

signals:
  /// \brief 按钮点击信号
  ///
  /// \param QModelIndex   包含点击位置信息(表的行列)
  /// \return       void
  /// \see 无
  void CheckBoxClicked(const QModelIndex&);


public slots:
};

#endif // STANDARDPRAGRAME_CHECKBOXDELEGATE_H
