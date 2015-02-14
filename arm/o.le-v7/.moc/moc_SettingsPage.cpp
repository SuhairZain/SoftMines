/****************************************************************************
** Meta object code from reading C++ file 'SettingsPage.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/Pages/SettingsPage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SettingsPage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SettingsPage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      25,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      51,   13,   13,   13, 0x08,
      68,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SettingsPage[] = {
    "SettingsPage\0\0close(int)\0"
    "musicEnabledChanged(bool)\0onCloseClicked()\0"
    "onSelectedIndexChanged(int)\0"
};

void SettingsPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SettingsPage *_t = static_cast<SettingsPage *>(_o);
        switch (_id) {
        case 0: _t->close((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->musicEnabledChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->onCloseClicked(); break;
        case 3: _t->onSelectedIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SettingsPage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SettingsPage::staticMetaObject = {
    { &Page::staticMetaObject, qt_meta_stringdata_SettingsPage,
      qt_meta_data_SettingsPage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SettingsPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SettingsPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SettingsPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SettingsPage))
        return static_cast<void*>(const_cast< SettingsPage*>(this));
    return Page::qt_metacast(_clname);
}

int SettingsPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Page::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void SettingsPage::close(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SettingsPage::musicEnabledChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
