#include "standardprograme_minusdelegate.h"

standardprograme_minusDelegate::standardprograme_minusDelegate(QWidget *parent) : QStyledItemDelegate(parent)
{

}

/**
 * @brief standardprograme_minusDelegate::虚函数
 * @param parent
 * @param option
 * @param index
 * @return
 */
QWidget *standardprograme_minusDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QPushButton *editor = new QPushButton(parent);
    editor->resize(100,42);
    editor->setIconSize(QSize(72,72));
    editor->setIcon(QIcon(tr(":/picture/standardPrograme/minus.png")));
    editor->installEventFilter(const_cast<standardprograme_minusDelegate*>(this));
    return editor;
}

void standardprograme_minusDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionButton* button = Btns.value(index);
//    if (!button) {
        button = new QStyleOptionButton();
        button->features |= QStyleOptionButton::AutoDefaultButton;
        button->rect = option.rect.adjusted(4, 4, -4, -4);
        button->iconSize = QSize(50,42);
        button->icon = QIcon(":/picture/standardPrograme/minus.png");
        button->text = tr("删除");
        (const_cast<standardprograme_minusDelegate *>(this))->Btns.insert(index, button);
//    }
    painter->save();

    if (option.state & QStyle::State_Selected) {

    }
    painter->restore();
    QApplication::style()->drawControl(QStyle::CE_PushButtonLabel, button, painter);
}

void standardprograme_minusDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

bool standardprograme_minusDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* e =(QMouseEvent*)event;
        if (option.rect.adjusted(4, 4, -4, -4).contains(e->x(), e->y()) &&Btns.contains(index)) {
            Btns.value(index)->state &= (~QStyle::State_Enabled);
            Btns.value(index)->text = tr("按下");
        }
    }
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent* e =(QMouseEvent*)event;
        if (option.rect.adjusted(4, 4, -4, -4).contains(e->x(), e->y()) && Btns.contains(index)) {
              Btns.value(index)->state|= QStyle::State_Enabled;
              Btns.value(index)->text = tr("删除");
              emit MinusBtnClicked(index);
        }
    }
}
