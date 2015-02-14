#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>
#include <bb/cascades/Application>
#include <bb/system/InvokeManager>
#include <bb/multimedia/MediaPlayer>
#include <bb/cascades/NavigationPane>
//#include <bb/cascades/Page>
#include <bb/cascades/ScrollView>
#include <bb/cascades/Sheet>
#include <bb/system/SystemToast>

#include <bb/platform/bbm/Context>
#include <bb/platform/bbm/MessageService>
#include <bb/platform/bbm/UserProfile>

using namespace bb::cascades;
using namespace bb::system;

#include "Controls/StatusBar.h"

class ApplicationUI : public QObject
{
    Q_OBJECT
private slots:
	void displayHelp();
	void displayHighScores();
	void displayInfo();
	void displaySettings();
	void gameIsAsleep();
	void gameIsAwake();
	void onGameFinished(bool);
	void onGameFlagsChanged(int);
	void onGamePauseClicked();
	void onGameResetClicked();
	void onGameResume();
	void onGameStarted();
	void onInvokeTargetWithUri(QString, QString);
	void onMineFieldChanged(bb::cascades::Control*);
	void onMusicEnabledChanged(bool);
	void onNavPanePopEnded(bb::cascades::Page*);
	void onNavPaneTopChanged();
	void onOrientationAboutToChange();
	void onSettingsPageClosed(int);
	void popNavPane();
	void registrationStateUpdated(bb::platform::bbm::RegistrationState::Type);
	void shareAllHighScores();
    void shareGame();
	void shareNewHighScore();
	void updateClock();

private:
	void setValues(int);

    InvokeManager *invokeManager;
    bb::multimedia::MediaPlayer *mediaPlayer;
    NavigationPane *navPane;
    ScrollView *mineField;
    StatusBar *gameStatus;
    SystemToast *toast;

    int gamePlayTime;
    int levelSelected, nRows, nCols, nMines, flagsLeft;
    int scrW, scrH;
    //int newHSEasy, newHSMedium, newHSHard;
    bool gameInProgress;

    QTimer *gameTimer;

    bb::platform::bbm::UserProfile *m_userProfile;
    bb::platform::bbm::Context *m_context;
    bb::platform::bbm::MessageService *m_messageService;

public:
    ApplicationUI(Application *app);
};

#endif /* ApplicationUI_HPP_ */
