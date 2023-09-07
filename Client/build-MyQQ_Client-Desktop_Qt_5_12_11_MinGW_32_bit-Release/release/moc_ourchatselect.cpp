/****************************************************************************
** Meta object code from reading C++ file 'ourchatselect.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MyQQ_Client/ourchatselect.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QSet>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ourchatselect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ourchatselect_t {
    QByteArrayData data[9];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ourchatselect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ourchatselect_t qt_meta_stringdata_ourchatselect = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ourchatselect"
QT_MOC_LITERAL(1, 14, 12), // "SIG_CheckYes"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 14), // "SIG_SendSelect"
QT_MOC_LITERAL(4, 43, 10), // "QSet<int>*"
QT_MOC_LITERAL(5, 54, 4), // "list"
QT_MOC_LITERAL(6, 59, 18), // "slot_deal_checkBox"
QT_MOC_LITERAL(7, 78, 2), // "id"
QT_MOC_LITERAL(8, 81, 20) // "on_pb_commit_clicked"

    },
    "ourchatselect\0SIG_CheckYes\0\0SIG_SendSelect\0"
    "QSet<int>*\0list\0slot_deal_checkBox\0"
    "id\0on_pb_commit_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ourchatselect[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    1,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   38,    2, 0x08 /* Private */,
       8,    0,   41,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,

       0        // eod
};

void ourchatselect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ourchatselect *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIG_CheckYes(); break;
        case 1: _t->SIG_SendSelect((*reinterpret_cast< QSet<int>*(*)>(_a[1]))); break;
        case 2: _t->slot_deal_checkBox((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_pb_commit_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ourchatselect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ourchatselect::SIG_CheckYes)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ourchatselect::*)(QSet<int> * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ourchatselect::SIG_SendSelect)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ourchatselect::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ourchatselect.data,
    qt_meta_data_ourchatselect,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ourchatselect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ourchatselect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ourchatselect.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ourchatselect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ourchatselect::SIG_CheckYes()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ourchatselect::SIG_SendSelect(QSet<int> * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
