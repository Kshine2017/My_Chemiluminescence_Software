/****************************************************************************
** Meta object code from reading C++ file 'calibration_onewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../calibrationWidget/calibration_onewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calibration_onewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_calibration_oneWidget_t {
    QByteArrayData data[8];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_calibration_oneWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_calibration_oneWidget_t qt_meta_stringdata_calibration_oneWidget = {
    {
QT_MOC_LITERAL(0, 0, 21), // "calibration_oneWidget"
QT_MOC_LITERAL(1, 22, 22), // "measurementFinshSignal"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 3), // "num"
QT_MOC_LITERAL(4, 50, 18), // "finishPlaceBtnSlot"
QT_MOC_LITERAL(5, 69, 11), // "nextBtnSlot"
QT_MOC_LITERAL(6, 81, 15), // "Display_btnSlot"
QT_MOC_LITERAL(7, 97, 30) // "calibration_queryTimerOverSlot"

    },
    "calibration_oneWidget\0measurementFinshSignal\0"
    "\0num\0finishPlaceBtnSlot\0nextBtnSlot\0"
    "Display_btnSlot\0calibration_queryTimerOverSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_calibration_oneWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   42,    2, 0x0a /* Public */,
       5,    0,   43,    2, 0x0a /* Public */,
       6,    1,   44,    2, 0x0a /* Public */,
       7,    0,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void,

       0        // eod
};

void calibration_oneWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        calibration_oneWidget *_t = static_cast<calibration_oneWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->measurementFinshSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->finishPlaceBtnSlot(); break;
        case 2: _t->nextBtnSlot(); break;
        case 3: _t->Display_btnSlot((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->calibration_queryTimerOverSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (calibration_oneWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&calibration_oneWidget::measurementFinshSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject calibration_oneWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_calibration_oneWidget.data,
      qt_meta_data_calibration_oneWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *calibration_oneWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *calibration_oneWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_calibration_oneWidget.stringdata0))
        return static_cast<void*>(const_cast< calibration_oneWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int calibration_oneWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void calibration_oneWidget::measurementFinshSignal(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
