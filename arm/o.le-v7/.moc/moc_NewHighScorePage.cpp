/****************************************************************************
** Meta object code from reading C++ file 'NewHighScorePage.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/Pages/NewHighScorePage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NewHighScorePage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NewHighScorePage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,
      28,   26,   17,   17, 0x05,
      65,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      85,   17,   17,   17, 0x08,
     103,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_NewHighScorePage[] = {
    "NewHighScorePage\0\0close()\0,\0"
    "invokeTargetWithUri(QString,QString)\0"
    "shareNewHighScore()\0onReviewClicked()\0"
    "onShareClicked()\0"
};

void NewHighScorePage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NewHighScorePage *_t = static_cast<NewHighScorePage *>(_o);
        switch (_id) {
        case 0: _t->close(); break;
        case 1: _t->invokeTargetWithUri((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->shareNewHighScore(); break;
        case 3: _t->onReviewClicked(); break;
        case 4: _t->onShareClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData NewHighScorePage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NewHighScorePage::staticMetaObject = {
    { &Page::staticMetaObject, qt_meta_stringdata_NewHighScorePage,
      qt_meta_data_NewHighScorePage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NewHighScorePage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NewHighScorePage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NewHighScorePage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewHighScorePage))
        return static_cast<void*>(const_cast< NewHighScorePage*>(this));
    return Page::qt_metacast(_clname);
}

int NewHighScorePage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Page::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void NewHighScorePage::close()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void NewHighScorePage::invokeTargetWithUri(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NewHighScorePage::shareNewHighScore()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
