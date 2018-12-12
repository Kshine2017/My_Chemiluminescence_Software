#include "standardprograme_actioncheckdelegate.h"

#include <QApplication>
#include <QPainter>
#include <QDebug>
standardprograme_actionCheckDelegate::standardprograme_actionCheckDelegate(QWidget *parent) : QStyledItemDelegate(parent)
{

}

/**
 * @brief standardprograme_actionCheckDelegate::虚函数
 * @param parent
 * @param option
 * @param index
 * @return
 */
QWidget *standardprograme_actionCheckDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //创建对象
    QComboBox *editor = new QComboBox(parent);
    //添加选项
    editor->insertItems(0, QStringList()<<tr("取反应管")
                                        <<tr("取液体(样本、试剂")
                                        <<tr("取磁珠")
                                        <<tr("清洗")
                                        <<tr("温育")
                                        <<tr("发光"));
    //安装事件过滤器
    editor->installEventFilter(const_cast<standardprograme_actionCheckDelegate*>(this));
    return editor;
}

void standardprograme_actionCheckDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //获取索引指向的单元格的 字符串名
    QString disString =index.model()->data(index,Qt::DisplayRole).toString();

    //获取指针，进行操作
    QComboBox *box = static_cast < QComboBox *>(editor);

    //让comboBox就显示当前单元格的字符内容
    box->setCurrentText(disString);
}

void standardprograme_actionCheckDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    //获取操作指针
    QComboBox *box = static_cast<QComboBox*>(editor);

    //修改指向的单元格的内容，为下拉框中选择的内容
    model->setData(index,box->currentText(),Qt::DisplayRole);
}

void standardprograme_actionCheckDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //修改对象的位置
    editor->setGeometry(option.rect);
}

void standardprograme_actionCheckDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 3)
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
