/****************************************************************************
** Meta object code from reading C++ file 'chatdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MyQQ_Client/chatdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chatdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_chatdialog_t {
    QByteArrayData data[25];
    char stringdata0[307];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_chatdialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_chatdialog_t qt_meta_stringdata_chatdialog = {
    {
QT_MOC_LITERAL(0, 0, 10), // "chatdialog"
QT_MOC_LITERAL(1, 11, 11), // "SIG_SendMsg"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 4), // "m_id"
QT_MOC_LITERAL(4, 29, 7), // "content"
QT_MOC_LITERAL(5, 37, 4), // "time"
QT_MOC_LITERAL(6, 42, 13), // "SIG_getSelect"
QT_MOC_LITERAL(7, 56, 12), // "SIG_SendFile"
QT_MOC_LITERAL(8, 69, 8), // "fileName"
QT_MOC_LITERAL(9, 78, 13), // "SIG_pauseFile"
QT_MOC_LITERAL(10, 92, 2), // "id"
QT_MOC_LITERAL(11, 95, 15), // "SIG_GetMoreChat"
QT_MOC_LITERAL(12, 111, 8), // "startnum"
QT_MOC_LITERAL(13, 120, 6), // "endnum"
QT_MOC_LITERAL(14, 127, 8), // "friendid"
QT_MOC_LITERAL(15, 136, 11), // "SIG_TALK_RQ"
QT_MOC_LITERAL(16, 148, 18), // "on_pb_file_clicked"
QT_MOC_LITERAL(17, 167, 18), // "on_pb_talk_clicked"
QT_MOC_LITERAL(18, 186, 21), // "on_pb_ourchat_clicked"
QT_MOC_LITERAL(19, 208, 20), // "on_pb_commit_clicked"
QT_MOC_LITERAL(20, 229, 24), // "on_pb_file_pause_clicked"
QT_MOC_LITERAL(21, 254, 22), // "on_pb_morechat_clicked"
QT_MOC_LITERAL(22, 277, 10), // "closeEvent"
QT_MOC_LITERAL(23, 288, 12), // "QCloseEvent*"
QT_MOC_LITERAL(24, 301, 5) // "event"

    },
    "chatdialog\0SIG_SendMsg\0\0m_id\0content\0"
    "time\0SIG_getSelect\0SIG_SendFile\0"
    "fileName\0SIG_pauseFile\0id\0SIG_GetMoreChat\0"
    "startnum\0endnum\0friendid\0SIG_TALK_RQ\0"
    "on_pb_file_clicked\0on_pb_talk_clicked\0"
    "on_pb_ourchat_clicked\0on_pb_commit_clicked\0"
    "on_pb_file_pause_clicked\0"
    "on_pb_morechat_clicked\0closeEvent\0"
    "QCloseEvent*\0event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_chatdialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   79,    2, 0x06 /* Public */,
       6,    0,   86,    2, 0x06 /* Public */,
       7,    2,   87,    2, 0x06 /* Public */,
       9,    1,   92,    2, 0x06 /* Public */,
      11,    3,   95,    2, 0x06 /* Public */,
      15,    1,  102,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    0,  105,    2, 0x08 /* Private */,
      17,    0,  106,    2, 0x08 /* Private */,
      18,    0,  107,    2, 0x08 /* Private */,
      19,    0,  108,    2, 0x08 /* Private */,
      20,    0,  109,    2, 0x08 /* Private */,
      21,    0,  110,    2, 0x08 /* Private */,
      22,    1,  111,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString,    3,    4,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   12,   13,   14,
    QMetaType::Void, QMetaType::Int,   14,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 23,   24,

       0        // eod
};

void chatdialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<chatdialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIG_SendMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->SIG_getSelect(); break;
        case 2: _t->SIG_SendFile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->SIG_pauseFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->SIG_GetMoreChat((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->SIG_TALK_RQ((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_pb_file_clicked(); break;
        case 7: _t->on_pb_talk_clicked(); break;
        case 8: _t->on_pb_ourchat_clicked(); break;
        case 9: _t->on_pb_commit_clicked(); break;
        case 10: _t->on_pb_file_pause_clicked(); break;
        case 11: _t->on_pb_morechat_clicked(); break;
        case 12: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (chatdialog::*)(int , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&chatdialog::SIG_SendMsg)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (chatdialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&chatdialog::SIG_getSelect)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (chatdialog::*)(int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&chatdialog::SIG_SendFile)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (chatdialog::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&chatdialog::SIG_pauseFile)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (chatdialog::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&chatdialog::SIG_GetMoreChat)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (chatdialog::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&chatdialog::SIG_TALK_RQ)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject chatdialog::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_chatdialog.data,
    qt_meta_data_chatdialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *chatdialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *chatdialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_chatdialog.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int chatdialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void chatdialog::SIG_SendMsg(int _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void chatdialog::SIG_getSelect()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void chatdialog::SIG_SendFile(int _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void chatdialog::SIG_pauseFile(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void chatdialog::SIG_GetMoreChat(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void chatdialog::SIG_TALK_RQ(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
