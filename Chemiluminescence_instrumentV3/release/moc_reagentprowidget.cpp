/****************************************************************************
** Meta object code from reading C++ file 'reagentprowidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../standardProgrameWidget/reagentprowidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'reagentprowidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_reagentProWidget_t {
    QByteArrayData data[13];
    char stringdata0[194];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_reagentProWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_reagentProWidget_t qt_meta_stringdata_reagentProWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "reagentProWidget"
QT_MOC_LITERAL(1, 17, 17), // "SaveBtnPress_Sign"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 13), // "OpenBtnSignal"
QT_MOC_LITERAL(4, 50, 14), // "startBtnSignal"
QT_MOC_LITERAL(5, 65, 11), // "saveBtnSlot"
QT_MOC_LITERAL(6, 77, 11), // "openBtnSlot"
QT_MOC_LITERAL(7, 89, 12), // "startBtnSlot"
QT_MOC_LITERAL(8, 102, 19), // "pauseContinuBtnSlot"
QT_MOC_LITERAL(9, 122, 11), // "stopBtnSlot"
QT_MOC_LITERAL(10, 134, 13), // "importBtnSlot"
QT_MOC_LITERAL(11, 148, 13), // "exportBtnSlot"
QT_MOC_LITERAL(12, 162, 31) // "reagentpro_InquiryTimerOverSlot"

    },
    "reagentProWidget\0SaveBtnPress_Sign\0\0"
    "OpenBtnSignal\0startBtnSignal\0saveBtnSlot\0"
    "openBtnSlot\0startBtnSlot\0pauseContinuBtnSlot\0"
    "stopBtnSlot\0importBtnSlot\0exportBtnSlot\0"
    "reagentpro_InquiryTimerOverSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_reagentProWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   72,    2, 0x0a /* Public */,
       6,    0,   73,    2, 0x0a /* Public */,
       7,    0,   74,    2, 0x0a /* Public */,
       8,    0,   75,    2, 0x0a /* Public */,
       9,    0,   76,    2, 0x0a /* Public */,
      10,    0,   77,    2, 0x0a /* Public */,
      11,    0,   78,    2, 0x0a /* Public */,
      12,    0,   79,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
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

void reagentProWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        reagentProWidget *_t = static_cast<reagentProWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SaveBtnPress_Sign(); break;
        case 1: _t->OpenBtnSignal(); break;
        case 2: _t->startBtnSignal(); break;
        case 3: _t->saveBtnSlot(); break;
        case 4: _t->openBtnSlot(); break;
        case 5: _t->startBtnSlot(); break;
        case 6: _t->pauseContinuBtnSlot(); break;
        case 7: _t->stopBtnSlot(); break;
        case 8: _t->importBtnSlot(); break;
        case 9: _t->exportBtnSlot(); break;
        case 10: _t->reagentpro_InquiryTimerOverSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (reagentProWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&reagentProWidget::SaveBtnPress_Sign)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (reagentProWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&reagentProWidget::OpenBtnSignal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (reagentProWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&reagentProWidget::startBtnSignal)) {
                *result = 2;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject reagentProWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_reagentProWidget.data,
      qt_meta_data_reagentProWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *reagentProWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *reagentProWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_reagentProWidget.stringdata0))
        return static_cast<void*>(const_cast< reagentProWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int reagentProWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void reagentProWidget::SaveBtnPress_Sign()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void reagentProWidget::OpenBtnSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void reagentProWidget::startBtnSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
