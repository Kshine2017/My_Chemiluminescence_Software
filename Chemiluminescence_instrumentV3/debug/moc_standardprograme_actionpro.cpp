/****************************************************************************
** Meta object code from reading C++ file 'standardprograme_actionpro.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../standardProgrameWidget/standardprograme_actionpro.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'standardprograme_actionpro.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_standardPrograme_actionPro_t {
    QByteArrayData data[8];
    char stringdata0[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_standardPrograme_actionPro_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_standardPrograme_actionPro_t qt_meta_stringdata_standardPrograme_actionPro = {
    {
QT_MOC_LITERAL(0, 0, 26), // "standardPrograme_actionPro"
QT_MOC_LITERAL(1, 27, 16), // "stepRunBtnSignal"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 4), // "step"
QT_MOC_LITERAL(4, 50, 13), // "addActionStep"
QT_MOC_LITERAL(5, 64, 5), // "index"
QT_MOC_LITERAL(6, 70, 15), // "minusActionStep"
QT_MOC_LITERAL(7, 86, 14) // "stepRunBtnSlot"

    },
    "standardPrograme_actionPro\0stepRunBtnSignal\0"
    "\0step\0addActionStep\0index\0minusActionStep\0"
    "stepRunBtnSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_standardPrograme_actionPro[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   37,    2, 0x0a /* Public */,
       6,    1,   40,    2, 0x0a /* Public */,
       7,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    5,
    QMetaType::Void, QMetaType::QModelIndex,    5,
    QMetaType::Void, QMetaType::QModelIndex,    5,

       0        // eod
};

void standardPrograme_actionPro::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        standardPrograme_actionPro *_t = static_cast<standardPrograme_actionPro *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stepRunBtnSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->addActionStep((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->minusActionStep((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: _t->stepRunBtnSlot((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (standardPrograme_actionPro::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&standardPrograme_actionPro::stepRunBtnSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject standardPrograme_actionPro::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_standardPrograme_actionPro.data,
      qt_meta_data_standardPrograme_actionPro,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *standardPrograme_actionPro::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *standardPrograme_actionPro::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_standardPrograme_actionPro.stringdata0))
        return static_cast<void*>(const_cast< standardPrograme_actionPro*>(this));
    return QWidget::qt_metacast(_clname);
}

int standardPrograme_actionPro::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void standardPrograme_actionPro::stepRunBtnSignal(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
