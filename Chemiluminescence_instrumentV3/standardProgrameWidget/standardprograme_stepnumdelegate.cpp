
#include "standardprograme_stepnumdelegate.h"

standardprograme_stepNumDelegate::standardprograme_stepNumDelegate(QWidget *parent) : QStyledItemDelegate(parent)
{

}

/**
 * @brief standardprograme_stepNumDelegate::虚函数
 * @param painter
 * @param option
 * @param index
 */
void standardprograme_stepNumDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}

void standardprograme_stepNumDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
