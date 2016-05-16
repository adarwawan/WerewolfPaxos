/****************************************************************************
** Meta object code from reading C++ file 'comm_client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../WerewolfClient/comm_client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'comm_client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_comm_client_t {
    QByteArrayData data[12];
    char stringdata0[184];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_comm_client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_comm_client_t qt_meta_stringdata_comm_client = {
    {
QT_MOC_LITERAL(0, 0, 11), // "comm_client"
QT_MOC_LITERAL(1, 12, 16), // "on_fail_or_error"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 26), // "on_accept_prepare_proposal"
QT_MOC_LITERAL(4, 57, 12), // "QHostAddress"
QT_MOC_LITERAL(5, 70, 25), // "on_accept_accept_proposal"
QT_MOC_LITERAL(6, 96, 11), // "readMessage"
QT_MOC_LITERAL(7, 108, 16), // "prepare_proposal"
QT_MOC_LITERAL(8, 125, 15), // "prepareProposal"
QT_MOC_LITERAL(9, 141, 11), // "json_object"
QT_MOC_LITERAL(10, 153, 14), // "acceptProposal"
QT_MOC_LITERAL(11, 168, 15) // "accept_proposal"

    },
    "comm_client\0on_fail_or_error\0\0"
    "on_accept_prepare_proposal\0QHostAddress\0"
    "on_accept_accept_proposal\0readMessage\0"
    "prepare_proposal\0prepareProposal\0"
    "json_object\0acceptProposal\0accept_proposal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_comm_client[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       3,    3,   57,    2, 0x06 /* Public */,
       5,    3,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   71,    2, 0x0a /* Public */,
       7,    0,   72,    2, 0x0a /* Public */,
       8,    1,   73,    2, 0x0a /* Public */,
      10,    1,   76,    2, 0x0a /* Public */,
      11,    0,   79,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QJsonObject, 0x80000000 | 4, QMetaType::UShort,    2,    2,    2,
    QMetaType::Void, QMetaType::QJsonObject, 0x80000000 | 4, QMetaType::UShort,    2,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,    9,
    QMetaType::Void, QMetaType::QJsonObject,    9,
    QMetaType::Void,

       0        // eod
};

void comm_client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        comm_client *_t = static_cast<comm_client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_fail_or_error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->on_accept_prepare_proposal((*reinterpret_cast< QJsonObject(*)>(_a[1])),(*reinterpret_cast< QHostAddress(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 2: _t->on_accept_accept_proposal((*reinterpret_cast< QJsonObject(*)>(_a[1])),(*reinterpret_cast< QHostAddress(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 3: _t->readMessage(); break;
        case 4: _t->prepare_proposal(); break;
        case 5: _t->prepareProposal((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 6: _t->acceptProposal((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 7: _t->accept_proposal(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (comm_client::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&comm_client::on_fail_or_error)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (comm_client::*_t)(QJsonObject , QHostAddress , quint16 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&comm_client::on_accept_prepare_proposal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (comm_client::*_t)(QJsonObject , QHostAddress , quint16 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&comm_client::on_accept_accept_proposal)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject comm_client::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_comm_client.data,
      qt_meta_data_comm_client,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *comm_client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *comm_client::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_comm_client.stringdata0))
        return static_cast<void*>(const_cast< comm_client*>(this));
    return QObject::qt_metacast(_clname);
}

int comm_client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void comm_client::on_fail_or_error(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void comm_client::on_accept_prepare_proposal(QJsonObject _t1, QHostAddress _t2, quint16 _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void comm_client::on_accept_accept_proposal(QJsonObject _t1, QHostAddress _t2, quint16 _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
