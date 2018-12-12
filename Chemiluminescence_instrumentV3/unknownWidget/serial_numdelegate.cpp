#include "serial_numdelegate.h"
#include <QSpinBox>
serial_numDelegate::serial_numDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}
QWidget *serial_numDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &/*option*/,const QModelIndex &/*index*/) const
{
    QSpinBox *editor = new QSpinBox(parent);
    editor->setRange(0,10000);
    editor->installEventFilter(const_cast<serial_numDelegate*>(this));

    return editor;
}

void serial_numDelegate::setEditorData(QWidget *editor,const QModelIndex &index) const
{
    int value =index.model()->data(index).toInt();
    QSpinBox *box = static_cast<QSpinBox*>(editor);
    box->setValue(value);
}

void serial_numDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
{
    QSpinBox *box = static_cast<QSpinBox*>(editor);
    int value = box->value();

    model->setData(index,value);
}

void serial_numDelegate::updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const
{
    editor->setGeometry(option.rect);
}
