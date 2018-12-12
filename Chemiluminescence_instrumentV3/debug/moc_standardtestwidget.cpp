/****************************************************************************
** Meta object code from reading C++ file 'standardtestwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../standardTestWidget/standardtestwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'standardtestwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_standardTestWidget_t {
    QByteArrayData data[7];
    char stringdata0[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_standardTestWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_standardTestWidget_t qt_meta_stringdata_standardTestWidget = {
    {
QT_MOC_LITERAL(0, 0, 18), // "standardTestWidget"
QT_MOC_LITERAL(1, 19, 16), // "twoReturnBtnSlot"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 16), // "SaveBtnPressSlot"
QT_MOC_LITERAL(4, 54, 16), // "nextBtnPressSlot"
QT_MOC_LITERAL(5, 71, 24), // "standardTest_cmdSignSlot"
QT_MOC_LITERAL(6, 96, 3) // "str"

    },
    "standardTestWidget\0twoReturnBtnSlot\0"
    "\0SaveBtnPressSlot\0nextBtnPressSlot\0"
    "standardTest_cmdSignSlot\0str"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_standardTestWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    0,   36,    2, 0x0a /* Public */,
       5,    1,   37,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,

       0        // eod
};

void standardTestWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        standardTestWidget *_t = static_cast<standardTestWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->twoReturnBtnSlot(); break;
        case 1: _t->SaveBtnPressSlot(); break;
        case 2: _t->nextBtnPressSlot(); break;
        case 3: _t->standardTest_cmdSignSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject standardTestWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_standardTestWidget.data,
      qt_meta_data_standardTestWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *standardTestWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *standardTestWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_standardTestWidget.stringdata0))
        return static_cast<void*>(const_cast< standardTestWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int standardTestWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
