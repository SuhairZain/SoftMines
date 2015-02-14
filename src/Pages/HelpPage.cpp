/*
 * HelpPage.cpp
 *
 *  Created on: Nov 10, 2014
 *      Author: SuhairZain
 */

#include <src/Pages/HelpPage.h>

#include <bb/cascades/Container>
#include <bb/cascades/DockLayout>
#include <bb/cascades/TitleBar>

HelpPage::HelpPage()
{
    startX = 0;

    imageNames<<"0.jpg"<<"1.jpg"<<"2.jpg"<<"3.jpg"<<"4.png"<<"5.jpg"<<"6.jpg"<<"7.png";
    helpText<<"The game consists of a field of squares in which "
            "some contain a mine. Tap anywhere on the field to start the game."
            <<"A safe square is one not containing a mine. "
            "The objective is to uncover all safe squares without uncovering a "
            "mine. The first square uncovered in the game is always a safe square."
            <<"If you uncover a square containing a mine, the game "
            "is over immediately. If it's a safe square, it contains clues to find"
            " the rest of the safe squares."
            <<"A 1 on a square indicates an adjacent "
            "mine, a 2 indicates 2 adjacent mines and so on. The mines "
            "may even be diagonal. A blank square denotes no adjacent mines and "
            "they are uncovered automatically."
            <<"In case you are certain that a square contains a mine, "
            "you may prevent accidental uncovering by flagging it by long pressing it."
            " Long press it again to remove the flag."
            <<"A timer keeps track of the time in MM:SS since you "
            "started the current game. A flag counter shows you the number "
            "of squares left to be flagged. A pause button and reset button is also provided."
            <<"Double tap an uncovered "
            "square to uncover all the neighboring unflagged squares. This way, "
            "you may finish the game faster."
            <<"The easy and medium levels are designed to help you "
            "get acquainted with the game and the hard level to test the real "
            "puzzle solver in you while the insane mode is made just to drive you nuts. Good luck.";

    pageIndex = 0;
    maxIndex = imageNames.size() - 1;

    helpImage = ImageView::create().
            horizontal(HorizontalAlignment::Center).
            image(Image("asset:///images/helpPage/help" + imageNames.at(0)));

    TextStyle textStyle;
    textStyle.setColor(Color::DarkMagenta);
    textStyle.setFontSize(FontSize::XLarge);
    textStyle.setFontWeight(FontWeight::W300);
    textStyle.setTextAlign(TextAlign::Center);
    textStyle.setLineHeight(0.9f);

    helpLabel = Label::create().
            horizontal(HorizontalAlignment::Center).
            multiline(TRUE).
            text(helpText.at(0)).
            textStyle(textStyle).
            format(TextFormat::Html);

    Container *contentC = Container::create().
            vertical(VerticalAlignment::Center).
            horizontal(HorizontalAlignment::Center).
            add(helpImage).
            add(helpLabel);

    Container *rootC = Container::create().
            horizontal(HorizontalAlignment::Fill).
            vertical(VerticalAlignment::Fill).
            layout(DockLayout::create()).
            add(contentC);

    rootView = ScrollView::create().
            //onTouch(this, SLOT(onTouch(bb::cascades::TouchEvent*))).
            content(rootC);

    prev = ActionItem::create().
            title("Close").
            connect(SIGNAL(triggered()), this, SLOT(prevClicked()));

    next = ActionItem::create().
            title("Next").
            connect(SIGNAL(triggered()), this, SLOT(nextClicked()));

    TitleBar *tBar = TitleBar::create().
            title("Help").
            dismissAction(prev).
            acceptAction(next);

    this->setContent(rootView);
    this->setTitleBar(tBar);
}

void HelpPage::nextClicked()
{
    //qDebug()<<pageIndex;
    if(pageIndex==maxIndex)
    {
        emit close();
        return;
    }

    helpImage->setImage(Image("asset:///images/helpPage/help" + imageNames.at(++pageIndex)));
    helpLabel->setText(helpText.at(pageIndex));

    if(pageIndex==1)
        prev->setTitle("Back");
    else if(pageIndex==maxIndex)
        next->setTitle("Close");
}

/*void HelpPage::onTouch(bb::cascades::TouchEvent *event)
{
    if(event->isMove())
    {
        int dist = event->screenX() - startX;
        rootView->setTranslationX(dist);
        if(dist>20)
            rootView->scrollViewProperties()->setScrollMode(ScrollMode::None);
    }
    else if(event->isDown())
    {
        startX = event->screenX();
    }
    else if(event->isUp())
    {
        int dist = event->screenX() - startX;
        if(dist<-100 && pageIndex!=maxIndex)
            nextClicked();
        else if(dist>100 && pageIndex!=0)
            prevClicked();
        rootView->resetTranslationX();
        rootView->scrollViewProperties()->setScrollMode(ScrollMode::Vertical);
        rootView->resetViewableArea();
    }
    else if(event->isCancel())
    {
        rootView->resetTranslationX();
        rootView->scrollViewProperties()->setScrollMode(ScrollMode::Vertical);
        rootView->resetViewableArea();
    }
}*/

void HelpPage::prevClicked()
{
    if(pageIndex==0)
    {
        emit close();
        return;
    }

    if(pageIndex==1)
        prev->setTitle("Close");
    else if(pageIndex==maxIndex)
        next->setTitle("Next");

    helpImage->setImage(Image("asset:///images/helpPage/help" + imageNames.at(--pageIndex)));
    helpLabel->setText(helpText.at(pageIndex));
}
