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
    QByteArrayData data[8];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_comm_client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_comm_client_t qt_meta_stringdata_comm_client = {
    {
QT_MOC_LITERAL(0, 0, 11), // "comm_client"
QT_MOC_LITERAL(1, 12, 9), // "readyRead"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 16), // "prepare_proposal"
QT_MOC_LITERAL(4, 40, 15), // "prepareProposal"
QT_MOC_LITERAL(5, 56, 11), // "json_object"
QT_MOC_LITERAL(6, 68, 14), // "acceptProposal"
QT_MOC_LITERAL(7, 83, 15) // "accept_proposal"

    },
    "comm_client\0readyRead\0\0prepare_proposal\0"
    "prepareProposal\0json_object\0acceptProposal\0"
    "accept_proposal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_comm_client[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    1,   41,    2, 0x0a /* Public */,
       6,    1,   44,    2, 0x0a /* Public */,
       7,    0,   47,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,    5,
    QMetaType::Void, QMetaType::QJsonObject,    5,
    QMetaType::Void,

       0        // eod
};

void comm_client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        comm_client *_t = static_cast<comm_client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readyRead(); break;
        case 1: _t->prepare_proposal(); break;
        case 2: _t->prepareProposal((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 3: _t->acceptProposal((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 4: _t->accept_proposal(); break;
        default: ;
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
QT_END_MOC_NAMESPACE
