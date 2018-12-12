/****************************************************************************
** Meta object code from reading C++ file 'standbight_controlwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../standardBightWidget/standbight_controlwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'standbight_controlwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_standBight_controlWidget_t {
    QByteArrayData data[10];
    char stringdata0[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_standBight_controlWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_standBight_controlWidget_t qt_meta_stringdata_standBight_controlWidget = {
    {
QT_MOC_LITERAL(0, 0, 24), // "standBight_controlWidget"
QT_MOC_LITERAL(1, 25, 15), // "initReagentType"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 14), // "strProjectName"
QT_MOC_LITERAL(4, 57, 13), // "initLotNumber"
QT_MOC_LITERAL(5, 71, 3), // "str"
QT_MOC_LITERAL(6, 75, 4), // "date"
QT_MOC_LITERAL(7, 80, 17), // "resetBightBtnSlot"
QT_MOC_LITERAL(8, 98, 22), // "currentTextChangedSlot"
QT_MOC_LITERAL(9, 121, 4) // "text"

    },
    "standBight_controlWidget\0initReagentType\0"
    "\0strProjectName\0initLotNumber\0str\0"
    "date\0resetBightBtnSlot\0currentTextChangedSlot\0"
    "text"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_standBight_controlWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       4,    1,   42,    2, 0x0a /* Public */,
       4,    1,   45,    2, 0x0a /* Public */,
       7,    0,   48,    2, 0x0a /* Public */,
       8,    1,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QDate,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void standBight_controlWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        standBight_controlWidget *_t = static_cast<standBight_controlWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initReagentType((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->initLotNumber((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->initLotNumber((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 3: _t->resetBightBtnSlot(); break;
        case 4: _t->currentTextChangedSlot((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject standBight_controlWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_standBight_controlWidget.data,
      qt_meta_data_standBight_controlWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *standBight_controlWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *standBight_controlWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_standBight_controlWidget.stringdata0))
        return static_cast<void*>(const_cast< standBight_controlWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int standBight_controlWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
