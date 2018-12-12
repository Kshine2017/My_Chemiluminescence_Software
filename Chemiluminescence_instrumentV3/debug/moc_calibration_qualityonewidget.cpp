/****************************************************************************
** Meta object code from reading C++ file 'calibration_qualityonewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../calibrationWidget/calibration_qualityonewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calibration_qualityonewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_calibration_qualityOneWidget_t {
    QByteArrayData data[8];
    char stringdata0[104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_calibration_qualityOneWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_calibration_qualityOneWidget_t qt_meta_stringdata_calibration_qualityOneWidget = {
    {
QT_MOC_LITERAL(0, 0, 28), // "calibration_qualityOneWidget"
QT_MOC_LITERAL(1, 29, 15), // "returnBtnSignal"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 3), // "num"
QT_MOC_LITERAL(4, 50, 14), // "disPlayBtnSlot"
QT_MOC_LITERAL(5, 65, 12), // "printBtnSlot"
QT_MOC_LITERAL(6, 78, 11), // "saveBtnSLot"
QT_MOC_LITERAL(7, 90, 13) // "returnBtnSlot"

    },
    "calibration_qualityOneWidget\0"
    "returnBtnSignal\0\0num\0disPlayBtnSlot\0"
    "printBtnSlot\0saveBtnSLot\0returnBtnSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_calibration_qualityOneWidget[] = {

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
       6,    0,   44,    2, 0x0a /* Public */,
       7,    0,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void calibration_qualityOneWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        calibration_qualityOneWidget *_t = static_cast<calibration_qualityOneWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->returnBtnSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->disPlayBtnSlot(); break;
        case 2: _t->printBtnSlot(); break;
        case 3: _t->saveBtnSLot(); break;
        case 4: _t->returnBtnSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (calibration_qualityOneWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&calibration_qualityOneWidget::returnBtnSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject calibration_qualityOneWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_calibration_qualityOneWidget.data,
      qt_meta_data_calibration_qualityOneWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *calibration_qualityOneWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *calibration_qualityOneWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_calibration_qualityOneWidget.stringdata0))
        return static_cast<void*>(const_cast< calibration_qualityOneWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int calibration_qualityOneWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void calibration_qualityOneWidget::returnBtnSignal(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
