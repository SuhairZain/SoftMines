#include "applicationui.hpp"

#include "MineAndField/MineField.h"

#include "Pages/FailurePage.h"
#include "Pages/HelpPage.h"
#include "Pages/HighScoresPage.h"
#include "Pages/InfoPage.h"
#include "Pages/NewHighScorePage.h"
#include "Pages/PausePage.h"
#include "Pages/SettingsPage.h"
#include "Pages/SuccessPage.h"

#include <bb/cascades/ActionItem>
#include <bb/cascades/Container>
#include <bb/device/DisplayInfo>
#include <bb/cascades/DockLayout>
#include <bb/cascades/HelpActionItem>
#include <bb/cascades/ImageView>
#include <bb/system/InvokeRequest>
#include <bb/system/InvokeTargetReply>
#include <bb/cascades/Menu>
#include <bb/cascades/OrientationSupport>
#include <bb/cascades/SceneCover>
#include <bb/cascades/SettingsActionItem>
#include <bb/cascades/StackLayoutProperties>

ApplicationUI::ApplicationUI(Application *app) : QObject(app)
{
    bb::device::DisplayInfo dispInfo;
    scrW = dispInfo.pixelSize().width();
    scrH = dispInfo.pixelSize().height();

    invokeManager = new InvokeManager(this);
    m_userProfile = NULL;
    m_messageService = NULL;

    toast = new SystemToast(this);

    gamePlayTime = 0;
    gameTimer = new QTimer(this);
    gameTimer->setInterval(1000);
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(updateClock()));

    TextStyle textStyle;
    textStyle.setFontWeight(FontWeight::W400);
    textStyle.setTextAlign(TextAlign::Center);
    textStyle.setFontSize(FontSize::XXLarge);

    HelpActionItem *appHelp = HelpActionItem::create().
            onTriggered(this, SLOT(displayHelp()));

    ActionItem *infoAction = ActionItem::create().
            image("asset:///images/icons/ic_info.png").
            title("Info").
            onTriggered(this, SLOT(displayInfo()));

    ActionItem *shareBBM = ActionItem::create().
            image("asset:///images/icons/ic_bbm.png").
            title("Share game").
            onTriggered(this, SLOT(shareGame()));

    ActionItem *highScores = ActionItem::create().
            image("asset:///images/icons/ic_highscores.png").
            title("High scores").
            onTriggered(this, SLOT(displayHighScores()));

    SettingsActionItem *appSettings = SettingsActionItem::create().
            onTriggered(this, SLOT(displaySettings()));

    Menu *appMenu = Menu::create().
            addAction(infoAction).
            addAction(shareBBM).
            addAction(highScores).
            help(appHelp).
            settings(appSettings);
    app->setMenu(appMenu);

    ImageView *coverLogo = ImageView::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center).
            image("asset:///images/coverImage.png");

    Container *coverC = Container::create().
            layout(DockLayout::create()).
            add(coverLogo);

    app->setCover(SceneCover::create().content(coverC));

    gameInProgress = FALSE;

    mineField = ScrollView::create().
            scrollMode(ScrollMode::Both).
            overScrollEffectMode(OverScrollEffectMode::OnScroll).
            pinchToZoomEnabled(TRUE);//.
    //content(mines).

    Container *rootC = Container::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center).
            //add(gameStatus).
            add(mineField);

    Container *finalRootC = Container::create().
            background(Color::fromARGB(0xff515151)).
            layout(DockLayout::create()).
            add(rootC);

    navPane = NavigationPane::create().
            peek(FALSE).
            backButtons(FALSE).
            add(Page::create().content(finalRootC)).
            connect(SIGNAL(popTransitionEnded(bb::cascades::Page*)), this, SLOT(onNavPanePopEnded(bb::cascades::Page*))).
            connect(SIGNAL(topChanged(bb::cascades::Page*)), this, SLOT(onNavPaneTopChanged()));

    QSettings savedValues("Suhair Zain", "Soft Mines");
    if(savedValues.value("levelSelected").isNull())
    {
        savedValues.setValue("levelSelected", 0);
        savedValues.setValue("easy", 9999);
        savedValues.setValue("medium", 9999);
        savedValues.setValue("hard", 9999);
        savedValues.setValue("insane", 9999);
        savedValues.setValue("playMusic", TRUE);
        savedValues.sync();
        displayHelp();
    }
    setValues(savedValues.value("levelSelected").toInt());

    flagsLeft = nMines;
    MineField *mines = new MineField(nRows, nCols, nMines);
    connect(mines, SIGNAL(gameStarted()), this, SLOT(onGameStarted()));
    connect(mines, SIGNAL(gameFinished(bool)), this, SLOT(onGameFinished(bool)));
    connect(mines, SIGNAL(gameFlagsChanged(int)), this, SLOT(onGameFlagsChanged(int)));
    mineField->setContent(mines);
    connect(mineField, SIGNAL(contentChanged(bb::cascades::Control*)),
            this, SLOT(onMineFieldChanged(bb::cascades::Control*)));

    int horDist=scrW, verDist=scrH;
    if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
    {
        int temp = horDist;
        horDist = verDist;
        verDist = temp;
    }
    verDist -= 128;

    if(horDist/nCols > verDist/nRows)
    {
        mineField->scrollViewProperties()->setMinContentScale(horDist/ float(48*nCols));
        mineField->scrollViewProperties()->setMaxContentScale(2*horDist/ float(48*nCols));
    }
    else
    {
        mineField->scrollViewProperties()->setMinContentScale(verDist/ float(48*nRows));
        mineField->scrollViewProperties()->setMaxContentScale(2*verDist/ float(48*nRows));
    }
    connect(OrientationSupport::instance(), SIGNAL(orientationAboutToChange(bb::cascades::UIOrientation::Type)),
            this, SLOT(onOrientationAboutToChange()));

    gameStatus = new StatusBar;
    gameStatus->setCount(nMines);
    connect(gameStatus, SIGNAL(pauseClicked()), this, SLOT(onGamePauseClicked()));
    connect(gameStatus, SIGNAL(resetClicked()), this, SLOT(onGameResetClicked()));
    //rootC->add(gameStatus);
    rootC->insert(0, gameStatus);

    connect(app, SIGNAL(asleep()), this, SLOT(gameIsAsleep()));
    connect(app, SIGNAL(awake()), this, SLOT(gameIsAwake()));

    app->setScene(navPane);

    m_context = new bb::platform::bbm::Context(QUuid("8c3660de-8c22-4af3-bf71-456a08e0c910"), this);
    if(m_context->registrationState() != bb::platform::bbm::RegistrationState::Allowed)
    {
        connect(m_context, SIGNAL(registrationStateUpdated (bb::platform::bbm::RegistrationState::Type)), this, SLOT(registrationStateUpdated (bb::platform::bbm::RegistrationState::Type)));
        m_context->requestRegisterApplication();
    }

    mediaPlayer = new bb::multimedia::MediaPlayer(app);
    mediaPlayer->setRepeatMode(bb::multimedia::RepeatMode::Track);
    mediaPlayer->setSourceUrl(QUrl("asset:///sounds/bg.mp3"));

    if(savedValues.value("playMusic").toBool())
        mediaPlayer->play();
}

void ApplicationUI::displayHelp()
{
    HelpPage *helpPage = new HelpPage;
    connect(helpPage, SIGNAL(close()), this, SLOT(popNavPane()));
    navPane->push(helpPage);
}

void ApplicationUI::displayHighScores()
{
    QSettings savedValues("Suhair Zain", "Soft Mines");
    int easy = savedValues.value("easy").toInt();
    int medium = savedValues.value("medium").toInt();
    int hard = savedValues.value("hard").toInt();
    int insane = savedValues.value("insane").toInt();
    HighScoresPage *hsPage = new HighScoresPage(easy, medium, hard, insane);
    connect(hsPage, SIGNAL(close()), this, SLOT(popNavPane()));
    connect(hsPage, SIGNAL(invokeTargetWithUri(QString, QString)),
            this, SLOT(onInvokeTargetWithUri(QString, QString)));
    connect(hsPage, SIGNAL(shareAllHighScores()), this, SLOT(shareAllHighScores()));
    navPane->push(hsPage);
}

void ApplicationUI::displayInfo()
{
    InfoPage *infoPage = new InfoPage;
    connect(infoPage, SIGNAL(close()), this, SLOT(popNavPane()));
    connect(infoPage, SIGNAL(invokeTargetWithUri(QString, QString)),
            this, SLOT(onInvokeTargetWithUri(QString, QString)));
    navPane->push(infoPage);
}

void ApplicationUI::displaySettings()
{
    QSettings savedValues("Suhair Zain", "Soft Mines");
    bool playMusic = savedValues.value("playMusic").toBool();
    SettingsPage *settingsPage = new SettingsPage(gameInProgress, levelSelected, playMusic);
    connect(settingsPage, SIGNAL(close(int)), this, SLOT(onSettingsPageClosed(int)));
    connect(settingsPage, SIGNAL(musicEnabledChanged(bool)), this, SLOT(onMusicEnabledChanged(bool)));
    navPane->push(settingsPage);
}

void ApplicationUI::gameIsAsleep()
{
    if(gameInProgress)
    {
        gameTimer->stop();
    }
}

void ApplicationUI::gameIsAwake()
{
    if(gameInProgress)
    {
        gameTimer->start();
    }
}

void ApplicationUI::onGameFinished(bool won)
{
    gameInProgress = FALSE;
    gameTimer->stop();
    gameStatus->setPauseEnabled(FALSE);
    if(won)
    {
        QSettings savedValues("Suhair Zain", "Soft Mines");
        int bestTimeForLevel;
        switch(levelSelected)
        {
            case 0:
                bestTimeForLevel = savedValues.value("easy").toInt();
                break;
            case 1:
                bestTimeForLevel = savedValues.value("medium").toInt();
                break;
            case 2:
                bestTimeForLevel = savedValues.value("hard").toInt();
                break;
            case 3:
                bestTimeForLevel = savedValues.value("insane").toInt();
                break;
            default:
                bestTimeForLevel = 0;
                break;
        }
        if(gamePlayTime<bestTimeForLevel)
        {
            switch(levelSelected)
            {
                case 0:
                    savedValues.setValue("easy", gamePlayTime);
                    break;
                case 1:
                    savedValues.setValue("medium", gamePlayTime);
                    break;
                case 2:
                    savedValues.setValue("hard", gamePlayTime);
                    break;
                case 3:
                    savedValues.setValue("insane", gamePlayTime);
                    break;
            }
            savedValues.sync();
            NewHighScorePage *hsPage = new NewHighScorePage(levelSelected, gamePlayTime);
            connect(hsPage, SIGNAL(close()), this, SLOT(popNavPane()));
            connect(hsPage, SIGNAL(invokeTargetWithUri(QString, QString)),
                    this, SLOT(onInvokeTargetWithUri(QString, QString)));
            connect(hsPage, SIGNAL(shareNewHighScore()), this, SLOT(shareNewHighScore()));
            navPane->push(hsPage);
        }
        else
        {
            SuccessPage *successPage = new SuccessPage;
            connect(successPage, SIGNAL(close()), this, SLOT(popNavPane()));
            connect(successPage, SIGNAL(invokeTargetWithUri(QString, QString)),
                    this, SLOT(onInvokeTargetWithUri(QString, QString)));
            navPane->push(successPage);
        }
    }
    else
    {
        FailurePage *failurePage = new FailurePage;
        connect(failurePage, SIGNAL(close()), this, SLOT(popNavPane()));
        navPane->push(failurePage);
    }
}

void ApplicationUI::onGameFlagsChanged(int count)
{
    flagsLeft = count;
    gameStatus->setCount(count);
}

void ApplicationUI::onGamePauseClicked()
{
    //gameTimer->stop();

    PausePage *pausePage = new PausePage(0, gamePlayTime, flagsLeft);
    connect(pausePage, SIGNAL(close()), this, SLOT(onGameResume()));
    navPane->push(pausePage);
}

void ApplicationUI::onGameResetClicked()
{
    gameInProgress = FALSE;
    gameTimer->stop();
    gamePlayTime = 0;

    MineField *mines = new MineField(nRows, nCols, nMines);
    connect(mines, SIGNAL(gameStarted()), this, SLOT(onGameStarted()));
    connect(mines, SIGNAL(gameFinished(bool)), this, SLOT(onGameFinished(bool)));
    connect(mines, SIGNAL(gameFlagsChanged(int)), this, SLOT(onGameFlagsChanged(int)));

    gameStatus->setPauseEnabled(FALSE);
    gameStatus->setResetEnabled(FALSE);
    gameStatus->setCount(nMines);
    gameStatus->setTimer(0);
    mineField->setContent(mines);

    int horDist=scrW, verDist=scrH;
    if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
    {
        //qDebug()<<"Landscape";
        int temp = horDist;
        horDist = verDist;
        verDist = temp;
    }
    verDist -= 128;

    if(horDist/nCols > verDist/nRows)
    {
        mineField->scrollViewProperties()->setMinContentScale(horDist/ float(48*nCols));
        mineField->scrollViewProperties()->setMaxContentScale(2 * horDist/ float(48*nCols));
        //mineField->zoomToRect(QRectF(0.0f, 0.0f, horDist, verDist));
    }
    else
    {
        mineField->scrollViewProperties()->setMinContentScale(verDist/ float(48*nRows));
        mineField->scrollViewProperties()->setMaxContentScale(2 * verDist/ float(48*nRows));
        //mineField->zoomToRect(QRectF(0.0f, 0.0f, horDist, verDist));
    }
}

void ApplicationUI::onGameResume()
{
    navPane->pop();
    //gameTimer->start();
}

void ApplicationUI::onGameStarted()
{
    gameInProgress = TRUE;
    gameStatus->setPauseEnabled(TRUE);
    gameStatus->setResetEnabled(TRUE);

    gameTimer->start();
}

void ApplicationUI::onInvokeTargetWithUri(QString target, QString uri)
{
    InvokeRequest req;
    req.setTarget(target);
    req.setUri(uri);

    invokeManager->invoke(req)->deleteLater();
}

void ApplicationUI::onMineFieldChanged(Control*)
{
    mineField->children().at(1)->deleteLater();
    //qDebug()<<mineField->children();
}

void ApplicationUI::onMusicEnabledChanged(bool played)
{
    if(played)
        mediaPlayer->play();
    else
        mediaPlayer->stop();
    QSettings savedSettings("Suhair Zain", "Soft Mines");
    savedSettings.setValue("playMusic", played);
}

void ApplicationUI::onNavPaneTopChanged()
{
    if(navPane->count()>1)
    {
        Application::instance()->setMenuEnabled(FALSE);
        if(gameInProgress)
            gameTimer->stop();
    }
    else
    {
        Application::instance()->setMenuEnabled(TRUE);
        if(gameInProgress)
            gameTimer->start();
    }
}

void ApplicationUI::onNavPanePopEnded(Page *poppedPage)
{
    poppedPage->setParent(NULL);
    poppedPage->deleteLater();
}

void ApplicationUI::onOrientationAboutToChange()
{
    int horDist=scrW, verDist=scrH;
    //Portrait now, will change to landscape
    if(OrientationSupport::instance()->orientation()==UIOrientation::Portrait)
    {
        int temp = horDist;
        horDist = verDist;
        verDist = temp;
    }
    verDist -= 128;

    if(horDist/nCols > verDist/nRows)
    {
        float scale = horDist/ float(48*nCols);
        mineField->scrollViewProperties()->setMinContentScale(scale);
        mineField->scrollViewProperties()->setMaxContentScale(2 * scale);
        //mineField->zoomToRect(QRectF(0.0f, 0.0f, horDist, verDist));
    }
    else
    {
        float scale = verDist/ float(48*nRows);
        mineField->scrollViewProperties()->setMinContentScale(scale);
        mineField->scrollViewProperties()->setMaxContentScale(2 * scale);
        //mineField->zoomToRect(QRectF(0.0f, 0.0f, horDist, verDist));
    }
}

void ApplicationUI::onSettingsPageClosed(int nLevel)
{
    if(nLevel!=levelSelected)
    {
        QSettings savedValues("Suhair Zain", "Soft Mines");
        savedValues.setValue("levelSelected", nLevel);
        savedValues.sync();
        setValues(nLevel);
        levelSelected = nLevel;
        onGameResetClicked();
    }
    navPane->pop();
}

void ApplicationUI::popNavPane()
{
    navPane->pop();
}

void ApplicationUI::registrationStateUpdated(bb::platform::bbm::RegistrationState::Type state)
{
    if(state==bb::platform::bbm::RegistrationState::Allowed)
    {
        m_messageService = new bb::platform::bbm::MessageService(m_context, m_context);
        m_userProfile = new bb::platform::bbm::UserProfile(m_context, m_context);
    }
    else if(state == bb::platform::bbm::RegistrationState::Unregistered)
    {
        m_context->requestRegisterApplication();
    }
}

void ApplicationUI::setValues(int level)
{
    switch(level)
    {
        case 0:
            levelSelected=0;
            nRows=10;
            nCols=10;
            nMines=10;
            break;

        case 1:
            levelSelected=1;
            nRows=15;
            nCols=15;
            nMines=36;
            break;

        case 2:
            levelSelected=2;
            nRows=15;
            nCols=30;
            nMines=90;
            break;

        case 3:
            levelSelected=3;
            nRows = 15;
            nCols = 25;
            nMines = 120;
            break;

        default:
            qDebug()<<"ERRORRRRRRRRRRRRR IN LEVEL SELECTION:"<<level;
    }
}

void ApplicationUI::shareAllHighScores()
{
    if(m_context->registrationState() == bb::platform::bbm::RegistrationState::Allowed)
    {
        QString statusMessage;

        QSettings savedValues("Suhair Zain", "Soft Mines");
        int easy = savedValues.value("easy").toInt();
        int medium = savedValues.value("medium").toInt();
        int hard = savedValues.value("hard").toInt();
        int insane = savedValues.value("insane").toInt();
        if(easy==9999 && medium==9999 && hard==9999 && insane==9999)
        {
            statusMessage = "I'm playing Soft Mines and it's highly addictive. Have you played it?";
        }
        else
        {
            QString tempChar;
            statusMessage = "My high scores: ";
            if(easy!=9999)
            {
                tempChar=easy%60<10?":0":":";
                statusMessage.append("  Easy " + QString::number(easy/60, 10) + tempChar + QString::number(easy%60, 10));
            }
            if(medium!=9999)
            {
                tempChar=medium%60<10?":0":":";
                statusMessage.append("  Medium " + QString::number(medium/60, 10) + tempChar + QString::number(medium%60, 10));
            }
            if(hard!=9999)
            {
                tempChar=hard%60<10?":0":":";
                statusMessage.append("  Hard " + QString::number(hard/60, 10) + tempChar + QString::number(hard%60, 10));
            }
            if(insane!=9999)
            {
                tempChar=hard%60<10?":0":":";
                statusMessage.append("  Insane " + QString::number(hard/60, 10) + tempChar + QString::number(hard%60, 10));
            }
        }
        m_userProfile->requestUpdatePersonalMessage(statusMessage);
    }
    else
    {
        toast->setBody("BBM is not currently connected. Please setup/sign-in to BBM.");
        toast->setIcon(QUrl("asset:///images/icons/ic_bbm.png"));
        toast->show();
        m_context->requestRegisterApplication();
    }
}

void ApplicationUI::shareGame()
{
    if(m_context->registrationState() == bb::platform::bbm::RegistrationState::Allowed)
    {
        m_messageService->sendDownloadInvitation();
    }
    else
    {
        toast->setBody("BBM is not currently connected. Please setup/sign-in to BBM.");
        toast->setIcon(QUrl("asset:///images/icons/ic_bbm.png"));
        toast->show();
        m_context->requestRegisterApplication();
    }
}

void ApplicationUI::shareNewHighScore()
{
    if (m_context->registrationState() == bb::platform::bbm::RegistrationState::Allowed)
    {
        QString statusMessage, tempChar;
        tempChar = gamePlayTime%60<10?"0":"";
        switch(levelSelected)
        {
            case 0:
                statusMessage = "Yeah! I've got a new high score of " + QString::number(gamePlayTime/60, 10) + ":" + tempChar + QString::number(gamePlayTime%60, 10) + " in Easy level";
                break;
            case 1:
                statusMessage = "Yeah! I've got a new high score of " + QString::number(gamePlayTime/60, 10) + ":" + tempChar + QString::number(gamePlayTime%60, 10) + " in Medium level";
                break;
            case 2:
                statusMessage = "Yeah! I've got a new high score of " + QString::number(gamePlayTime/60, 10) + ":" + tempChar + QString::number(gamePlayTime%60, 10) + " in Hard level";
                break;
            case 3:
                statusMessage = "Yeah! I've got a new high score of " + QString::number(gamePlayTime/60, 10) + ":" + tempChar + QString::number(gamePlayTime%60, 10) + " in Insane level";
                break;
        }
        m_userProfile->requestUpdatePersonalMessage(statusMessage);
    }
    else
    {
        toast->setBody("BBM is not currently connected. Please setup/sign-in to BBM.");
        toast->setIcon(QUrl("asset:///images/icons/ic_bbm.png"));
        toast->show();
        m_context->requestRegisterApplication();
    }
}

void ApplicationUI::updateClock()
{
    gameStatus->setTimer(++gamePlayTime);
}
