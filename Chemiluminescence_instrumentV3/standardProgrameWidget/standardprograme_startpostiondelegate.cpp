#include "standardprograme_startpostiondelegate.h"
#include <QApplication>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
standardPrograme_startPostionDelegate::standardPrograme_startPostionDelegate(QWidget *parent) : QStyledItemDelegate(parent)
{

}

/**
 * @brief standardPrograme_startPostionDelegate::虚函数
 * @param parent
 * @param option
 * @param index
 * @return
 */
QWidget *standardPrograme_startPostionDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);


    editor->insertItems(0, QStringList()
                        << tr("#1") << tr("#2") <<tr("#3") <<tr("#4") << tr("#5") <<tr("#6")
                        << tr("#7") << tr("#8") <<tr("#9") <<tr("#10") << tr("#11") <<tr("#13") <<tr("#14") <<tr("#15") <<tr("#16")
                        <<  QString(tr("温育孔#1")) << QString(tr("温育孔#2")));
    editor->installEventFilter(const_cast<standardPrograme_startPostionDelegate*>(this));
    return editor;
}

void standardPrograme_startPostionDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString disString =index.model()->data(index,Qt::DisplayRole).toString();
    QComboBox *box = static_cast < QComboBox *>(editor);
    box->setCurrentText(disString);
}

void standardPrograme_startPostionDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *box = static_cast<QComboBox*>(editor);
    model->setData(index,box->currentText(),Qt::DisplayRole);
}

void standardPrograme_startPostionDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void standardPrograme_startPostionDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 5)
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

bool standardPrograme_startPostionDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
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
              Btns.value(index)->text = tr("启动");
              emit stepRnBtnClicked(index);;
        }
    }
}
