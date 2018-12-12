/****************************************************************************
** Meta object code from reading C++ file 'serial_thread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../serical_thread/serial_thread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serial_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_serial_thread_t {
    QByteArrayData data[15];
    char stringdata0[232];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_serial_thread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_serial_thread_t qt_meta_stringdata_serial_thread = {
    {
QT_MOC_LITERAL(0, 0, 13), // "serial_thread"
QT_MOC_LITERAL(1, 14, 16), // "okAnswering_Sign"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 3), // "str"
QT_MOC_LITERAL(4, 36, 17), // "ErrAnswering_Sign"
QT_MOC_LITERAL(5, 54, 26), // "communicationComplete_Sign"
QT_MOC_LITERAL(6, 81, 17), // "self_test_cmdSign"
QT_MOC_LITERAL(7, 99, 24), // "reagent_programe_cmdSign"
QT_MOC_LITERAL(8, 124, 15), // "unkonow_cmdSign"
QT_MOC_LITERAL(9, 140, 16), // "standard_cmdSign"
QT_MOC_LITERAL(10, 157, 19), // "calibration_cmdSign"
QT_MOC_LITERAL(11, 177, 13), // "other_cmdSign"
QT_MOC_LITERAL(12, 191, 15), // "quality_cmdSign"
QT_MOC_LITERAL(13, 207, 12), // "sendDataSign"
QT_MOC_LITERAL(14, 220, 11) // "ErrDataSign"

    },
    "serial_thread\0okAnswering_Sign\0\0str\0"
    "ErrAnswering_Sign\0communicationComplete_Sign\0"
    "self_test_cmdSign\0reagent_programe_cmdSign\0"
    "unkonow_cmdSign\0standard_cmdSign\0"
    "calibration_cmdSign\0other_cmdSign\0"
    "quality_cmdSign\0sendDataSign\0ErrDataSign"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_serial_thread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    1,   77,    2, 0x06 /* Public */,
       5,    0,   80,    2, 0x06 /* Public */,
       6,    1,   81,    2, 0x06 /* Public */,
       7,    1,   84,    2, 0x06 /* Public */,
       8,    1,   87,    2, 0x06 /* Public */,
       9,    1,   90,    2, 0x06 /* Public */,
      10,    1,   93,    2, 0x06 /* Public */,
      11,    1,   96,    2, 0x06 /* Public */,
      12,    1,   99,    2, 0x06 /* Public */,
      13,    1,  102,    2, 0x06 /* Public */,
      14,    1,  105,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void serial_thread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        serial_thread *_t = static_cast<serial_thread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->okAnswering_Sign((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->ErrAnswering_Sign((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->communicationComplete_Sign(); break;
        case 3: _t->self_test_cmdSign((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->reagent_programe_cmdSign((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->unkonow_cmdSign((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->standard_cmdSign((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->calibration_cmdSign((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->other_cmdSign((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->quality_cmdSign((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->sendDataSign((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->ErrDataSign((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (serial_thread::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&serial_thread::okAnswering_Sign)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (serial_thread::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&serial_thread::ErrAnswering_Sign)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (serial_thread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&serial_thread::communicationComplete_Sign)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (serial_thread::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&serial_thread::self_test_cmdSign)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (serial_thread::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&serial_thread::reagent_programe_cmdSign)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (serial_thread::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&serial_thread::unkonow_cmdSign)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (serial_thread::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&serial_thread::standard_cmdSign)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (serial_thread::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&serial_thread::calibration_cmdSign)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (serial_thread::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&serial_thread::other_cmdSign)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (serial_thread::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&serial_thread::quality_cmdSign)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (serial_thread::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&serial_thread::sendDataSign)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (serial_thread::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&serial_thread::ErrDataSign)) {
                *result = 11;
                return;
            }
        }
    }
}

const QMetaObject serial_thread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_serial_thread.data,
      qt_meta_data_serial_thread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *serial_thread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *serial_thread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_serial_thread.stringdata0))
        return static_cast<void*>(const_cast< serial_thread*>(this));
    return QThread::qt_metacast(_clname);
}

int serial_thread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void serial_thread::okAnswering_Sign(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void serial_thread::ErrAnswering_Sign(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void serial_thread::communicationComplete_Sign()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void serial_thread::self_test_cmdSign(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void serial_thread::reagent_programe_cmdSign(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void serial_thread::unkonow_cmdSign(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void serial_thread::standard_cmdSign(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void serial_thread::calibration_cmdSign(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void serial_thread::other_cmdSign(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void serial_thread::quality_cmdSign(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void serial_thread::sendDataSign(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void serial_thread::ErrDataSign(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}
QT_END_MOC_NAMESPACE
