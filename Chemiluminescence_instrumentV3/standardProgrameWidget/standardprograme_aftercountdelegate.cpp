#include "standardprograme_aftercountdelegate.h"
#include <QApplication>
#include <QPainter>
#include <QDebug>
standardPrograme_afterCountDelegate::standardPrograme_afterCountDelegate(QWidget *parent) : QStyledItemDelegate(parent)
{

}
/**
 * @brief standardPrograme_afterCountDelegate::虚函数
 * @param parent
 * @param option
 * @param index
 * @return
 */
QWidget *standardPrograme_afterCountDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->insertItems(0, QStringList()
                        <<tr("0")<< tr("1") << tr("2") <<tr("3") <<tr("4") << tr("5") <<tr("6")
                        << tr("7") << tr("8") <<tr("9") <<tr("10"));
    editor->installEventFilter(const_cast<standardPrograme_afterCountDelegate*>(this));
    return editor;
}

void standardPrograme_afterCountDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString disString =index.model()->data(index,Qt::DisplayRole).toString();
    QComboBox *box = static_cast < QComboBox *>(editor);
    box->setCurrentText(disString);
}

void standardPrograme_afterCountDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *box = static_cast<QComboBox*>(editor);
    model->setData(index,box->currentText(),Qt::DisplayRole);
}

void standardPrograme_afterCountDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void standardPrograme_afterCountDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 11)
    {
        QString disString = index.data().toString();
        QStyleOptionComboBox *comboxOption = new QStyleOptionComboBox();
        comboxOption->rect = option.rect;
        comboxOption->currentText = disString;
        QApplication::style()->drawControl(QStyle::CE_ComboBoxLabel, comboxOption, painter);
        painter->save();
    }
   else
    {
        //否则调用默认委托
        QStyledItemDelegate::paint(painter, option, index);
    }
}
