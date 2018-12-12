#include "reagentvesseleditor.h"

/*
 * 标准品试剂船编辑界面
 */
ReagentVesselEditor::ReagentVesselEditor(QWidget *parent) : QWidget(parent)
{
    QFont *font1 = new QFont("AcadEref",20,20);//字体大小20，
    QFont *font2 = new QFont("AcadEref",14,20);
    this->setFont(*font2);
    mainLayout = new QVBoxLayout(this);//主步局
    layout_editor = new QHBoxLayout(); // 编辑布局
    layout_detailSteps = new QVBoxLayout();//详细步骤布局

    label_editor = new QLabel(QString(tr("      试剂船编辑区域")));//编辑标签
    label_editor->setFont(*font2);
//    label_editor->setStyleSheet("QLabel{border-image: url(:/new/prefix1/picture/title.png)}");
    label_detailSteps = new QLabel(QString(tr("        详细步骤")));;//详细步骤标签
    label_detailSteps->setFont(*font2);
//    label_detailSteps->setStyleSheet("QLabel{border-image: url(:/new/prefix1/picture/title.png)}");

    label_pit = new QLabel(QString(tr("试剂船图片")));//放图片
    layout_grooves1 = new QVBoxLayout();//槽布局1
    layout_grooves2 = new QVBoxLayout();//槽布局2
    label_groove1 = new QLabel(QString(tr("槽1")));//槽1
    label_groove1->setFrameStyle(QFrame::Box);//设置Label的方框格式

    label_groove2 = new QLabel(QString(tr("槽2")));//槽2
    label_groove3 = new QLabel(QString(tr("槽3")));//槽3
    label_groove4 = new QLabel(QString(tr("槽4")));//槽4
    label_groove5 = new QLabel(QString(tr("槽5")));//槽5
    label_groove6 = new QLabel(QString(tr("槽6")));//槽6
    label_groove7 = new QLabel(QString(tr("槽7")));//槽7
    label_groove8 = new QLabel(QString(tr("槽8")));//槽8
    label_groove9 = new QLabel(QString(tr("槽9")));//槽9
    label_groove10 = new QLabel(QString(tr("槽10")));//槽10
    label_groove11 = new QLabel(QString(tr("槽11")));//槽11
    label_groove12 = new QLabel(QString(tr("槽12")));//槽12
    label_groove13 = new QLabel(QString(tr("槽13")));//槽13
    label_groove14 = new QLabel(QString(tr("槽14")));//槽14

    /*
     * 槽布局1
     */
    layout_grooves1->addWidget(label_groove1);
    layout_grooves1->addWidget(label_groove2);
    layout_grooves1->addWidget(label_groove3);
    layout_grooves1->addWidget(label_groove4);
    layout_grooves1->addWidget(label_groove5);
    layout_grooves1->addWidget(label_groove6);

    /*
     * 槽布局2
     */
    layout_grooves2->addWidget(label_groove7);
    layout_grooves2->addWidget(label_groove8);
    layout_grooves2->addWidget(label_groove9);
    layout_grooves2->addWidget(label_groove10);
    layout_grooves2->addWidget(label_groove11);
    layout_grooves2->addWidget(label_groove12);
    /*
     * 试剂船编辑区域
     */
    layout_editor->addWidget(label_pit);
    layout_editor->addStretch();
    layout_editor->addLayout(layout_grooves1);
    layout_editor->addLayout(layout_grooves2);

    //按钮区域

    layout_btn = new QHBoxLayout;
    btn_start = new QPushButton(QString(tr("运行")));
    btn_pause = new QPushButton(QString(tr("暂停")));
    btn_continue = new QPushButton(QString(tr("继续")));
    btn_stop = new QPushButton(QString(tr("停止")));
    btn_cancel = new QPushButton(QString(tr("返回")));
    btn_next = new QPushButton(QString(tr("下一步")));

    layout_btn->addWidget(btn_start);
    layout_btn->addWidget(btn_pause);
    layout_btn->addWidget(btn_continue);
    layout_btn->addWidget(btn_stop);
    layout_btn->addWidget(btn_cancel);
    layout_btn->addWidget(btn_next);
    layout_btn->addStretch();

//    //文件信息区域
    layout_fileInfo = new QHBoxLayout;

    label_fileName = new QLabel(QString(tr("文件名称：")));//文件名
    label_fileName->setFrameStyle(6);
    edit_fileName = new QLineEdit;//文件名输入

    label_fileNameAbbreviation = new QLabel(QString(tr("文件名简写：")));//文件名简写
    label_fileNameAbbreviation->setFrameStyle(6);
    edit_fileNameAbbreviation= new QLineEdit;//文件名简写输入

    label_barcode = new QLabel(QString(tr("条码图像：")));//条码图像
    label_barcode->setFrameStyle(6);
    label_barcodeImage = new QLabel(QString(tr("放图片或其他！")));//存放条码图片
    label_barcodeImage->setFrameStyle(6);

    label_startTime = new QLabel(QString(tr("开始使用时间：")));//开始使用时间
    label_startTime->setFrameStyle(6);
    edit_startTime = new QLineEdit();

    label_endTime = new QLabel(QString(tr("结束使用时间：")));//结束使用时间
    label_endTime->setFrameStyle(6);
    edit_endTime = new QLineEdit();

    layout_fileInfo->addWidget(label_fileName);
    layout_fileInfo->addWidget(edit_fileName);
    layout_fileInfo->addWidget(label_fileNameAbbreviation);
    layout_fileInfo->addWidget(edit_fileNameAbbreviation);
    layout_fileInfo->addWidget(label_barcode);
    layout_fileInfo->addWidget(label_barcodeImage);
    layout_fileInfo->addWidget(label_startTime);
    layout_fileInfo->addWidget(edit_startTime);
    layout_fileInfo->addWidget(label_endTime);
    layout_fileInfo->addWidget(edit_endTime);

    //当前工作区域
    layout_currentWorkPhase = new QHBoxLayout();
    layout_currentWork = new QVBoxLayout();
    layout_progress = new QVBoxLayout();
    layout_startTime = new QVBoxLayout();
    layout_endTime = new QVBoxLayout();

    label_currentWork = new QLabel(QString(tr("当前工作阶段")));
    label_currentWorkName = new QLabel(QString(tr("温育")));
    layout_currentWork->addWidget(label_currentWork);
    layout_currentWork->addWidget(label_currentWorkName);


    label_progress = new QLabel(QString(tr("进度条")));
    progressBar = new QProgressBar();
    layout_progress->addWidget(label_progress);
    layout_progress->addWidget(progressBar);

    progressBar->setValue(50);


    label_workStartTime = new QLabel(QString(tr("开始时间")));
    label_workStartTimeShow = new QLabel(QString(tr("20:13")));
    layout_startTime->addWidget(label_workStartTime);
    layout_startTime->addWidget(label_workStartTimeShow);

    label_workEndTime = new QLabel(QString(tr("结束时间")));
    label_workEndTimeShow = new QLabel(QString(tr("20:50")));

    label_currentWork->setFrameStyle(6);
    label_currentWorkName->setFrameStyle(6);
    label_currentWorkName->setAlignment(Qt::AlignCenter);//文字居中
    label_progress->setFrameStyle(6);
    label_progress->setAlignment(Qt::AlignCenter);//文字居中
    label_workStartTime->setFrameStyle(6);
    label_workStartTimeShow->setFrameStyle(6);
    label_workEndTime->setFrameStyle(6);
    label_workEndTimeShow->setFrameStyle(6);

    layout_endTime->addWidget(label_workEndTime);
    layout_endTime->addWidget(label_workEndTimeShow);

    layout_currentWorkPhase->addLayout(layout_currentWork);
    layout_currentWorkPhase->addLayout(layout_progress);
    layout_currentWorkPhase->addLayout(layout_startTime);
    layout_currentWorkPhase->addLayout(layout_endTime);

    //编辑区域
    layout_infoEdit = new QHBoxLayout();//编辑区域
    layout_infoEditor = new QVBoxLayout();
    layout_name = new QHBoxLayout();;//名字区域
    layout_position = new QHBoxLayout();;//位置区域
    layout_capacity = new QHBoxLayout();;//容量区域

    label_infoEditName = new QLabel(QString(tr("试剂船编辑:")));//试剂船编辑
    label_name = new QLabel(QString(tr("名称:")));//名称
    label_positionName = new QLabel(QString(tr("位置(mm):")));//位置
    label_capacityName = new QLabel(QString(tr("容量(ul):")));//容量

    label_reactionTube = new QLabel(QString(tr("反应管")));//反应管
    label_bufferWaste = new QLabel(QString(tr("废液池")));//废液池
    label_washingLiquid = new QLabel(QString(tr("洗涤液")));//洗涤液
    label_reagent3 = new QLabel(QString(tr("试剂3")));//试剂3
    label_magneticBeads = new QLabel(QString(tr("磁珠")));//磁珠
    label_reagent2 = new QLabel(QString(tr("试剂2")));//试剂2
    label_reagent1 = new QLabel(QString(tr("试剂1")));//试剂1
    label_substrateSolution = new QLabel(QString(tr("底物液")));//底物液
    label_reactionTube2 = new QLabel(QString(tr("反应管2")));//反应管2
    label_tip2 = new QLabel(QString(tr("TP2"))); //tp2
    label_tip1 = new QLabel(QString(tr("TP1"))); //tp1

    label_infoEditName->setFrameStyle(6);
    label_name->setFrameStyle(6);
    label_positionName->setFrameStyle(6);
    label_capacityName->setFrameStyle(6);
    label_reactionTube->setFrameStyle(6);
    label_bufferWaste->setFrameStyle(6);
    label_washingLiquid->setFrameStyle(6);
    label_reagent3->setFrameStyle(6);
    label_magneticBeads->setFrameStyle(6);
    label_reagent2->setFrameStyle(6);
    label_reagent1->setFrameStyle(6);
    label_substrateSolution->setFrameStyle(6);
    label_reactionTube2->setFrameStyle(6);
    label_tip2->setFrameStyle(6);
    label_tip1->setFrameStyle(6);



    edit_reactionTubeCapacity = new QLineEdit();//反应管容量
    edit_bufferWasteCapacity = new QLineEdit();//废液池容量
    edit_washingLiquidCapacity = new QLineEdit();//洗涤液容量
    edit_reagent3Capacity = new QLineEdit();//试剂3容量
    edit_magneticBeadsCapacity = new QLineEdit();//磁珠容量
    edit_reagent2Capacity = new QLineEdit();//试剂2容量
    edit_reagent1Capacity = new QLineEdit();//试剂1容量
    edit_substrateSolutionCapacity = new QLineEdit();//底物液容量
    edit_reactionTube2Capacity = new QLineEdit();//反应管2容量
    edit_tip2Capacity = new QLineEdit(); //tp2容量
    edit_tip1Capacity = new QLineEdit(); //tp1容量



    edit_reactionTubePosition = new QLineEdit();//反应管位置
    edit_bufferWastePosition = new QLineEdit();//废液池位置
    edit_washingLiquidPosition = new QLineEdit();//洗涤液位置
    edit_reagent3Position = new QLineEdit();//试剂3位置
    edit_magneticBeadsPosition = new QLineEdit();//磁珠位置
    edit_reagent2Position = new QLineEdit();//试剂2位置
    edit_reagent1Position = new QLineEdit();//试剂1位置
    edit_substrateSolutionPosition = new QLineEdit();//位置
    edit_reactionTube2Position = new QLineEdit();//反应管2位置
    edit_tip2Position = new QLineEdit(); //tp2位置
    edit_tip1Position = new QLineEdit(); //tp1位置

    layout_name->addWidget(label_name);
    layout_name->addWidget(label_reactionTube);
    layout_name->addWidget(label_bufferWaste);
    layout_name->addWidget(label_washingLiquid);
    layout_name->addWidget(label_reagent3);
    layout_name->addWidget(label_magneticBeads);
    layout_name->addWidget(label_reagent2);
    layout_name->addWidget(label_reagent1);
    layout_name->addWidget(label_substrateSolution);
    layout_name->addWidget(label_reactionTube2);
    layout_name->addWidget(label_tip2);
    layout_name->addWidget(label_tip1);

    layout_position->addWidget(label_positionName);
    layout_position->addWidget(edit_reactionTubePosition);
    layout_position->addWidget(edit_bufferWastePosition);
    layout_position->addWidget(edit_washingLiquidPosition);
    layout_position->addWidget(edit_reagent3Position);
    layout_position->addWidget(edit_magneticBeadsPosition);
    layout_position->addWidget(edit_reagent2Position);
    layout_position->addWidget(edit_reagent1Position);
    layout_position->addWidget(edit_substrateSolutionPosition);
    layout_position->addWidget(edit_reactionTube2Position);
    layout_position->addWidget(edit_tip2Position);
    layout_position->addWidget(edit_tip1Position);

    layout_capacity->addWidget(label_capacityName);
    layout_capacity->addWidget(edit_reactionTubeCapacity);
    layout_capacity->addWidget(edit_bufferWasteCapacity);
    layout_capacity->addWidget(edit_washingLiquidCapacity);
    layout_capacity->addWidget(edit_reagent3Capacity);
    layout_capacity->addWidget(edit_magneticBeadsCapacity);
    layout_capacity->addWidget(edit_reagent2Capacity);
    layout_capacity->addWidget(edit_reagent1Capacity);
    layout_capacity->addWidget(edit_substrateSolutionCapacity);
    layout_capacity->addWidget(edit_reactionTube2Capacity);
    layout_capacity->addWidget(edit_tip2Capacity);
    layout_capacity->addWidget(edit_tip1Capacity);

    layout_infoEditor->addLayout(layout_name);
    layout_infoEditor->addLayout(layout_position);
    layout_infoEditor->addLayout(layout_capacity);

    layout_infoEdit->addWidget(label_infoEditName);
    layout_infoEdit->addLayout(layout_infoEditor);


    /*
     * 添加步骤区域
     */
    step1 = new Operation_step();
    Operation_step *step2 = new Operation_step();
    step2->label_step->setText("步骤2:");







    /*
     * 详细步骤区域
     */
    layout_detailSteps->addLayout(layout_btn);
    layout_detailSteps->addLayout(layout_fileInfo);
    layout_detailSteps->addLayout(layout_currentWorkPhase);
    layout_detailSteps->addLayout(layout_infoEdit);
    layout_detailSteps->addWidget(step1);
    layout_detailSteps->addWidget(step2);


    /*
     * 主布局
     */

    mainLayout->addWidget(label_editor);
    mainLayout->addLayout(layout_editor);
    mainLayout->addWidget(label_detailSteps);
    mainLayout->addLayout(layout_detailSteps);

}
