/****************************************************************************
** Meta object code from reading C++ file 'historysearch.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../queryWidget/historysearch.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'historysearch.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HistorySearch_t {
    QByteArrayData data[8];
    char stringdata0[114];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HistorySearch_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HistorySearch_t qt_meta_stringdata_HistorySearch = {
    {
QT_MOC_LITERAL(0, 0, 13), // "HistorySearch"
QT_MOC_LITERAL(1, 14, 5), // "query"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 25), // "patientInformationCollect"
QT_MOC_LITERAL(4, 47, 23), // "correctedExperimentData"
QT_MOC_LITERAL(5, 71, 15), // "slot_btn_delete"
QT_MOC_LITERAL(6, 87, 20), // "slot_click_tableView"
QT_MOC_LITERAL(7, 108, 5) // "index"

    },
    "HistorySearch\0query\0\0patientInformationCollect\0"
    "correctedExperimentData\0slot_btn_delete\0"
    "slot_click_tableView\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HistorySearch[] = {

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
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    0,   42,    2, 0x0a /* Public */,
       6,    1,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    7,

       0        // eod
};

void HistorySearch::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HistorySearch *_t = static_cast<HistorySearch *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->query(); break;
        case 1: _t->patientInformationCollect(); break;
        case 2: _t->correctedExperimentData(); break;
        case 3: _t->slot_btn_delete(); break;
        case 4: _t->slot_click_tableView((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject HistorySearch::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_HistorySearch.data,
      qt_meta_data_HistorySearch,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HistorySearch::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HistorySearch::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HistorySearch.stringdata0))
        return static_cast<void*>(const_cast< HistorySearch*>(this));
    return QWidget::qt_metacast(_clname);
}

int HistorySearch::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
