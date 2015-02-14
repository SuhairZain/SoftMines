/****************************************************************************
** Meta object code from reading C++ file 'MineField.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/MineAndField/MineField.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MineField.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MineField[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      30,   10,   10,   10, 0x05,
      52,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      68,   66,   10,   10, 0x08,
      96,   66,   10,   10, 0x08,
     119,   66,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MineField[] = {
    "MineField\0\0gameFinished(bool)\0"
    "gameFlagsChanged(int)\0gameStarted()\0"
    ",\0onMineDoubleTapped(int,int)\0"
    "onMineFlagged(int,int)\0onMineTapped(int,int)\0"
};

void MineField::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MineField *_t = static_cast<MineField *>(_o);
        switch (_id) {
        case 0: _t->gameFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->gameFlagsChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->gameStarted(); break;
        case 3: _t->onMineDoubleTapped((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->onMineFlagged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->onMineTapped((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MineField::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MineField::staticMetaObject = {
    { &Container::staticMetaObject, qt_meta_stringdata_MineField,
      qt_meta_data_MineField, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MineField::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MineField::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MineField::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MineField))
        return static_cast<void*>(const_cast< MineField*>(this));
    return Container::qt_metacast(_clname);
}

int MineField::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Container::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void MineField::gameFinished(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MineField::gameFlagsChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MineField::gameStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
