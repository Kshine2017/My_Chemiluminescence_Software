/****************************************************************************
** Meta object code from reading C++ file 'reagentnumber.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../systemWidget/reagentNumber/reagentnumber.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'reagentnumber.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_reagentNumber_t {
    QByteArrayData data[13];
    char stringdata0[180];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_reagentNumber_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_reagentNumber_t qt_meta_stringdata_reagentNumber = {
    {
QT_MOC_LITERAL(0, 0, 13), // "reagentNumber"
QT_MOC_LITERAL(1, 14, 11), // "btn_addSlot"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 14), // "btn_updateSlot"
QT_MOC_LITERAL(4, 42, 14), // "btn_deleteSlot"
QT_MOC_LITERAL(5, 57, 13), // "btn_querySlot"
QT_MOC_LITERAL(6, 71, 11), // "fresh_table"
QT_MOC_LITERAL(7, 83, 18), // "fresh_table_select"
QT_MOC_LITERAL(8, 102, 12), // "str_category"
QT_MOC_LITERAL(9, 115, 15), // "str_projectName"
QT_MOC_LITERAL(10, 131, 15), // "str_reagentType"
QT_MOC_LITERAL(11, 147, 26), // "slot_doubleclick_tableview"
QT_MOC_LITERAL(12, 174, 5) // "index"

    },
    "reagentNumber\0btn_addSlot\0\0btn_updateSlot\0"
    "btn_deleteSlot\0btn_querySlot\0fresh_table\0"
    "fresh_table_select\0str_category\0"
    "str_projectName\0str_reagentType\0"
    "slot_doubleclick_tableview\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_reagentNumber[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    3,   54,    2, 0x0a /* Public */,
      11,    1,   61,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    8,    9,   10,
    QMetaType::Void, QMetaType::QModelIndex,   12,

       0        // eod
};

void reagentNumber::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        reagentNumber *_t = static_cast<reagentNumber *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->btn_addSlot(); break;
        case 1: _t->btn_updateSlot(); break;
        case 2: _t->btn_deleteSlot(); break;
        case 3: _t->btn_querySlot(); break;
        case 4: _t->fresh_table(); break;
        case 5: _t->fresh_table_select((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 6: _t->slot_doubleclick_tableview((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject reagentNumber::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_reagentNumber.data,
      qt_meta_data_reagentNumber,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *reagentNumber::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *reagentNumber::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_reagentNumber.stringdata0))
        return static_cast<void*>(const_cast< reagentNumber*>(this));
    return QWidget::qt_metacast(_clname);
}

int reagentNumber::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
