/****************************************************************************
** Meta object code from reading C++ file 'dialogadddepartment.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../systemWidget/clinicalDiagnosis/dialogadddepartment.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogadddepartment.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DialogAddDepartment_t {
    QByteArrayData data[8];
    char stringdata0[83];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogAddDepartment_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogAddDepartment_t qt_meta_stringdata_DialogAddDepartment = {
    {
QT_MOC_LITERAL(0, 0, 19), // "DialogAddDepartment"
QT_MOC_LITERAL(1, 20, 14), // "signal_saveAdd"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 16), // "signal_saveClose"
QT_MOC_LITERAL(4, 53, 4), // "init"
QT_MOC_LITERAL(5, 58, 7), // "saveAdd"
QT_MOC_LITERAL(6, 66, 9), // "saveClose"
QT_MOC_LITERAL(7, 76, 6) // "cancel"

    },
    "DialogAddDepartment\0signal_saveAdd\0\0"
    "signal_saveClose\0init\0saveAdd\0saveClose\0"
    "cancel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogAddDepartment[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DialogAddDepartment::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogAddDepartment *_t = static_cast<DialogAddDepartment *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_saveAdd(); break;
        case 1: _t->signal_saveClose(); break;
        case 2: _t->init(); break;
        case 3: _t->saveAdd(); break;
        case 4: _t->saveClose(); break;
        case 5: _t->cancel(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DialogAddDepartment::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DialogAddDepartment::signal_saveAdd)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DialogAddDepartment::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DialogAddDepartment::signal_saveClose)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject DialogAddDepartment::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogAddDepartment.data,
      qt_meta_data_DialogAddDepartment,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DialogAddDepartment::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogAddDepartment::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DialogAddDepartment.stringdata0))
        return static_cast<void*>(const_cast< DialogAddDepartment*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogAddDepartment::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void DialogAddDepartment::signal_saveAdd()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void DialogAddDepartment::signal_saveClose()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
