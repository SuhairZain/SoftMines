/****************************************************************************
** Meta object code from reading C++ file 'applicationui.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/applicationui.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'applicationui.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ApplicationUI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      29,   14,   14,   14, 0x08,
      49,   14,   14,   14, 0x08,
      63,   14,   14,   14, 0x08,
      81,   14,   14,   14, 0x08,
      96,   14,   14,   14, 0x08,
     110,   14,   14,   14, 0x08,
     131,   14,   14,   14, 0x08,
     155,   14,   14,   14, 0x08,
     176,   14,   14,   14, 0x08,
     197,   14,   14,   14, 0x08,
     212,   14,   14,   14, 0x08,
     230,  228,   14,   14, 0x08,
     269,   14,   14,   14, 0x08,
     312,   14,   14,   14, 0x08,
     340,   14,   14,   14, 0x08,
     379,   14,   14,   14, 0x08,
     401,   14,   14,   14, 0x08,
     430,   14,   14,   14, 0x08,
     456,   14,   14,   14, 0x08,
     469,   14,   14,   14, 0x08,
     538,   14,   14,   14, 0x08,
     559,   14,   14,   14, 0x08,
     571,   14,   14,   14, 0x08,
     591,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ApplicationUI[] = {
    "ApplicationUI\0\0displayHelp()\0"
    "displayHighScores()\0displayInfo()\0"
    "displaySettings()\0gameIsAsleep()\0"
    "gameIsAwake()\0onGameFinished(bool)\0"
    "onGameFlagsChanged(int)\0onGamePauseClicked()\0"
    "onGameResetClicked()\0onGameResume()\0"
    "onGameStarted()\0,\0"
    "onInvokeTargetWithUri(QString,QString)\0"
    "onMineFieldChanged(bb::cascades::Control*)\0"
    "onMusicEnabledChanged(bool)\0"
    "onNavPanePopEnded(bb::cascades::Page*)\0"
    "onNavPaneTopChanged()\0"
    "onOrientationAboutToChange()\0"
    "onSettingsPageClosed(int)\0popNavPane()\0"
    "registrationStateUpdated(bb::platform::bbm::RegistrationState::Type)\0"
    "shareAllHighScores()\0shareGame()\0"
    "shareNewHighScore()\0updateClock()\0"
};

void ApplicationUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ApplicationUI *_t = static_cast<ApplicationUI *>(_o);
        switch (_id) {
        case 0: _t->displayHelp(); break;
        case 1: _t->displayHighScores(); break;
        case 2: _t->displayInfo(); break;
        case 3: _t->displaySettings(); break;
        case 4: _t->gameIsAsleep(); break;
        case 5: _t->gameIsAwake(); break;
        case 6: _t->onGameFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->onGameFlagsChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->onGamePauseClicked(); break;
        case 9: _t->onGameResetClicked(); break;
        case 10: _t->onGameResume(); break;
        case 11: _t->onGameStarted(); break;
        case 12: _t->onInvokeTargetWithUri((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 13: _t->onMineFieldChanged((*reinterpret_cast< bb::cascades::Control*(*)>(_a[1]))); break;
        case 14: _t->onMusicEnabledChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->onNavPanePopEnded((*reinterpret_cast< bb::cascades::Page*(*)>(_a[1]))); break;
        case 16: _t->onNavPaneTopChanged(); break;
        case 17: _t->onOrientationAboutToChange(); break;
        case 18: _t->onSettingsPageClosed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->popNavPane(); break;
        case 20: _t->registrationStateUpdated((*reinterpret_cast< bb::platform::bbm::RegistrationState::Type(*)>(_a[1]))); break;
        case 21: _t->shareAllHighScores(); break;
        case 22: _t->shareGame(); break;
        case 23: _t->shareNewHighScore(); break;
        case 24: _t->updateClock(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ApplicationUI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ApplicationUI::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ApplicationUI,
      qt_meta_data_ApplicationUI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ApplicationUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ApplicationUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ApplicationUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ApplicationUI))
        return static_cast<void*>(const_cast< ApplicationUI*>(this));
    return QObject::qt_metacast(_clname);
}

int ApplicationUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
