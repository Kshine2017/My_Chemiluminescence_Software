#include "calibration_progressbardelegate.h"

/**
 * @brief calibration_ProgressBarDelegate::构造
 * @param parent
 */
calibration_ProgressBarDelegate::calibration_ProgressBarDelegate(QObject *parent):QStyledItemDelegate(parent)
{

}

/**
 * @brief calibration_ProgressBarDelegate::从模型接收数据，返回用户修改的数据
 * @param parent
 * @param option
 * @param index
 * @return
 */
QWidget *calibration_ProgressBarDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QProgressBar *editor = new QProgressBar(parent);//如果不继承的话，点击之后 ，代理生成的进度条会飘在别的位置

//这里设置的样式，是点击之后的样式
//    editor->setStyleSheet("QProgressBar{border: 1px solid grey;border-radius: 5px;text-align: center;}"
//                          "QProgressBar::chunk{background-color: #CD96CD;width: 6px;margin: 0.5px;}");
   // editor->resize(300,42);
    editor->setRange(0,100);//数值从0~100
    editor->setAlignment(Qt::AlignCenter);//文字居中对齐
    editor->setFixedSize(420-16,42-16);
//    editor->setGeometry(8,8,  420-16, 42-16);

    editor->installEventFilter(const_cast<calibration_ProgressBarDelegate*>(this));
    return editor;
}

/**
 * @brief calibration_ProgressBarDelegate::创建的组件在显示所需要的值
 * @param editor
 * @param index
 */
void calibration_ProgressBarDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
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
void calibration_ProgressBarDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
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
void calibration_ProgressBarDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int nLeft = 8;
    int nTop = 8;
    int nWidth = option.rect.width() - 2 * nLeft;
    int nHeight = option.rect.height() - 2 * nTop;
    editor->setGeometry(QRect(option.rect.left() + nLeft, option.rect.top() + nTop,  nWidth, nHeight));


}

/**
 * @brief calibration_ProgressBarDelegate::组件渲染
 * @param painter
 * @param option
 * @param index
 */
void calibration_ProgressBarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{


        if (index.column() == 8)
        {
            int nProgress =  index.data().toInt();
            int nLeft = 8;
            int nTop = 8;
            int nWidth = option.rect.width() - 2 * nLeft;
            int nHeight = option.rect.height() - 2 * nTop;

            // 设置进度条的风格
            QStyleOptionProgressBar progressBarOption;

            progressBarOption.initFrom(option.widget);
            // 设置进度条显示的区域
            progressBarOption.rect = QRect(option.rect.left() + nLeft, option.rect.top() + nTop,  nWidth, nHeight);
            // 设置最小值
            progressBarOption.minimum = 0;
            // 设置最大值
            progressBarOption.maximum = 100;
            // 设置对齐方式
            progressBarOption.textAlignment = Qt::AlignCenter;
            // 设置进度
            progressBarOption.progress = nProgress;
            // 设置文本（百分比）
            progressBarOption.text = QString("%1%").arg(nProgress);
            // 设置文本可见
            progressBarOption.textVisible = true;

            QProgressBar progressBar;


            //绘制进度条
            QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter, &progressBar);
}
        }





