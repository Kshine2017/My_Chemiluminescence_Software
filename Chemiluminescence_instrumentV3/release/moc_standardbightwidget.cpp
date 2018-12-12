/****************************************************************************
** Meta object code from reading C++ file 'standardbightwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../standardBightWidget/standardbightwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'standardbightwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_standardBightWidget_t {
    QByteArrayData data[15];
    char stringdata0[206];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_standardBightWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_standardBightWidget_t qt_meta_stringdata_standardBightWidget = {
    {
QT_MOC_LITERAL(0, 0, 19), // "standardBightWidget"
QT_MOC_LITERAL(1, 20, 10), // "quitOkSign"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 11), // "saveBtnSlot"
QT_MOC_LITERAL(4, 44, 11), // "quitBtnSlot"
QT_MOC_LITERAL(5, 56, 11), // "createCurve"
QT_MOC_LITERAL(6, 68, 16), // "checkBoxBtn1Slot"
QT_MOC_LITERAL(7, 85, 5), // "state"
QT_MOC_LITERAL(8, 91, 16), // "checkBoxBtn2Slot"
QT_MOC_LITERAL(9, 108, 16), // "checkBoxBtn3Slot"
QT_MOC_LITERAL(10, 125, 16), // "checkBoxBtn4Slot"
QT_MOC_LITERAL(11, 142, 16), // "checkBoxBtn5Slot"
QT_MOC_LITERAL(12, 159, 16), // "checkBoxBtn6Slot"
QT_MOC_LITERAL(13, 176, 16), // "checkBoxBtn7Slot"
QT_MOC_LITERAL(14, 193, 12) // "radioBtnSlot"

    },
    "standardBightWidget\0quitOkSign\0\0"
    "saveBtnSlot\0quitBtnSlot\0createCurve\0"
    "checkBoxBtn1Slot\0state\0checkBoxBtn2Slot\0"
    "checkBoxBtn3Slot\0checkBoxBtn4Slot\0"
    "checkBoxBtn5Slot\0checkBoxBtn6Slot\0"
    "checkBoxBtn7Slot\0radioBtnSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_standardBightWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   75,    2, 0x0a /* Public */,
       4,    0,   76,    2, 0x0a /* Public */,
       5,    0,   77,    2, 0x0a /* Public */,
       6,    1,   78,    2, 0x0a /* Public */,
       8,    1,   81,    2, 0x0a /* Public */,
       9,    1,   84,    2, 0x0a /* Public */,
      10,    1,   87,    2, 0x0a /* Public */,
      11,    1,   90,    2, 0x0a /* Public */,
      12,    1,   93,    2, 0x0a /* Public */,
      13,    1,   96,    2, 0x0a /* Public */,
      14,    0,   99,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,

       0        // eod
};

void standardBightWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        standardBightWidget *_t = static_cast<standardBightWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->quitOkSign(); break;
        case 1: _t->saveBtnSlot(); break;
        case 2: _t->quitBtnSlot(); break;
        case 3: _t->createCurve(); break;
        case 4: _t->checkBoxBtn1Slot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->checkBoxBtn2Slot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->checkBoxBtn3Slot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->checkBoxBtn4Slot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->checkBoxBtn5Slot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->checkBoxBtn6Slot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->checkBoxBtn7Slot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->radioBtnSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (standardBightWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&standardBightWidget::quitOkSign)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject standardBightWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_standardBightWidget.data,
      qt_meta_data_standardBightWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *standardBightWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *standardBightWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_standardBightWidget.stringdata0))
        return static_cast<void*>(const_cast< standardBightWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int standardBightWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void standardBightWidget::quitOkSign()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
