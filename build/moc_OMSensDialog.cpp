/****************************************************************************
** Meta object code from reading C++ file 'OMSensDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../OMSensDialog.h"
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
    QByteArrayData data[16];
    char stringdata0[332];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OMSensDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OMSensDialog_t qt_meta_stringdata_OMSensDialog = {
    {
QT_MOC_LITERAL(0, 0, 12), // "OMSensDialog"
QT_MOC_LITERAL(1, 13, 7), // "readOut"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 7), // "readErr"
QT_MOC_LITERAL(4, 30, 20), // "runIndivSensAnalysis"
QT_MOC_LITERAL(5, 51, 22), // "runMultiParameterSweep"
QT_MOC_LITERAL(6, 74, 24), // "runVectorialSensAnalysis"
QT_MOC_LITERAL(7, 99, 31), // "showMultiParameterSweepAnalysis"
QT_MOC_LITERAL(8, 131, 25), // "showVectorialSensAnalysis"
QT_MOC_LITERAL(9, 157, 21), // "showIndivSensAnalysis"
QT_MOC_LITERAL(10, 179, 22), // "openSensAnalysisResult"
QT_MOC_LITERAL(11, 202, 21), // "openSensAnalysisImage"
QT_MOC_LITERAL(12, 224, 37), // "launchOMSensBackendChooseFold..."
QT_MOC_LITERAL(13, 262, 33), // "launchPythonBinChooseFolderDi..."
QT_MOC_LITERAL(14, 296, 10), // "helpDialog"
QT_MOC_LITERAL(15, 307, 24) // "loadExperimentFileDialog"

    },
    "OMSensDialog\0readOut\0\0readErr\0"
    "runIndivSensAnalysis\0runMultiParameterSweep\0"
    "runVectorialSensAnalysis\0"
    "showMultiParameterSweepAnalysis\0"
    "showVectorialSensAnalysis\0"
    "showIndivSensAnalysis\0openSensAnalysisResult\0"
    "openSensAnalysisImage\0"
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
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x0a /* Public */,
       3,    0,   85,    2, 0x0a /* Public */,
       4,    0,   86,    2, 0x0a /* Public */,
       5,    0,   87,    2, 0x0a /* Public */,
       6,    0,   88,    2, 0x0a /* Public */,
       7,    0,   89,    2, 0x0a /* Public */,
       8,    0,   90,    2, 0x0a /* Public */,
       9,    0,   91,    2, 0x0a /* Public */,
      10,    0,   92,    2, 0x0a /* Public */,
      11,    0,   93,    2, 0x0a /* Public */,
      12,    0,   94,    2, 0x0a /* Public */,
      13,    0,   95,    2, 0x0a /* Public */,
      14,    0,   96,    2, 0x0a /* Public */,
      15,    0,   97,    2, 0x0a /* Public */,

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
        case 0: _t->readOut(); break;
        case 1: _t->readErr(); break;
        case 2: _t->runIndivSensAnalysis(); break;
        case 3: _t->runMultiParameterSweep(); break;
        case 4: _t->runVectorialSensAnalysis(); break;
        case 5: _t->showMultiParameterSweepAnalysis(); break;
        case 6: _t->showVectorialSensAnalysis(); break;
        case 7: _t->showIndivSensAnalysis(); break;
        case 8: _t->openSensAnalysisResult(); break;
        case 9: _t->openSensAnalysisImage(); break;
        case 10: _t->launchOMSensBackendChooseFolderDialog(); break;
        case 11: _t->launchPythonBinChooseFolderDialog(); break;
        case 12: _t->helpDialog(); break;
        case 13: _t->loadExperimentFileDialog(); break;
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
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
