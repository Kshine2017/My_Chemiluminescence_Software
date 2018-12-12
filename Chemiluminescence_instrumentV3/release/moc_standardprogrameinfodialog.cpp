/****************************************************************************
** Meta object code from reading C++ file 'standardprogrameinfodialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../standardProgrameWidget/standardprogrameinfodialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'standardprogrameinfodialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_StandardProgrameInfoDialog_t {
    QByteArrayData data[12];
    char stringdata0[206];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StandardProgrameInfoDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StandardProgrameInfoDialog_t qt_meta_stringdata_StandardProgrameInfoDialog = {
    {
QT_MOC_LITERAL(0, 0, 26), // "StandardProgrameInfoDialog"
QT_MOC_LITERAL(1, 27, 16), // "OpenStandardInfo"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 8), // "QString&"
QT_MOC_LITERAL(4, 54, 13), // "fileShortName"
QT_MOC_LITERAL(5, 68, 18), // "DeleteStandardInfo"
QT_MOC_LITERAL(6, 87, 13), // "btn_sure_solt"
QT_MOC_LITERAL(7, 101, 15), // "btn_delete_solt"
QT_MOC_LITERAL(8, 117, 15), // "btn_cancel_solt"
QT_MOC_LITERAL(9, 133, 29), // "getIndex_click_tableView_slot"
QT_MOC_LITERAL(10, 163, 5), // "index"
QT_MOC_LITERAL(11, 169, 36) // "getIndex_Double_click_tableVi..."

    },
    "StandardProgrameInfoDialog\0OpenStandardInfo\0"
    "\0QString&\0fileShortName\0DeleteStandardInfo\0"
    "btn_sure_solt\0btn_delete_solt\0"
    "btn_cancel_solt\0getIndex_click_tableView_slot\0"
    "index\0getIndex_Double_click_tableView_slot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StandardProgrameInfoDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       5,    1,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   55,    2, 0x0a /* Public */,
       7,    0,   56,    2, 0x0a /* Public */,
       8,    0,   57,    2, 0x0a /* Public */,
       9,    1,   58,    2, 0x0a /* Public */,
      11,    1,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   10,
    QMetaType::Void, QMetaType::QModelIndex,   10,

       0        // eod
};

void StandardProgrameInfoDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StandardProgrameInfoDialog *_t = static_cast<StandardProgrameInfoDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OpenStandardInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->DeleteStandardInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->btn_sure_solt(); break;
        case 3: _t->btn_delete_solt(); break;
        case 4: _t->btn_cancel_solt(); break;
        case 5: _t->getIndex_click_tableView_slot((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 6: _t->getIndex_Double_click_tableView_slot((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (StandardProgrameInfoDialog::*_t)(QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StandardProgrameInfoDialog::OpenStandardInfo)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (StandardProgrameInfoDialog::*_t)(QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StandardProgrameInfoDialog::DeleteStandardInfo)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject StandardProgrameInfoDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_StandardProgrameInfoDialog.data,
      qt_meta_data_StandardProgrameInfoDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *StandardProgrameInfoDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StandardProgrameInfoDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_StandardProgrameInfoDialog.stringdata0))
        return static_cast<void*>(const_cast< StandardProgrameInfoDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int StandardProgrameInfoDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void StandardProgrameInfoDialog::OpenStandardInfo(QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StandardProgrameInfoDialog::DeleteStandardInfo(QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
