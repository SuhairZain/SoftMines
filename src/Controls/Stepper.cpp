/*
 * Stepper.cpp
 *
 *  Created on: Nov 12, 2014
 *      Author: SuhairZain
 */

#include <src/Controls/Stepper.h>

#include <bb/cascades/DockLayout>
#include <bb/cascades/StackLayout>

Stepper::Stepper(QString title, int min, int max, int dVal)
{
    currValue = dVal;
    minValue = min;
    maxValue = max;

    Label *titleLabel = Label::create().
            horizontal(HorizontalAlignment::Center).
            text(title);

    minus = ImageButton::create().
            defaultImage("asset:///images/stepper/minus.png").
            pressedImage("asset:///images/stepper/minus.png").
            disabledImage("asset:///images/stepper/minusDisabled.png").
            connect(SIGNAL(clicked()), this, SLOT(onMinusClicked()));

    Container *minusC = Container::create().
            add(minus);

    ImageView *center = ImageView::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center).
            image("asset:///images/stepper/center.png");

    countLabel = Label::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center).
            text(QString::number(currValue));

    Container *centerC = Container::create().
            layout(DockLayout::create()).
            add(center).
            add(countLabel);

    plus = ImageButton::create().
            defaultImage("asset:///images/stepper/plus.png").
            pressedImage("asset:///images/stepper/plus.png").
            disabledImage("asset:///images/stepper/plusDisabled.png").
            connect(SIGNAL(clicked()), this, SLOT(onPlusClicked()));

    Container *plusC = Container::create().
            add(plus);

    Container *imagesC = Container::create().
            horizontal(HorizontalAlignment::Center).
            layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
            add(minusC).
            add(centerC).
            add(plusC);

    this->add(titleLabel);
    this->add(imagesC);
}

void Stepper::onMinusClicked()
{
    if(--currValue==minValue)
        minus->setEnabled(FALSE);
    else
        plus->setEnabled(TRUE);

    countLabel->setText(QString::number(currValue));
    emit valueChanged(currValue);
}

void Stepper::onPlusClicked()
{
    if(++currValue==maxValue)
        plus->setEnabled(FALSE);
    else
        minus->setEnabled(TRUE);

    countLabel->setText(QString::number(currValue));
    emit valueChanged(currValue);
}

void Stepper::setMaxValue(int nVal)
{
    if(nVal>maxValue)
        plus->setEnabled(TRUE);
    else
        plus->setEnabled(FALSE);

    maxValue = nVal;
    if(currValue>nVal)
        currValue = nVal;

    countLabel->setText(QString::number(currValue));
}
