#include "applicationui.hpp"

#include <time.h>
#include <stdlib.h>

int clickedPosI, clickedPosJ, nColsGlobal, nRowsGlobal, nSquaresFreed, nMinesGlobal, nFreeSquares, nMinesLeft;
bool firstGame=TRUE, gameInProgress=FALSE, gameLost=FALSE;
bool firstClickHappened=FALSE, tapToUncover=TRUE, newHS=FALSE;

TextField *connectorBetweenClasses;
Square **fieldSquares;
//MediaPlayer *player;
//int **field;


ApplicationUI::ApplicationUI(bb::cascades::Application *app) : QObject(app)
{
	invokeManager = new InvokeManager;
	invokeRequest = new InvokeRequest;
	invokeReply = new InvokeTargetReply;

	helpFirstTime = infoFirstTime = highScoresFirstTime = settingsFirstTime = TRUE;
	pauseFirstTime = TRUE;
	failureFirst = highScoreFirst = successFirst = TRUE;

	toast = new SystemToast(app);

	connectorBetweenClasses = TextField::create().
			text("NOCLICKSHAPPENED").
			parent(app).
			connect(SIGNAL(textChanged(QString)), this, SLOT(checkWhatHappened(QString)));

	gameTimer = new QTimer;
	connect(gameTimer, SIGNAL(timeout()), this, SLOT(updateClock()));

	easy = Label::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Center);

	medium = Label::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Center);

	hard = Label::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Center);

	TextStyle textStyle;
	textStyle.setFontWeight(FontWeight::W400);
	textStyle.setTextAlign(TextAlign::Center);
	textStyle.setFontSize(FontSize::XXLarge);

	hsLabel = Label::create().
			horizontal(HorizontalAlignment::Center).
			textStyle(textStyle).
			multiline(TRUE);


	TextStyle levelChooserStyle;
	levelChooserStyle.setFontSize(FontSize::Large);
	levelChooserStyle.setFontWeight(FontWeight::W300);
	levelChooserStyle.setColor(Color::Red);
	levelChooserStyle.setTextAlign(TextAlign::Center);

	loseGameWarning = Label::create().
			horizontal(HorizontalAlignment::Center).
			text("If you change the level now, you will lose the current game. "
					"Else please change after completing this game.").
					multiline(TRUE).
					visible(FALSE).
					textStyle(levelChooserStyle);

	appSheet = Sheet::create().
			peek(FALSE).
			parent(app).
			connect(SIGNAL(opened()), this, SLOT(sheetOpened())).
			connect(SIGNAL(closed()), this, SLOT(sheetClosed()));

	appHelp = HelpActionItem::create();

	infoAction = ActionItem::create().
			image("asset:///images/icons/ic_info.png").
			title("Info");

	shareBBM = ActionItem::create().
			image("asset:///images/icons/ic_bbm.png").
			title("Share game");

	highScores = ActionItem::create().
			image("asset:///images/icons/ic_highscores.png").
			title("High scores");

	appSettings = SettingsActionItem::create();

	connect(appHelp, SIGNAL(triggered()), this, SLOT(displayHelp()));
	connect(infoAction, SIGNAL(triggered()), this, SLOT(displayInfo()));
	connect(shareBBM, SIGNAL(triggered()), this, SLOT(shareApp()));
	connect(highScores, SIGNAL(triggered()), this, SLOT(displayHighScores()));
	connect(appSettings, SIGNAL(triggered()), this, SLOT(displaySettings()));

	appMenu = Menu::create().
			addAction(infoAction).
			addAction(shareBBM).
			addAction(highScores);
	appMenu->setHelpAction(appHelp);
	appMenu->setSettingsAction(appSettings);

	app->setMenu(appMenu);

	/*toggleFAU = ActionItem::create().
			title("Uncover Squares").
			image("asset:///images/gamePage/uncover.png").
			connect(SIGNAL(triggered()), this, SLOT(toggleTouchMethod()));*/

	restartGame = DeleteActionItem::create().
			enabled(FALSE).
			title("New game").
			image("asset:///images/icons/ic_reload.png").
			connect(SIGNAL(triggered()), this, SLOT(checkForLevelChange()));

	/*pauseGame = ActionItem::create().
			enabled(FALSE).
			title("Pause").
			image("asset:///images/gamePage/ic_pause.png").
			connect(SIGNAL(triggered()), this, SLOT(displayPauseScreen()));*/

	gameRoot = Container::create().
			layout(DockLayout::create());

	rootPage = Page::create().
			content(gameRoot).
			//addAction(pauseGame).
			addAction(restartGame);

	uncoverMode = Tab::create().
			title("Uncover Squares").
			image("asset:///images/gamePage/uncoverActive.png");

	flagMode = Tab::create().
			title("Flag / Unflag Mines").
			image("asset:///images/gamePage/flag.png");

	modeChooser = TabbedPane::create().
			activePane(rootPage).
			showTabsOnActionBar(TRUE).
			add(uncoverMode).
			add(flagMode);

	connect(modeChooser, SIGNAL(activeTabChanged(bb::cascades::Tab*)), this, SLOT(toggleTouchMethod(bb::cascades::Tab *)));

	app->setScene(modeChooser);
	//app->setScene(rootPage);
	this->setParent(app);

	m_context = new bb::platform::bbm::Context(QUuid("8c3660de-8c22-4af3-bf71-456a08e0c910"));
	if(m_context->registrationState() != bb::platform::bbm::RegistrationState::Allowed)
	{
		connect(m_context, SIGNAL(registrationStateUpdated (bb::platform::bbm::RegistrationState::Type)), this, SLOT(registrationStateUpdated (bb::platform::bbm::RegistrationState::Type)));
		m_context->requestRegisterApplication();
	}

	savedHS = new QSettings("Suhair Zain", "Soft Mines", app);
	if(savedHS->value("highScoresSet", 0).toInt()==0)
	{
		newHSEasy=newHSMedium=newHSHard=9999;
		savedHS->setValue("highScoresSet", 1);
		savedHS->setValue("easy", 9999);
		savedHS->setValue("medium", 9999);
		savedHS->setValue("hard", 9999);
		displayHelp();
	}
	else
	{
		newHSEasy = savedHS->value("easy").toInt();
		newHSMedium = savedHS->value("medium").toInt();
		newHSHard = savedHS->value("hard").toInt();
	}
	setValues(savedHS->value("levelSelected", 0).toInt());
	qDebug()<<"HS: "<<newHSEasy<<" "<<newHSMedium<<" "<<newHSHard;
	initialiseGameField();

	Container *coverContainer, *coverContent;
	Label *appName;
	SceneCover *appCover;

	coverContainer = Container::create().layout(DockLayout::create());
	coverContainer->setBackground(Color::fromARGB(0xff121212));

	coverContent = Container::create();
	coverContent->setHorizontalAlignment(HorizontalAlignment::Center);
	coverContent->setVerticalAlignment(VerticalAlignment::Center);

	appName = Label::create().
			text("Soft Mines");
	appName->textStyle()->setFontSize(FontSize::XLarge);

	TextStyle style;
	style.setColor(Color::fromARGB(0xffebebeb));
	style.setFontSize(FontSize::PointValue);
	style.setFontSizeValue(6);

	timeInCover = Label::create().
			multiline(TRUE).
			text("No game in progress").
			textStyle(style).
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Center);

	coverContent->add(appName);
	coverContent->add(timeInCover);

	coverContainer->add(coverContent);

	appCover = SceneCover::create().content(coverContainer);

	Application::instance()->setCover(appCover);

	connect(app, SIGNAL(asleep()), this, SLOT(gameIsAsleep()));
	connect(app, SIGNAL(awake()), this, SLOT(gameIsAwake()));

/*	player = new MediaPlayer(app);
	player->setSourceUrl(QUrl("asset:///sounds/blasterSound.mp3"));

	bgPlayer = new MediaPlayer(app);
	bgPlayer->setSourceUrl(QUrl("asset:///sounds/BG.mp3"));
	bgPlayer->play();*/
}

ApplicationUI::~ApplicationUI()
{
	qDebug()<<"DESTRUCTOR OPENED";

	delete invokeManager;
	delete invokeRequest;
	delete invokeReply;

	delete m_userProfile;
	//delete m_context;
	//delete m_messageService;

	/*for(int i=0; i<backupnRows; ++i)
	{
		delete [] field[i];
	}
	delete [] field;*/

	qDebug()<<"DESTRUCTOR CLOSED";
}

void ApplicationUI::checkForLevelChange()
{
	//if(levelSelected!=backupLevelSelected)
	//{
	qDebug()<<"OLD AND NEW: "<<backupLevelSelected<<" | "<<levelSelected;
	int i, j;

	/*for(i=0; i<backupnRows; ++i)
	{
		delete [] field[i];
	}
	delete [] field;

	field = new int*[nRows];
	for (i=0; i<nRows; i++)
	{
		field[i] = new int[nCols];
	}*/


	for(i=0; i<backupnRows; ++i)
	{
		delete [] fieldSquares[i];
	}
	delete [] fieldSquares;

	fieldSquares = new Square *[nRows];
	for(i=0; i<nRows; i++)
	{
		fieldSquares[i] = new Square[nCols];
	}

	for(i=0; i<backupnRows; i++)
	{
		mineFieldContainer->remove(&rowsContainer[i]);
	}


	delete [] rowsContainer;

	rowsContainer = new Container[nRows];

	for(i=0; i<nRows; i++)
	{
		rowsContainer[i].setLayout(StackLayout::create().
				orientation(LayoutOrientation::LeftToRight));
	}

	for(i=0; i<nRows; i++)
	{
		for(j=0; j<nCols; j++)
		{
			fieldSquares[i][j].posI=i;
			fieldSquares[i][j].posJ=j;
			fieldSquares[i][j].square->setTopMargin(2.0f);
			fieldSquares[i][j].square->setRightMargin(0.0f);
			fieldSquares[i][j].square->setBottomMargin(2.0f);
			fieldSquares[i][j].square->setLeftMargin(0.0f);
			rowsContainer[i].add(fieldSquares[i][j].square);
		}
		mineFieldContainer->add(&rowsContainer[i]);
	}

	backupLevelSelected=levelSelected;
	backupnRows=nRows;
	backupnCols=nCols;
	backupnMines=nMines;
	loseGameWarning->setVisible(FALSE);
	//}//CLEAR ROWC AND OTHER THINGS

	//RESET THE TIMERS AND ALL

	switch(levelSelected)
	{
	case 0:
		mineField->scrollViewProperties()->setMinContentScale(2.06f);
		mineField->zoomToRect(QRectF(qreal(0.0f), qreal(0.0f), qreal(480.0f), qreal(480.0f)));
		break;
	default:
		mineField->scrollViewProperties()->setMinContentScale(1.363f);
		mineField->zoomToRect(QRectF(qreal(0.0f), qreal(0.0f), qreal(720.0f), qreal(720.0f)));
	}

	if(gameTimer->isActive())
	{
		gameTimer->stop();
	}
	gamePlayTime=0;
	timeLabel->setText("0:00");
	firstClickHappened=FALSE;
	gameInProgress=FALSE;
	tapToUncover=1;
	uncoverMode->setEnabled(TRUE);
	flagMode->setEnabled(FALSE);
	restartGame->setEnabled(FALSE);
	pauseGame->setEnabled(FALSE);
	modeChooser->setActiveTab(uncoverMode);
	//toggleFAU->setTitle("Uncover Squares");
	//toggleFAU->setImage("asset:///images/gamePage/uncover.png");
	//toggleFAU->setEnabled(FALSE);
	nMinesLeft = nMines;
	nSquaresFreed=0;
	countLabel->setText(QString::number(nMinesLeft));
	connectorBetweenClasses->setText("NOCLICKSHAPPENED");

	for(int i=0; i<nRows; i++)
	{
		for(int j=0; j<nCols; j++)
		{
			fieldSquares[i][j].flagged=0;
			fieldSquares[i][j].square->resetDisabledImage();
			fieldSquares[i][j].square->setEnabled(TRUE);
		}
	}
}

void ApplicationUI::checkWhatHappened(QString text)
{
	qDebug()<<"RESULT: "<<text;
	if(text=="CLICKED")
	{
		nRowsGlobal=nRows;
		nColsGlobal=nCols;
		nMinesGlobal=nMines;
		nFreeSquares=nRows*nCols-nMines;
		fillTheField();
		flagMode->setEnabled(TRUE);
		restartGame->setEnabled(TRUE);
		pauseGame->setEnabled(TRUE);
		//modeChooser->setActiveTab(uncoverMode);
		//toggleFAU->setEnabled(TRUE);
	}
	else if(text=="GAMEOVER")
	{
		gameInProgress=FALSE;
		gameLost=TRUE;
		gameTimer->stop();
		uncoverMode->setEnabled(FALSE);
		flagMode->setEnabled(FALSE);
		pauseGame->setEnabled(FALSE);
		modeChooser->setActiveTab(uncoverMode);
		//toggleFAU->setEnabled(FALSE);
		gameOver();
		displaySheetFailure();
	}
	else if(text=="SUCCESS")
	{
		newHS = FALSE;
		gameTimer->stop();
		gameInProgress=FALSE;
		gameLost=FALSE;
		uncoverMode->setEnabled(FALSE);
		flagMode->setEnabled(FALSE);
		pauseGame->setEnabled(FALSE);
		modeChooser->setActiveTab(uncoverMode);
		//toggleFAU->setEnabled(FALSE);
		QString tempChar;
		tempChar = gamePlayTime%60<10?"0":"";
		switch(backupLevelSelected)
		{
		case 0:
			if(gamePlayTime<newHSEasy)
			{
				newHS=TRUE;
				savedHS->setValue("easy", gamePlayTime);
				newHSEasy=gamePlayTime;
				easy->setText(QString::number(gamePlayTime/60, 10) + ":" + tempChar + QString::number(gamePlayTime%60, 10));
				hsLabel->setText("Level: Easy\nScore: " + easy->text());
			}
			break;
		case 1:
			if(gamePlayTime<newHSMedium)
			{
				newHS=TRUE;
				savedHS->setValue("medium", gamePlayTime);
				newHSMedium=gamePlayTime;
				medium->setText(QString::number(gamePlayTime/60, 10) + ":" + tempChar + QString::number(gamePlayTime%60, 10));
				hsLabel->setText("Level: Medium\nScore: " + medium->text());
			}
			break;
		case 2:
			if(gamePlayTime<newHSHard)
			{
				newHS=TRUE;
				savedHS->setValue("hard", gamePlayTime);
				newHSHard=gamePlayTime;
				hard->setText(QString::number(gamePlayTime/60, 10) + ":" + tempChar + QString::number(gamePlayTime%60, 10));
				hsLabel->setText("Level: Hard\nScore: " + hard->text());
			}
			break;
		}
		if(newHS)
		{
			displaySheetHS();
		}
		else
		{
			displaySheetSuccess();
		}
		gameOver();
	}
	else if(text=="SQUAREFLAGGEDORUNFLAGGED")
	{
		countLabel->setText(QString::number(nMinesLeft));
		connectorBetweenClasses->setText("NULL");
	}
}

void ApplicationUI::closeSettingsSheet()
{
	if(levelSelected!=backupLevelSelected)
	{
		checkForLevelChange();
		loseGameWarning->setVisible(FALSE);
	}
	appSheet->close();
}

void ApplicationUI::displayHelp()
{
	if(helpFirstTime)
	{
		helpFirstTime = FALSE;

		ActionItem *close;
		Container *root, *content, *textC;
		TitleBar *titleBar;

		//700x450

		helpImage = ImageView::create().
				horizontal(HorizontalAlignment::Center);

		TextStyle textStyle;
		textStyle.setColor(Color::DarkMagenta);
		textStyle.setFontSize(FontSize::XLarge);
		textStyle.setFontWeight(FontWeight::W300);
		textStyle.setTextAlign(TextAlign::Center);
		textStyle.setLineHeight(0.9f);

		textHowToPlay = Label::create().
				vertical(VerticalAlignment::Top).
				horizontal(HorizontalAlignment::Center).
				multiline(TRUE).
				textStyle(textStyle).
				format(TextFormat::Html);

		textC = Container::create().
				layout(DockLayout::create()).
				horizontal(HorizontalAlignment::Center).
				preferredHeight(500.0f).
				preferredWidth(720.0f).
				add(textHowToPlay);

		helpSlider = Slider::create().
				horizontal(HorizontalAlignment::Center).
				preferredWidth(710.0f);
		helpSlider->setRange(0.0f, 7.0f);
		connect(helpSlider, SIGNAL(valueChanged(float)), this, SLOT(handleHelpSlider(float)));
		connect(helpSlider, SIGNAL(immediateValueChanged(float)), this, SLOT(handleHelpSliderImm(float)));

		content = Container::create().
				vertical(VerticalAlignment::Center).
				horizontal(HorizontalAlignment::Center).
				add(helpImage).
				add(textC).
				add(helpSlider);

		root = Container::create().
				layout(DockLayout::create()).
				add(content);

		close = ActionItem::create().
				title("Close").
				connect(SIGNAL(triggered()), appSheet, SLOT(close()));

		titleBar = TitleBar::create().
				title("Help").
				dismissAction(close);

		helpPage = Page::create().
				content(root).
				titleBar(titleBar);
	}
	helpLevel=0;
	helpSlider->setValue(0.0f);
	setContentForHelp();

	appSheet->setContent(helpPage);
	appSheet->open();
}

void ApplicationUI::displayHighScores()
{
	if(highScoresFirstTime)
	{
		highScoresFirstTime = FALSE;

		ActionItem *close;
		Button *shareHighScores;
		Container *root, *content;
		Container *easyC, *mediumC, *hardC;
		Container *easyCC, *mediumCC, *hardCC;
		ImageView *easy1, *easy2, *medium1, *medium2, *hard1, *hard2;
		TitleBar *titleBar;

		easy1 = ImageView::create().
				image("asset:///images/hsPage/easy1.png");

		easy2 = ImageView::create().
				horizontal(HorizontalAlignment::Center).
				vertical(VerticalAlignment::Center).
				image("asset:///images/hsPage/easy2.png");

		easyCC = Container::create().
				layout(DockLayout::create()).
				add(easy2).
				add(easy);

		easyC = Container::create().
				layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
				horizontal(HorizontalAlignment::Center).
				add(easy1).
				add(easyCC);

		medium1 = ImageView::create().
				image("asset:///images/hsPage/medium1.png");

		medium2 = ImageView::create().
				horizontal(HorizontalAlignment::Center).
				vertical(VerticalAlignment::Center).
				image("asset:///images/hsPage/medium2.png");

		mediumCC = Container::create().
				layout(DockLayout::create()).
				add(medium2).
				add(medium);

		mediumC = Container::create().
				layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
				horizontal(HorizontalAlignment::Center).
				add(medium1).
				add(mediumCC);

		hard1 = ImageView::create().
				image("asset:///images/hsPage/hard1.png");

		hard2 = ImageView::create().
				horizontal(HorizontalAlignment::Center).
				vertical(VerticalAlignment::Center).
				image("asset:///images/hsPage/hard2.png");

		hardCC = Container::create().
				layout(DockLayout::create()).
				add(hard2).
				add(hard);

		hardC = Container::create().
				layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
				horizontal(HorizontalAlignment::Center).
				add(hard1).
				add(hardCC);

		shareHighScores = Button::create().
				horizontal(HorizontalAlignment::Center).
				text(".                  Share to BBM                  .").
				connect(SIGNAL(clicked()), this, SLOT(shareAllHighScores()));

		content = Container::create().
				vertical(VerticalAlignment::Center).
				horizontal(HorizontalAlignment::Center).
				add(easyC).
				add(mediumC).
				add(hardC).
				add(shareHighScores);

		root = Container::create().
				layout(DockLayout::create()).
				add(content);

		close = ActionItem::create().
				title("Close").
				connect(SIGNAL(triggered()), appSheet, SLOT(close()));

		titleBar = TitleBar::create().
				title("High scores").
				dismissAction(close);

		highScoresPage = Page::create().
				content(root).
				titleBar(titleBar);

		if(newHSEasy==9999)
		{
			easy->setText("- : -");
		}
		else
		{
			easy->setText(QString::number(newHSEasy/60, 10) + ":" + QString::number(newHSEasy%60, 10));
		}

		if(newHSMedium==9999)
		{
			medium->setText("- : -");
		}
		else
		{
			medium->setText(QString::number(newHSMedium/60, 10) + ":" + QString::number(newHSMedium%60, 10));
		}

		if(newHSHard==9999)
		{
			hard->setText("- : -");
		}
		else
		{
			hard->setText(QString::number(newHSHard/60, 10) + ":" + QString::number(newHSHard%60, 10));
		}
	}
	appSheet->setContent(highScoresPage);
	appSheet->open();
}

void ApplicationUI::displayInfo()
{
	if(infoFirstTime)
	{
		infoFirstTime = FALSE;

		ActionItem *close;
		Container *content, *root, *svAndRubus;
		ImageButton *infoLogo, *svLogo, *rubusLogo;
		Label *infoLabel, *privacyPolicy;
		TitleBar *titleBar;

		infoLogo = ImageButton::create().
				horizontal(HorizontalAlignment::Center).
				defaultImage("asset:///images/logos/logo.png").
				pressedImage("asset:///images/logos/logoPressed.png");

		TextStyle textStyle;
		textStyle.setFontWeight(FontWeight::W300);
		textStyle.setFontSize(FontSize::XLarge);
		textStyle.setTextAlign(TextAlign::Center);

		infoLabel = Label::create().multiline(TRUE).
				horizontal(HorizontalAlignment::Center).
				textStyle(textStyle).
				text("built by STAW\n"
						"with help from\n"
						"Rubus Labs\n"
						"and\n"
						"Startup Village, Kochi");

		textStyle.setFontSize(FontSize::Medium);
		textStyle.setColor(Color::Blue);

		privacyPolicy = Label::create().
				vertical(VerticalAlignment::Bottom).
				horizontal(HorizontalAlignment::Center).
				textStyle(textStyle).
				text("View privacy policy");

		svLogo = ImageButton::create().
				defaultImage("asset:///images/logos/sv.png").
				pressedImage("asset:///images/logos/svPressed.png");

		rubusLogo = ImageButton::create().
				defaultImage("asset:///images/logos/rubus.png").
				pressedImage("asset:///images/logos/rubusPressed.png");

		svAndRubus = Container::create().
				layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
				horizontal(HorizontalAlignment::Center).
				add(svLogo).
				add(rubusLogo);

		content = Container::create().
				vertical(VerticalAlignment::Center).
				horizontal(HorizontalAlignment::Center).
				add(infoLogo).
				add(infoLabel).
				add(svAndRubus).
				add(privacyPolicy);

		root = Container::create().
				layout(DockLayout::create()).
				add(content);

		close = ActionItem::create().
				title("Close").
				connect(SIGNAL(triggered()), appSheet, SLOT(close()));

		titleBar = TitleBar::create().
				title("Info").
				dismissAction(close);

		infoPage = Page::create().
				content(root).
				titleBar(titleBar);

		connect(infoLogo, SIGNAL(clicked()), this, SLOT(goToGameOnFB()));
		connect(svLogo, SIGNAL(clicked()), this, SLOT(goToSV()));
		connect(rubusLogo, SIGNAL(clicked()), this, SLOT(goToRubus()));
		connect(privacyPolicy, SIGNAL(touch(bb::cascades::TouchEvent*)), this, SLOT(goToPrivacyPolicy(bb::cascades::TouchEvent*)));
	}
	appSheet->setContent(infoPage);
	appSheet->open();
}

void ApplicationUI::displayPauseScreen()
{
	if(pauseFirstTime)
	{
		pauseFirstTime = FALSE;

		ActionItem *resume;
		Container *root, *content;
		Container *levelC, *timeC, *countC;
		Label *levelD, *timeD, *countD;
		TitleBar *titleBar;

		TextStyle gameInfoStyle;
		gameInfoStyle.setFontSize(FontSize::XLarge);
		gameInfoStyle.setFontWeight(FontWeight::W400);
		gameInfoStyle.setTextAlign(TextAlign::Center);
		gameInfoStyle.setColor(Color::fromARGB(0xFFFFA500));

		levelD = Label::create().
				textStyle(gameInfoStyle).
				text("Level: ");

		timeD = Label::create().
				textStyle(gameInfoStyle).
				text("Gametime: ");

		countD = Label::create().
				textStyle(gameInfoStyle).
				text("Squares left to flag: ");

		gameInfoStyle.setColor(Color::Black);
		gameInfoStyle.setFontWeight(FontWeight::W300);

		pauseLevel = Label::create().
				textStyle(gameInfoStyle);

		pauseTime = Label::create().
				textStyle(gameInfoStyle);

		pauseCount = Label::create().
				textStyle(gameInfoStyle);

		levelC = Container::create().
				layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
				add(levelD).
				add(pauseLevel);

		timeC = Container::create().
				layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
				add(timeD).
				add(pauseTime);

		countC = Container::create().
				layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
				add(countD).
				add(pauseCount);

		content = Container::create().
				vertical(VerticalAlignment::Center).
				horizontal(HorizontalAlignment::Center).
				add(levelC).
				add(timeC).
				add(countC);

		root = Container::create().
				layout(DockLayout::create()).
				add(content);

		resume = ActionItem::create().
				title("Resume").
				connect(SIGNAL(triggered()), appSheet, SLOT(close()));

		titleBar = TitleBar::create().
				title("Game paused").
				acceptAction(resume);

		pausePage = Page::create().
				content(root).
				titleBar(titleBar);
	}
	switch(levelSelected)
	{
	case 0:
		pauseLevel->setText("Easy");
		break;

	case 1:
		pauseLevel->setText("Medium");
		break;

	default:
		pauseLevel->setText("Hard");
	}

	pauseTime->setText(timeLabel->text());
	pauseCount->setText(countLabel->text());

	appSheet->setContent(pausePage);
	appSheet->open();
}

void ApplicationUI::displaySettings()
{
	if(settingsFirstTime)
	{
		settingsFirstTime = FALSE;

		ActionItem *close;
		Container *root, *content;
		Label *levelChooserLabel;
		Option *easyOption, *mediumOption, *hardOption;
		TitleBar *titleBar;

		TextStyle levelChooserStyle;
		levelChooserStyle.setFontSize(FontSize::XLarge);
		levelChooserStyle.setFontWeight(FontWeight::W400);

		levelChooserLabel = Label::create().
				text("Choose a level:").
				textStyle(levelChooserStyle);

		levelChooserStyle.setFontWeight(FontWeight::W300);
		levelChooserStyle.setColor(Color::Blue);
		levelChooserStyle.setTextAlign(TextAlign::Center);

		easyOption = Option::create().text("Easy");
		mediumOption = Option::create().text("Medium");
		hardOption = Option::create().text("Hard");

		levelChooser = RadioGroup::create().
				add(easyOption).
				add(mediumOption).
				add(hardOption).
				dividers(TRUE).
				connect(SIGNAL(selectedIndexChanged(int)), this, SLOT(handleLevelChange(int)));
		levelChooser->setSelectedIndex(levelSelected);

		content = Container::create().
				vertical(VerticalAlignment::Top).
				horizontal(HorizontalAlignment::Center).
				add(levelChooserLabel).
				add(levelChooser).
				add(loseGameWarning);

		root = Container::create().
				layout(DockLayout::create()).
				add(content);

		close = ActionItem::create().
				title("Close").
				connect(SIGNAL(triggered()), this, SLOT(closeSettingsSheet()));

		titleBar = TitleBar::create().
				title("Settings").
				dismissAction(close);

		settingsPage = Page::create().
				content(root).
				titleBar(titleBar);
	}
	appSheet->setContent(settingsPage);
	appSheet->open();
}

void ApplicationUI::displaySheetFailure()
{
	if(failureFirst)
	{
		failureFirst = FALSE;

		ActionItem *close;
		Container *root;
		ImageView *rootImage;
		TitleBar *titleBar;

		rootImage = ImageView::create().
				horizontal(HorizontalAlignment::Center).
				vertical(VerticalAlignment::Center).
				image("asset:///images/resultsPage/failure.jpg");

		root = Container::create().
				layout(DockLayout::create()).
				add(rootImage);

		close = ActionItem::create().
				title("Close").
				connect(SIGNAL(triggered()), appSheet, SLOT(close()));

		titleBar = TitleBar::create().
				title("Game Over!").
				dismissAction(close);

		failurePage = Page::create().
				content(root).
				titleBar(titleBar);
	}
	appSheet->setContent(failurePage);
	appSheet->open();
}

void ApplicationUI::displaySheetHS()
{
	qDebug()<<"HS Obtained";
	if(highScoreFirst)
	{
		highScoreFirst = FALSE;

		ActionItem *close;
		Button *shareButton;
		Container *root, *content;
		ImageView *rootImage;
		TitleBar *titleBar;

		rootImage = ImageView::create().
				horizontal(HorizontalAlignment::Center).
				vertical(VerticalAlignment::Center).
				image("asset:///images/resultsPage/newHighScore.jpg").
				opacity(0.3f);

		shareButton = Button::create().
				horizontal(HorizontalAlignment::Center).
				text("Share to BBM").
				connect(SIGNAL(clicked()), this, SLOT(shareNewHighScore()));

		Button *reviewButton = Button::create().
				horizontal(HorizontalAlignment::Center).
				text("Leave a review").
				connect(SIGNAL(clicked()), this, SLOT(goToGamePage()));

		content = Container::create().
				horizontal(HorizontalAlignment::Center).
				vertical(VerticalAlignment::Center).
				add(hsLabel).
				add(shareButton);

		root = Container::create().
				layout(DockLayout::create()).
				add(rootImage).
				add(content);

		close = ActionItem::create().
				title("Close").
				connect(SIGNAL(triggered()), appSheet, SLOT(close()));

		titleBar = TitleBar::create().
				title("New Highscore!").
				dismissAction(close);

		hsPage = Page::create().
				content(root).
				titleBar(titleBar);
	}
	appSheet->setContent(hsPage);
	appSheet->open();
}

void ApplicationUI::displaySheetSuccess()
{
	if(successFirst)
	{
		successFirst = FALSE;

		ActionItem *close;
		Container *root;
		ImageView *rootImage;
		TitleBar *titleBar;

		rootImage = ImageView::create().
				horizontal(HorizontalAlignment::Center).
				vertical(VerticalAlignment::Center).
				image("asset:///images/resultsPage/success.jpg");

		Button *reviewButton = Button::create().
				horizontal(HorizontalAlignment::Center).
				vertical(VerticalAlignment::Center).
				text("Leave us a review").
				connect(SIGNAL(clicked()), this, SLOT(goToGamePage()));

		root = Container::create().
				layout(DockLayout::create()).
				add(rootImage).
				add(reviewButton);

		close = ActionItem::create().
				title("Close").
				connect(SIGNAL(triggered()), appSheet, SLOT(close()));

		titleBar = TitleBar::create().
				title("You Won!").
				dismissAction(close);

		ActionItem *review = ActionItem::create().
				image("asset:///images/icons/ic_open.png").
				title("Leave a review");

		successPage = Page::create().
				content(root).
				titleBar(titleBar).
				addAction(review, ActionBarPlacement::OnBar);
	}
	appSheet->setContent(successPage);
	appSheet->open();
}

void ApplicationUI::fillTheField()
{
	srand(time(NULL));

	int i, j, nMinesFilled=0, nSquares, startI, startJ;
	nSquares=nRows*nCols-9;

	startI=clickedPosI;
	startJ=clickedPosJ;

	for(i=0; i<nRows; i++)
	{
		for(j=0; j<nCols; j++)
		{
			fieldSquares[i][j].value=0;
		}
	}

	while(1)
	{
		for(i=0; i<nRows; i++)
		{
			for(j=0; j<nCols; j++)
			{
				if(nMinesFilled==nMines)
				{
					gameInProgress=TRUE;

					for(int x=0; x<nRows; x++)
					{
						for(int y=0; y<nCols; y++)
						{
							if(fieldSquares[x][y].value==0)
								fieldSquares[x][y].value=fieldSquares[x][y].nOfZAroundXY(x, y, 9);
						}
					}
					//fieldSquares[startI][startJ].value=0;
					//fieldSquares[startI][startJ].handleButtonClick();

					gameTimer->start(1000);
					//setValuesToNonMines();
					//setValuesToSquares();
					return;
				}
				if(rand()%nSquares==0)
				{
					if(fieldSquares[i][j].value==0 && !((i==startI || i==startI-1 || i==startI+1) && (j==startJ || j==startJ-1 || j==startJ+1)))
					{
						//field[i][j]=9;
						fieldSquares[i][j].value=9;
						nMinesFilled++;
					}
				}
			}
		}
	}
}

void ApplicationUI::gameIsAsleep()
{
	if(gameTimer->isActive() && gameInProgress)
	{
		gameTimer->stop();
	}

	if(gameInProgress)
	{
		QString tempChar;
		tempChar = gamePlayTime%60<10?"0":"";
		timeInCover->textStyle()->setFontSizeValue(30);
		timeInCover->setText(QString::number(gamePlayTime/60, 10) + ":" + tempChar + QString::number(gamePlayTime%60, 10));
	}
	else
	{
		timeInCover->textStyle()->setFontSizeValue(6);
		timeInCover->setText("No game in progress");
	}

}

void ApplicationUI::gameIsAwake()
{
	if(gameTimer->isActive()==0 && gameInProgress==1)
	{
		gameTimer->start();
	}
}

void ApplicationUI::gameOver()
{
	int i, j;

	for(i=0; i<nRows; i++){
		for(j=0; j<nCols; j++)
		{
			if(fieldSquares[i][j].square->isEnabled())
			{
				fieldSquares[i][j].square->setEnabled(FALSE);
				fieldSquares[i][j].disableAndSetImage();
			}
		}
	}
}

void ApplicationUI::goToPrivacyPolicy(bb::cascades::TouchEvent* event)
{
	if(event->isUp())
	{
		invokeRequest->setTarget("sys.browser");
		invokeRequest->setAction("bb.action.OPEN");
		invokeRequest->setMimeType("text/html");
		invokeRequest->setUri("http://www.aassk.in/staw/privacypolicy.html");

		invokeReply = invokeManager->invoke(*invokeRequest);

		if(invokeReply)
		{
			invokeReply->setParent(this);
			connect(invokeReply, SIGNAL(finished()), this, SLOT(invokeFinished()));
		}
	}
}

void ApplicationUI::goToSV()
{
	invokeRequest->setTarget("sys.browser");
	invokeRequest->setAction("bb.action.OPEN");
	invokeRequest->setMimeType("text/html");
	invokeRequest->setUri("http://startupvillage.in");

	invokeReply = invokeManager->invoke(*invokeRequest);

	if(invokeReply)
	{
		invokeReply->setParent(this);
		connect(invokeReply, SIGNAL(finished()), this, SLOT(invokeFinished()));
	}
}

void ApplicationUI::goToGameOnFB()
{
	invokeRequest->setTarget("sys.browser");
	invokeRequest->setAction("bb.action.OPEN");
	invokeRequest->setMimeType("text/html");
	invokeRequest->setUri("http://www.facebook.com/pages/Soft-Mines/622041597853338");

	invokeReply = invokeManager->invoke(*invokeRequest);

	if(invokeReply)
	{
		invokeReply->setParent(this);
		connect(invokeReply, SIGNAL(finished()), this, SLOT(invokeFinished()));
	}
}

void ApplicationUI::goToGamePage()
{
	invokeRequest->setTarget("sys.appworld");
	invokeRequest->setAction("bb.action.OPEN");
	invokeRequest->setUri("appworld://content/35618894");

	invokeReply = invokeManager->invoke(*invokeRequest);

	if(invokeReply)
	{
		invokeReply->setParent(this);
		connect(invokeReply, SIGNAL(finished()), this, SLOT(invokeFinished()));
	}
}

void ApplicationUI::goToRubus()
{
	invokeRequest->setTarget("sys.browser");
	invokeRequest->setAction("bb.action.OPEN");
	invokeRequest->setMimeType("text/html");
	invokeRequest->setUri("http://startupvillage.in/rubuslabs");

	invokeReply = invokeManager->invoke(*invokeRequest);

	if(invokeReply)
	{
		invokeReply->setParent(this);
		connect(invokeReply, SIGNAL(finished()), this, SLOT(invokeFinished()));
	}
}

/*void ApplicationUI::handleDiscardGameConfirmation(bb::system::SystemUiResult::Type dialogResult){
	if(dialogResult==SystemUiResult::ConfirmButtonSelection)
	{
		gameInProgress=0;
		//checkForChangeInLevel();
		disconnect(discardConf, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(handleDiscardGameConfirmation(bb::system::SystemUiResult::Type)));
		discardConf->deleteLater();
	}
	else
	{
		gameTimer->start();
	}
}*/

void ApplicationUI::handleHelpSlider(float val)
{
	if(val<=0.75)
	{
		helpSlider->setValue(0.0);
	}
	else if(val>=0.75 && val<=1.75)
	{
		helpSlider->setValue(1.0);
	}
	else if(val>=1.75 && val<=2.75)
	{
		helpSlider->setValue(2.0);
	}
	else if(val>=2.75 && val<3.75)
	{
		helpSlider->setValue(3.0);
	}
	else if(val>=3.75 && val<=4.75)
	{
		helpSlider->setValue(4.0);
	}
	else if(val>=4.75 && val<=5.75)
	{
		helpSlider->setValue(5.0);
	}
	else if(val>=5.75 && val<=6.75)
	{
		helpSlider->setValue(6.0);
	}
	else if(val>=6.75)
	{
		helpSlider->setValue(7.0);
	}

	/*else if(val>=3.75)
	{
		helpSlider->setValue(4.0);
	}*/
	//sliderLastVal = int(helpSlider->value());
}

void ApplicationUI::handleHelpSliderImm(float val)
{
	if(val<=0.75)
	{
		helpLevel=0;
	}
	else if(val>=0.75 && val<=1.75)
	{
		helpLevel=1;
	}
	else if(val>=1.75 && val<=2.75)
	{
		helpLevel=2;
	}
	else if(val>=2.75 && val<=3.75)
	{
		helpLevel=3;
	}
	else if(val>=3.75 && val<=4.75)
	{
		helpLevel=4;
	}
	else if(val>=4.75 && val<=5.75)
	{
		helpLevel=5;
	}
	else if(val>=5.75 && val<=6.75)
	{
		helpLevel=6;
	}
	else if(val>6.75)
	{
		helpLevel=7;
	}
	/*else if(val>=3.75)
	{
		helpLevel=4;
	}*/
	setContentForHelp();
}

void ApplicationUI::handleLevelChange(int index)
{
	if(index!=backupLevelSelected)
	{
		if(gameInProgress)
		{
			loseGameWarning->setVisible(TRUE);
		}
		else
		{
			loseGameWarning->setVisible(FALSE);
		}
		savedHS->setValue("levelSelected", index);
	}
	else
	{
		loseGameWarning->setVisible(FALSE);
	}
	setValues(index);
}

void ApplicationUI::initialiseGameField()
{
	Container *timeContainer, *countContainer, *topContainer;
	Container *timeSpaceContainer, *pauseContainer, *countSpaceContainer;
	ImageView *timeBG, *pauseBG, *countBG;

	TextStyle labelStyle;
	labelStyle.setFontWeight(FontWeight::W700);
	labelStyle.setFontSize(FontSize::XXLarge);
	labelStyle.setColor(Color::Gray);

	timeBG = ImageView::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Center).
			image("asset:///images/gamePage/scoreBoard.png");

	timeLabel = Label::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Center).
			textStyle(labelStyle).
			text("0:00");

	timeContainer = Container::create().
			layout(DockLayout::create()).
			add(timeBG).
			add(timeLabel);

	timeSpaceContainer = Container::create().
			horizontal(HorizontalAlignment::Left).
			vertical(VerticalAlignment::Center).
			//left(100.0f).
			left(45.0f).
			add(timeContainer);

	countBG = ImageView::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Center).
			image("asset:///images/gamePage/scoreBoard.png");

	countLabel = Label::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Center).
			textStyle(labelStyle);

	countContainer = Container::create().
			layout(DockLayout::create()).
			add(countBG).
			add(countLabel);

	countSpaceContainer = Container::create().
			horizontal(HorizontalAlignment::Right).
			vertical(VerticalAlignment::Center).
			//right(100.0f).
			right(45.0f).
			add(countContainer);

	pauseBG = ImageView::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Center).
			image("asset:///images/gamePage/pauseBG.png");

	pauseGame = ImageButton::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Center).
			enabled(FALSE).
			defaultImage("asset:///images/gamePage/ic_pause.png").
			pressedImage("asset:///images/gamePage/ic_pausePressed.png").
			disabledImage("asset:///images/gamePage/ic_pauseDisabled.png").
			connect(SIGNAL(clicked()), this, SLOT(displayPauseScreen()));

	pauseContainer = Container::create().
			layout(DockLayout::create()).
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Center).
			add(pauseBG).
			add(pauseGame);

	topContainer = Container::create().
			layout(DockLayout::create()).
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Top).
			preferredWidth(768.0f).
			preferredHeight(155.0f).
			background(Color::LightGray).
			add(timeSpaceContainer).
			add(pauseContainer).
			add(countSpaceContainer);

	mineFieldContainer = Container::create();

	mineField = ScrollView::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Bottom).
			preferredHeight(985.0f).
			scrollMode(ScrollMode::Both).
			pinchToZoomEnabled(TRUE).
			content(mineFieldContainer);

	gameRoot->add(topContainer);
	gameRoot->add(mineField);

	qDebug()<<"Initialized";

	int i, j;

	nMinesLeft=nMines;

	backupLevelSelected=levelSelected;
	backupnRows=nRows;
	backupnCols=nCols;
	backupnMines=nMines;

	gamePlayTime=0;

	countLabel->setText(QString::number(nMinesLeft));

	qDebug()<<"nL, nM, nR,nC:"<<levelSelected<<" "<<nMines<<" "<<nRows<<" "<<nCols;

	/*field = new int*[nRows];
	for(i=0; i<nRows; i++)
	{
		field[i] = new int[nCols];
	}

	for(i=0; i<nRows; i++)
	{
		for(j=0; j<nCols; j++)
		{
			field[i][j]=0;
		}
	}//THE MATRIX THAT WILL HOLD VALUES*/

	switch(levelSelected)
	{
	case 0:
		mineField->scrollViewProperties()->setMinContentScale(2.05f);
		break;
	default:
		mineField->scrollViewProperties()->setMinContentScale(1.363f);
	}
	mineField->scrollViewProperties()->setMaxContentScale(5.0f);

	rowsContainer = new Container [nRows];
	for(i=0; i<nRows; i++)
	{
		rowsContainer[i].setLayout(StackLayout::create().
				orientation(LayoutOrientation::LeftToRight));
	}

	fieldSquares = new Square *[nRows];
	for(i=0; i<nRows; i++)
	{
		fieldSquares[i] = new Square[nCols];
	}//THE MATRIX OF ELEMENTS

	for(i=0; i<nRows; i++)
	{
		for(j=0; j<nCols; j++)
		{
			fieldSquares[i][j].posI=i;
			fieldSquares[i][j].posJ=j;
			fieldSquares[i][j].square->setTopMargin(2.0f);
			fieldSquares[i][j].square->setRightMargin(0.0f);
			fieldSquares[i][j].square->setBottomMargin(2.0f);
			fieldSquares[i][j].square->setLeftMargin(0.0f);
			rowsContainer[i].add(fieldSquares[i][j].square);
		}
		mineFieldContainer->add(&rowsContainer[i]);
	}
	qDebug()<<mineFieldContainer->count();
	flagMode->setEnabled(FALSE);
	//toggleFAU->setEnabled(FALSE);

	qDebug()<<"game field set";
}

void ApplicationUI::invokeFinished()
{
	switch (invokeReply->error())
	{
	case InvokeReplyError::NoTarget:
		qDebug()<<"Target not found";
		break;
	case InvokeReplyError::BadRequest:
		qDebug()<<"Bad request";
		break;
	case InvokeReplyError::Internal:
		qDebug()<<"Internal error";
		break;
	default:
		qDebug()<<"No errors found, carried out successfully";
		break;
	}
}

void ApplicationUI::registrationStateUpdated(bb::platform::bbm::RegistrationState::Type state)
{
	if(state==bb::platform::bbm::RegistrationState::Allowed)
	{
		m_messageService = new bb::platform::bbm::MessageService(m_context, this);
		m_userProfile = new bb::platform::bbm::UserProfile(m_context, this);
	}
	else if(state == bb::platform::bbm::RegistrationState::Unregistered)
	{
		m_context->requestRegisterApplication();
	}
}

void ApplicationUI::setContentForHelp()
{
	switch(helpLevel)
	{
	case 0:
		helpImage->setImage(Image("asset:///images/helpPage/help0.jpg"));
		textHowToPlay->setText("The game consists of a field of squares in which "
				"some contain a mine. Tap anywhere on the field to start the game.");
		break;

	case 1:
		helpImage->setImage("asset:///images/helpPage/help1.jpg");
		textHowToPlay->setText("A safe square is one not containing a mine. "
				"The objective is to uncover all safe squares without uncovering a "
				"mine. The first square uncovered in the game is always a safe square.");
		break;

	case 2:
		helpImage->setImage("asset:///images/helpPage/help2.jpg");
		textHowToPlay->setText("If you uncover a square containing a mine, the game "
				"is over immediately. If it's a safe square, it contains clues to find"
				" the rest of the safe squares.");
		break;

	case 3:
		helpImage->setImage("asset:///images/helpPage/help3.jpg");
		textHowToPlay->setText("A 1 on a square indicates an adjacent "
				"mine, a 2 indicates 2 adjacent mines and so on. The mines "
				"may even be diagonal. A blank square denotes no adjacent mines and "
				"they are uncovered automatically.");
		break;

	case 4:
		helpImage->setImage("asset:///images/helpPage/help4.png");
		textHowToPlay->setText("In case you are certain that a square contains a mine, "
				"you may prevent accidental uncovering by flagging it by tapping the "
				"square while in flag mode and a flag may be removed by tapping it again.");
		break;

	case 5:
		helpImage->setImage("asset:///images/helpPage/help5.jpg");
		textHowToPlay->setText("A timer keeps track of the time in MM:SS since you "
				"started the current game. A flag counter shows you the number "
				"of squares left to be flagged. A pause button is also provided.");
		break;

	case 6:
			helpImage->setImage("asset:///images/helpPage/help6.jpg");
			textHowToPlay->setText("New in v2.1,\n<b>Blaster:</b> Double tap an uncovered "
					"square to uncover all the neighboring unflagged squares. This way, "
					"you may finish the game faster and it works in both modes.");
	break;

	case 7:
		helpImage->setImage("asset:///images/helpPage/help7.png");
		textHowToPlay->setText("The easy and medium levels are designed to help you "
				"get acquainted with the game and the hard level to test the real "
				"puzzle solver in you. Good luck.");
		break;
	default:
		qDebug()<<"Unexpected value for helpLevel: "<<helpLevel;
		break;
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

	default:
		qDebug()<<"ERRORRRRRRRRRRRRR IN LEVEL SELECTION:"<<level;
	}
}

/*void ApplicationUI::setValuesToNonMines()
{
	int i, j;

	for(i=0; i<nRows; i++){
		for(j=0; j<nCols; j++)
		{
			if(field[i][j]!=9)
			{
				field[i][j]=nOfZAroundXY(i, j, 9);
			}
		}
	}
}*/

/*void ApplicationUI::setValuesToSquare()
{
	field[i][j]=nOfZAroundXY(i, j, 9);

	fieldSquares[i][j].value=field[i][j];
}*/

void ApplicationUI::shareAllHighScores()
{
	if(m_context->registrationState() == bb::platform::bbm::RegistrationState::Allowed)
	{
		QString statusMessage;

		if(newHSEasy==9999 && newHSMedium==9999 && newHSHard==9999)
		{
			statusMessage = "I've started playing Soft Mines, why don't you try it too?";
		}
		else
		{
			QString tempChar;
			statusMessage = "My high scores: ";
			if(newHSEasy!=9999)
			{
				tempChar=newHSEasy%60<10?":0":":";
				statusMessage.append("  Easy " + QString::number(newHSEasy/60, 10) + tempChar + QString::number(newHSEasy%60, 10));
			}
			if(newHSMedium!=9999)
			{
				tempChar=newHSMedium%60<10?":0":":";
				statusMessage.append("  Medium " + QString::number(newHSMedium/60, 10) + tempChar + QString::number(newHSMedium%60, 10));
			}
			if(newHSHard!=9999)
			{
				tempChar=newHSHard%60<10?":0":":";
				statusMessage.append("  Hard " + QString::number(newHSHard/60, 10) + tempChar + QString::number(newHSHard%60, 10));
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

void ApplicationUI::shareNewHighScore()
{
	if (m_context->registrationState() == bb::platform::bbm::RegistrationState::Allowed)
	{
		QString statusMessage, tempChar;
		tempChar = gamePlayTime%60<10?"0":"";
		switch(backupLevelSelected)
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
		}
		m_userProfile->requestUpdatePersonalMessage(statusMessage);
		appSheet->close();
	}
	else
	{
		toast->setBody("BBM is not currently connected. Please setup/sign-in to BBM.");
		toast->setIcon(QUrl("asset:///images/icons/ic_bbm.png"));
		toast->show();
		m_context->requestRegisterApplication();
	}
}

void ApplicationUI::shareApp()
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

void ApplicationUI::sheetClosed()
{
	if(gameInProgress)
	{
		gameTimer->start();
	}
}

void ApplicationUI::sheetOpened()
{
	if(gameInProgress)
	{
		gameTimer->stop();
	}
}

void ApplicationUI::toggleTouchMethod(bb::cascades::Tab *selectedTab)
{
	if(selectedTab==flagMode)
	{
		tapToUncover=0; //Set to FLAG mode
		flagMode->setImage("asset:///images/gamePage/flagActive.png");
		uncoverMode->setImage("asset:///images/gamePage/uncover.png");
		//toggleFAU->setTitle("Flag Mines");
		//toggleFAU->setImage("asset:///images/gamePage/flag.png");
	}
	else
	{
		tapToUncover=1; //Set to UNCOVER mode
		uncoverMode->setImage("asset:///images/gamePage/uncoverActive.png");
		flagMode->setImage("asset:///images/gamePage/flag.png");
		//toggleFAU->setTitle("Uncover Squares");
		//toggleFAU->setImage("asset:///images/gamePage/uncover.png");
	}
}

void ApplicationUI::updateClock()
{
	gamePlayTime++;
	QString sec;
	if(gamePlayTime%60<10)
	{
		sec="0" + QString::number(gamePlayTime%60);
	}
	else
	{
		sec=QString::number(gamePlayTime%60);
	}
	timeLabel->setText(QString::number(gamePlayTime/60, 10) + ":" + sec);
}

Square::Square()
{
	value=0;
	posI=posJ=0;
	flagged=FALSE;

	rootContainer = Container::create().
			layout(DockLayout::create());

	square = ImageButton::create().
			defaultImage("asset:///images/mines/covered.png").
			pressedImage("asset:///images/mines/uncoverPressed.png").
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Center);

	connect(square, SIGNAL(clicked()), this, SLOT(handleButtonClick()));
	connect(square, SIGNAL(enabledChanged(bool)), this, SLOT(checkIfAnySquaresLeft()));
}

Square::~Square()
{
	delete rootContainer;
	//delete square;
}

void Square::checkAroundForZeroes(int currentPosI, int currentPosJ)
{
	int i, j, p, q, posI, posJ;

	posI=currentPosI;
	posJ=currentPosJ;

	for(i=-1; i<2; i++)
	{
		p=posI+i;
		if(p>=0 && p<nRowsGlobal)
		{
			for(j=-1; j<2; j++)
			{
				q=posJ+j;
				if(q>=0 && q<nColsGlobal && !(i==0 && j==0) && fieldSquares[p][q].square->isEnabled())
				{
					//fieldSquares[p][q].value=nOfZAroundXY(p, q, 9);
					fieldSquares[p][q].handleButtonClick();
				}
			}
		}
	}
}

void Square::checkAroundForZeroesInClear(int currentPosI, int currentPosJ)
{
	int i, j, p, q, posI, posJ;

	posI=currentPosI;
	posJ=currentPosJ;

	for(i=-1; i<2; i++)
	{
		p=posI+i;
		if(p>=0 && p<nRowsGlobal)
		{
			for(j=-1; j<2; j++)
			{
				q=posJ+j;
				if(q>=0 && q<nColsGlobal && !(i==0 && j==0) && fieldSquares[p][q].square->isEnabled())
				{
					//fieldSquares[p][q].value=nOfZAroundXY(p, q, 9);
					fieldSquares[p][q].handleClear();
				}
			}
		}
	}
}

void Square::checkIfAnySquaresLeft()
{
	//qDebug()<<"NSQFR"<<nSquaresFreed<<" NFREESQ"<<nFreeSquares<<" And enabled changed to "<<square->isEnabled()<<" at ("<<posI<<", "<<posJ<<")";
	if(nSquaresFreed==nFreeSquares)
	{
		connectorBetweenClasses->setText("SUCCESS");
	}
}

void Square::clearAllNearby(int currentPosI, int currentPosJ)
{
	//qDebug()<<"CLEAR CALLED::::";
	int i, j, p, q, posI, posJ;

	posI=currentPosI;
	posJ=currentPosJ;

	//posI=0;
	//posJ=0;

	for(i=-1; i<2; i++)
	{
		p=posI+i;
		if(p>=0 && p<nRowsGlobal)
		{
			for(j=-1; j<2; j++)
			{
				q=posJ+j;
				if(q>=0 && q<nColsGlobal && !(i==0 && j==0) && fieldSquares[p][q].square->isEnabled() && !fieldSquares[p][q].flagged)
				{
					fieldSquares[p][q].handleClear();
				}
			}
		}
	}
}

void Square::disableAndSetImage()
{
	if(flagged)
	{
		if(value==9)
		{
			square->setDisabledImage("asset:///images/mines/flagged.png");
		}
		else
		{
			square->setDisabledImage("asset:///images/mines/wrongFlag.png");
		}
	}
	else if(value==9 && gameLost)
	{
		square->setDisabledImage("asset:///images/mines/mine2.png");
	}
	else
	{
		square->setDisabledImage("asset:///images/mines/covered.png");
	}
}

void Square::emitDTSignal()
{
	//player->play();

	emit emitDoubleTapSignal(posI, posJ);
}

void Square::handleButtonClick()
{
	if(!firstClickHappened)
	{
		firstClickHappened=TRUE;
		clickedPosI=posI;
		clickedPosJ=posJ;
		connectorBetweenClasses->setText("CLICKED");
	}
	if(tapToUncover && !flagged)
	{
		switch(value)
		{
		case 0:
			nSquaresFreed++;
			////qDebug()<<"INCR AT ("<<posI<<", "<<posJ<<")";
			square->setDisabledImage("asset:///images/mines/0.png");
			square->setEnabled(FALSE);
			checkAroundForZeroes(posI, posJ);
			break;
		case 1:
			nSquaresFreed++;
			//qDebug()<<"INCR AT ("<<posI<<", "<<posJ<<")";
			square->setDisabledImage("asset:///images/mines/1.png");
			square->setEnabled(FALSE);
			break;
		case 2:
			nSquaresFreed++;
			//qDebug()<<"INCR AT ("<<posI<<", "<<posJ<<")";
			square->setDisabledImage("asset:///images/mines/2.png");
			square->setEnabled(FALSE);
			break;
		case 3:
			nSquaresFreed++;
			//qDebug()<<"INCR AT ("<<posI<<", "<<posJ<<")";
			square->setDisabledImage("asset:///images/mines/3.png");
			square->setEnabled(FALSE);
			break;
		case 4:
			nSquaresFreed++;
			//qDebug()<<"INCR AT ("<<posI<<", "<<posJ<<")";
			square->setDisabledImage("asset:///images/mines/4.png");
			square->setEnabled(FALSE);
			break;
		case 5:
			nSquaresFreed++;
			//qDebug()<<"INCR AT ("<<posI<<", "<<posJ<<")";
			square->setDisabledImage("asset:///images/mines/5.png");
			square->setEnabled(FALSE);
			break;
		case 6:
			nSquaresFreed++;
			//qDebug()<<"INCR AT ("<<posI<<", "<<posJ<<")";
			square->setDisabledImage("asset:///images/mines/6.png");
			square->setEnabled(FALSE);
			break;
		case 7:
			nSquaresFreed++;
			//qDebug()<<"INCR AT ("<<posI<<", "<<posJ<<")";
			square->setDisabledImage("asset:///images/mines/7.png");
			square->setEnabled(FALSE);
			break;
		case 8:
			nSquaresFreed++;
			//qDebug()<<"INCR AT ("<<posI<<", "<<posJ<<")";
			square->setDisabledImage("asset:///images/mines/8.png");
			square->setEnabled(FALSE);
			break;
		case 9:
			connectorBetweenClasses->setText("GAMEOVER");
			square->setDisabledImage("asset:///images/mines/explodedMine.png");
			square->setEnabled(FALSE);
			break;
		}

		if(value!=0 && value!=9)
		{
			DoubleTapHandler *tapHandler;
			tapHandler = DoubleTapHandler::create().
					onDoubleTapped(this, SLOT(emitDTSignal()));

			connect(this, SIGNAL(emitDoubleTapSignal(int, int)), this, SLOT(clearAllNearby(int, int)));

			square->addGestureHandler(tapHandler);
		}
	}

	else if(!tapToUncover && !flagged)
	{
		flagged=TRUE;
		nMinesLeft--;
		connectorBetweenClasses->setText("SQUAREFLAGGEDORUNFLAGGED");
		square->setDefaultImage("asset:///images/mines/flagged.png");
		square->setPressedImage("asset:///images/mines/flagged.png");
	}
	else if(!tapToUncover && flagged)
	{
		flagged=FALSE;
		nMinesLeft++;
		connectorBetweenClasses->setText("SQUAREFLAGGEDORUNFLAGGED");
		square->setDefaultImage("asset:///images/mines/covered.png");
		square->setPressedImage("asset:///images/mines/uncoverPressed.png");
	}
}

void Square::handleClear()
{
	switch(value)
	{
	case 0:
		nSquaresFreed++;
		////qDebug()<<"INCR AT ("<<posI<<", "<<posJ<<")";
		square->setDisabledImage("asset:///images/mines/0.png");
		square->setEnabled(FALSE);
		checkAroundForZeroesInClear(posI, posJ);
		break;
	case 1:
		nSquaresFreed++;
		//qDebug()<<"INCR AT ("<<posI<<", "<<posJ<<")";
		square->setDisabledImage("asset:///images/mines/1.png");
		square->setEnabled(FALSE);
		break;
	case 2:
		nSquaresFreed++;
		//qDebug()<<"INCR AT ("<<posI<<", "<<posJ<<")";
		square->setDisabledImage("asset:///images/mines/2.png");
		square->setEnabled(FALSE);
		break;
	case 3:
		nSquaresFreed++;
		//qDebug()<<"INCR AT ("<<posI<<", "<<posJ<<")";
		square->setDisabledImage("asset:///images/mines/3.png");
		square->setEnabled(FALSE);
		break;
	case 4:
		nSquaresFreed++;
		//qDebug()<<"INCR AT ("<<posI<<", "<<posJ<<")";
		square->setDisabledImage("asset:///images/mines/4.png");
		square->setEnabled(FALSE);
		break;
	case 5:
		nSquaresFreed++;
		//qDebug()<<"INCR AT ("<<posI<<", "<<posJ<<")";
		square->setDisabledImage("asset:///images/mines/5.png");
		square->setEnabled(FALSE);
		break;
	case 6:
		nSquaresFreed++;
		//qDebug()<<"INCR AT ("<<posI<<", "<<posJ<<")";
		square->setDisabledImage("asset:///images/mines/6.png");
		square->setEnabled(FALSE);
		break;
	case 7:
		nSquaresFreed++;
		//qDebug()<<"INCR AT ("<<posI<<", "<<posJ<<")";
		square->setDisabledImage("asset:///images/mines/7.png");
		square->setEnabled(FALSE);
		break;
	case 8:
		nSquaresFreed++;
		//qDebug()<<"INCR AT ("<<posI<<", "<<posJ<<")";
		square->setDisabledImage("asset:///images/mines/8.png");
		square->setEnabled(FALSE);
		break;
	case 9:
		connectorBetweenClasses->setText("GAMEOVER");
		square->setDisabledImage("asset:///images/mines/explodedMine.png");
		square->setEnabled(FALSE);
		break;
	}

	if(value!=0 && value!=9)
	{
		DoubleTapHandler *tapHandler;
		tapHandler = DoubleTapHandler::create().
				onDoubleTapped(this, SLOT(emitDTSignal()));

		connect(this, SIGNAL(emitDoubleTapSignal(int, int)), this, SLOT(clearAllNearby(int, int)));

		square->addGestureHandler(tapHandler);
	}
}

int Square::nOfZAroundXY(int x, int y, int z)
{
	int i, j, p, q, count=0;
	for(i=-1; i<2; i++){
		p=x+i;
		if(p>=0 && p<nRowsGlobal)
		{
			for(j=-1; j<2; j++)
			{
				q=y+j;
				if(q>=0 && q<nColsGlobal)
				{
					if((i!=0 || j!=0) && fieldSquares[p][q].value==z)
					{
						count++;
					}
				}
			}
		}
	}
	return count;
}
