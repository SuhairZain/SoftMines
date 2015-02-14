#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>
#include <bb/cascades/ActionItem>
#include <bb/cascades/Application>
#include <bb/cascades/Button>
#include <bb/cascades/Container>
#include <bb/cascades/CustomControl>
#include <bb/cascades/DeleteActionItem>
#include <bb/cascades/Divider>
#include <bb/cascades/DockLayout>
#include <bb/cascades/DoubleTapHandler>
#include <bb/cascades/HelpActionItem>
#include <bb/cascades/ImageButton>
#include <bb/cascades/ImageView>
#include <bb/system/InvokeManager>
#include <bb/system/InvokeRequest>
#include <bb/system/InvokeTargetReply>
#include <bb/cascades/Label>
//#include <bb/multimedia/MediaPlayer>
#include <bb/cascades/Menu>
#include <bb/cascades/Option>
#include <bb/cascades/Page>
#include <bb/cascades/RadioGroup>
#include <bb/cascades/SceneCover>
#include <bb/cascades/ScrollView>
#include <bb/cascades/SettingsActionItem>
#include <bb/cascades/Slider>
#include <bb/cascades/Sheet>
#include <bb/cascades/StackLayout>
//#include <bb/system/SystemDialog>
#include <bb/system/SystemToast>
#include <bb/cascades/TabbedPane>
#include <bb/cascades/TextField>
#include <bb/cascades/TextStyle>
#include <bb/cascades/TitleBar>

#include <bb/platform/bbm/Context>
#include <bb/platform/bbm/MessageService>
#include <bb/platform/bbm/UserProfile>


namespace bb
{
    namespace cascades
    {
        class Application;
    }
}

//using namespace bb::multimedia;
using namespace bb::cascades;
using namespace bb::system;

/*!
 * @brief Application object
 *
 *
 */

class ApplicationUI : public QObject
{
    Q_OBJECT
public:
    ApplicationUI(bb::cascades::Application *app);
    virtual ~ApplicationUI();
private slots:
	void checkForLevelChange();
	void checkWhatHappened(QString);
	//void confirmGameRestart();
	void closeSettingsSheet();
	void displayHelp();
	void displayHighScores();
	void displayInfo();
	void displayPauseScreen();
	void displaySettings();
	void gameIsAsleep();
	void gameIsAwake();
	void gameOver();
	void goToPrivacyPolicy(bb::cascades::TouchEvent*);
	void goToGameOnFB();
	void goToGamePage();
	void goToRubus();
	void goToSV();
//	void handleDiscardGameConfirmation(bb::system::SystemUiResult::Type);
	void handleHelpSlider(float);
	void handleHelpSliderImm(float);
	void handleLevelChange(int);
	void invokeFinished();
	void registrationStateUpdated(bb::platform::bbm::RegistrationState::Type);
	void setContentForHelp();
	void shareAllHighScores();
	void shareNewHighScore();
	void shareApp();
	void sheetClosed();
	void sheetOpened();
	void toggleTouchMethod(bb::cascades::Tab *);
	void updateClock();

private:
    void displaySheetFailure();
    void displaySheetHS();
    void displaySheetSuccess();
    void fillTheField();
    void initialiseGameField();//OK
    void setValues(int);
	//void setValuesToSquare();
	//void setValuesToNonMines();


    ActionItem *infoAction, *shareBBM, *highScores;
    //ActionItem *pauseGame;
    Container *gameRoot, *mineFieldContainer, *rowsContainer;
    DeleteActionItem *restartGame;
    HelpActionItem *appHelp;
    ImageButton *pauseGame;
    ImageView *helpImage;
    InvokeManager *invokeManager;
    InvokeRequest *invokeRequest;
    InvokeTargetReply *invokeReply;
    Label *timeInCover;
    Label *timeLabel, *countLabel;
    Label *textHowToPlay;
    Label *easy, *medium, *hard;
    Label *loseGameWarning;
    Label *pauseLevel, *pauseTime, *pauseCount;
    Label *hsLabel;
    Menu *appMenu;
    Page *rootPage, *helpPage, *infoPage, *highScoresPage, *settingsPage;
    Page *pausePage;
    Page *failurePage, *hsPage, *successPage;
    RadioGroup *levelChooser;
    ScrollView *mineField;
    SettingsActionItem *appSettings;
    Sheet *appSheet;
    Slider *helpSlider;
    //SystemDialog *discardConf;
    SystemToast *toast;
    Tab *uncoverMode, *flagMode;
    TabbedPane *modeChooser;

    bool helpFirstTime, infoFirstTime, highScoresFirstTime, settingsFirstTime;
    bool pauseFirstTime;
    bool failureFirst, highScoreFirst, successFirst;
    int helpLevel;

    int nRows, nCols, nMines, gamePlayTime;
    int levelSelected;
    int backupLevelSelected, backupnRows, backupnCols, backupnMines;
    int newHSEasy, newHSMedium, newHSHard;

    QSettings *savedHS;
    QTimer *gameTimer;

    bb::platform::bbm::UserProfile *m_userProfile;
    bb::platform::bbm::Context *m_context;
    bb::platform::bbm::MessageService *m_messageService;
};

class Square: public bb::cascades::CustomControl{
	Q_OBJECT

public:
	Square();
	virtual ~Square();

	ImageButton *square;
	Container *rootContainer;
	int value, posI, posJ;
	bool flagged;

	public slots:
	void checkIfAnySquaresLeft();
	void clearAllNearby(int, int);
	void emitDTSignal();
	void handleButtonClick();

	public:
	void checkAroundForZeroes(int, int);
	void checkAroundForZeroesInClear(int, int);
	void disableAndSetImage();
	void handleClear();
	int nOfZAroundXY(int, int, int);

	signals:
	void emitDoubleTapSignal(int, int);
};

#endif /* ApplicationUI_HPP_ */
