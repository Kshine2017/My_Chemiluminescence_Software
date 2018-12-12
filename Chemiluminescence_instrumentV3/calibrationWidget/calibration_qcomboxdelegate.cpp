#include "calibration_qcomboxdelegate.h"

#include <QApplication>
#include <QPainter>
#include <QDebug>
#include <QAbstractItemModel>
calibration_QComboxDelegate::calibration_QComboxDelegate(QObject *parent):QStyledItemDelegate(parent)
{

}

QWidget *calibration_QComboxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);

    editor->insertItems(0, QStringList()
     << QApplication::translate("MainWindow", "A", 0)
     << QApplication::translate("MainWindow", "B", 0));
    editor->installEventFilter(const_cast<calibration_QComboxDelegate*>(this));
    return editor;
}

void calibration_QComboxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString disString =index.model()->data(index,Qt::DisplayRole).toString();
    QComboBox *box = static_cast < QComboBox *>(editor);
    box->setCurrentText(disString);
}

void calibration_QComboxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *box = static_cast<QComboBox*>(editor);
    model->setData(index,box->currentText(),Qt::DisplayRole);
}

void calibration_QComboxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void calibration_QComboxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 6)
    {
        QString disString = index.data().toString();
//        qDebug()<< disString << "$$$$$$$$";
        QStyleOptionComboBox *comboxOption = new QStyleOptionComboBox();
        comboxOption->rect = option.rect;
        comboxOption->currentText = disString;
        QApplication::style()->drawControl(QStyle::CE_ComboBoxLabel, comboxOption, painter);
        /***********************************************/

        /************************************************/

        painter->save();
    }
   else
    {
        //否则调用默认委托
        QStyledItemDelegate::paint(painter, option, index);
    }
}
