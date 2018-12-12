/**
  *  @brief    自定义校准确定按钮代理
  *  @file     calibration_okbtndelegate.h
  *  @author   谢飞
  *  @version  1.0(版本号)
  *  @date     2017-10-11
  */
#include "calibration_okbtndelegate.h"
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QApplication>
/**
 * @brief calibration_okBtnDelegate::校准按钮代理
 * @param parent
 */
calibration_okBtnDelegate::calibration_okBtnDelegate(QObject *parent):QStyledItemDelegate(parent)
{

}

/**
 * @brief calibration_okBtnDelegate::按钮虚函数
 * @param painter
 * @param option
 * @param index
 */

QWidget *calibration_okBtnDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QPushButton *editor = new QPushButton(parent);
    editor->resize(100,42);
    editor->setIconSize(QSize(72,72));
    editor->setIcon(QIcon(tr(":/picture/calibrationWidget/display_png.png")));
    editor->installEventFilter(const_cast<calibration_okBtnDelegate*>(this));
    return editor;
}



void calibration_okBtnDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
//    int value =index.model()->data(index).toInt();
//    QProgressBar *box = static_cast<QProgressBar*>(editor);
//    box->setValue(value);
}

void calibration_okBtnDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
//    QProgressBar *box = static_cast<QProgressBar*>(editor);
//    int value = box->value();

//    model->setData(index,value);
}

void calibration_okBtnDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
     editor->setGeometry(option.rect);
}

bool calibration_okBtnDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* e =(QMouseEvent*)event;
        if (option.rect.adjusted(4, 4, -4, -4).contains(e->x(), e->y()) &&Display_btns.contains(index.row())) {
            Display_btns.value(index.row())->state &= (~QStyle::State_Enabled);

        }
    }
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent* e =(QMouseEvent*)event;

        if (option.rect.adjusted(4, 4, -4, -4).contains(e->x(), e->y()) && Display_btns.contains(index.row())) {
              Display_btns.value(index.row())->state|= QStyle::State_Enabled;
              Display_btns.value(index.row())->text = tr("完成");
              emit btnClicked(index);
        }
    }
}



void calibration_okBtnDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionButton* button = Display_btns.value(index.row());
    if (!button) {
        button = new QStyleOptionButton();
        button->features |= QStyleOptionButton::AutoDefaultButton;
        button->rect = option.rect.adjusted(4, 4, -4, -4);
        button->iconSize = QSize(50,42);
        button->icon = QIcon(":/picture/calibrationWidget/display_png.png");

        (const_cast<calibration_okBtnDelegate *>(this))->Display_btns.insert(index.row(), button);
    }
    painter->save();

    if (option.state & QStyle::State_Selected) {

    }
    painter->restore();
    QApplication::style()->drawControl(QStyle::CE_PushButtonLabel, button, painter);
}




