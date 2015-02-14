/*void ApplicationUI::checkForLevelChange()
{
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
    //toggleFAU->setTitle("Uncover Squares");
    //toggleFAU->setImage("asset:///images/gamePage/uncover.png");
    //toggleFAU->setEnabled(FALSE);
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

    field = new Mine *[nRows];
    for(i=0; i<nRows; i++)
    {
        field[i] = new Mine[nCols];
    }//THE MATRIX OF ELEMENTS

    for(i=0; i<nRows; i++)
    {
        for(j=0; j<nCols; j++)
        {
            field[i][j].posI=i;
            field[i][j].posJ=j;
            field[i][j].square->setTopMargin(2.0f);
            field[i][j].square->setRightMargin(0.0f);
            field[i][j].square->setBottomMargin(2.0f);
            field[i][j].square->setLeftMargin(0.0f);
            rowsContainer[i].add(field[i][j].square);
        }
        mineFieldContainer->add(&rowsContainer[i]);
    }
    qDebug()<<mineFieldContainer->count();
    flagMode->setEnabled(FALSE);
    //toggleFAU->setEnabled(FALSE);

    qDebug()<<"game field set";
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
}*/
