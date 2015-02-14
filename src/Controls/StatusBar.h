/*
 * StatusBar.h
 *
 *  Created on: Nov 10, 2014
 *      Author: SuhairZain
 */

#ifndef STATUSBAR_H_
#define STATUSBAR_H_

#include <bb/cascades/Container>
#include <bb/cascades/ImageButton>
#include <bb/cascades/Label>

using namespace bb::cascades;

class StatusBar: public Container
{
Q_OBJECT
signals:
    void pauseClicked();
    void resetClicked();

private:
    ImageButton *pauseButton, *resetButton;
    Label *timeLabel, *countLabel;

public:
    StatusBar();

    void setCount(int);
    void setPauseEnabled(bool);
    void setResetEnabled(bool);
    void setTimer(int);
};

#endif /* STATUSBAR_H_ */
