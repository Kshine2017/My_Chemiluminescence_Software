#include "standardpragrame_checkboxdelegate.h"


standardpragrame_checkBoxDelegate::standardpragrame_checkBoxDelegate(QWidget *parent) : QStyledItemDelegate(parent)
{

}
static QRect CheckBoxRect(const QStyleOptionViewItem &viewItemStyleOptions)/*const*/
{
    //绘制按钮所需要的参数
    QStyleOptionButton checkBoxStyleOption;
    //按照给定的风格参数 返回元素子区域
    QRect checkBoxRect = QApplication::style()->subElementRect( QStyle::SE_CheckBoxIndicator, &checkBoxStyleOption);
    //返回QCheckBox坐标
    QPoint checkBoxPoint(viewItemStyleOptions.rect.x() + viewItemStyleOptions.rect.width() / 2 - checkBoxRect.width() / 2,
                         viewItemStyleOptions.rect.y() + viewItemStyleOptions.rect.height() / 2 - checkBoxRect.height() / 2);
    //返回QCheckBox几何形状
    return QRect(checkBoxPoint, checkBoxRect.size());
}

/**
 * @brief standardpragrame_runBtnDelegate::虚函数
 * @param parent
 * @param option
 * @param index
 * @return
 */
QWidget *standardpragrame_checkBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return NULL;//editor;
}
void standardpragrame_checkBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{


}

void standardpragrame_checkBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    bool checked = index.model()->data(index, Qt::DisplayRole).toBool();

        if(index.column() == 0){
            QStyleOptionButton checkBoxStyleOption;
            checkBoxStyleOption.state |= QStyle::State_Enabled;
//            checkBoxStyleOption.state |= checked? QStyle::State_On : QStyle::State_Off;
//            checkBoxStyleOption.rect = CheckBoxRect(option);
            checkBoxStyleOption.rect = QRect(option.rect.left()+20,option.rect.top(),option.rect.width(),option.rect.height());

            if (checked)
            {
                checkBoxStyleOption.iconSize = QSize(30,30);
                checkBoxStyleOption.icon = QIcon(":/picture/selfTest/Checked_png.png");
               // option.state = QStyle::State_On;
            }
            else
            {
                checkBoxStyleOption.iconSize = QSize(30,30);
                checkBoxStyleOption.icon = QIcon(":/picture/selfTest/UnChecked_png.png");
               // option.state = QStyle::State_Off;
            }

            QApplication::style()->drawControl(QStyle::CE_CheckBoxLabel,&checkBoxStyleOption,painter);
        }else{
            QStyledItemDelegate::paint(painter, option, index);
        }
}



bool standardpragrame_checkBoxDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(index.column() == 0){   //如果是第一列
        if((event->type() == QEvent::MouseButtonRelease) ||
                (event->type() == QEvent::MouseButtonDblClick)){
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() != Qt::LeftButton ||
                    !option.rect.contains(mouseEvent->pos())){
                return true;
            }
            if(event->type() == QEvent::MouseButtonDblClick){
                return true;
            }
        }else if(event->type() == QEvent::KeyPress){
            if(static_cast<QKeyEvent*>(event)->key() != Qt::Key_Space &&
                    static_cast<QKeyEvent*>(event)->key() != Qt::Key_Select){
                return false;
            }
        }else{
            return false;
        }

        bool checked = index.model()->data(index, Qt::DisplayRole).toBool();

        return model->setData(index, !checked, Qt::EditRole);
        }else{
            return QStyledItemDelegate::editorEvent(event, model, option, index);
    }
}

void standardpragrame_checkBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int value = index.model()->data(index, Qt::DisplayRole).toInt();

            QCheckBox *checkBox = static_cast<QCheckBox*>(editor);
            if(value == 1)
                checkBox->setCheckState(Qt::Checked);
            else
                checkBox->setCheckState(Qt::Unchecked);
}
