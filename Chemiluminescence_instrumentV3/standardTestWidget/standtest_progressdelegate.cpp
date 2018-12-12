
#include "standtest_progressdelegate.h"
#include <QProgressBar>
#include <QPainter>
#include <QApplication>
#include <QStyleOptionProgressBarV2>
/**
 * @brief standTest_ProgressDelegate::进度条代理构造函数
 * @param parent
 */
standTest_ProgressDelegate::standTest_ProgressDelegate(QObject *parent):QStyledItemDelegate(parent)
{

}


/**
 * @brief calibration_ProgressBarDelegate::从模型接收数据，返回用户修改的数据
 * @param parent
 * @param option
 * @param index
 * @return
 */
QWidget *standTest_ProgressDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QProgressBar *editor = new QProgressBar(parent);
    editor->resize(300,42);
    editor->setRange(0,100);
    editor->installEventFilter(const_cast<standTest_ProgressDelegate*>(this));
    return editor;
}

/**
 * @brief calibration_ProgressBarDelegate::创建的组件在显示所需要的值
 * @param editor
 * @param index
 */
void standTest_ProgressDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int value =index.model()->data(index).toInt();
    QProgressBar *box = static_cast <QProgressBar *>(editor);
    box->setValue(value);
}

/**
 * @brief calibration_ProgressBarDelegate::返回给模型用户修改过的数据
 * @param editor
 * @param model
 * @param index
 */
void standTest_ProgressDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QProgressBar *box = static_cast<QProgressBar*>(editor);
    int value = box->value();

    model->setData(index,value);
}

/**
 * @brief calibration_ProgressBarDelegate::确保组件为编辑器能够显示出来
 * @param editor
 * @param option
 * @param index
 */
void standTest_ProgressDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

/**
 * @brief calibration_ProgressBarDelegate::组件渲染
 * @param painter
 * @param option
 * @param index
 */
void standTest_ProgressDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 5)
    {
        int progrss = index.data().toInt();

        /***********************更改进度条样式*************************/

//        //进度条的风格选项
         QStyleOptionProgressBarV2 *progressBarOption = new QStyleOptionProgressBarV2();
//         progressBarOption->rect = option.rect;
         progressBarOption->minimum = 0;
         progressBarOption->maximum = 100;
         progressBarOption->progress = progrss;
         progressBarOption->text = QString::number(progrss) + "%";
         progressBarOption->textVisible = true;

         /***********************更改进度条样式*************************/
         int nLeft = 4;
         int nTop = 8;
         int nWidth = option.rect.width() - 2 * nLeft;
         int nHeight = option.rect.height() - 2 * nTop;
         progressBarOption->rect = QRect(option.rect.left() + nLeft, option.rect.top() + nTop,  nWidth, nHeight);
//        //绘制进度条
         QApplication::style()->drawControl(QStyle::CE_ProgressBar, progressBarOption, painter);

    }
   else
    {
        //否则调用默认委托
        QStyledItemDelegate::paint(painter, option, index);
    }
}

