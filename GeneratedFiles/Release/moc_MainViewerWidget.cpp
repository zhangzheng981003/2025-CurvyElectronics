/****************************************************************************
** Meta object code from reading C++ file 'MainViewerWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MeshViewer/MainViewerWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainViewerWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainViewerWidget_t {
    QByteArrayData data[24];
    char stringdata0[335];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainViewerWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainViewerWidget_t qt_meta_stringdata_MainViewerWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "MainViewerWidget"
QT_MOC_LITERAL(1, 17, 12), // "haveLoadMesh"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 8), // "filePath"
QT_MOC_LITERAL(4, 40, 24), // "setMouseMode_signal_main"
QT_MOC_LITERAL(5, 65, 23), // "setDrawMode_signal_main"
QT_MOC_LITERAL(6, 89, 27), // "set_edit_undo_enable_signal"
QT_MOC_LITERAL(7, 117, 27), // "set_edit_redo_enable_signal"
QT_MOC_LITERAL(8, 145, 15), // "open_mesh_query"
QT_MOC_LITERAL(9, 161, 15), // "save_mesh_query"
QT_MOC_LITERAL(10, 177, 16), // "saveOpenGLScreen"
QT_MOC_LITERAL(11, 194, 18), // "save_opengl_screen"
QT_MOC_LITERAL(12, 213, 3), // "str"
QT_MOC_LITERAL(13, 217, 11), // "update_mesh"
QT_MOC_LITERAL(14, 229, 14), // "clear_all_mesh"
QT_MOC_LITERAL(15, 244, 18), // "clear_all_selected"
QT_MOC_LITERAL(16, 263, 17), // "LoadMeshFromInner"
QT_MOC_LITERAL(17, 281, 2), // "OK"
QT_MOC_LITERAL(18, 284, 5), // "fname"
QT_MOC_LITERAL(19, 290, 10), // "print_info"
QT_MOC_LITERAL(20, 301, 11), // "ChooseModel"
QT_MOC_LITERAL(21, 313, 4), // "cont"
QT_MOC_LITERAL(22, 318, 8), // "LoadMesh"
QT_MOC_LITERAL(23, 327, 7) // "LoadSeg"

    },
    "MainViewerWidget\0haveLoadMesh\0\0filePath\0"
    "setMouseMode_signal_main\0"
    "setDrawMode_signal_main\0"
    "set_edit_undo_enable_signal\0"
    "set_edit_redo_enable_signal\0open_mesh_query\0"
    "save_mesh_query\0saveOpenGLScreen\0"
    "save_opengl_screen\0str\0update_mesh\0"
    "clear_all_mesh\0clear_all_selected\0"
    "LoadMeshFromInner\0OK\0fname\0print_info\0"
    "ChooseModel\0cont\0LoadMesh\0LoadSeg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainViewerWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,
       4,    1,  102,    2, 0x06 /* Public */,
       5,    1,  105,    2, 0x06 /* Public */,
       6,    1,  108,    2, 0x06 /* Public */,
       7,    1,  111,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,  114,    2, 0x0a /* Public */,
       9,    0,  115,    2, 0x0a /* Public */,
      10,    0,  116,    2, 0x0a /* Public */,
      11,    1,  117,    2, 0x0a /* Public */,
      13,    0,  120,    2, 0x0a /* Public */,
      14,    0,  121,    2, 0x0a /* Public */,
      15,    0,  122,    2, 0x0a /* Public */,
      16,    2,  123,    2, 0x0a /* Public */,
      19,    0,  128,    2, 0x0a /* Public */,
      20,    1,  129,    2, 0x0a /* Public */,
      22,    0,  132,    2, 0x0a /* Public */,
      23,    0,  133,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,   17,   18,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainViewerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainViewerWidget *_t = static_cast<MainViewerWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->haveLoadMesh((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->setMouseMode_signal_main((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setDrawMode_signal_main((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->set_edit_undo_enable_signal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->set_edit_redo_enable_signal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->open_mesh_query(); break;
        case 6: _t->save_mesh_query(); break;
        case 7: _t->saveOpenGLScreen(); break;
        case 8: _t->save_opengl_screen((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->update_mesh(); break;
        case 10: _t->clear_all_mesh(); break;
        case 11: _t->clear_all_selected(); break;
        case 12: _t->LoadMeshFromInner((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 13: _t->print_info(); break;
        case 14: _t->ChooseModel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->LoadMesh(); break;
        case 16: _t->LoadSeg(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MainViewerWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainViewerWidget::haveLoadMesh)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainViewerWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainViewerWidget::setMouseMode_signal_main)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MainViewerWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainViewerWidget::setDrawMode_signal_main)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MainViewerWidget::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainViewerWidget::set_edit_undo_enable_signal)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MainViewerWidget::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainViewerWidget::set_edit_redo_enable_signal)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject MainViewerWidget::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MainViewerWidget.data,
      qt_meta_data_MainViewerWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainViewerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainViewerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainViewerWidget.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int MainViewerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void MainViewerWidget::haveLoadMesh(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainViewerWidget::setMouseMode_signal_main(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainViewerWidget::setDrawMode_signal_main(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainViewerWidget::set_edit_undo_enable_signal(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainViewerWidget::set_edit_redo_enable_signal(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
