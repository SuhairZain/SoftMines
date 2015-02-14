/****************************************************************************
** Meta object code from reading C++ file 'SuccessPage.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/Pages/SuccessPage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SuccessPage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SuccessPage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      23,   21,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      60,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SuccessPage[] = {
    "SuccessPage\0\0close()\0,\0"
    "invokeTargetWithUri(QString,QString)\0"
    "onReviewClicked()\0"
};

void SuccessPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SuccessPage *_t = static_cast<SuccessPage *>(_o);
        switch (_id) {
        case 0: _t->close(); break;
        case 1: _t->invokeTargetWithUri((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->onReviewClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SuccessPage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SuccessPage::staticMetaObject = {
    { &Page::staticMetaObject, qt_meta_stringdata_SuccessPage,
      qt_meta_data_SuccessPage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SuccessPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SuccessPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SuccessPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SuccessPage))
        return static_cast<void*>(const_cast< SuccessPage*>(this));
    return Page::qt_metacast(_clname);
}

int SuccessPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Page::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SuccessPage::close()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SuccessPage::invokeTargetWithUri(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
