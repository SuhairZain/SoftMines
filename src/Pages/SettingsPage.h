/*
 * SettingsPage.h
 *
 *  Created on: Nov 10, 2014
 *      Author: SuhairZain
 */

#ifndef SETTINGSPAGE_H_
#define SETTINGSPAGE_H_

//#include "../Controls/Stepper.h"

#include <bb/cascades/Container>
#include <bb/cascades/Label>
#include <bb/cascades/Page>

using namespace bb::cascades;

class SettingsPage: public Page
{
Q_OBJECT
signals:
    void close(int);
    void musicEnabledChanged(bool);

private slots:
    void onCloseClicked();
    void onSelectedIndexChanged(int);
    //void onValuesChanged();
    /*void onValueColumnsChanged();
    void onValueMinesChanged();
    void onValueRowsChanged();*/

private:
    int initialLevel, finalLevel;//, initialR, initialC, initialM;
    bool gameIsActive;
    //Container *customC;
    Label *loseGameWarning;
    //Stepper *rowStepper, *columnStepper, *mineStepper;

public:
    SettingsPage(bool, int, bool/*, int, int, int*/);
};

#endif /* SETTINGSPAGE_H_ */
