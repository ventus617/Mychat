/****************************************************************************
** Meta object code from reading C++ file 'avdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MyQQ_Client/avdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'avdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_avdialog_t {
    QByteArrayData data[13];
    char stringdata0[183];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_avdialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_avdialog_t qt_meta_stringdata_avdialog = {
    {
QT_MOC_LITERAL(0, 0, 8), // "avdialog"
QT_MOC_LITERAL(1, 9, 14), // "SIG_audio_play"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 15), // "SIG_audio_pause"
QT_MOC_LITERAL(4, 41, 14), // "SIG_video_play"
QT_MOC_LITERAL(5, 56, 2), // "id"
QT_MOC_LITERAL(6, 59, 15), // "SIG_video_pause"
QT_MOC_LITERAL(7, 75, 9), // "SIG_close"
QT_MOC_LITERAL(8, 85, 19), // "on_qc_audio_clicked"
QT_MOC_LITERAL(9, 105, 19), // "on_pb_small_clicked"
QT_MOC_LITERAL(10, 125, 17), // "on_pb_max_clicked"
QT_MOC_LITERAL(11, 143, 19), // "on_pb_close_clicked"
QT_MOC_LITERAL(12, 163, 19) // "on_qc_video_clicked"

    },
    "avdialog\0SIG_audio_play\0\0SIG_audio_pause\0"
    "SIG_video_play\0id\0SIG_video_pause\0"
    "SIG_close\0on_qc_audio_clicked\0"
    "on_pb_small_clicked\0on_pb_max_clicked\0"
    "on_pb_close_clicked\0on_qc_video_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_avdialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    1,   66,    2, 0x06 /* Public */,
       6,    0,   69,    2, 0x06 /* Public */,
       7,    0,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   71,    2, 0x08 /* Private */,
       9,    0,   72,    2, 0x08 /* Private */,
      10,    0,   73,    2, 0x08 /* Private */,
      11,    0,   74,    2, 0x08 /* Private */,
      12,    0,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void avdialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<avdialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIG_audio_play(); break;
        case 1: _t->SIG_audio_pause(); break;
        case 2: _t->SIG_video_play((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->SIG_video_pause(); break;
        case 4: _t->SIG_close(); break;
        case 5: _t->on_qc_audio_clicked(); break;
        case 6: _t->on_pb_small_clicked(); break;
        case 7: _t->on_pb_max_clicked(); break;
        case 8: _t->on_pb_close_clicked(); break;
        case 9: _t->on_qc_video_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (avdialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&avdialog::SIG_audio_play)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (avdialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&avdialog::SIG_audio_pause)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (avdialog::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&avdialog::SIG_video_play)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (avdialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&avdialog::SIG_video_pause)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (avdialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&avdialog::SIG_close)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject avdialog::staticMetaObject = { {
    &CustomMoveDialog::staticMetaObject,
    qt_meta_stringdata_avdialog.data,
    qt_meta_data_avdialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *avdialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *avdialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_avdialog.stringdata0))
        return static_cast<void*>(this);
    return CustomMoveDialog::qt_metacast(_clname);
}

int avdialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CustomMoveDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void avdialog::SIG_audio_play()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void avdialog::SIG_audio_pause()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void avdialog::SIG_video_play(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void avdialog::SIG_video_pause()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void avdialog::SIG_close()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
