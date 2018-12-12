/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[16];
    char stringdata0[277];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 20), // "create_UnknownWindow"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 24), // "create_CalibrationWindow"
QT_MOC_LITERAL(4, 58, 21), // "create_SelfTestWindow"
QT_MOC_LITERAL(5, 80, 18), // "create_QueryWindow"
QT_MOC_LITERAL(6, 99, 19), // "create_SystemWindow"
QT_MOC_LITERAL(7, 119, 29), // "create_StandardPragrameWindow"
QT_MOC_LITERAL(8, 149, 25), // "create_StandardTestWindow"
QT_MOC_LITERAL(9, 175, 26), // "create_StandardBightWindow"
QT_MOC_LITERAL(10, 202, 13), // "CancelBtnSlot"
QT_MOC_LITERAL(11, 216, 17), // "other_cmdSignSlot"
QT_MOC_LITERAL(12, 234, 3), // "str"
QT_MOC_LITERAL(13, 238, 8), // "showTime"
QT_MOC_LITERAL(14, 247, 15), // "questionBtnSlot"
QT_MOC_LITERAL(15, 263, 13) // "returnBtnSlot"

    },
    "MainWindow\0create_UnknownWindow\0\0"
    "create_CalibrationWindow\0create_SelfTestWindow\0"
    "create_QueryWindow\0create_SystemWindow\0"
    "create_StandardPragrameWindow\0"
    "create_StandardTestWindow\0"
    "create_StandardBightWindow\0CancelBtnSlot\0"
    "other_cmdSignSlot\0str\0showTime\0"
    "questionBtnSlot\0returnBtnSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a /* Public */,
       3,    0,   80,    2, 0x0a /* Public */,
       4,    0,   81,    2, 0x0a /* Public */,
       5,    0,   82,    2, 0x0a /* Public */,
       6,    0,   83,    2, 0x0a /* Public */,
       7,    0,   84,    2, 0x0a /* Public */,
       8,    0,   85,    2, 0x0a /* Public */,
       9,    0,   86,    2, 0x0a /* Public */,
      10,    0,   87,    2, 0x0a /* Public */,
      11,    1,   88,    2, 0x0a /* Public */,
      13,    0,   91,    2, 0x0a /* Public */,
      14,    0,   92,    2, 0x0a /* Public */,
      15,    0,   93,    2, 0x0a /* Public */,

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
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->create_UnknownWindow(); break;
        case 1: _t->create_CalibrationWindow(); break;
        case 2: _t->create_SelfTestWindow(); break;
        case 3: _t->create_QueryWindow(); break;
        case 4: _t->create_SystemWindow(); break;
        case 5: _t->create_StandardPragrameWindow(); break;
        case 6: _t->create_StandardTestWindow(); break;
        case 7: _t->create_StandardBightWindow(); break;
        case 8: _t->CancelBtnSlot(); break;
        case 9: _t->other_cmdSignSlot((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->showTime(); break;
        case 11: _t->questionBtnSlot(); break;
        case 12: _t->returnBtnSlot(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
