#ifndef REAGENTVESSELEDITOR_H
#define REAGENTVESSELEDITOR_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QProgressBar>
#include <operation_step.h>

class ReagentVesselEditor : public QWidget
{
    Q_OBJECT
public:
    explicit ReagentVesselEditor(QWidget *parent = 0);
private:
    QLabel *label_editor;//编辑标签
    QLabel *label_detailSteps;//详细步骤标签
    QVBoxLayout *mainLayout;
    QHBoxLayout *layout_editor;
    QVBoxLayout *layout_detailSteps;

    QLabel *label_pit;//放图片
    QVBoxLayout *layout_grooves1;//槽布局1
    QVBoxLayout *layout_grooves2;//槽布局2
    QLabel *label_groove1;//槽1
    QLabel *label_groove2;//槽2
    QLabel *label_groove3;//槽3
    QLabel *label_groove4;//槽4
    QLabel *label_groove5;//槽5
    QLabel *label_groove6;//槽6
    QLabel *label_groove7;//槽7
    QLabel *label_groove8;//槽8
    QLabel *label_groove9;//槽9
    QLabel *label_groove10;//槽10
    QLabel *label_groove11;//槽11
    QLabel *label_groove12;//槽12

    QLabel *label_groove13;//槽13
    QLabel *label_groove14;//槽14

    //按钮
    QHBoxLayout *layout_btn;
    QPushButton *btn_start;
    QPushButton *btn_pause;
    QPushButton *btn_continue;
    QPushButton *btn_stop;
    QPushButton *btn_cancel;
    QPushButton *btn_next;

    //文件信息
    QHBoxLayout *layout_fileInfo;
    QLabel *label_fileName;//文件名
    QLineEdit *edit_fileName;//文件名输入
    QLabel *label_fileNameAbbreviation;//文件名简写
    QLineEdit *edit_fileNameAbbreviation;//文件名简写输入
    QLabel *label_barcode;//条码图像
    QLabel *label_barcodeImage;//存放条码图片
    QLabel *label_startTime;//开始使用时间
    QLineEdit *edit_startTime;
    QLabel *label_endTime;//结束使用时间
    QLineEdit *edit_endTime;

    //当前工作布局
    QHBoxLayout *layout_currentWorkPhase;
    QVBoxLayout *layout_currentWork;
    QVBoxLayout *layout_progress;
    QVBoxLayout *layout_startTime;
    QVBoxLayout *layout_endTime;

    QLabel *label_currentWork;
    QLabel *label_currentWorkName;

    QLabel *label_progress;
    QProgressBar *progressBar;

    QLabel *label_workStartTime;
    QLabel *label_workStartTimeShow;

    QLabel *label_workEndTime;
    QLabel *label_workEndTimeShow;

    //编辑区域
    QHBoxLayout *layout_infoEdit;//编辑区域
    QVBoxLayout *layout_infoEditor;
    QHBoxLayout *layout_name;//名字区域
    QHBoxLayout *layout_position;//位置区域
    QHBoxLayout *layout_capacity;//容量区域

    QLabel *label_infoEditName;
    QLabel *label_name;
    QLabel *label_positionName;//位置
    QLabel *label_capacityName;//容量

    QLabel *label_reactionTube;//反应管
    QLabel *label_bufferWaste;//废液池
    QLabel *label_washingLiquid;//洗涤液
    QLabel *label_reagent3;//试剂3
    QLabel *label_magneticBeads;//磁珠
    QLabel *label_reagent2;//试剂2
    QLabel *label_reagent1;//试剂1
    QLabel *label_substrateSolution;//底物液
    QLabel *label_reactionTube2;//反应管2
    QLabel *label_tip2; //tp2
    QLabel *label_tip1; //tp1

    QLineEdit *edit_reactionTubeCapacity;//反应管容量
    QLineEdit *edit_bufferWasteCapacity;//废液池容量
    QLineEdit *edit_washingLiquidCapacity;//洗涤液容量
    QLineEdit *edit_reagent3Capacity;//试剂3容量
    QLineEdit *edit_magneticBeadsCapacity;//磁珠容量
    QLineEdit *edit_reagent2Capacity;//试剂2容量
    QLineEdit *edit_reagent1Capacity;//试剂1容量
    QLineEdit *edit_substrateSolutionCapacity;//底物液容量
    QLineEdit *edit_reactionTube2Capacity;//反应管2容量
    QLineEdit *edit_tip2Capacity; //tp2容量
    QLineEdit *edit_tip1Capacity; //tp1容量

    QLineEdit *edit_reactionTubePosition;//反应管位置
    QLineEdit *edit_bufferWastePosition;//废液池位置
    QLineEdit *edit_washingLiquidPosition;//洗涤液位置
    QLineEdit *edit_reagent3Position;//试剂3位置
    QLineEdit *edit_magneticBeadsPosition;//磁珠位置
    QLineEdit *edit_reagent2Position;//试剂2位置
    QLineEdit *edit_reagent1Position;//试剂1位置
    QLineEdit *edit_substrateSolutionPosition;//位置
    QLineEdit *edit_reactionTube2Position;//反应管2位置
    QLineEdit *edit_tip2Position; //tp2位置
    QLineEdit *edit_tip1Position; //tp1位置

    /*
     * 添加步骤区域
     */
    Operation_step *step1;


signals:

public slots:
};

#endif // REAGENTVESSELEDITOR_H
