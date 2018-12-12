/****************************************************************************
** Meta object code from reading C++ file 'standardtest_onewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../standardTestWidget/standardtest_onewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'standardtest_onewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_standardTest_OneWidget_t {
    QByteArrayData data[9];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_standardTest_OneWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_standardTest_OneWidget_t qt_meta_stringdata_standardTest_OneWidget = {
    {
QT_MOC_LITERAL(0, 0, 22), // "standardTest_OneWidget"
QT_MOC_LITERAL(1, 23, 16), // "nextBtnPressSign"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 13), // "returnBtnSlot"
QT_MOC_LITERAL(4, 55, 18), // "finsh_placeBtnSlot"
QT_MOC_LITERAL(5, 74, 11), // "nextBtnSlot"
QT_MOC_LITERAL(6, 86, 17), // "okBtnDelegateSlot"
QT_MOC_LITERAL(7, 104, 5), // "index"
QT_MOC_LITERAL(8, 110, 18) // "queryTimerOverSlot"

    },
    "standardTest_OneWidget\0nextBtnPressSign\0"
    "\0returnBtnSlot\0finsh_placeBtnSlot\0"
    "nextBtnSlot\0okBtnDelegateSlot\0index\0"
    "queryTimerOverSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_standardTest_OneWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    1,   48,    2, 0x0a /* Public */,
       8,    0,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void,

       0        // eod
};

void standardTest_OneWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        standardTest_OneWidget *_t = static_cast<standardTest_OneWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->nextBtnPressSign(); break;
        case 1: _t->returnBtnSlot(); break;
        case 2: _t->finsh_placeBtnSlot(); break;
        case 3: _t->nextBtnSlot(); break;
        case 4: _t->okBtnDelegateSlot((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->queryTimerOverSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (standardTest_OneWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&standardTest_OneWidget::nextBtnPressSign)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject standardTest_OneWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_standardTest_OneWidget.data,
      qt_meta_data_standardTest_OneWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *standardTest_OneWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *standardTest_OneWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_standardTest_OneWidget.stringdata0))
        return static_cast<void*>(const_cast< standardTest_OneWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int standardTest_OneWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void standardTest_OneWidget::nextBtnPressSign()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
