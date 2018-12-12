/****************************************************************************
** Meta object code from reading C++ file 'clinicaldiagnosis.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../systemWidget/clinicalDiagnosis/clinicaldiagnosis.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clinicaldiagnosis.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ClinicalDiagnosis_t {
    QByteArrayData data[10];
    char stringdata0[153];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClinicalDiagnosis_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClinicalDiagnosis_t qt_meta_stringdata_ClinicalDiagnosis = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ClinicalDiagnosis"
QT_MOC_LITERAL(1, 18, 4), // "init"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 13), // "addDepartment"
QT_MOC_LITERAL(4, 38, 16), // "deleteDepartment"
QT_MOC_LITERAL(5, 55, 21), // "AddDiagnosticCategory"
QT_MOC_LITERAL(6, 77, 24), // "deleteDiagnosticCategory"
QT_MOC_LITERAL(7, 102, 16), // "update_tableView"
QT_MOC_LITERAL(8, 119, 27), // "slot_getTablerow_department"
QT_MOC_LITERAL(9, 147, 5) // "index"

    },
    "ClinicalDiagnosis\0init\0\0addDepartment\0"
    "deleteDepartment\0AddDiagnosticCategory\0"
    "deleteDiagnosticCategory\0update_tableView\0"
    "slot_getTablerow_department\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClinicalDiagnosis[] = {

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
       7,    0,   54,    2, 0x0a /* Public */,
       8,    1,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    9,

       0        // eod
};

void ClinicalDiagnosis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClinicalDiagnosis *_t = static_cast<ClinicalDiagnosis *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->init(); break;
        case 1: _t->addDepartment(); break;
        case 2: _t->deleteDepartment(); break;
        case 3: _t->AddDiagnosticCategory(); break;
        case 4: _t->deleteDiagnosticCategory(); break;
        case 5: _t->update_tableView(); break;
        case 6: _t->slot_getTablerow_department((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ClinicalDiagnosis::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ClinicalDiagnosis.data,
      qt_meta_data_ClinicalDiagnosis,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ClinicalDiagnosis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClinicalDiagnosis::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ClinicalDiagnosis.stringdata0))
        return static_cast<void*>(const_cast< ClinicalDiagnosis*>(this));
    return QWidget::qt_metacast(_clname);
}

int ClinicalDiagnosis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
