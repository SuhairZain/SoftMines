/*
 * Stepper.h
 *
 *  Created on: Nov 12, 2014
 *      Author: SuhairZain
 */

#ifndef STEPPER_H_
#define STEPPER_H_

#include <bb/cascades/Container>
#include <bb/cascades/ImageButton>
#include <bb/cascades/ImageView>
#include <bb/cascades/Label>

using namespace bb::cascades;

class Stepper: public Container
{
Q_OBJECT
signals:
    void valueChanged(int);

private slots:
    void onMinusClicked();
    void onPlusClicked();

private:
    int currValue, minValue, maxValue;
    ImageButton *minus, *plus;
    Label *countLabel;

public:
    Stepper(QString, int, int, int);

    int value(){return currValue;}
    void setMaxValue(int);
};

#endif /* STEPPER_H_ */
