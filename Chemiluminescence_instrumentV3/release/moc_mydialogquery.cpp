/****************************************************************************
** Meta object code from reading C++ file 'mydialogquery.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../systemWidget/userManage/mydialogquery.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mydialogquery.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MyDialogQuery_t {
    QByteArrayData data[5];
    char stringdata0[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyDialogQuery_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyDialogQuery_t qt_meta_stringdata_MyDialogQuery = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MyDialogQuery"
QT_MOC_LITERAL(1, 14, 25), // "siganl_please_fresh_table"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 14), // "btn_cancelSlot"
QT_MOC_LITERAL(4, 56, 11) // "btn_addSlot"

    },
    "MyDialogQuery\0siganl_please_fresh_table\0"
    "\0btn_cancelSlot\0btn_addSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyDialogQuery[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyDialogQuery::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyDialogQuery *_t = static_cast<MyDialogQuery *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->siganl_please_fresh_table(); break;
        case 1: _t->btn_cancelSlot(); break;
        case 2: _t->btn_addSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MyDialogQuery::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyDialogQuery::siganl_please_fresh_table)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MyDialogQuery::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MyDialogQuery.data,
      qt_meta_data_MyDialogQuery,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MyDialogQuery::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyDialogQuery::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MyDialogQuery.stringdata0))
        return static_cast<void*>(const_cast< MyDialogQuery*>(this));
    return QDialog::qt_metacast(_clname);
}

int MyDialogQuery::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MyDialogQuery::siganl_please_fresh_table()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
