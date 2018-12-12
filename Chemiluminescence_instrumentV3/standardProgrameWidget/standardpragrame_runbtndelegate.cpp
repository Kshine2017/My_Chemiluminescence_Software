#include "standardpragrame_runbtndelegate.h"

standardpragrame_runBtnDelegate::standardpragrame_runBtnDelegate(QWidget *parent) : QStyledItemDelegate(parent)
{

}

/**
 * @brief standardpragrame_runBtnDelegate::虚函数
 * @param parent
 * @param option
 * @param index
 * @return
 */
QWidget *standardpragrame_runBtnDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QPushButton *editor = new QPushButton(parent);
    editor->resize(100,42);
    editor->setIconSize(QSize(30,30));
    editor->setIcon(QIcon(tr(":/picture/standardPrograme/start—up.png")));
    editor->installEventFilter(const_cast<standardpragrame_runBtnDelegate*>(this));
    return editor;
}

void standardpragrame_runBtnDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionButton* button = Btns.value(index);
//  if (!button) {
        button = new QStyleOptionButton();
        button->features |= QStyleOptionButton::AutoDefaultButton;
        button->rect = option.rect.adjusted(4, 4, -4, -4);
        button->iconSize = QSize(30,30);
        button->icon = QIcon(":/picture/standardPrograme/start—up.png");
        button->text = tr("单步运行");
        (const_cast<standardpragrame_runBtnDelegate *>(this))->Btns.insert(index, button);
//  }
    painter->save();

    if (option.state & QStyle::State_Selected) {

    }
    painter->restore();
    QApplication::style()->drawControl(QStyle::CE_PushButtonLabel, button, painter);
}

void standardpragrame_runBtnDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

bool standardpragrame_runBtnDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* e =(QMouseEvent*)event;
        if (option.rect.adjusted(4, 4, -4, -4).contains(e->x(), e->y()) &&Btns.contains(index)) {
//            Btns.value(index)->state &= (~QStyle::State_Enabled);
            Btns.value(index)->text = tr("按下");
        }
    }
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent* e =(QMouseEvent*)event;
        if (option.rect.adjusted(4, 4, -4, -4).contains(e->x(), e->y()) && Btns.contains(index)) {
              Btns.value(index)->state|= QStyle::State_Enabled;
              Btns.value(index)->text = tr("单步运行");
              emit stepRnBtnClicked(index);
        }
    }
}
