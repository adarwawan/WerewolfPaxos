/****************************************************************************
** Meta object code from reading C++ file 'comm_server.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../WerewolfClient/comm_server.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'comm_server.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_comm_server_t {
    QByteArrayData data[12];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_comm_server_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_comm_server_t qt_meta_stringdata_comm_server = {
    {
QT_MOC_LITERAL(0, 0, 11), // "comm_server"
QT_MOC_LITERAL(1, 12, 8), // "on_login"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "on_ready"
QT_MOC_LITERAL(4, 31, 8), // "on_start"
QT_MOC_LITERAL(5, 40, 10), // "on_clients"
QT_MOC_LITERAL(6, 51, 14), // "on_changephase"
QT_MOC_LITERAL(7, 66, 9), // "connected"
QT_MOC_LITERAL(8, 76, 12), // "disconnected"
QT_MOC_LITERAL(9, 89, 11), // "sendMessage"
QT_MOC_LITERAL(10, 101, 7), // "message"
QT_MOC_LITERAL(11, 109, 11) // "readMessage"

    },
    "comm_server\0on_login\0\0on_ready\0on_start\0"
    "on_clients\0on_changephase\0connected\0"
    "disconnected\0sendMessage\0message\0"
    "readMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_comm_server[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    1,   61,    2, 0x06 /* Public */,
       5,    0,   64,    2, 0x06 /* Public */,
       6,    1,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   68,    2, 0x0a /* Public */,
       8,    0,   69,    2, 0x0a /* Public */,
       9,    1,   70,    2, 0x0a /* Public */,
      11,    0,   73,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,   10,
    QMetaType::Void,

       0        // eod
};

void comm_server::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        comm_server *_t = static_cast<comm_server *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_login(); break;
        case 1: _t->on_ready(); break;
        case 2: _t->on_start((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 3: _t->on_clients(); break;
        case 4: _t->on_changephase((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 5: _t->connected(); break;
        case 6: _t->disconnected(); break;
        case 7: _t->sendMessage((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 8: _t->readMessage(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (comm_server::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&comm_server::on_login)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (comm_server::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&comm_server::on_ready)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (comm_server::*_t)(QJsonObject );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&comm_server::on_start)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (comm_server::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&comm_server::on_clients)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (comm_server::*_t)(QJsonObject );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&comm_server::on_changephase)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject comm_server::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_comm_server.data,
      qt_meta_data_comm_server,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *comm_server::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *comm_server::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_comm_server.stringdata0))
        return static_cast<void*>(const_cast< comm_server*>(this));
    return QObject::qt_metacast(_clname);
}

int comm_server::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void comm_server::on_login()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void comm_server::on_ready()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void comm_server::on_start(QJsonObject _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void comm_server::on_clients()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void comm_server::on_changephase(QJsonObject _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
