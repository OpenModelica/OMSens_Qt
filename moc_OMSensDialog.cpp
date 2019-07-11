/****************************************************************************
** Meta object code from reading C++ file 'OMSensDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "OMSensDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OMSensDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OMSensDialog_t {
    QByteArrayData data[11];
    char stringdata0[236];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OMSensDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OMSensDialog_t qt_meta_stringdata_OMSensDialog = {
    {
QT_MOC_LITERAL(0, 0, 12), // "OMSensDialog"
QT_MOC_LITERAL(1, 13, 20), // "runIndivSensAnalysis"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 22), // "runMultiParameterSweep"
QT_MOC_LITERAL(4, 58, 24), // "runVectorialSensAnalysis"
QT_MOC_LITERAL(5, 83, 22), // "openSensAnalysisResult"
QT_MOC_LITERAL(6, 106, 21), // "openSensAnalysisImage"
QT_MOC_LITERAL(7, 128, 37), // "launchOMSensBackendChooseFold..."
QT_MOC_LITERAL(8, 166, 33), // "launchPythonBinChooseFolderDi..."
QT_MOC_LITERAL(9, 200, 10), // "helpDialog"
QT_MOC_LITERAL(10, 211, 24) // "loadExperimentFileDialog"

    },
    "OMSensDialog\0runIndivSensAnalysis\0\0"
    "runMultiParameterSweep\0runVectorialSensAnalysis\0"
    "openSensAnalysisResult\0openSensAnalysisImage\0"
    "launchOMSensBackendChooseFolderDialog\0"
    "launchPythonBinChooseFolderDialog\0"
    "helpDialog\0loadExperimentFileDialog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OMSensDialog[] = {

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
       5,    0,   62,    2, 0x0a /* Public */,
       6,    0,   63,    2, 0x0a /* Public */,
       7,    0,   64,    2, 0x0a /* Public */,
       8,    0,   65,    2, 0x0a /* Public */,
       9,    0,   66,    2, 0x0a /* Public */,
      10,    0,   67,    2, 0x0a /* Public */,

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

       0        // eod
};

void OMSensDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OMSensDialog *_t = static_cast<OMSensDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->runIndivSensAnalysis(); break;
        case 1: _t->runMultiParameterSweep(); break;
        case 2: _t->runVectorialSensAnalysis(); break;
        case 3: _t->openSensAnalysisResult(); break;
        case 4: _t->openSensAnalysisImage(); break;
        case 5: _t->launchOMSensBackendChooseFolderDialog(); break;
        case 6: _t->launchPythonBinChooseFolderDialog(); break;
        case 7: _t->helpDialog(); break;
        case 8: _t->loadExperimentFileDialog(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject OMSensDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_OMSensDialog.data,
      qt_meta_data_OMSensDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *OMSensDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OMSensDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OMSensDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int OMSensDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
