/****************************************************************************
** Meta object code from reading C++ file 'Mine.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/MineAndField/Mine.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Mine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Mine[] = {

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
       8,    6,    5,    5, 0x05,
      34,    6,    5,    5, 0x05,
      55,    6,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
      75,    5,    5,    5, 0x0a,
      92,    5,    5,    5, 0x0a,
     108,    5,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Mine[] = {
    "Mine\0\0,\0mineDoubleTapped(int,int)\0"
    "mineFlagged(int,int)\0mineTapped(int,int)\0"
    "onDoubleTapped()\0onLongPressed()\0"
    "onTapped()\0"
};

void Mine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Mine *_t = static_cast<Mine *>(_o);
        switch (_id) {
        case 0: _t->mineDoubleTapped((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->mineFlagged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->mineTapped((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->onDoubleTapped(); break;
        case 4: _t->onLongPressed(); break;
        case 5: _t->onTapped(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Mine::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Mine::staticMetaObject = {
    { &ImageButton::staticMetaObject, qt_meta_stringdata_Mine,
      qt_meta_data_Mine, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Mine::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Mine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Mine::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Mine))
        return static_cast<void*>(const_cast< Mine*>(this));
    return ImageButton::qt_metacast(_clname);
}

int Mine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ImageButton::qt_metacall(_c, _id, _a);
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
void Mine::mineDoubleTapped(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Mine::mineFlagged(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Mine::mineTapped(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
