/****************************************************************************
** Meta object code from reading C++ file 'gameplay.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../WerewolfClient/gameplay.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gameplay.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_gameplay_t {
    QByteArrayData data[12];
    char stringdata0[159];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_gameplay_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_gameplay_t qt_meta_stringdata_gameplay = {
    {
QT_MOC_LITERAL(0, 0, 8), // "gameplay"
QT_MOC_LITERAL(1, 9, 14), // "do_changephase"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 19), // "do_populate_players"
QT_MOC_LITERAL(4, 45, 19), // "do_proposal_prepare"
QT_MOC_LITERAL(5, 65, 7), // "message"
QT_MOC_LITERAL(6, 73, 12), // "QHostAddress"
QT_MOC_LITERAL(7, 86, 9), // "sender_ip"
QT_MOC_LITERAL(8, 96, 11), // "sender_port"
QT_MOC_LITERAL(9, 108, 18), // "do_proposal_accept"
QT_MOC_LITERAL(10, 127, 19), // "do_set_kpu_selected"
QT_MOC_LITERAL(11, 147, 11) // "do_set_rule"

    },
    "gameplay\0do_changephase\0\0do_populate_players\0"
    "do_proposal_prepare\0message\0QHostAddress\0"
    "sender_ip\0sender_port\0do_proposal_accept\0"
    "do_set_kpu_selected\0do_set_rule"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_gameplay[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       3,    0,   47,    2, 0x08 /* Private */,
       4,    3,   48,    2, 0x08 /* Private */,
       9,    3,   55,    2, 0x08 /* Private */,
      10,    0,   62,    2, 0x08 /* Private */,
      11,    1,   63,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject, 0x80000000 | 6, QMetaType::UShort,    5,    7,    8,
    QMetaType::Void, QMetaType::QJsonObject, 0x80000000 | 6, QMetaType::UShort,    5,    7,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,    5,

       0        // eod
};

void gameplay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        gameplay *_t = static_cast<gameplay *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->do_changephase((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 1: _t->do_populate_players(); break;
        case 2: _t->do_proposal_prepare((*reinterpret_cast< QJsonObject(*)>(_a[1])),(*reinterpret_cast< QHostAddress(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 3: _t->do_proposal_accept((*reinterpret_cast< QJsonObject(*)>(_a[1])),(*reinterpret_cast< QHostAddress(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 4: _t->do_set_kpu_selected(); break;
        case 5: _t->do_set_rule((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject gameplay::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_gameplay.data,
      qt_meta_data_gameplay,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *gameplay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gameplay::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_gameplay.stringdata0))
        return static_cast<void*>(const_cast< gameplay*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int gameplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
