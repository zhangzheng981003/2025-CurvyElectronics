/****************************************************************************
** Meta object code from reading C++ file 'InteractiveViewerWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MeshViewer/InteractiveViewerWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InteractiveViewerWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_InteractiveViewerWidget_t {
    QByteArrayData data[27];
    char stringdata0[367];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InteractiveViewerWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InteractiveViewerWidget_t qt_meta_stringdata_InteractiveViewerWidget = {
    {
QT_MOC_LITERAL(0, 0, 23), // "InteractiveViewerWidget"
QT_MOC_LITERAL(1, 24, 18), // "mouse_press_signal"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 11), // "Mesh::Point"
QT_MOC_LITERAL(4, 56, 1), // "P"
QT_MOC_LITERAL(5, 58, 17), // "mouse_move_signal"
QT_MOC_LITERAL(6, 76, 15), // "OpenMesh::Vec3d"
QT_MOC_LITERAL(7, 92, 2), // "xy"
QT_MOC_LITERAL(8, 95, 20), // "mouse_release_signal"
QT_MOC_LITERAL(9, 116, 20), // "draw_from_out_signal"
QT_MOC_LITERAL(10, 137, 19), // "setMouseMode_signal"
QT_MOC_LITERAL(11, 157, 34), // "set_edit_undo_enable_viewer_s..."
QT_MOC_LITERAL(12, 192, 34), // "set_edit_redo_enable_viewer_s..."
QT_MOC_LITERAL(13, 227, 15), // "ResetEditSignal"
QT_MOC_LITERAL(14, 243, 16), // "render_text_slot"
QT_MOC_LITERAL(15, 260, 3), // "pos"
QT_MOC_LITERAL(16, 264, 3), // "str"
QT_MOC_LITERAL(17, 268, 17), // "set_t2_mouse_mode"
QT_MOC_LITERAL(18, 286, 2), // "tm"
QT_MOC_LITERAL(19, 289, 6), // "NoEdit"
QT_MOC_LITERAL(20, 296, 8), // "SeamEdit"
QT_MOC_LITERAL(21, 305, 7), // "AddSeam"
QT_MOC_LITERAL(22, 313, 8), // "UndoSeam"
QT_MOC_LITERAL(23, 322, 7), // "MeshCut"
QT_MOC_LITERAL(24, 330, 12), // "Click_to_BPE"
QT_MOC_LITERAL(25, 343, 11), // "std::string"
QT_MOC_LITERAL(26, 355, 11) // "fileDirPath"

    },
    "InteractiveViewerWidget\0mouse_press_signal\0"
    "\0Mesh::Point\0P\0mouse_move_signal\0"
    "OpenMesh::Vec3d\0xy\0mouse_release_signal\0"
    "draw_from_out_signal\0setMouseMode_signal\0"
    "set_edit_undo_enable_viewer_signal\0"
    "set_edit_redo_enable_viewer_signal\0"
    "ResetEditSignal\0render_text_slot\0pos\0"
    "str\0set_t2_mouse_mode\0tm\0NoEdit\0"
    "SeamEdit\0AddSeam\0UndoSeam\0MeshCut\0"
    "Click_to_BPE\0std::string\0fileDirPath"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InteractiveViewerWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       5,    1,   97,    2, 0x06 /* Public */,
       8,    1,  100,    2, 0x06 /* Public */,
       9,    0,  103,    2, 0x06 /* Public */,
      10,    1,  104,    2, 0x06 /* Public */,
      11,    1,  107,    2, 0x06 /* Public */,
      12,    1,  110,    2, 0x06 /* Public */,
      13,    0,  113,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    2,  114,    2, 0x0a /* Public */,
      17,    1,  119,    2, 0x0a /* Public */,
      19,    0,  122,    2, 0x0a /* Public */,
      20,    0,  123,    2, 0x0a /* Public */,
      21,    0,  124,    2, 0x0a /* Public */,
      22,    0,  125,    2, 0x0a /* Public */,
      23,    0,  126,    2, 0x0a /* Public */,
      24,    1,  127,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6, QMetaType::QString,   15,   16,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 25,   26,

       0        // eod
};

void InteractiveViewerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        InteractiveViewerWidget *_t = static_cast<InteractiveViewerWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mouse_press_signal((*reinterpret_cast< Mesh::Point(*)>(_a[1]))); break;
        case 1: _t->mouse_move_signal((*reinterpret_cast< OpenMesh::Vec3d(*)>(_a[1]))); break;
        case 2: _t->mouse_release_signal((*reinterpret_cast< Mesh::Point(*)>(_a[1]))); break;
        case 3: _t->draw_from_out_signal(); break;
        case 4: _t->setMouseMode_signal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->set_edit_undo_enable_viewer_signal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->set_edit_redo_enable_viewer_signal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->ResetEditSignal(); break;
        case 8: _t->render_text_slot((*reinterpret_cast< OpenMesh::Vec3d(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: _t->set_t2_mouse_mode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->NoEdit(); break;
        case 11: _t->SeamEdit(); break;
        case 12: _t->AddSeam(); break;
        case 13: _t->UndoSeam(); break;
        case 14: _t->MeshCut(); break;
        case 15: _t->Click_to_BPE((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (InteractiveViewerWidget::*_t)(Mesh::Point );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InteractiveViewerWidget::mouse_press_signal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (InteractiveViewerWidget::*_t)(OpenMesh::Vec3d );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InteractiveViewerWidget::mouse_move_signal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (InteractiveViewerWidget::*_t)(Mesh::Point );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InteractiveViewerWidget::mouse_release_signal)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (InteractiveViewerWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InteractiveViewerWidget::draw_from_out_signal)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (InteractiveViewerWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InteractiveViewerWidget::setMouseMode_signal)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (InteractiveViewerWidget::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InteractiveViewerWidget::set_edit_undo_enable_viewer_signal)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (InteractiveViewerWidget::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InteractiveViewerWidget::set_edit_redo_enable_viewer_signal)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (InteractiveViewerWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InteractiveViewerWidget::ResetEditSignal)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject InteractiveViewerWidget::staticMetaObject = {
    { &MeshViewerWidget::staticMetaObject, qt_meta_stringdata_InteractiveViewerWidget.data,
      qt_meta_data_InteractiveViewerWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *InteractiveViewerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InteractiveViewerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_InteractiveViewerWidget.stringdata0))
        return static_cast<void*>(this);
    return MeshViewerWidget::qt_metacast(_clname);
}

int InteractiveViewerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MeshViewerWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void InteractiveViewerWidget::mouse_press_signal(Mesh::Point _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void InteractiveViewerWidget::mouse_move_signal(OpenMesh::Vec3d _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void InteractiveViewerWidget::mouse_release_signal(Mesh::Point _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void InteractiveViewerWidget::draw_from_out_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void InteractiveViewerWidget::setMouseMode_signal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void InteractiveViewerWidget::set_edit_undo_enable_viewer_signal(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void InteractiveViewerWidget::set_edit_redo_enable_viewer_signal(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void InteractiveViewerWidget::ResetEditSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
