#include "standardtest_okbtndelegate.h"
#include <QPushButton>
#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
/**
 * @brief standardText_okBtnDelegate::构造函数
 * @param parent
 */
standardText_okBtnDelegate::standardText_okBtnDelegate(QObject *parent):QStyledItemDelegate(parent)
{

}

/**
 * @brief calibration_okBtnDelegate::按钮虚函数
 * @param painter
 * @param option
 * @param index
 */

QWidget *standardText_okBtnDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QPushButton *editor = new QPushButton(parent);
    editor->resize(100,42);
    editor->setIconSize(QSize(72,72));
    editor->setIcon(QIcon(tr(":/picture/standardTest/complate.png")));
    editor->installEventFilter(const_cast<standardText_okBtnDelegate*>(this));
    return editor;
}



void standardText_okBtnDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
//    int value =index.model()->data(index).toInt();
//    QProgressBar *box = static_cast<QProgressBar*>(editor);
//    box->setValue(value);
}

void standardText_okBtnDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
//    QProgressBar *box = static_cast<QProgressBar*>(editor);
//    int value = box->value();

//    model->setData(index,value);
}

void standardText_okBtnDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
     editor->setGeometry(option.rect);
}

bool standardText_okBtnDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* e =(QMouseEvent*)event;
        if (option.rect.adjusted(4, 4, -4, -4).contains(e->x(), e->y()) &&okBtn_btns.contains(index.row())) {
            okBtn_btns.value(index.row())->state &= (~QStyle::State_Enabled);

        }
    }
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent* e =(QMouseEvent*)event;

        if (option.rect.adjusted(4, 4, -4, -4).contains(e->x(), e->y()) && okBtn_btns.contains(index.row())) {
              okBtn_btns.value(index.row())->state|= QStyle::State_Enabled;
              okBtn_btns.value(index.row())->text = tr("完成");
              emit OkBtnClicked(index);
        }
    }
}



void standardText_okBtnDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionButton* button = okBtn_btns.value(index.row());
    if (!button) {
        button = new QStyleOptionButton();
        button->features |= QStyleOptionButton::AutoDefaultButton;
        button->rect = option.rect.adjusted(4, 4, -4, -4);
        button->iconSize = QSize(50,42);
        button->icon = QIcon(":/picture/standardTest/complate.png");

        (const_cast<standardText_okBtnDelegate *>(this))->okBtn_btns.insert(index.row(), button);
    }
    painter->save();

    if (option.state & QStyle::State_Selected) {

    }
    painter->restore();
    QApplication::style()->drawControl(QStyle::CE_PushButtonLabel, button, painter);
}
