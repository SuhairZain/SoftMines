/*
 * Square.cpp
 *
 *  Created on: Nov 9, 2014
 *      Author: SuhairZain
 */

#include "Mine.h"

#include <bb/cascades/LongPressHandler>
#include <bb/cascades/TapHandler>

Mine::Mine(int i, int j)
{
    posI = i;
    posJ = j;

    this->setHorizontalAlignment(HorizontalAlignment::Center);
    this->setVerticalAlignment(VerticalAlignment::Center);
    this->setDefaultImage("asset:///images/mines/covered.png");
    //this->setDisabledImage("asset:///images/mines/covered.png");
    this->setPressedImage("asset:///images/mines/uncoverPressed.png");

    //this->setTopMargin(2.0f);
    //this->setRightMargin(0.0f);
    //this->setBottomMargin(2.0f);
    //this->setLeftMargin(0.0f);

    this->addGestureHandler(TapHandler::create().onTapped(this, SLOT(onTapped())));
    this->addGestureHandler(LongPressHandler::create().onLongPressed(this, SLOT(onLongPressed())));
}

/*void Mine::disableAndSetImage(int value)
{
    if(isFlagged)
    {
        if(value==9)
        {
            this->setDisabledImage("asset:///images/mines/flagged.png");
        }
        else
        {
            this->setDisabledImage("asset:///images/mines/wrongFlag.png");
        }
    }
    else if(value==9)
    {
        this->setDisabledImage("asset:///images/mines/mine2.png");
    }
    else
    {
        this->setDisabledImage("asset:///images/mines/covered.png");
    }
}*/

void Mine::onDoubleTapped()
{
    emit mineDoubleTapped(posI, posJ);
}

void Mine::onLongPressed()
{
    /*if(this->isEnabled() && StaticVariables::fieldIsSet)
    {
        isFlagged = !isFlagged;

        if(isFlagged)
        {
            this->setDefaultImage("asset:///images/mines/flagged.png");
            this->setPressedImage("asset:///images/mines/flagged.png");
        }
        else
        {
            this->setDefaultImage("asset:///images/mines/covered.png");
            this->setPressedImage("asset:///images/mines/uncoverPressed.png");
        }
    }*/
    emit mineFlagged(posI, posJ);
}

void Mine::onTapped()
{
    //if(!isFlagged)
    emit mineTapped(posI, posJ);
}

/*void Mine::setDisabledOnSuccess()
{
    if(isFlagged)
        this->setDisabledImage("asset:///images/mines/flagged.png");
    else
        this->setDisabledImage("asset:///images/mines/flagged.png");
}*/
