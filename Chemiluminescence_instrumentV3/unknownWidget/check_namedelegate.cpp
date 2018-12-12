#include "check_namedelegate.h"

check_nameDelegate::check_nameDelegate(QObject *parent) :
  QStyledItemDelegate(parent)
{

}

QWidget *check_nameDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &/*option*/,const QModelIndex &/*index*/) const
{
    QLabel *editor = new QLabel(parent);
    editor->setText(tr(" PCT "));
    editor->installEventFilter(const_cast<check_nameDelegate*>(this));
    return editor;
}

void check_nameDelegate::setEditorData(QWidget *editor,const QModelIndex &index) const
{
    QString str =index.model()->data(index).toString();
    QLabel *box = static_cast<QLabel*>(editor);
    box->setText(str);
}

void check_nameDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLabel *box = static_cast<QLabel*>(editor);
    QString str = box->text();
    model->setData(index,str);
}

void check_nameDelegate::updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const
{
    editor->setGeometry(option.rect);
}
