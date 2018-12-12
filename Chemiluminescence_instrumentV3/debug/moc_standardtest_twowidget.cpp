/****************************************************************************
** Meta object code from reading C++ file 'standardtest_twowidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../standardTestWidget/standardtest_twowidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'standardtest_twowidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_standardTest_TwoWidget_t {
    QByteArrayData data[5];
    char stringdata0[65];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_standardTest_TwoWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_standardTest_TwoWidget_t qt_meta_stringdata_standardTest_TwoWidget = {
    {
QT_MOC_LITERAL(0, 0, 22), // "standardTest_TwoWidget"
QT_MOC_LITERAL(1, 23, 16), // "SaveBtnPressSign"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 11), // "SureBtnSlot"
QT_MOC_LITERAL(4, 53, 11) // "saveBtnSlot"

    },
    "standardTest_TwoWidget\0SaveBtnPressSign\0"
    "\0SureBtnSlot\0saveBtnSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_standardTest_TwoWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void standardTest_TwoWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        standardTest_TwoWidget *_t = static_cast<standardTest_TwoWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SaveBtnPressSign(); break;
        case 1: _t->SureBtnSlot(); break;
        case 2: _t->saveBtnSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (standardTest_TwoWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&standardTest_TwoWidget::SaveBtnPressSign)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject standardTest_TwoWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_standardTest_TwoWidget.data,
      qt_meta_data_standardTest_TwoWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *standardTest_TwoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *standardTest_TwoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_standardTest_TwoWidget.stringdata0))
        return static_cast<void*>(const_cast< standardTest_TwoWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int standardTest_TwoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void standardTest_TwoWidget::SaveBtnPressSign()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
