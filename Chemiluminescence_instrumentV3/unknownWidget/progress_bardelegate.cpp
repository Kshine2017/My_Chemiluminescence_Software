#include "progress_bardelegate.h"
#include <QApplication>
#include <QPainter>
progress_BarDelegate::progress_BarDelegate(QObject *parent):QStyledItemDelegate(parent)
{

}

QWidget *progress_BarDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &/*option*/,const QModelIndex &/*index*/) const
{
    QProgressBar *editor = new QProgressBar(parent);
    editor->setStyleSheet("QProgressBar{border: 1px solid grey;border-radius: 5px;text-align: center;}"
                          "QProgressBar::chunk{background-color: #CD96CD;width: 10px;margin: 0.5px;}");
    editor->resize(300,42);
    editor->setRange(0,100);
    editor->installEventFilter(const_cast<progress_BarDelegate*>(this));
    return editor;
}

void progress_BarDelegate::setEditorData(QWidget *editor,const QModelIndex &index) const
{
    int value =index.model()->data(index).toInt();
    QProgressBar *box = static_cast<QProgressBar*>(editor);
    box->setValue(value);
}

void progress_BarDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
{
    QProgressBar *box = static_cast<QProgressBar*>(editor);
    int value = box->value();

    model->setData(index,value);
}

void progress_BarDelegate::updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const
{
    editor->setGeometry(option.rect);
}


void progress_BarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
    if (index.column() == 6)
    {
        ////        painter->fillRect( option.rect, option.palette.highlight() );

        //          // 数据是存储在QStandardItemModel的QStandardItem，会自动根据当前行进行匹配（我认为）
        //          int value = index.model()->data( index, Qt::DisplayRole ).toInt(); // 这句，取得当前行的数据
        //          double factor = double(value)/100.0; // 计算比例因子

        //          painter->save(); // 保存旧画板（我认为）
        //          // 进度条背景色
        //          if( factor > 0.8 )
        //          {
        //            painter->setBrush( Qt::red ); // 超过0.8画纯红色
        //            factor = 1;
        //          }
        //          else
        //            painter->setBrush( QColor( 0, int(factor*255), 255-int(factor*255) ) ); // 否则颜色依次变淡

        //          painter->setPen( Qt::white ); // 画笔颜色（这里没用到，我认为）
        //          // 前面都是准备工作，这里才是真正画进度条
        //          painter->drawRect( option.rect.x()+2, option.rect.y()+2, int(factor*(option.rect.width()-5)), option.rect.height()-5 );
        //          painter->restore(); // 恢复新画板（我认为）

        int progrss = index.data().toInt();
        //进度条的风格选项
        QStyleOptionProgressBar *progressBarOption = new QStyleOptionProgressBar();

        progressBarOption->textAlignment = Qt::AlignRight;
        /***********************更改进度条样式*************************/

        int nLeft = 4;
        int nTop = 8;
        int nWidth = option.rect.width() - 2 * nLeft;
        int nHeight = option.rect.height() - 2 * nTop;
        progressBarOption->rect = QRect(option.rect.left() + nLeft, option.rect.top() + nTop,  nWidth, nHeight);
        /***********************更改进度条样式*************************/

        progressBarOption->state = QStyle::State_Sunken;
        progressBarOption->minimum = 0;
        progressBarOption->maximum = 100;
        progressBarOption->progress = progrss;  //当前进度条值
        progressBarOption->text = QString::number(progrss) + "%";
        progressBarOption->textVisible = true;
        /****************设置画笔属性****/
        painter->save();
        QConicalGradient conicalGradient2(nWidth/2, nHeight/2, 90);
//        conicalGradient2.setColorAt(0, QColor(45, 204, 112));
//        conicalGradient2.setColorAt(1.0, QColor(51, 152, 219));
//        painter->setPen(QPen(QBrush(conicalGradient2), 70));
//        if(progrss == 100)
//        {
//            painter->setPen(QPen(QColor(0,255,0)));
//        }else
//        {
//           painter->setPen(QPen(QColor(255-2.55*progrss,255,0)));
//        }

        painter->setPen(QPen("black"));


        /**********************/
        if (option.state & QStyle::State_Selected) {
            painter->fillRect(option.rect, option.palette.highlight());
            painter->setBrush(option.palette.highlightedText());
        }
        QProgressBar proBar;
        proBar.setFont(QFont("title",28,50));
        //         proBar.setStyleSheet("QProgressBar{border: 1px solid grey;border-radius: 5px;text-align: center;}"
        //                              "QProgressBar::chunk{background-color: #CD96CD;width: 10px;margin: 0.5px;}");
        //         progressBarOption->initFrom(&proBar);
        QApplication::style()->drawControl(QStyle::CE_ProgressBar, progressBarOption, painter,&proBar);
    }
    else
    {
        //否则调用默认委托
        QStyledItemDelegate::paint(painter, option, index);
    }

}
