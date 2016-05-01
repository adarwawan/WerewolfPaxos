/****************************************************************************
** Meta object code from reading C++ file 'handler_server.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../WerewolfClient/handler_server.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'handler_server.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_handler_server_t {
    QByteArrayData data[8];
    char stringdata0[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_handler_server_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_handler_server_t qt_meta_stringdata_handler_server = {
    {
QT_MOC_LITERAL(0, 0, 14), // "handler_server"
QT_MOC_LITERAL(1, 15, 8), // "on_login"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 9), // "connected"
QT_MOC_LITERAL(4, 35, 12), // "disconnected"
QT_MOC_LITERAL(5, 48, 21), // "sendMessageJSONObject"
QT_MOC_LITERAL(6, 70, 7), // "message"
QT_MOC_LITERAL(7, 78, 11) // "readMessage"

    },
    "handler_server\0on_login\0\0connected\0"
    "disconnected\0sendMessageJSONObject\0"
    "message\0readMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_handler_server[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    1,   42,    2, 0x0a /* Public */,
       7,    0,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,    6,
    QMetaType::Void,

       0        // eod
};

void handler_server::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        handler_server *_t = static_cast<handler_server *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_login(); break;
        case 1: _t->connected(); break;
        case 2: _t->disconnected(); break;
        case 3: _t->sendMessageJSONObject((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 4: _t->readMessage(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (handler_server::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&handler_server::on_login)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject handler_server::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_handler_server.data,
      qt_meta_data_handler_server,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *handler_server::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *handler_server::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_handler_server.stringdata0))
        return static_cast<void*>(const_cast< handler_server*>(this));
    return QObject::qt_metacast(_clname);
}

int handler_server::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void handler_server::on_login()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
