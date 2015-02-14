/****************************************************************************
** Meta object code from reading C++ file 'InfoPage.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/Pages/InfoPage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InfoPage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InfoPage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      20,   18,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      57,    9,    9,    9, 0x08,
      72,    9,    9,    9, 0x08,
      87,    9,    9,    9, 0x08,
      96,    9,    9,    9, 0x08,
     108,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_InfoPage[] = {
    "InfoPage\0\0close()\0,\0"
    "invokeTargetWithUri(QString,QString)\0"
    "goToGameOnFB()\0goToGamePage()\0goToPP()\0"
    "goToRubus()\0goToSV()\0"
};

void InfoPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        InfoPage *_t = static_cast<InfoPage *>(_o);
        switch (_id) {
        case 0: _t->close(); break;
        case 1: _t->invokeTargetWithUri((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->goToGameOnFB(); break;
        case 3: _t->goToGamePage(); break;
        case 4: _t->goToPP(); break;
        case 5: _t->goToRubus(); break;
        case 6: _t->goToSV(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData InfoPage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject InfoPage::staticMetaObject = {
    { &Page::staticMetaObject, qt_meta_stringdata_InfoPage,
      qt_meta_data_InfoPage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InfoPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InfoPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InfoPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InfoPage))
        return static_cast<void*>(const_cast< InfoPage*>(this));
    return Page::qt_metacast(_clname);
}

int InfoPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Page::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void InfoPage::close()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void InfoPage::invokeTargetWithUri(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
