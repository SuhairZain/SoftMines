/*
 * MineField.cpp
 *
 *  Created on: Nov 9, 2014
 *      Author: SuhairZain
 */

#include <stdlib.h>
#include <time.h>

#include <src/MineAndField/MineField.h>

#include <bb/cascades/DoubleTapHandler>
#include <bb/cascades/StackLayout>

MineField::MineField(int rows, int cols, int nMines)
{
    nMinesOpened = 0;
    fieldNeedsToBeSet = TRUE;
    gameIsActive = FALSE;

    nRows = rows;
    nColumns = cols;
    nMinesLeftToFlag = nActiveMines = nMines;
    nSafeMines = nRows*nColumns - nActiveMines;

    field = new MineDetails* [nRows];
    for(int i=0; i<nRows; ++i)
    {
        field[i] = new MineDetails[nColumns];
        Container *horizontalC = Container::create().
                layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight));
        this->add(horizontalC);

        for(int j=0; j<nColumns; ++j)
        {
            Mine *tempMine = new Mine(i, j);
            connect(tempMine, SIGNAL(mineTapped(int,int)), this, SLOT(onMineTapped(int, int)));
            connect(tempMine, SIGNAL(mineFlagged(int, int)), this, SLOT(onMineFlagged(int, int)));

            field[i][j].isEnabled = TRUE;
            field[i][j].isFlagged = FALSE;
            field[i][j].value = 0;
            field[i][j].mine = tempMine;

            horizontalC->add(Container::create().add(tempMine));
        }
    }
}

MineField::~MineField()
{
    for(int i=0; i<nRows; ++i)
    {
        delete [] field[i];
    }
    delete [] field;
}

void MineField::fillField(int tappedI, int tappedJ)
{
    srand(time(NULL));

    int nMinesFilled=0, nMines = nRows*nColumns-9;

    while(TRUE)
    {
        for(int i=0; i<nRows; ++i)
        {
            for(int j=0; j<nColumns; ++j)
            {
                if(nMinesFilled==nActiveMines)
                {
                    for(int x=0; x<nRows; ++x)
                    {
                        for(int y=0; y<nColumns; ++y)
                        {
                            if(field[x][y].value == 0)
                                field[x][y].value = numberOfMinesAround(x, y);
                        }
                    }

                    //StaticVariables::fieldIsSet = TRUE;
                    //gameTimer->start(1000);
                    return;
                }

                if(rand()%nMines==0)
                {
                    if(field[i][j].value == 0 &&
                            !((i==tappedI || i==tappedI-1 || i==tappedI+1) &&
                                    (j==tappedJ || j==tappedJ-1 || j==tappedJ+1)))
                    {
                        field[i][j].value = 9;
                        ++nMinesFilled;
                    }
                }
            }
        }
    }
}

void MineField::onMineDoubleTapped(int tappedI, int tappedJ)
{
    if(gameIsActive)
    {
        for(int i=-1; i<2; ++i)
        {
            int p = tappedI + i;
            if(p>=0 && p<nRows)
            {
                for(int j=-1; j<2; ++j)
                {
                    int q = tappedJ + j;
                    if(q>=0 && q<nColumns)
                    {
                        if(!(i==0 && j==0) && !field[p][q].isFlagged && field[p][q].isEnabled)
                        {
                            uncoverMineInClearAt(p, q);
                        }
                    }
                }
            }
        }
    }
}

void MineField::onMineFlagged(int flaggedI, int flaggedJ)
{
    if(field[flaggedI][flaggedJ].mine->isEnabled() && !fieldNeedsToBeSet)
    {
        bool f = field[flaggedI][flaggedJ].isFlagged;

        if(f)
        {
            ++nMinesLeftToFlag;
            Mine *currMine = field[flaggedI][flaggedJ].mine;
            currMine->setDefaultImage("asset:///images/mines/covered.png");
            currMine->setPressedImage("asset:///images/mines/uncoverPressed.png");
        }
        else
        {
            --nMinesLeftToFlag;
            Mine *currMine = field[flaggedI][flaggedJ].mine;
            currMine->setDefaultImage("asset:///images/mines/flagged.png");
            currMine->setPressedImage("asset:///images/mines/flagged.png");
        }
        field[flaggedI][flaggedJ].isFlagged = !f;
        emit gameFlagsChanged(nMinesLeftToFlag);
    }
}

void MineField::onMineTapped(int tappedI, int tappedJ)
{
    if(fieldNeedsToBeSet)
    {
        fieldNeedsToBeSet = FALSE;
        fillField(tappedI, tappedJ);

        emit gameStarted();
        gameIsActive = TRUE;
    }

    if(gameIsActive && !field[tappedI][tappedJ].isFlagged)
        uncoverMineAt(tappedI, tappedJ);
}

int MineField::numberOfMinesAround(int tappedI, int tappedJ)
{
    int count = 0;
    for(int i=-1; i<2; ++i)
    {
        int p = tappedI + i;
        if(p>=0 && p<nRows)
        {
            for(int j=-1; j<2; ++j)
            {
                int q = tappedJ + j;
                if(q>=0 && q<nColumns)
                {
                    if(!(i==0 && j==0) && field[p][q].value==9)
                    {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}

void MineField::uncoverAroundZero(int tappedI, int tappedJ)
{
    for(int i=-1; i<2; ++i)
    {
        int p = tappedI + i;
        if(p>=0 && p<nRows)
        {
            for(int j=-1; j<2; ++j)
            {
                int q = tappedJ + j;

                if(q>=0 && q<nColumns && !(i==0 && j==0) && field[p][q].isEnabled)
                {
                    uncoverMineAt(p, q);
                }
            }
        }
    }
}

void MineField::uncoverAroundZeroInClear(int tappedI, int tappedJ)
{
    qDebug()<<"Uncover around"<<tappedI<<tappedJ;
    for(int i=-1; i<2; ++i)
    {
        int p = tappedI + i;
        if(p>=0 && p<nRows)
        {
            for(int j=-1; j<2; ++j)
            {
                int q = tappedJ + j;

                if(q>=0 && q<nColumns && !(i==0 && j==0) && field[p][q].isEnabled && !field[p][q].isFlagged)
                {
                    uncoverMineInClearAt(p, q);
                }
            }
        }
    }
}

void MineField::uncoverMineAt(int i, int j)
{
    Mine *currentMine = field[i][j].mine;
    int mineValue = field[i][j].value;
    field[i][j].isEnabled = FALSE;
    if(mineValue==9)
    {
        qDebug()<<"Explosion at"<<i<<j;
        currentMine->setEnabled(FALSE);
        currentMine->setDisabledImage("asset:///images/mines/explodedMine.png");
        gameIsActive = FALSE;
        emit gameFinished(FALSE);

        for(int i=0; i<nRows; ++i)
        {
            for(int j=0; j<nColumns; ++j)
            {
                Mine *currMine = field[i][j].mine;
                if(currMine->isEnabled())
                {
                    currMine->setEnabled(FALSE);

                    if(field[i][j].isFlagged)
                    {
                        if(field[i][j].value==9)
                        {
                            currMine->setDisabledImage("asset:///images/mines/flagged.png");
                        }
                        else
                        {
                            currMine->setDisabledImage("asset:///images/mines/wrongFlag.png");
                        }
                    }
                    else if(field[i][j].value==9)
                    {
                        currMine->setDisabledImage("asset:///images/mines/mine2.png");
                    }
                    else
                    {
                        currMine->setDisabledImage("asset:///images/mines/covered.png");
                    }
                }
            }
        }
        //return TRUE;
    }
    else
    {
        currentMine->setDisabledImage(Image("asset:///images/mines/" + QString::number(mineValue) + ".png"));

        if(mineValue==0)
        {
            uncoverAroundZero(i, j);
        }
        else
        {
            currentMine->addGestureHandler(DoubleTapHandler::create().
                    onDoubleTapped(currentMine, SLOT(onDoubleTapped())));
            connect(currentMine, SIGNAL(mineDoubleTapped(int, int)), this, SLOT(onMineDoubleTapped(int, int)));
        }

        if(++nMinesOpened==nSafeMines)
        {
            emit gameFinished(TRUE);
            gameIsActive = FALSE;

            for(int i=0; i<nRows; ++i)
            {
                for(int j=0; j<nColumns; ++j)
                {
                    Mine *currMine = field[i][j].mine;
                    if(currMine->isEnabled())
                    {
                        currMine->setEnabled(FALSE);

                        if(field[i][j].isFlagged)
                            currMine->setDisabledImage("asset:///images/mines/flagged.png");
                        else
                        {
                            int val = field[i][j].value;
                            if(val==9)
                                currMine->setDisabledImage(Image("asset:///images/mines/covered.png"));
                            else
                                currMine->setDisabledImage(Image("asset:///images/mines/" + QString::number(val) + ".png"));
                        }
                        //currMine->setDisabledOnSuccess();
                    }
                }
            }
        }
        currentMine->setEnabled(FALSE);
        //return FALSE;
    }
}

void MineField::uncoverMineInClearAt(int i, int j)
{
    qDebug()<<"Uncover at"<<i<<j;
    Mine *currentMine = field[i][j].mine;
    int mineValue = field[i][j].value;
    field[i][j].isEnabled = FALSE;
    if(mineValue==9)
    {
        qDebug()<<"Explosion at"<<i<<j;
        currentMine->setEnabled(FALSE);
        currentMine->setDisabledImage("asset:///images/mines/explodedMine.png");
        gameIsActive = FALSE;
        emit gameFinished(FALSE);

        for(int i=0; i<nRows; ++i)
        {
            for(int j=0; j<nColumns; ++j)
            {
                Mine *currMine = field[i][j].mine;
                if(currMine->isEnabled())
                {
                    currMine->setEnabled(FALSE);

                    if(field[i][j].isFlagged)
                    {
                        if(field[i][j].value==9)
                        {
                            currMine->setDisabledImage("asset:///images/mines/flagged.png");
                        }
                        else
                        {
                            currMine->setDisabledImage("asset:///images/mines/wrongFlag.png");
                        }
                    }
                    else if(field[i][j].value==9)
                    {
                        currMine->setDisabledImage("asset:///images/mines/mine2.png");
                    }
                    else
                    {
                        currMine->setDisabledImage("asset:///images/mines/covered.png");
                    }
                }
            }
        }
        //return TRUE;
    }
    else
    {
        currentMine->setDisabledImage(Image("asset:///images/mines/" + QString::number(mineValue) + ".png"));

        if(mineValue==0)
        {
            uncoverAroundZeroInClear(i, j);
        }
        else
        {
            currentMine->addGestureHandler(DoubleTapHandler::create().
                    onDoubleTapped(currentMine, SLOT(onDoubleTapped())));
            connect(currentMine, SIGNAL(mineDoubleTapped(int, int)), this, SLOT(onMineDoubleTapped(int, int)));
        }

        if(++nMinesOpened==nSafeMines)
        {
            emit gameFinished(TRUE);
            gameIsActive = FALSE;

            for(int i=0; i<nRows; ++i)
            {
                for(int j=0; j<nColumns; ++j)
                {
                    Mine *currMine = field[i][j].mine;
                    if(currMine->isEnabled())
                    {
                        currMine->setEnabled(FALSE);

                        if(field[i][j].isFlagged)
                            currMine->setDisabledImage("asset:///images/mines/flagged.png");
                        else
                        {
                            int val = field[i][j].value;
                            if(val==9)
                                currMine->setDisabledImage(Image("asset:///images/mines/covered.png"));
                            else
                                currMine->setDisabledImage(Image("asset:///images/mines/" + QString::number(val) + ".png"));
                        }
                        //currMine->setDisabledOnSuccess();
                    }
                }
            }
        }
        currentMine->setEnabled(FALSE);
        //return FALSE;
    }
}
