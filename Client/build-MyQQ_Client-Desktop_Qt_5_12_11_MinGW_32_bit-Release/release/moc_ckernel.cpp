/****************************************************************************
** Meta object code from reading C++ file 'ckernel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MyQQ_Client/ckernel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QSet>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ckernel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ckernel_t {
    QByteArrayData data[53];
    char stringdata0[617];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ckernel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ckernel_t qt_meta_stringdata_ckernel = {
    {
QT_MOC_LITERAL(0, 0, 7), // "ckernel"
QT_MOC_LITERAL(1, 8, 14), // "SIG_SendSelect"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 14), // "ourchatselect*"
QT_MOC_LITERAL(4, 39, 8), // "m_select"
QT_MOC_LITERAL(5, 48, 14), // "slot_readyData"
QT_MOC_LITERAL(6, 63, 5), // "char*"
QT_MOC_LITERAL(7, 69, 3), // "buf"
QT_MOC_LITERAL(8, 73, 4), // "nLen"
QT_MOC_LITERAL(9, 78, 2), // "IP"
QT_MOC_LITERAL(10, 81, 19), // "slot_registerCommit"
QT_MOC_LITERAL(11, 101, 3), // "tel"
QT_MOC_LITERAL(12, 105, 4), // "name"
QT_MOC_LITERAL(13, 110, 8), // "password"
QT_MOC_LITERAL(14, 119, 16), // "slot_LogInCommit"
QT_MOC_LITERAL(15, 136, 12), // "slot_sendMsg"
QT_MOC_LITERAL(16, 149, 2), // "ID"
QT_MOC_LITERAL(17, 152, 7), // "content"
QT_MOC_LITERAL(18, 160, 4), // "time"
QT_MOC_LITERAL(19, 165, 16), // "slot_showChatDlg"
QT_MOC_LITERAL(20, 182, 19), // "slot_showOurChatDlg"
QT_MOC_LITERAL(21, 202, 14), // "slot_addFriend"
QT_MOC_LITERAL(22, 217, 18), // "slot_closeLogInDlg"
QT_MOC_LITERAL(23, 236, 17), // "slot_closeMyUIDlg"
QT_MOC_LITERAL(24, 254, 17), // "slot_deleteFriend"
QT_MOC_LITERAL(25, 272, 15), // "slot_ShowSelect"
QT_MOC_LITERAL(26, 288, 17), // "slot_selectFriend"
QT_MOC_LITERAL(27, 306, 10), // "QSet<int>*"
QT_MOC_LITERAL(28, 317, 3), // "set"
QT_MOC_LITERAL(29, 321, 16), // "slot_Our_sendMsg"
QT_MOC_LITERAL(30, 338, 14), // "slot_send_file"
QT_MOC_LITERAL(31, 353, 8), // "filename"
QT_MOC_LITERAL(32, 362, 15), // "slot_pause_file"
QT_MOC_LITERAL(33, 378, 17), // "slot_getmore_chat"
QT_MOC_LITERAL(34, 396, 8), // "startnum"
QT_MOC_LITERAL(35, 405, 6), // "endnum"
QT_MOC_LITERAL(36, 412, 8), // "friendid"
QT_MOC_LITERAL(37, 421, 20), // "slot_getmore_ourchat"
QT_MOC_LITERAL(38, 442, 6), // "linkid"
QT_MOC_LITERAL(39, 449, 12), // "slot_talk_rq"
QT_MOC_LITERAL(40, 462, 15), // "slot_close_talk"
QT_MOC_LITERAL(41, 478, 15), // "slot_audio_play"
QT_MOC_LITERAL(42, 494, 16), // "slot_audio_pause"
QT_MOC_LITERAL(43, 511, 15), // "slot_video_play"
QT_MOC_LITERAL(44, 527, 2), // "id"
QT_MOC_LITERAL(45, 530, 16), // "slot_video_pause"
QT_MOC_LITERAL(46, 547, 17), // "slot_refreshvideo"
QT_MOC_LITERAL(47, 565, 4), // "m_id"
QT_MOC_LITERAL(48, 570, 7), // "QImage&"
QT_MOC_LITERAL(49, 578, 3), // "img"
QT_MOC_LITERAL(50, 582, 15), // "slot_videoFrame"
QT_MOC_LITERAL(51, 598, 15), // "slot_audioFrame"
QT_MOC_LITERAL(52, 614, 2) // "ba"

    },
    "ckernel\0SIG_SendSelect\0\0ourchatselect*\0"
    "m_select\0slot_readyData\0char*\0buf\0"
    "nLen\0IP\0slot_registerCommit\0tel\0name\0"
    "password\0slot_LogInCommit\0slot_sendMsg\0"
    "ID\0content\0time\0slot_showChatDlg\0"
    "slot_showOurChatDlg\0slot_addFriend\0"
    "slot_closeLogInDlg\0slot_closeMyUIDlg\0"
    "slot_deleteFriend\0slot_ShowSelect\0"
    "slot_selectFriend\0QSet<int>*\0set\0"
    "slot_Our_sendMsg\0slot_send_file\0"
    "filename\0slot_pause_file\0slot_getmore_chat\0"
    "startnum\0endnum\0friendid\0slot_getmore_ourchat\0"
    "linkid\0slot_talk_rq\0slot_close_talk\0"
    "slot_audio_play\0slot_audio_pause\0"
    "slot_video_play\0id\0slot_video_pause\0"
    "slot_refreshvideo\0m_id\0QImage&\0img\0"
    "slot_videoFrame\0slot_audioFrame\0ba"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ckernel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  149,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    3,  152,    2, 0x0a /* Public */,
      10,    3,  159,    2, 0x0a /* Public */,
      14,    2,  166,    2, 0x0a /* Public */,
      15,    3,  171,    2, 0x0a /* Public */,
      19,    1,  178,    2, 0x0a /* Public */,
      20,    1,  181,    2, 0x0a /* Public */,
      21,    0,  184,    2, 0x0a /* Public */,
      22,    0,  185,    2, 0x0a /* Public */,
      23,    0,  186,    2, 0x0a /* Public */,
      24,    0,  187,    2, 0x0a /* Public */,
      25,    0,  188,    2, 0x0a /* Public */,
      26,    1,  189,    2, 0x0a /* Public */,
      29,    3,  192,    2, 0x0a /* Public */,
      30,    2,  199,    2, 0x0a /* Public */,
      32,    1,  204,    2, 0x0a /* Public */,
      33,    3,  207,    2, 0x0a /* Public */,
      37,    3,  214,    2, 0x0a /* Public */,
      39,    1,  221,    2, 0x0a /* Public */,
      40,    0,  224,    2, 0x0a /* Public */,
      41,    0,  225,    2, 0x0a /* Public */,
      42,    0,  226,    2, 0x0a /* Public */,
      43,    1,  227,    2, 0x0a /* Public */,
      45,    0,  230,    2, 0x0a /* Public */,
      46,    3,  231,    2, 0x0a /* Public */,
      50,    1,  238,    2, 0x0a /* Public */,
      51,    1,  241,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int, QMetaType::Long,    7,    8,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   11,   12,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   11,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString,   16,   17,   18,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 27,   28,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString,   16,   17,   18,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   16,   31,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   34,   35,   36,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   34,   35,   38,
    QMetaType::Void, QMetaType::Int,   36,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 48,   44,   47,   49,
    QMetaType::Void, QMetaType::QImage,   49,
    QMetaType::Void, QMetaType::QByteArray,   52,

       0        // eod
};

void ckernel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ckernel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIG_SendSelect((*reinterpret_cast< ourchatselect*(*)>(_a[1]))); break;
        case 1: _t->slot_readyData((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< long(*)>(_a[3]))); break;
        case 2: _t->slot_registerCommit((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 3: _t->slot_LogInCommit((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->slot_sendMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 5: _t->slot_showChatDlg((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slot_showOurChatDlg((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->slot_addFriend(); break;
        case 8: _t->slot_closeLogInDlg(); break;
        case 9: _t->slot_closeMyUIDlg(); break;
        case 10: _t->slot_deleteFriend(); break;
        case 11: _t->slot_ShowSelect(); break;
        case 12: _t->slot_selectFriend((*reinterpret_cast< QSet<int>*(*)>(_a[1]))); break;
        case 13: _t->slot_Our_sendMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 14: _t->slot_send_file((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 15: _t->slot_pause_file((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->slot_getmore_chat((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 17: _t->slot_getmore_ourchat((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 18: _t->slot_talk_rq((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->slot_close_talk(); break;
        case 20: _t->slot_audio_play(); break;
        case 21: _t->slot_audio_pause(); break;
        case 22: _t->slot_video_play((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->slot_video_pause(); break;
        case 24: _t->slot_refreshvideo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QImage(*)>(_a[3]))); break;
        case 25: _t->slot_videoFrame((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 26: _t->slot_audioFrame((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ourchatselect* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ckernel::*)(ourchatselect * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ckernel::SIG_SendSelect)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ckernel::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ckernel.data,
    qt_meta_data_ckernel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ckernel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ckernel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ckernel.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ckernel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    }
    return _id;
}

// SIGNAL 0
void ckernel::SIG_SendSelect(ourchatselect * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
