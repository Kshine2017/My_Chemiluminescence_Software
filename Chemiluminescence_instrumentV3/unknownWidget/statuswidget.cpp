#include "statuswidget.h"
#include <QDebug>
StatusWidget::StatusWidget(QWidget *parent) : QWidget(parent)
{
    //每个位置槽的状态标签
    setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(":/picture/unknowWidget/shijichuan_background.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    setPalette(palette);
    setFixedSize(1068,328);
    statusLab_1 = new QLabel;
    statusLab_2 = new QLabel;
    statusLab_3 = new QLabel;
    statusLab_4 = new QLabel;
    statusLab_5 = new QLabel;
    statusLab_6 = new QLabel;
    statusLab_7 = new QLabel;
    statusLab_8 = new QLabel;
    statusLab_9 = new QLabel;
    statusLab_10 = new QLabel;
    statusLab_11 = new QLabel;
    statusLab_12 = new QLabel;

    statusLab_1->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
    statusLab_2->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
    statusLab_3->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
    statusLab_4->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
    statusLab_5->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
    statusLab_6->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
    statusLab_7->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
    statusLab_8->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
    statusLab_9->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
    statusLab_10->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
    statusLab_11->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
    statusLab_12->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));




    //加急区和普通区位置槽标签
    urgentLabel = new QLabel;
    urgentLabel->setText(tr("      加急区"));
    commonLabel = new QLabel;
    commonLabel->setText(tr("          普通区"));
    urgentNumLabel = new QLabel;
    urgentNumLabel->setPixmap(QPixmap(":/picture/unknowWidget/1~3.png"));
    commonNumLabel = new QLabel;
    commonNumLabel->setPixmap(QPixmap(":/picture/unknowWidget/4~12.png"));
    //水平布局
    status1layout = new QHBoxLayout;
    status2layout = new QHBoxLayout;
    status3layout = new QHBoxLayout;
    //竖直布局
    statusSub1Layout = new QVBoxLayout;
    statusSub2Layout = new QVBoxLayout;
    //水平布局
    mainlayout = new QHBoxLayout;

    status2layout->addSpacing(1);
    status2layout->addWidget(statusLab_1);
    status2layout->addSpacing(9);
    status2layout->addWidget(statusLab_2);
    status2layout->addSpacing(9);
    status2layout->addWidget(statusLab_3);
    status2layout->addSpacing(35);
    status2layout->addWidget(statusLab_4);
    status2layout->addSpacing(9);
    status2layout->addWidget(statusLab_5);
    status2layout->addSpacing(9);
    status2layout->addWidget(statusLab_6);
    status2layout->addSpacing(9);
    status2layout->addWidget(statusLab_7);
    status2layout->addSpacing(9);
    status2layout->addWidget(statusLab_8);
    status2layout->addSpacing(9);
    status2layout->addWidget(statusLab_9);
    status2layout->addSpacing(9);
    status2layout->addWidget(statusLab_10);
    status2layout->addSpacing(9);
    status2layout->addWidget(statusLab_11);
    status2layout->addSpacing(9);
    status2layout->addWidget(statusLab_12);

    status1layout->addSpacing(10);
    status1layout->addWidget(urgentNumLabel);
    status1layout->addSpacing(70);
    status1layout->addWidget(commonNumLabel);
    status1layout->addSpacing(20);


    status3layout->addWidget(urgentLabel);
    status3layout->addWidget(commonLabel);


    statusSub1Layout->addLayout(status2layout);
    statusSub1Layout->addLayout(status1layout);
    statusSub1Layout->addLayout(status3layout);



    //      statusSub1Layout->addLayout(status1layout);
    //      statusSub1Layout->addWidget(urgentNumLabel);
    //      statusSub1Layout->addWidget(urgentLabel);

    //      statusSub2Layout->addLayout(status2layout);
    //      statusSub2Layout->addWidget(commonNumLabel);
    //      statusSub2Layout->addWidget(commonLabel);

    statusLab = new QLabel;
    statusLab->setPixmap(QPixmap(":/picture/unknowWidget/status_icon.png"));
    mainlayout->addSpacing(20);
    mainlayout->addLayout(statusSub1Layout);
    //    mainlayout->addSpacing(50);
    //    mainlayout->addLayout(statusSub2Layout);
    mainlayout->addSpacing(50);
    mainlayout->addWidget(statusLab);
     mainlayout->addSpacing(50);
    setLayout(mainlayout);

    for(int i =0;i< 12;i++){
        Reagent_status[i] = FREE; //初始化12个船仓状态
    }
}

/**
 * @brief setReagent_Status:更改试剂仓状态
 * @param space_num：试剂仓号
 * @param data：当前状态(空闲，运行，结束，异常)
 */
void StatusWidget::setReagent_Status(int space_num, StatusWidget::STATUS data)
{
    int temp = space_num;
    switch( space_num ){
    case 1:
        switch(data){
        case FREE:
            statusLab_1->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
            Reagent_status[temp-1] = FREE;
            break;
        case AWAIT:
            statusLab_1->setPixmap(QPixmap(tr(":/picture/unknowWidget/daiji.png")));
            Reagent_status[temp-1] = AWAIT;
            break;
        case RUN:
            statusLab_1->setPixmap(QPixmap(tr(":/picture/unknowWidget/yunxing_icon.png")));
            Reagent_status[temp-1] = RUN;
            break;
        case FINISH:
            statusLab_1->setPixmap(QPixmap(tr(":/picture/unknowWidget/jieshu_icon.png")));
            Reagent_status[temp-1] = FINISH;
            break;
        case ERR:
            statusLab_1->setPixmap(QPixmap(tr(":/picture/unknowWidget/yichang_icon.png")));
            Reagent_status[temp-1] = ERR;
            break;
        }
        break;
    case 2:
        switch(data){
        case FREE:
            statusLab_2->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
            Reagent_status[temp-1] = FREE;
            break;
        case AWAIT:
            statusLab_2->setPixmap(QPixmap(tr(":/picture/unknowWidget/daiji.png")));
            Reagent_status[temp-1] = AWAIT;
            break;
        case RUN:
            statusLab_2->setPixmap(QPixmap(tr(":/picture/unknowWidget/yunxing_icon.png")));
            Reagent_status[temp-1] = RUN;
            break;
        case FINISH:
            statusLab_2->setPixmap(QPixmap(tr(":/picture/unknowWidget/jieshu_icon.png")));
            Reagent_status[temp-1] = FINISH;
            break;
        case ERR:
            statusLab_2->setPixmap(QPixmap(tr(":/picture/unknowWidget/yichang_icon.png")));
            Reagent_status[temp-1] = ERR;
            break;
        }
        break;
    case 3:
        switch(data){
        case FREE:
            statusLab_3->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
            Reagent_status[temp-1] = FREE;
            break;
        case AWAIT:
            statusLab_3->setPixmap(QPixmap(tr(":/picture/unknowWidget/daiji.png")));
            Reagent_status[temp-1] = AWAIT;
            break;
        case RUN:
            statusLab_3->setPixmap(QPixmap(tr(":/picture/unknowWidget/yunxing_icon.png")));
            Reagent_status[temp-1] = RUN;
            break;
        case FINISH:
            statusLab_3->setPixmap(QPixmap(tr(":/picture/unknowWidget/jieshu_icon.png")));
            Reagent_status[temp-1] = FINISH;
            break;
        case ERR:
            statusLab_3->setPixmap(QPixmap(tr(":/picture/unknowWidget/yichang_icon.png")));
            Reagent_status[temp-1] = ERR;
            break;
        }
        break;
    case 4:
        switch(data){
        case FREE:
            statusLab_4->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
            Reagent_status[temp-1] = FREE;
            break;
        case AWAIT:
            statusLab_4->setPixmap(QPixmap(tr(":/picture/unknowWidget/daiji.png")));
            Reagent_status[temp-1] = AWAIT;
            break;
        case RUN:
            statusLab_4->setPixmap(QPixmap(tr(":/picture/unknowWidget/yunxing_icon.png")));
            Reagent_status[temp-1] = RUN;
            break;
        case FINISH:
            statusLab_4->setPixmap(QPixmap(tr(":/picture/unknowWidget/jieshu_icon.png")));
            Reagent_status[temp-1] = FINISH;
            break;
        case ERR:
            statusLab_4->setPixmap(QPixmap(tr(":/picture/unknowWidget/yichang_icon.png")));
            Reagent_status[temp-1] = ERR;
            break;
        }
        break;
    case 5:
        switch(data){
        case FREE:
            statusLab_5->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
            Reagent_status[temp-1] = FREE;
            break;
        case AWAIT:
            statusLab_5->setPixmap(QPixmap(tr(":/picture/unknowWidget/daiji.png")));
            Reagent_status[temp-1] = AWAIT;
            break;
        case RUN:
            statusLab_5->setPixmap(QPixmap(tr(":/picture/unknowWidget/yunxing_icon.png")));
            Reagent_status[temp-1] = RUN;
            break;
        case FINISH:
            statusLab_5->setPixmap(QPixmap(tr(":/picture/unknowWidget/jieshu_icon.png")));
            Reagent_status[temp-1] = FINISH;
            break;
        case ERR:
            statusLab_5->setPixmap(QPixmap(tr(":/picture/unknowWidget/yichang_icon.png")));
            Reagent_status[temp-1] = ERR;
            break;
        }
        break;
    case 6:
        switch(data){
        case FREE:
            statusLab_6->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
            Reagent_status[temp-1] = FREE;
            break;
        case AWAIT:
            statusLab_6->setPixmap(QPixmap(tr(":/picture/unknowWidget/daiji.png")));
            Reagent_status[temp-1] = AWAIT;
            break;
        case RUN:
            statusLab_6->setPixmap(QPixmap(tr(":/picture/unknowWidget/yunxing_icon.png")));
            Reagent_status[temp-1] = RUN;
            break;
        case FINISH:
            statusLab_6->setPixmap(QPixmap(tr(":/picture/unknowWidget/jieshu_icon.png")));
            Reagent_status[temp-1] = FINISH;
            break;
        case ERR:
            statusLab_6->setPixmap(QPixmap(tr(":/picture/unknowWidget/yichang_icon.png")));
            Reagent_status[temp-1] = ERR;
            break;
        }
        break;
    case 7:
        switch(data){
        case FREE:
            statusLab_7->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
            Reagent_status[temp-1] = FREE;
            break;
        case AWAIT:
            statusLab_7->setPixmap(QPixmap(tr(":/picture/unknowWidget/daiji.png")));
            Reagent_status[temp-1] = AWAIT;
            break;
        case RUN:
            statusLab_7->setPixmap(QPixmap(tr(":/picture/unknowWidget/yunxing_icon.png")));
            Reagent_status[temp-1] = RUN;
            break;
        case FINISH:
            statusLab_7->setPixmap(QPixmap(tr(":/picture/unknowWidget/jieshu_icon.png")));
            Reagent_status[temp-1] = FINISH;
            break;
        case ERR:
            statusLab_7->setPixmap(QPixmap(tr(":/picture/unknowWidget/yichang_icon.png")));
            Reagent_status[temp-1] = ERR;
            break;
        }
        break;
    case 8:
        switch(data){
        case FREE:
            statusLab_8->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
            Reagent_status[temp-1] = FREE;
            break;
        case AWAIT:
            statusLab_8->setPixmap(QPixmap(tr(":/picture/unknowWidget/daiji.png")));
            Reagent_status[temp-1] = AWAIT;
            break;
        case RUN:
            statusLab_8->setPixmap(QPixmap(tr(":/picture/unknowWidget/yunxing_icon.png")));
            Reagent_status[temp-1] = RUN;
            break;
        case FINISH:
            statusLab_8->setPixmap(QPixmap(tr(":/picture/unknowWidget/jieshu_icon.png")));
            Reagent_status[temp-1] = FINISH;
            break;
        case ERR:
            statusLab_8->setPixmap(QPixmap(tr(":/picture/unknowWidget/yichang_icon.png")));
            Reagent_status[temp-1] = ERR;
            break;
        }
        break;
    case 9:
        switch(data){
        case FREE:
            statusLab_9->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
            Reagent_status[temp-1] = FREE;
            break;
        case AWAIT:
            statusLab_9->setPixmap(QPixmap(tr(":/picture/unknowWidget/daiji.png")));
            Reagent_status[temp-1] = AWAIT;
            break;
        case RUN:
            statusLab_9->setPixmap(QPixmap(tr(":/picture/unknowWidget/yunxing_icon.png")));
            Reagent_status[temp-1] = RUN;
            break;
        case FINISH:
            statusLab_9->setPixmap(QPixmap(tr(":/picture/unknowWidget/jieshu_icon.png")));
            Reagent_status[temp-1] = FINISH;
            break;
        case ERR:
            statusLab_9->setPixmap(QPixmap(tr(":/picture/unknowWidget/yichang_icon.png")));
            Reagent_status[temp-1] = ERR;
            break;
        }
        break;
    case 10:
        switch(data){
        case FREE:
            statusLab_10->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
            Reagent_status[temp-1] = FREE;
            break;
        case AWAIT:
            statusLab_10->setPixmap(QPixmap(tr(":/picture/unknowWidget/daiji.png")));
            Reagent_status[temp-1] = AWAIT;
            break;
        case RUN:
            statusLab_10->setPixmap(QPixmap(tr(":/picture/unknowWidget/yunxing_icon.png")));
            Reagent_status[temp-1] = RUN;
            break;
        case FINISH:
            statusLab_10->setPixmap(QPixmap(tr(":/picture/unknowWidget/jieshu_icon.png")));
            Reagent_status[temp-1] = FINISH;
            break;
        case ERR:
            statusLab_10->setPixmap(QPixmap(tr(":/picture/unknowWidget/yichang_icon.png")));
            Reagent_status[temp-1] = ERR;
            break;
        }
        break;
    case 11:
        switch(data){
        case FREE:
            statusLab_11->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
            Reagent_status[temp-1] = FREE;
            break;
        case AWAIT:
            statusLab_11->setPixmap(QPixmap(tr(":/picture/unknowWidget/daiji.png")));
            Reagent_status[temp-1] = AWAIT;
            break;
        case RUN:
            statusLab_11->setPixmap(QPixmap(tr(":/picture/unknowWidget/yunxing_icon.png")));
            Reagent_status[temp-1] = RUN;
            break;
        case FINISH:
            statusLab_11->setPixmap(QPixmap(tr(":/picture/unknowWidget/jieshu_icon.png")));
            Reagent_status[temp-1] = FINISH;
            break;
        case ERR:
            statusLab_11->setPixmap(QPixmap(tr(":/picture/unknowWidget/yichang_icon.png")));
            Reagent_status[temp-1] = ERR;
            break;
        }
        break;
    case 12:
        switch(data){
        case FREE:
            statusLab_12->setPixmap(QPixmap(tr(":/picture/unknowWidget/kongxian_icon.png")));
            Reagent_status[temp-1] = FREE;
            break;
        case AWAIT:
            statusLab_12->setPixmap(QPixmap(tr(":/picture/unknowWidget/daiji.png")));
            Reagent_status[temp-1] = AWAIT;
            break;
        case RUN:
            statusLab_12->setPixmap(QPixmap(tr(":/picture/unknowWidget/yunxing_icon.png")));
            Reagent_status[temp-1] = RUN;
            break;
        case FINISH:
            statusLab_12->setPixmap(QPixmap(tr(":/picture/unknowWidget/jieshu_icon.png")));
            Reagent_status[temp-1] = FINISH;
            break;
        case ERR:
            statusLab_12->setPixmap(QPixmap(tr(":/picture/unknowWidget/yichang_icon.png")));
            Reagent_status[temp-1] = ERR;
            break;
        }
        break;
    }
}
