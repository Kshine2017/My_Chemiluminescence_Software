/****************************************************************************
** Meta object code from reading C++ file 'selftestwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SelfTestWidget/selftestwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'selftestwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_selfTestWidget_t {
    QByteArrayData data[14];
    char stringdata0[169];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_selfTestWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_selfTestWidget_t qt_meta_stringdata_selfTestWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "selfTestWidget"
QT_MOC_LITERAL(1, 15, 12), // "getStepDatas"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 17), // "setAllCheckStatus"
QT_MOC_LITERAL(4, 47, 17), // "runSignalStepSlot"
QT_MOC_LITERAL(5, 65, 3), // "num"
QT_MOC_LITERAL(6, 69, 5), // "count"
QT_MOC_LITERAL(7, 75, 20), // "InquiryTimerOverSlot"
QT_MOC_LITERAL(8, 96, 17), // "self_Test_CMDSlot"
QT_MOC_LITERAL(9, 114, 3), // "str"
QT_MOC_LITERAL(10, 118, 12), // "startBtnSlot"
QT_MOC_LITERAL(11, 131, 11), // "stopBtnSlot"
QT_MOC_LITERAL(12, 143, 12), // "pauseBtnSlot"
QT_MOC_LITERAL(13, 156, 12) // "resetBtnSlot"

    },
    "selfTestWidget\0getStepDatas\0\0"
    "setAllCheckStatus\0runSignalStepSlot\0"
    "num\0count\0InquiryTimerOverSlot\0"
    "self_Test_CMDSlot\0str\0startBtnSlot\0"
    "stopBtnSlot\0pauseBtnSlot\0resetBtnSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_selfTestWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    1,   60,    2, 0x0a /* Public */,
       4,    2,   63,    2, 0x0a /* Public */,
       7,    0,   68,    2, 0x0a /* Public */,
       8,    1,   69,    2, 0x0a /* Public */,
      10,    0,   72,    2, 0x0a /* Public */,
      11,    0,   73,    2, 0x0a /* Public */,
      12,    0,   74,    2, 0x0a /* Public */,
      13,    0,   75,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void selfTestWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        selfTestWidget *_t = static_cast<selfTestWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getStepDatas(); break;
        case 1: _t->setAllCheckStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->runSignalStepSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->InquiryTimerOverSlot(); break;
        case 4: _t->self_Test_CMDSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->startBtnSlot(); break;
        case 6: _t->stopBtnSlot(); break;
        case 7: _t->pauseBtnSlot(); break;
        case 8: _t->resetBtnSlot(); break;
        default: ;
        }
    }
}

const QMetaObject selfTestWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_selfTestWidget.data,
      qt_meta_data_selfTestWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *selfTestWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *selfTestWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_selfTestWidget.stringdata0))
        return static_cast<void*>(const_cast< selfTestWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int selfTestWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
