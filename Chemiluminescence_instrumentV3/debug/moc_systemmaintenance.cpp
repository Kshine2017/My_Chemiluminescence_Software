/****************************************************************************
** Meta object code from reading C++ file 'systemmaintenance.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../systemWidget/systemMaintenance/systemmaintenance.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'systemmaintenance.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SystemMaintenance_t {
    QByteArrayData data[11];
    char stringdata0[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SystemMaintenance_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SystemMaintenance_t qt_meta_stringdata_SystemMaintenance = {
    {
QT_MOC_LITERAL(0, 0, 17), // "SystemMaintenance"
QT_MOC_LITERAL(1, 18, 20), // "automaticDayMaintain"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 21), // "automaticWeekMaintain"
QT_MOC_LITERAL(4, 62, 14), // "initInstrument"
QT_MOC_LITERAL(5, 77, 7), // "testPMT"
QT_MOC_LITERAL(6, 85, 13), // "startMaintain"
QT_MOC_LITERAL(7, 99, 13), // "pauseMaintain"
QT_MOC_LITERAL(8, 113, 16), // "continueMaintain"
QT_MOC_LITERAL(9, 130, 15), // "startInstrument"
QT_MOC_LITERAL(10, 146, 14) // "stopInstrument"

    },
    "SystemMaintenance\0automaticDayMaintain\0"
    "\0automaticWeekMaintain\0initInstrument\0"
    "testPMT\0startMaintain\0pauseMaintain\0"
    "continueMaintain\0startInstrument\0"
    "stopInstrument"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SystemMaintenance[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x0a /* Public */,
       6,    0,   63,    2, 0x0a /* Public */,
       7,    0,   64,    2, 0x0a /* Public */,
       8,    0,   65,    2, 0x0a /* Public */,
       9,    0,   66,    2, 0x0a /* Public */,
      10,    0,   67,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SystemMaintenance::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SystemMaintenance *_t = static_cast<SystemMaintenance *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->automaticDayMaintain(); break;
        case 1: _t->automaticWeekMaintain(); break;
        case 2: _t->initInstrument(); break;
        case 3: _t->testPMT(); break;
        case 4: _t->startMaintain(); break;
        case 5: _t->pauseMaintain(); break;
        case 6: _t->continueMaintain(); break;
        case 7: _t->startInstrument(); break;
        case 8: _t->stopInstrument(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SystemMaintenance::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SystemMaintenance.data,
      qt_meta_data_SystemMaintenance,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SystemMaintenance::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SystemMaintenance::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SystemMaintenance.stringdata0))
        return static_cast<void*>(const_cast< SystemMaintenance*>(this));
    return QWidget::qt_metacast(_clname);
}

int SystemMaintenance::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
