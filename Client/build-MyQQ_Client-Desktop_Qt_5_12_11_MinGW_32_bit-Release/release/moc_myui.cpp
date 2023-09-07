/****************************************************************************
** Meta object code from reading C++ file 'myui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MyQQ_Client/myui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_myUI_t {
    QByteArrayData data[9];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myUI_t qt_meta_stringdata_myUI = {
    {
QT_MOC_LITERAL(0, 0, 4), // "myUI"
QT_MOC_LITERAL(1, 5, 13), // "SIG_addFriend"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 18), // "SIG_closeMyChatDlg"
QT_MOC_LITERAL(4, 39, 16), // "SIG_deleteFriend"
QT_MOC_LITERAL(5, 56, 18), // "on_pb_menu_clicked"
QT_MOC_LITERAL(6, 75, 25), // "slot_deal_pb_Menu_Clicked"
QT_MOC_LITERAL(7, 101, 8), // "QAction*"
QT_MOC_LITERAL(8, 110, 6) // "action"

    },
    "myUI\0SIG_addFriend\0\0SIG_closeMyChatDlg\0"
    "SIG_deleteFriend\0on_pb_menu_clicked\0"
    "slot_deal_pb_Menu_Clicked\0QAction*\0"
    "action"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myUI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    0,   41,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   42,    2, 0x08 /* Private */,
       6,    1,   43,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void myUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<myUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIG_addFriend(); break;
        case 1: _t->SIG_closeMyChatDlg(); break;
        case 2: _t->SIG_deleteFriend(); break;
        case 3: _t->on_pb_menu_clicked(); break;
        case 4: _t->slot_deal_pb_Menu_Clicked((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (myUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myUI::SIG_addFriend)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (myUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myUI::SIG_closeMyChatDlg)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (myUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myUI::SIG_deleteFriend)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject myUI::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_myUI.data,
    qt_meta_data_myUI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *myUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myUI.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int myUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void myUI::SIG_addFriend()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void myUI::SIG_closeMyChatDlg()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void myUI::SIG_deleteFriend()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
