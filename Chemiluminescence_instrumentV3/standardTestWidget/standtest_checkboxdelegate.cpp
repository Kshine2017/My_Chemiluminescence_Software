#include "standtest_checkboxdelegate.h"
#include <QCheckBox>
#include <QStyleOptionButton>
#include <QApplication>
#include <QPainter>
#include <QDebug>
/**
 * @brief standtest_checkBoxDelegate::模型视图选择代理构造函数
 * @param parent
 */
standtest_checkBoxDelegate::standtest_checkBoxDelegate(QObject *parent):QStyledItemDelegate(parent)
{

}

  /**
   * @brief standtest_checkBoxDelegate::下面是虚函数
   * @param parent
   * @param option
   * @param index
   * @return
   */
QWidget *standtest_checkBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QCheckBox *editor = new QCheckBox(parent);
    editor->setStyleSheet("QCheckBox::indicator{ width: 48px;  height: 48px;}QCheckBox::indicator:checked{image:url(:/picture/standardTest/Checked_png.png);}"
                          "QCheckBox::indicator:unchecked{image:url(:/picture/standardTest/UnChecked_png.png); } "
                          "QCheckBox::indicator:checked:disabled{image:url(:/picture/standardTest/UnChecked_png.png);}"
                          );

    editor->installEventFilter(const_cast<standtest_checkBoxDelegate*>(this));
    return editor;

}

void standtest_checkBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
        bool value = index.model()->data(index, Qt::DisplayRole).toBool();
        QCheckBox *box = static_cast<QCheckBox*>(editor);
        if(value){
            box->setCheckState(Qt::Unchecked);
        }
        else{
            box->setCheckState(Qt::Checked);
         }
}

void standtest_checkBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
        QCheckBox *box = static_cast<QCheckBox*>(editor);
        int value = box->checkState();

        model->setData(index,value);
}

void standtest_checkBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void standtest_checkBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
 if (index.column() == 0){
     bool state = index.data(Qt::DisplayRole).toBool();
     QStyleOptionButton* button = new QStyleOptionButton;
     button->rect = option.rect.adjusted(0, 0, 0, 0);
     button->iconSize = QSize(48,48);
     if(state ){
         button->state |= QStyle::State_Enabled;
         button->icon = QIcon(":/picture/standardTest/Checked_png.png");
         button->text = QString(tr("已选择"));
     }else{
         button->state &=(~QStyle::State_Enabled);
         button->icon = QIcon(":/picture/standardTest/UnChecked_png.png");
         button->text = QString(tr("未选择"));
     }
//     (const_cast<standtest_checkBoxDelegate *>(this))->CheckBox.insert(index, button);

//     if (option.state & QStyle::State_Selected) {

//     }
//     painter->save();
     QApplication::style()->drawControl(QStyle::QStyle::CE_CheckBoxLabel, button, painter);
  }
  else{
       //否则调用默认委托
       QStyledItemDelegate::paint(painter, option, index);
   }
}
