/****************************************************************************
** Meta object code from reading C++ file 'myreagentdialogquery.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../systemWidget/reagentNumber/myreagentdialogquery.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myreagentdialogquery.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MyReagentDialogQuery_t {
    QByteArrayData data[14];
    char stringdata0[288];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyReagentDialogQuery_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyReagentDialogQuery_t qt_meta_stringdata_MyReagentDialogQuery = {
    {
QT_MOC_LITERAL(0, 0, 20), // "MyReagentDialogQuery"
QT_MOC_LITERAL(1, 21, 25), // "siganl_please_fresh_table"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 12), // "str_category"
QT_MOC_LITERAL(4, 61, 15), // "str_projectName"
QT_MOC_LITERAL(5, 77, 16), // "str_REAGENT_TYPE"
QT_MOC_LITERAL(6, 94, 14), // "btn_cancelSlot"
QT_MOC_LITERAL(7, 109, 11), // "btn_addSlot"
QT_MOC_LITERAL(8, 121, 28), // "slot_fresh_cBox_PROJECT_NAME"
QT_MOC_LITERAL(9, 150, 28), // "slot_fresh_cBox_REAGENT_TYPE"
QT_MOC_LITERAL(10, 179, 27), // "slot_fresh_le_CATEGORY_code"
QT_MOC_LITERAL(11, 207, 31), // "slot_fresh_le_PROJECT_NAME_code"
QT_MOC_LITERAL(12, 239, 16), // "str_PROJECT_NAME"
QT_MOC_LITERAL(13, 256, 31) // "slot_fresh_le_REAGENT_TYPE_code"

    },
    "MyReagentDialogQuery\0siganl_please_fresh_table\0"
    "\0str_category\0str_projectName\0"
    "str_REAGENT_TYPE\0btn_cancelSlot\0"
    "btn_addSlot\0slot_fresh_cBox_PROJECT_NAME\0"
    "slot_fresh_cBox_REAGENT_TYPE\0"
    "slot_fresh_le_CATEGORY_code\0"
    "slot_fresh_le_PROJECT_NAME_code\0"
    "str_PROJECT_NAME\0slot_fresh_le_REAGENT_TYPE_code"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyReagentDialogQuery[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   61,    2, 0x0a /* Public */,
       7,    0,   62,    2, 0x0a /* Public */,
       8,    1,   63,    2, 0x0a /* Public */,
       9,    1,   66,    2, 0x0a /* Public */,
      10,    1,   69,    2, 0x0a /* Public */,
      11,    1,   72,    2, 0x0a /* Public */,
      13,    1,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString,    5,

       0        // eod
};

void MyReagentDialogQuery::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyReagentDialogQuery *_t = static_cast<MyReagentDialogQuery *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->siganl_please_fresh_table((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: _t->btn_cancelSlot(); break;
        case 2: _t->btn_addSlot(); break;
        case 3: _t->slot_fresh_cBox_PROJECT_NAME((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->slot_fresh_cBox_REAGENT_TYPE((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->slot_fresh_le_CATEGORY_code((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->slot_fresh_le_PROJECT_NAME_code((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->slot_fresh_le_REAGENT_TYPE_code((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef int (MyReagentDialogQuery::*_t)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyReagentDialogQuery::siganl_please_fresh_table)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MyReagentDialogQuery::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MyReagentDialogQuery.data,
      qt_meta_data_MyReagentDialogQuery,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MyReagentDialogQuery::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyReagentDialogQuery::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MyReagentDialogQuery.stringdata0))
        return static_cast<void*>(const_cast< MyReagentDialogQuery*>(this));
    return QDialog::qt_metacast(_clname);
}

int MyReagentDialogQuery::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
int MyReagentDialogQuery::siganl_please_fresh_table(QString _t1, QString _t2, QString _t3)
{
    int _t0 = int();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}
QT_END_MOC_NAMESPACE
