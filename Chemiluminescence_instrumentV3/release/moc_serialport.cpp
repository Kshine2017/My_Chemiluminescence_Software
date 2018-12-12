/****************************************************************************
** Meta object code from reading C++ file 'serialport.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Serial_port/serialport.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_serialPort_t {
    QByteArrayData data[13];
    char stringdata0[211];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_serialPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_serialPort_t qt_meta_stringdata_serialPort = {
    {
QT_MOC_LITERAL(0, 0, 10), // "serialPort"
QT_MOC_LITERAL(1, 11, 12), // "mySerialRead"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 24), // "SendOvertime_dealFuction"
QT_MOC_LITERAL(4, 50, 27), // "ReceiveOvertime_dealFuction"
QT_MOC_LITERAL(5, 78, 20), // "okAnswering_SignSlot"
QT_MOC_LITERAL(6, 99, 6), // "string"
QT_MOC_LITERAL(7, 106, 21), // "ErrAnswering_SignSlot"
QT_MOC_LITERAL(8, 128, 15), // "ErrDataSignSlot"
QT_MOC_LITERAL(9, 144, 3), // "str"
QT_MOC_LITERAL(10, 148, 30), // "communicationComplete_SignSlot"
QT_MOC_LITERAL(11, 179, 14), // "queryTimerSlot"
QT_MOC_LITERAL(12, 194, 16) // "sendDataSignSlot"

    },
    "serialPort\0mySerialRead\0\0"
    "SendOvertime_dealFuction\0"
    "ReceiveOvertime_dealFuction\0"
    "okAnswering_SignSlot\0string\0"
    "ErrAnswering_SignSlot\0ErrDataSignSlot\0"
    "str\0communicationComplete_SignSlot\0"
    "queryTimerSlot\0sendDataSignSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_serialPort[] = {

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
       5,    1,   62,    2, 0x0a /* Public */,
       7,    1,   65,    2, 0x0a /* Public */,
       8,    1,   68,    2, 0x0a /* Public */,
      10,    0,   71,    2, 0x0a /* Public */,
      11,    0,   72,    2, 0x0a /* Public */,
      12,    1,   73,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void serialPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        serialPort *_t = static_cast<serialPort *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mySerialRead(); break;
        case 1: _t->SendOvertime_dealFuction(); break;
        case 2: _t->ReceiveOvertime_dealFuction(); break;
        case 3: _t->okAnswering_SignSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->ErrAnswering_SignSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->ErrDataSignSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->communicationComplete_SignSlot(); break;
        case 7: _t->queryTimerSlot(); break;
        case 8: _t->sendDataSignSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject serialPort::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_serialPort.data,
      qt_meta_data_serialPort,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *serialPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *serialPort::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_serialPort.stringdata0))
        return static_cast<void*>(const_cast< serialPort*>(this));
    return QWidget::qt_metacast(_clname);
}

int serialPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
