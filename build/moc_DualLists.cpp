/****************************************************************************
** Meta object code from reading C++ file 'DualLists.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../DualLists.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DualLists.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DualLists_t {
    QByteArrayData data[9];
    char stringdata0[140];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DualLists_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DualLists_t qt_meta_stringdata_DualLists = {
    {
QT_MOC_LITERAL(0, 0, 9), // "DualLists"
QT_MOC_LITERAL(1, 10, 16), // "moveOneItemRight"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 15), // "moveOneItemLeft"
QT_MOC_LITERAL(4, 44, 21), // "enableLeftToRightBtns"
QT_MOC_LITERAL(5, 66, 21), // "enableRightToLeftBtns"
QT_MOC_LITERAL(6, 88, 17), // "moveAllItemsRight"
QT_MOC_LITERAL(7, 106, 16), // "moveAllItemsLeft"
QT_MOC_LITERAL(8, 123, 16) // "updateBtnsStatus"

    },
    "DualLists\0moveOneItemRight\0\0moveOneItemLeft\0"
    "enableLeftToRightBtns\0enableRightToLeftBtns\0"
    "moveAllItemsRight\0moveAllItemsLeft\0"
    "updateBtnsStatus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DualLists[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DualLists::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DualLists *_t = static_cast<DualLists *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->moveOneItemRight(); break;
        case 1: _t->moveOneItemLeft(); break;
        case 2: _t->enableLeftToRightBtns(); break;
        case 3: _t->enableRightToLeftBtns(); break;
        case 4: _t->moveAllItemsRight(); break;
        case 5: _t->moveAllItemsLeft(); break;
        case 6: _t->updateBtnsStatus(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject DualLists::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DualLists.data,
      qt_meta_data_DualLists,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DualLists::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DualLists::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DualLists.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DualLists::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
