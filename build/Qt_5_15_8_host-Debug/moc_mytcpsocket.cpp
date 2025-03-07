/****************************************************************************
** Meta object code from reading C++ file 'mytcpsocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Datasystem/mytcpsocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mytcpsocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyTcpSocket_t {
    QByteArrayData data[17];
    char stringdata0[182];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyTcpSocket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyTcpSocket_t qt_meta_stringdata_MyTcpSocket = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MyTcpSocket"
QT_MOC_LITERAL(1, 12, 7), // "Timeout"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 11), // "RegisterMsg"
QT_MOC_LITERAL(4, 33, 7), // "RecvMsg"
QT_MOC_LITERAL(5, 41, 7), // "SendMsg"
QT_MOC_LITERAL(6, 49, 9), // "byteArray"
QT_MOC_LITERAL(7, 59, 12), // "ResetTimeout"
QT_MOC_LITERAL(8, 72, 9), // "OnTimeout"
QT_MOC_LITERAL(9, 82, 4), // "Init"
QT_MOC_LITERAL(10, 87, 14), // "AnalyzeRcvData"
QT_MOC_LITERAL(11, 102, 13), // "HandleRcvData"
QT_MOC_LITERAL(12, 116, 3), // "str"
QT_MOC_LITERAL(13, 120, 21), // "HandleVarRegisterData"
QT_MOC_LITERAL(14, 142, 3), // "msg"
QT_MOC_LITERAL(15, 146, 16), // "HandleVarAskData"
QT_MOC_LITERAL(16, 163, 18) // "HandleFirmwareData"

    },
    "MyTcpSocket\0Timeout\0\0RegisterMsg\0"
    "RecvMsg\0SendMsg\0byteArray\0ResetTimeout\0"
    "OnTimeout\0Init\0AnalyzeRcvData\0"
    "HandleRcvData\0str\0HandleVarRegisterData\0"
    "msg\0HandleVarAskData\0HandleFirmwareData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyTcpSocket[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    1,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   78,    2, 0x0a /* Public */,
       5,    1,   79,    2, 0x0a /* Public */,
       7,    0,   82,    2, 0x0a /* Public */,
       8,    0,   83,    2, 0x0a /* Public */,
       9,    0,   84,    2, 0x0a /* Public */,
      10,    0,   85,    2, 0x0a /* Public */,
      11,    1,   86,    2, 0x0a /* Public */,
      13,    1,   89,    2, 0x0a /* Public */,
      15,    1,   92,    2, 0x0a /* Public */,
      16,    1,   95,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QByteArrayList,   12,
    QMetaType::Void, QMetaType::QByteArray,   14,
    QMetaType::Void, QMetaType::QByteArray,   14,
    QMetaType::Void, QMetaType::QByteArray,   14,

       0        // eod
};

void MyTcpSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyTcpSocket *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->Timeout(); break;
        case 1: _t->RegisterMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->RecvMsg(); break;
        case 3: _t->SendMsg((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->ResetTimeout(); break;
        case 5: _t->OnTimeout(); break;
        case 6: _t->Init(); break;
        case 7: { bool _r = _t->AnalyzeRcvData();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->HandleRcvData((*reinterpret_cast< QList<QByteArray>(*)>(_a[1]))); break;
        case 9: _t->HandleVarRegisterData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 10: _t->HandleVarAskData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 11: _t->HandleFirmwareData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyTcpSocket::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyTcpSocket::Timeout)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MyTcpSocket::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyTcpSocket::RegisterMsg)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyTcpSocket::staticMetaObject = { {
    QMetaObject::SuperData::link<QTcpSocket::staticMetaObject>(),
    qt_meta_stringdata_MyTcpSocket.data,
    qt_meta_data_MyTcpSocket,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyTcpSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyTcpSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyTcpSocket.stringdata0))
        return static_cast<void*>(this);
    return QTcpSocket::qt_metacast(_clname);
}

int MyTcpSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void MyTcpSocket::Timeout()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MyTcpSocket::RegisterMsg(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
