/****************************************************************************
** Meta object code from reading C++ file 'unkownwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../unknownWidget/unkownwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'unkownwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UnkownWidget_t {
    QByteArrayData data[14];
    char stringdata0[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UnkownWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UnkownWidget_t qt_meta_stringdata_UnkownWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "UnkownWidget"
QT_MOC_LITERAL(1, 13, 13), // "selectRowSign"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 3), // "num"
QT_MOC_LITERAL(4, 32, 9), // "OkBtnSlot"
QT_MOC_LITERAL(5, 42, 12), // "startBtnSlot"
QT_MOC_LITERAL(6, 55, 20), // "selectionIndexesSlot"
QT_MOC_LITERAL(7, 76, 14), // "QItemSelection"
QT_MOC_LITERAL(8, 91, 9), // "newSelect"
QT_MOC_LITERAL(9, 101, 9), // "delSelect"
QT_MOC_LITERAL(10, 111, 19), // "infoWidgetOkBtnSlot"
QT_MOC_LITERAL(11, 131, 19), // "unkonow_cmdSignSlot"
QT_MOC_LITERAL(12, 151, 3), // "str"
QT_MOC_LITERAL(13, 155, 25) // "Unknow_queryTimerOverSlot"

    },
    "UnkownWidget\0selectRowSign\0\0num\0"
    "OkBtnSlot\0startBtnSlot\0selectionIndexesSlot\0"
    "QItemSelection\0newSelect\0delSelect\0"
    "infoWidgetOkBtnSlot\0unkonow_cmdSignSlot\0"
    "str\0Unknow_queryTimerOverSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UnkownWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   52,    2, 0x0a /* Public */,
       5,    1,   55,    2, 0x0a /* Public */,
       6,    2,   58,    2, 0x0a /* Public */,
      10,    1,   63,    2, 0x0a /* Public */,
      11,    1,   66,    2, 0x0a /* Public */,
      13,    0,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 7,    8,    9,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,

       0        // eod
};

void UnkownWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UnkownWidget *_t = static_cast<UnkownWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->selectRowSign((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->OkBtnSlot((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->startBtnSlot((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: _t->selectionIndexesSlot((*reinterpret_cast< QItemSelection(*)>(_a[1])),(*reinterpret_cast< QItemSelection(*)>(_a[2]))); break;
        case 4: _t->infoWidgetOkBtnSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->unkonow_cmdSignSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->Unknow_queryTimerOverSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QItemSelection >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UnkownWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UnkownWidget::selectRowSign)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject UnkownWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UnkownWidget.data,
      qt_meta_data_UnkownWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UnkownWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UnkownWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UnkownWidget.stringdata0))
        return static_cast<void*>(const_cast< UnkownWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int UnkownWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void UnkownWidget::selectRowSign(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
