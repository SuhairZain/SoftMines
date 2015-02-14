/*
 * StatusBar.cpp
 *
 *  Created on: Nov 10, 2014
 *      Author: SuhairZain
 */

#include <src/Controls/StatusBar.h>

#include <bb/cascades/DockLayout>
#include <bb/cascades/ImageView>
#include <bb/cascades/StackLayout>
#include <bb/cascades/StackLayoutProperties>
#include <bb/cascades/TextStyle>

StatusBar::StatusBar()
{
    this->setBackground(Color::fromARGB(0xff515151));
    this->setLayout(StackLayout::create().orientation(LayoutOrientation::LeftToRight));
    this->setTopPadding(20);
    this->setBottomPadding(20);

    TextStyle labelStyle;
    labelStyle.setFontWeight(FontWeight::W700);
    labelStyle.setFontSize(FontSize::XXLarge);
    labelStyle.setColor(Color::Gray);

    ImageView *timeBG = ImageView::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center).
            image("asset:///images/gamePage/scoreBoard.png");

    timeLabel = Label::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center).
            text("0:00").
            textStyle(labelStyle);

    Container *timeInnerC = Container::create().
            horizontal(HorizontalAlignment::Fill).
            vertical(VerticalAlignment::Fill).
            layout(DockLayout::create()).
            add(timeBG).
            add(timeLabel);

    Container *timeC = Container::create().
            layoutProperties(StackLayoutProperties::create().spaceQuota(1)).
            add(timeInnerC);
    this->add(timeC);

    ImageView *pauseBG = ImageView::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center).
            image("asset:///images/gamePage/pauseBG.png");

    pauseButton = ImageButton::create().
            enabled(FALSE).
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center).
            defaultImage("asset:///images/icons/ic_pause.png").
            pressedImage("asset:///images/icons/ic_pausePressed.png").
            disabledImage("asset:///images/icons/ic_pauseDisabled.png").
            connect(SIGNAL(clicked()), this, SIGNAL(pauseClicked()));

    Container *pauseC = Container::create().
            rightMargin(20).
            layout(DockLayout::create()).
            add(pauseBG).
            add(pauseButton);
    this->add(pauseC);

    ImageView *resetBG = ImageView::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center).
            image("asset:///images/gamePage/pauseBG.png");

    resetButton = ImageButton::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center).
            enabled(FALSE).
            defaultImage("asset:///images/icons/ic_reset.png").
            pressedImage("asset:///images/icons/ic_resetPressed.png").
            disabledImage("asset:///images/icons/ic_resetDisabled.png").
            connect(SIGNAL(clicked()), this, SIGNAL(resetClicked()));

    Container *resetC = Container::create().
            layout(DockLayout::create()).
            add(resetBG).
            add(resetButton);
    this->add(resetC);

    ImageView *countBG = ImageView::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center).
            image("asset:///images/gamePage/scoreBoard.png");

    countLabel = Label::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center).
            text("10").
            textStyle(labelStyle);

    Container *countInnerC = Container::create().
            horizontal(HorizontalAlignment::Fill).
            vertical(VerticalAlignment::Fill).
            layout(DockLayout::create()).
            add(countBG).
            add(countLabel);

    Container *countC = Container::create().
            layoutProperties(StackLayoutProperties::create().spaceQuota(1)).
            add(countInnerC);
    this->add(countC);
}

void StatusBar::setCount(int count)
{
    countLabel->setText(QString::number(count));
}

void StatusBar::setPauseEnabled(bool enabled)
{
    pauseButton->setEnabled(enabled);
}

void StatusBar::setResetEnabled(bool enabled)
{
    resetButton->setEnabled(enabled);
}

void StatusBar::setTimer(int time)
{
    QString sec;
    if(time%60<10)
    {
        sec="0" + QString::number(time%60);
    }
    else
    {
        sec=QString::number(time%60);
    }
    timeLabel->setText(QString::number(time/60, 10) + ":" + sec);
}
