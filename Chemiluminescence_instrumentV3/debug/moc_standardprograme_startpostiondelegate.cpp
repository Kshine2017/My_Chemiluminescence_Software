/****************************************************************************
** Meta object code from reading C++ file 'standardprograme_startpostiondelegate.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../standardProgrameWidget/standardprograme_startpostiondelegate.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'standardprograme_startpostiondelegate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_standardPrograme_startPostionDelegate_t {
    QByteArrayData data[3];
    char stringdata0[56];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_standardPrograme_startPostionDelegate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_standardPrograme_startPostionDelegate_t qt_meta_stringdata_standardPrograme_startPostionDelegate = {
    {
QT_MOC_LITERAL(0, 0, 37), // "standardPrograme_startPostion..."
QT_MOC_LITERAL(1, 38, 16), // "stepRnBtnClicked"
QT_MOC_LITERAL(2, 55, 0) // ""

    },
    "standardPrograme_startPostionDelegate\0"
    "stepRnBtnClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_standardPrograme_startPostionDelegate[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QModelIndex,    2,

       0        // eod
};

void standardPrograme_startPostionDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        standardPrograme_startPostionDelegate *_t = static_cast<standardPrograme_startPostionDelegate *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stepRnBtnClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (standardPrograme_startPostionDelegate::*_t)(const QModelIndex & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&standardPrograme_startPostionDelegate::stepRnBtnClicked)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject standardPrograme_startPostionDelegate::staticMetaObject = {
    { &QStyledItemDelegate::staticMetaObject, qt_meta_stringdata_standardPrograme_startPostionDelegate.data,
      qt_meta_data_standardPrograme_startPostionDelegate,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *standardPrograme_startPostionDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *standardPrograme_startPostionDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_standardPrograme_startPostionDelegate.stringdata0))
        return static_cast<void*>(const_cast< standardPrograme_startPostionDelegate*>(this));
    return QStyledItemDelegate::qt_metacast(_clname);
}

int standardPrograme_startPostionDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStyledItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void standardPrograme_startPostionDelegate::stepRnBtnClicked(const QModelIndex & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
