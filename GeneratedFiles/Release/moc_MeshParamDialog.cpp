/****************************************************************************
** Meta object code from reading C++ file 'MeshParamDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MeshViewer/MeshParamDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MeshParamDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MeshParamDialog_t {
    QByteArrayData data[10];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MeshParamDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MeshParamDialog_t qt_meta_stringdata_MeshParamDialog = {
    {
QT_MOC_LITERAL(0, 0, 15), // "MeshParamDialog"
QT_MOC_LITERAL(1, 16, 17), // "print_info_signal"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 12), // "NoEditSignal"
QT_MOC_LITERAL(4, 48, 14), // "SeamEditSignal"
QT_MOC_LITERAL(5, 63, 13), // "AddSeamSignal"
QT_MOC_LITERAL(6, 77, 14), // "UndoSeamSignal"
QT_MOC_LITERAL(7, 92, 13), // "MeshCutSignal"
QT_MOC_LITERAL(8, 106, 17), // "ChooseModelSignal"
QT_MOC_LITERAL(9, 124, 9) // "ResetEdit"

    },
    "MeshParamDialog\0print_info_signal\0\0"
    "NoEditSignal\0SeamEditSignal\0AddSeamSignal\0"
    "UndoSeamSignal\0MeshCutSignal\0"
    "ChooseModelSignal\0ResetEdit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MeshParamDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,
       5,    0,   57,    2, 0x06 /* Public */,
       6,    0,   58,    2, 0x06 /* Public */,
       7,    0,   59,    2, 0x06 /* Public */,
       8,    1,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void MeshParamDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MeshParamDialog *_t = static_cast<MeshParamDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->print_info_signal(); break;
        case 1: _t->NoEditSignal(); break;
        case 2: _t->SeamEditSignal(); break;
        case 3: _t->AddSeamSignal(); break;
        case 4: _t->UndoSeamSignal(); break;
        case 5: _t->MeshCutSignal(); break;
        case 6: _t->ChooseModelSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->ResetEdit(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MeshParamDialog::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MeshParamDialog::print_info_signal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MeshParamDialog::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MeshParamDialog::NoEditSignal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MeshParamDialog::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MeshParamDialog::SeamEditSignal)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MeshParamDialog::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MeshParamDialog::AddSeamSignal)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MeshParamDialog::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MeshParamDialog::UndoSeamSignal)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (MeshParamDialog::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MeshParamDialog::MeshCutSignal)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (MeshParamDialog::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MeshParamDialog::ChooseModelSignal)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject MeshParamDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MeshParamDialog.data,
      qt_meta_data_MeshParamDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MeshParamDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MeshParamDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MeshParamDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int MeshParamDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void MeshParamDialog::print_info_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MeshParamDialog::NoEditSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MeshParamDialog::SeamEditSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MeshParamDialog::AddSeamSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MeshParamDialog::UndoSeamSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MeshParamDialog::MeshCutSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MeshParamDialog::ChooseModelSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
