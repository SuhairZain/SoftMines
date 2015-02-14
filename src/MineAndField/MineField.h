/*
 * MineField.h
 *
 *  Created on: Nov 9, 2014
 *      Author: SuhairZain
 */

#ifndef MINEFIELD_H_
#define MINEFIELD_H_

#include "Mine.h"

#include <bb/cascades/Container>

using namespace bb::cascades;

struct MineDetails
{
    int value;
    bool isEnabled;
    bool isFlagged;
    Mine *mine;
};

class MineField: public Container
{
Q_OBJECT
signals:
    void gameFinished(bool);
    void gameFlagsChanged(int);
    void gameStarted();

private slots:
    void onMineDoubleTapped(int, int);
    void onMineFlagged(int, int);
    void onMineTapped(int, int);

private:
    MineDetails** field;
    int nRows, nColumns, nActiveMines;
    int nMinesOpened, nMinesLeftToFlag, nSafeMines;
    bool fieldNeedsToBeSet;
    bool gameIsActive;

    void fillField(int, int);
    int numberOfMinesAround(int, int);
    void uncoverMineAt(int, int);
    void uncoverMineInClearAt(int, int);
    void uncoverAroundZero(int, int);
    void uncoverAroundZeroInClear(int, int);
    //void uncoverZeroesAroundInClear(int, int);

public:
    MineField(int, int, int);
    ~MineField();
};

#endif /* MINEFIELD_H_ */
