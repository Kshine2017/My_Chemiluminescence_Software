#include "standardprograme_addbtndelegate.h"

standardPrograme_addBtnDelegate::standardPrograme_addBtnDelegate(QWidget *parent) : QStyledItemDelegate(parent)
{

}


/**
 * @brief standardPrograme_addBtnDelegate::重载虚函数
 * @param parent
 * @param option
 * @param index
 * @return
 */
QWidget *standardPrograme_addBtnDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QPushButton *editor = new QPushButton(parent);
    editor->resize(100,42);
    editor->setIconSize(QSize(72,72));
    editor->setIcon(QIcon(tr(":/picture/standardPrograme/add.png")));
    editor->installEventFilter(const_cast<standardPrograme_addBtnDelegate*>(this));
    return editor;
}

void standardPrograme_addBtnDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionButton* button = Btns.value(index);
//    if (!button) {
        button = new QStyleOptionButton();
        button->features |= QStyleOptionButton::AutoDefaultButton;
        button->rect = option.rect.adjusted(4, 4, -4, -4);
        button->iconSize = QSize(50,42);
        button->icon = QIcon(":/picture/standardPrograme/add.png");
        button->text = QString(tr("增加"));
        (const_cast<standardPrograme_addBtnDelegate *>(this))->Btns.insert(index, button);
//    }
    painter->save();

    if (option.state & QStyle::State_Selected) {

    }
    painter->restore();
    QApplication::style()->drawControl(QStyle::CE_PushButtonLabel, button, painter);
}

void standardPrograme_addBtnDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
         editor->setGeometry(option.rect);
}

bool standardPrograme_addBtnDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
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
              Btns.value(index)->text = tr("增加");
              emit AddBtnClicked(index);
        }
    }
}
