/*
 * HighScoresPage.cpp
 *
 *  Created on: Nov 10, 2014
 *      Author: SuhairZain
 */

#include <src/Pages/HighScoresPage.h>

#include <bb/cascades/ActionItem>
#include <bb/cascades/Button>
#include <bb/cascades/Container>
#include <bb/cascades/DockLayout>
#include <bb/cascades/ImageView>
#include <bb/cascades/Label>
#include <bb/cascades/StackLayout>
#include <bb/cascades/TitleBar>

HighScoresPage::HighScoresPage(int hsEasy, int hsMedium, int hsHard, int hsInsane)
{
    ImageView *easy1 = ImageView::create().
            image("asset:///images/hsPage/easy.png");

    ImageView *easy2 = ImageView::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center).
            image("asset:///images/hsPage/end.png");

    Label *easy = Label::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center);

    Container *easyCC = Container::create().
            layout(DockLayout::create()).
            add(easy2).
            add(easy);

    Container *easyC = Container::create().
            layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
            horizontal(HorizontalAlignment::Center).
            add(easy1).
            add(easyCC);

    ImageView *medium1 = ImageView::create().
            image("asset:///images/hsPage/medium.png");

    ImageView *medium2 = ImageView::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center).
            image("asset:///images/hsPage/end.png");

    Label *medium = Label::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center);

    Container *mediumCC = Container::create().
            layout(DockLayout::create()).
            add(medium2).
            add(medium);

    Container *mediumC = Container::create().
            layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
            horizontal(HorizontalAlignment::Center).
            add(medium1).
            add(mediumCC);

    ImageView *hard1 = ImageView::create().
            image("asset:///images/hsPage/hard.png");

    ImageView *hard2 = ImageView::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center).
            image("asset:///images/hsPage/end.png");

    Label *hard = Label::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center);

    Container *hardCC = Container::create().
            layout(DockLayout::create()).
            add(hard2).
            add(hard);

    Container *hardC = Container::create().
            layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
            horizontal(HorizontalAlignment::Center).
            add(hard1).
            add(hardCC);

    ImageView *insane1 = ImageView::create().
            image("asset:///images/hsPage/insane.png");

    ImageView *insane2 = ImageView::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center).
            image("asset:///images/hsPage/end.png");

    Label *insane = Label::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center);

    Container *insaneCC = Container::create().
            layout(DockLayout::create()).
            add(insane2).
            add(insane);

    Container *insaneC = Container::create().
            layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
            horizontal(HorizontalAlignment::Center).
            add(insane1).
            add(insaneCC);

    Button *shareHighScores = Button::create().
            horizontal(HorizontalAlignment::Center).
            text(".                  Share to BBM                  .").
            connect(SIGNAL(clicked()), this, SIGNAL(shareAllHighScores()));

    Container *contentC = Container::create().
            vertical(VerticalAlignment::Center).
            horizontal(HorizontalAlignment::Center).
            add(easyC).
            add(mediumC).
            add(hardC).
            add(insaneC).
            add(shareHighScores);

    Container *rootC = Container::create().
            layout(DockLayout::create()).
            add(contentC);

    ActionItem *close = ActionItem::create().
            title("Close").
            connect(SIGNAL(triggered()), this, SIGNAL(close()));

    ActionItem *review = ActionItem::create().
            image("asset:///images/icons/ic_review.png").
            title("Review").
            connect(SIGNAL(triggered()), this, SLOT(onReviewClicked()));

    TitleBar *tBar = TitleBar::create().
            title("High scores").
            dismissAction(close).
            acceptAction(review);

    this->setContent(rootC);
    this->setTitleBar(tBar);

    if(hsEasy==9999)
    {
        easy->setText("- : -");
    }
    else
    {
        QString spacer = hsEasy%60<10?"0":"";
        easy->setText(QString::number(hsEasy/60, 10) + ":" + spacer + QString::number(hsEasy%60, 10));
    }

    if(hsMedium==9999)
    {
        medium->setText("- : -");
    }
    else
    {
        QString spacer = hsMedium%60<10?"0":"";
        medium->setText(QString::number(hsMedium/60, 10) + ":" + spacer + QString::number(hsMedium%60, 10));
    }

    if(hsHard==9999)
    {
        hard->setText("- : -");
    }
    else
    {
        QString spacer = hsHard%60<10?"0":"";
        hard->setText(QString::number(hsHard/60, 10) + ":" + spacer + QString::number(hsHard%60, 10));
    }

    if(hsInsane==9999)
    {
        insane->setText("- : -");
    }
    else
    {
        QString spacer = hsInsane%60<10?"0":"";
        insane->setText(QString::number(hsInsane/60, 10) + ":" + spacer + QString::number(hsInsane%60, 10));
    }
}

void HighScoresPage::onReviewClicked()
{
    emit invokeTargetWithUri("sys.appworld", "appworld://content/35618894");
}
