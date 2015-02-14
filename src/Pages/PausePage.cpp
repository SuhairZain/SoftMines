/*
 * PausePage.cpp
 *
 *  Created on: Nov 10, 2014
 *      Author: SuhairZain
 */

#include <src/Pages/PausePage.h>

#include <bb/cascades/ActionItem>
#include <bb/cascades/Container>
#include <bb/cascades/DockLayout>
#include <bb/cascades/Label>
#include <bb/cascades/StackLayout>
#include <bb/cascades/TextStyle>
#include <bb/cascades/TitleBar>

PausePage::PausePage(int level, int time, int count)
{
    TextStyle gameInfoStyle;
    gameInfoStyle.setFontSize(FontSize::XLarge);
    gameInfoStyle.setFontWeight(FontWeight::W400);
    gameInfoStyle.setTextAlign(TextAlign::Center);
    gameInfoStyle.setColor(Color::fromARGB(0xFFFFA500));

    Label *levelD = Label::create().
            textStyle(gameInfoStyle).
            text("Level: ");

    Label *timeD = Label::create().
            textStyle(gameInfoStyle).
            text("Gametime: ");

    Label *countD = Label::create().
            textStyle(gameInfoStyle).
            text("Squares left to flag: ");

    gameInfoStyle.setColor(Color::Black);
    gameInfoStyle.setFontWeight(FontWeight::W300);

    Label *pauseLevel = Label::create().
            textStyle(gameInfoStyle);

    Label *pauseTime = Label::create().
            textStyle(gameInfoStyle);

    Label *pauseCount = Label::create().
            textStyle(gameInfoStyle);

    Container *levelC = Container::create().
            layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
            add(levelD).
            add(pauseLevel);

    Container *timeC = Container::create().
            layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
            add(timeD).
            add(pauseTime);

    Container *countC = Container::create().
            layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
            add(countD).
            add(pauseCount);

    Container *contentC = Container::create().
            vertical(VerticalAlignment::Center).
            horizontal(HorizontalAlignment::Center).
            add(levelC).
            add(timeC).
            add(countC);

    Container *rootC = Container::create().
            layout(DockLayout::create()).
            add(contentC);

    ActionItem *resume = ActionItem::create().
            title("Resume").
            connect(SIGNAL(triggered()), this, SIGNAL(close()));

    TitleBar *tBar = TitleBar::create().
            title("Game paused").
            acceptAction(resume);

    this->setContent(rootC);
    this->setTitleBar(tBar);

    switch(level)
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

    QString sec;
    if(time%60<10)
    {
        sec="0" + QString::number(time%60);
    }
    else
    {
        sec=QString::number(time%60);
    }
    pauseTime->setText(QString::number(time/60, 10) + ":" + sec);
    pauseCount->setText(QString::number(count));
}

