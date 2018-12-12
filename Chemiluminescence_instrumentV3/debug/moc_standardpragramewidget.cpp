/****************************************************************************
** Meta object code from reading C++ file 'standardpragramewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../standardProgrameWidget/standardpragramewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'standardpragramewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_standardPragrameWidget_t {
    QByteArrayData data[19];
    char stringdata0[314];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_standardPragrameWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_standardPragrameWidget_t qt_meta_stringdata_standardPragrameWidget = {
    {
QT_MOC_LITERAL(0, 0, 22), // "standardPragrameWidget"
QT_MOC_LITERAL(1, 23, 20), // "signal_refreshNumber"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 18), // "StartBtnSignalSlot"
QT_MOC_LITERAL(4, 64, 16), // "SaveBtnPressSlot"
QT_MOC_LITERAL(5, 81, 11), // "OpenBtnSlot"
QT_MOC_LITERAL(6, 93, 12), // "DataToWindow"
QT_MOC_LITERAL(7, 106, 8), // "QString&"
QT_MOC_LITERAL(8, 115, 11), // "ACTION_CODE"
QT_MOC_LITERAL(9, 127, 28), // "reagent_programe_cmdSignSlot"
QT_MOC_LITERAL(10, 156, 3), // "str"
QT_MOC_LITERAL(11, 160, 20), // "stepRunBtnSignalSlot"
QT_MOC_LITERAL(12, 181, 4), // "step"
QT_MOC_LITERAL(13, 186, 35), // "slot_RefreshComoBox_FileName_..."
QT_MOC_LITERAL(14, 222, 4), // "text"
QT_MOC_LITERAL(15, 227, 23), // "slot_RefreshComoBox__SN"
QT_MOC_LITERAL(16, 251, 22), // "slot_autoGenerateNumer"
QT_MOC_LITERAL(17, 274, 34), // "slot_send_signal_autoGenerate..."
QT_MOC_LITERAL(18, 309, 4) // "date"

    },
    "standardPragrameWidget\0signal_refreshNumber\0"
    "\0StartBtnSignalSlot\0SaveBtnPressSlot\0"
    "OpenBtnSlot\0DataToWindow\0QString&\0"
    "ACTION_CODE\0reagent_programe_cmdSignSlot\0"
    "str\0stepRunBtnSignalSlot\0step\0"
    "slot_RefreshComoBox_FileName_And_SN\0"
    "text\0slot_RefreshComoBox__SN\0"
    "slot_autoGenerateNumer\0"
    "slot_send_signal_autoGenerateNumer\0"
    "date"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_standardPragrameWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   75,    2, 0x0a /* Public */,
       4,    0,   76,    2, 0x0a /* Public */,
       5,    0,   77,    2, 0x0a /* Public */,
       6,    1,   78,    2, 0x0a /* Public */,
       9,    1,   81,    2, 0x0a /* Public */,
      11,    1,   84,    2, 0x0a /* Public */,
      13,    1,   87,    2, 0x0a /* Public */,
      15,    1,   90,    2, 0x0a /* Public */,
      16,    0,   93,    2, 0x0a /* Public */,
      17,    1,   94,    2, 0x0a /* Public */,
      17,    1,   97,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate,   18,
    QMetaType::Void, QMetaType::QString,   14,

       0        // eod
};

void standardPragrameWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        standardPragrameWidget *_t = static_cast<standardPragrameWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_refreshNumber(); break;
        case 1: _t->StartBtnSignalSlot(); break;
        case 2: _t->SaveBtnPressSlot(); break;
        case 3: _t->OpenBtnSlot(); break;
        case 4: _t->DataToWindow((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->reagent_programe_cmdSignSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->stepRunBtnSignalSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->slot_RefreshComoBox_FileName_And_SN((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->slot_RefreshComoBox__SN((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->slot_autoGenerateNumer(); break;
        case 10: _t->slot_send_signal_autoGenerateNumer((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 11: _t->slot_send_signal_autoGenerateNumer((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (standardPragrameWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&standardPragrameWidget::signal_refreshNumber)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject standardPragrameWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_standardPragrameWidget.data,
      qt_meta_data_standardPragrameWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *standardPragrameWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *standardPragrameWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_standardPragrameWidget.stringdata0))
        return static_cast<void*>(const_cast< standardPragrameWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int standardPragrameWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void standardPragrameWidget::signal_refreshNumber()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
