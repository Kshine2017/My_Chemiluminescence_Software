#-------------------------------------------------
#
# Project created by QtCreator 2017-08-17T10:39:05
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += serialport
QT       += printsupport
CONFIG   += qaxcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chemiluminescence_instrument
TEMPLATE = app


SOURCES += main.cpp\
        login\login.cpp \
    login\register.cpp \
    mainwindow.cpp \
    unknownWidget\unkownwidget.cpp \
    Serial_port/serialport.cpp \
    serical_thread/serial_thread.cpp \
    calibrationWidget/calibrationwidget.cpp \
    SelfTestWidget/selftestwidget.cpp \
    queryWidget/querywidget.cpp \
    standardProgrameWidget/standardpragramewidget.cpp \
    systemWidget/systemwidget.cpp \
    standardBightWidget/standardbightwidget.cpp \
    unknownWidget/statuswidget.cpp \
    unknownWidget/infowidget.cpp \
    standardProgrameWidget/reagentdisplay.cpp \
    standardProgrameWidget/reagentprowidget.cpp \
    unknownWidget/check_namedelegate.cpp \
    unknownWidget/serial_numdelegate.cpp \
    unknownWidget/progress_bardelegate.cpp \
    unknownWidget/start_pushbuttondelegate.cpp \
    unknownWidget/okbtn_delegate.cpp \
    QMessgeBox/mymessgebox.cpp \
    calibrationWidget/calibration_onewidget.cpp \
    calibrationWidget/calibration_twowidget.cpp \
    calibrationWidget/calibration_progressbardelegate.cpp \
    calibrationWidget/calibration_qcomboxdelegate.cpp \
    calibrationWidget/calibration_okbtndelegate.cpp \
    standardTestWidget/standardtest_okbtndelegate.cpp \
    standardTestWidget/standardtest_onewidget.cpp \
    standardTestWidget/standardtest_twowidget.cpp \
    standardTestWidget/standardtestwidget.cpp \
    standardTestWidget/standtest_progressdelegate.cpp \
    standardTestWidget/standtest_checkboxdelegate.cpp \
    standardBightWidget/standbight_controlwidget.cpp \
    standardBightWidget/standardbight_drawewidget.cpp \
    standardProgrameWidget/standardprograme_actionpro.cpp \
    standardProgrameWidget/standardprograme_addbtndelegate.cpp \
    standardProgrameWidget/standardprograme_minusdelegate.cpp \
    standardProgrameWidget/standardprograme_actioncheckdelegate.cpp \
    standardProgrameWidget/standardprograme_startpostiondelegate.cpp \
    standardProgrameWidget/standardprograme_endpostiondelegate.cpp \
    standardProgrameWidget/standardprograme_beforecountdelegate.cpp \
    standardProgrameWidget/standardprograme_aftercountdelegate.cpp \
    standardProgrameWidget/standardpragrame_runbtndelegate.cpp \
    manul_book/manul_bookwidget.cpp \
    QMessgeBox/mycheckmessagebox.cpp \
    calibrationWidget/calibration_calionewidget.cpp \
    calibrationWidget/calibration_qualityonewidget.cpp \
    queryWidget/historysearch.cpp \
    queryWidget/qualitydataquery.cpp \
    SelfTestWidget/myheaderview.cpp \
    SelfTestWidget/selfteststep.cpp \
    systemWidget/qmysqlquerymodel.cpp \
    systemWidget/clinicalDiagnosis/clinicaldiagnosis.cpp \
    systemWidget/clinicalDiagnosis/dialogadddepartment.cpp \
    systemWidget/clinicalDiagnosis/dialogadddiagnosticcategory.cpp \
    systemWidget/faultDiagnosis/faultdiagnosis.cpp \
    systemWidget/systemMaintenance/systemmaintenance.cpp \
    systemWidget/userManage/ordinaryusermanagement.cpp \
    systemWidget/userManage/userinformation.cpp \
    systemWidget/userManage/usermanagement.cpp \
    standardBightWidget/cruvegeneration.cpp \
    standardBightWidget/qcustomplot.cpp \
    queue/queue.cpp \
    SelfTestWidget/QRoundProgressBar.cpp \
    standardProgrameWidget/workprogressarea.cpp \
    menu/temperatureplot.cpp \
    calibrationWidget/displaycruve.cpp \
    stndog.cpp \
    systemWidget/userManage/adminitratormanagement.cpp \
    systemWidget/userManage/mydialogadd.cpp \
    systemWidget/userManage/adddelupdsel.cpp \
    systemWidget/userManage/mydialogupdate.cpp \
    systemWidget/userManage/mydialogquery.cpp \
    standardProgrameWidget/standardpragrame_checkboxdelegate.cpp \
    standardProgrameWidget/dataopration.cpp \
    standardTestWidget/dataopationstandardtest.cpp \
    data/configfile.cpp \
    standardProgrameWidget/exportimportexcel.cpp \
    standardProgrameWidget/standardprogrameinfodialog.cpp \
    menu/qwaitdialog.cpp \
    SelfTestWidget/myroundprogressbar.cpp \
    standardBightWidget/fourParameterLogistic/CouveFitter.cpp \
    standardBightWidget/fourParameterLogistic/logistic.cpp \
    standardBightWidget/polynomial/duoxiangshi.cpp \
    standardBightWidget/LogLinearFit/linnear_fit.cpp \
    standardBightWidget/LogLogistic/lr.cpp \
    systemWidget/reagentNumber/reagentnumber.cpp \
    systemWidget/reagentNumber/myreagentdialogadd.cpp \
    systemWidget/reagentNumber/myreagentdialogupdata.cpp \
    systemWidget/reagentNumber/databaseoperation.cpp \
    systemWidget/reagentNumber/myreagentdialogquery.cpp


HEADERS  += login\login.h \
    connection.h \
    login\register.h \
    mainwindow.h \
    unknownWidget\unkownwidget.h \
    login/login.h \
    Serial_port/serialport.h \
    serical_thread/serial_thread.h \
    calibrationWidget/calibrationwidget.h \
    SelfTestWidget/selftestwidget.h \
    queryWidget/querywidget.h \
    standardProgrameWidget/standardpragramewidget.h \
    systemWidget/systemwidget.h \
    standardBightWidget/standardbightwidget.h \
    data/connection.h \
    unknownWidget/statuswidget.h \
    unknownWidget/infowidget.h \
    standardProgrameWidget/reagentdisplay.h \
    standardProgrameWidget/reagentprowidget.h \
    unknownWidget/check_namedelegate.h \
    unknownWidget/serial_numdelegate.h \
    unknownWidget/progress_bardelegate.h \
    unknownWidget/start_pushbuttondelegate.h \
    unknownWidget/okbtn_delegate.h \
    QMessgeBox/mymessgebox.h \
    calibrationWidget/calibration_onewidget.h \
    calibrationWidget/calibration_twowidget.h \
    calibrationWidget/calibration_progressbardelegate.h \
    calibrationWidget/calibration_qcomboxdelegate.h \
    calibrationWidget/calibration_okbtndelegate.h \
    standardTestWidget/standardtest_okbtndelegate.h \
    standardTestWidget/standardtest_onewidget.h \
    standardTestWidget/standardtest_twowidget.h \
    standardTestWidget/standardtestwidget.h \
    standardTestWidget/standtest_progressdelegate.h \
    standardTestWidget/standtest_checkboxdelegate.h \
    standardBightWidget/standbight_controlwidget.h \
    standardBightWidget/standardbight_drawewidget.h \
    standardProgrameWidget/standardprograme_actionpro.h \
    standardProgrameWidget/standardprograme_addbtndelegate.h \
    standardProgrameWidget/standardprograme_minusdelegate.h \
    standardProgrameWidget/standardprograme_actioncheckdelegate.h \
    standardProgrameWidget/standardprograme_startpostiondelegate.h \
    standardProgrameWidget/standardprograme_endpostiondelegate.h \
    standardProgrameWidget/standardprograme_beforecountdelegate.h \
    standardProgrameWidget/standardprograme_aftercountdelegate.h \
    standardProgrameWidget/standardpragrame_runbtndelegate.h \
    manul_book/manul_bookwidget.h \
    QMessgeBox/mycheckmessagebox.h \
    calibrationWidget/calibration_calionewidget.h \
    calibrationWidget/calibration_qualityonewidget.h \
    queryWidget/historysearch.h \
    queryWidget/qualitydataquery.h \
    SelfTestWidget/myheaderview.h \
    SelfTestWidget/selfteststep.h \
    systemWidget/qmysqlquerymodel.h \
    systemWidget/clinicalDiagnosis/clinicaldiagnosis.h \
    systemWidget/clinicalDiagnosis/dialogadddepartment.h \
    systemWidget/clinicalDiagnosis/dialogadddiagnosticcategory.h \
    systemWidget/faultDiagnosis/faultdiagnosis.h \
    systemWidget/systemMaintenance/systemmaintenance.h \
    systemWidget/userManage/ordinaryusermanagement.h \
    systemWidget/userManage/userinformation.h \
    systemWidget/userManage/usermanagement.h \
    standardBightWidget/cruvegeneration.h \
    standardBightWidget/qcustomplot.h \
    data/util.h \
    queue/queue.h \
    SelfTestWidget/QRoundProgressBar.h \
    standardProgrameWidget/workprogressarea.h \
    menu/temperatureplot.h \
    calibrationWidget/displaycruve.h \
    stndog.h \
    systemWidget/userManage/adminitratormanagement.h \
    systemWidget/userManage/mydialogadd.h \
    systemWidget/userManage/adddelupdsel.h \
    systemWidget/userManage/mydialogupdate.h \
    systemWidget/userManage/mydialogquery.h \
    standardProgrameWidget/standardpragrame_checkboxdelegate.h \
    standardProgrameWidget/dataopration.h \
    standardTestWidget/dataopationstandardtest.h \
    data/configfile.h \
    standardProgrameWidget/exportimportexcel.h \
    standardProgrameWidget/standardprogrameinfodialog.h \
    menu/qwaitdialog.h \
    SelfTestWidget/myroundprogressbar.h \
    standardBightWidget/fourParameterLogistic/CouveFitter.h \
    standardBightWidget/fourParameterLogistic/logistic.h \
    standardBightWidget/polynomial/duoxiangshi.h \
    standardBightWidget/LogLinearFit/linnear_fit.h \
    standardBightWidget/LogLogistic/lr.h \
    systemWidget/reagentNumber/reagentnumber.h \
    systemWidget/reagentNumber/myreagentdialogadd.h \
    systemWidget/reagentNumber/myreagentdialogupdata.h \
    systemWidget/reagentNumber/databaseoperation.h \
    systemWidget/reagentNumber/myreagentdialogquery.h

FORMS +=

RESOURCES += \
    icon.qrc

DISTFILES +=

#LIBS += "./lib/hasp_windows_106373.a"
