/*
 * NewHighScorePage.cpp
 *
 *  Created on: Nov 10, 2014
 *      Author: SuhairZain
 */

#include <src/Pages/NewHighScorePage.h>

#include <bb/cascades/ActionItem>
#include <bb/cascades/Button>
#include <bb/cascades/Container>
#include <bb/cascades/DockLayout>
#include <bb/cascades/ImageView>
#include <bb/cascades/Label>
#include <bb/cascades/TitleBar>

NewHighScorePage::NewHighScorePage(int level, int hs)
{
    ImageView *rootImage = ImageView::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center).
            image("asset:///images/resultsPage/newHighScore.jpg").
            opacity(0.3f);

    Button *shareButton = Button::create().
            horizontal(HorizontalAlignment::Center).
            text("Share to BBM").
            connect(SIGNAL(clicked()), this, SLOT(onShareClicked()));

    Button *reviewButton = Button::create().
            horizontal(HorizontalAlignment::Center).
            text("Leave a review").
            connect(SIGNAL(clicked()), this, SLOT(onReviewClicked()));

    QString levelText;
    switch(level)
    {
        case 0:
            levelText = "Easy level";
            break;
        case 1:
            levelText = "Medium level";
            break;
        case 2:
            levelText = "Hard level";
            break;
        case 3:
            levelText = "Insane level";
            break;
    }
    QString spacer = hs%60<10?"0":"";
    Label *hsLabel = Label::create().
            text(QString::number(hs/60, 10) + ":" + spacer + QString::number(hs%60, 10) + " in " + levelText);
    hsLabel->textStyle()->setFontSize(FontSize::XXLarge);
    hsLabel->textStyle()->setFontWeight(FontWeight::W400);

    Container *contentC = Container::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center).
            add(hsLabel).
            add(shareButton).
            add(reviewButton);

    Container *rootC = Container::create().
            layout(DockLayout::create()).
            add(rootImage).
            add(contentC);

    ActionItem *close = ActionItem::create().
            title("Close").
            connect(SIGNAL(triggered()), this, SIGNAL(close()));

    ActionItem *review = ActionItem::create().
            image("asset:///images/icons/ic_review.png").
            title("Review").
            connect(SIGNAL(triggered()), this, SLOT(onReviewClicked()));

    TitleBar *tBar = TitleBar::create().
            title("Highscore!").
            dismissAction(close).
            acceptAction(review);

    this->setContent(rootC);
    this->setTitleBar(tBar);
}

void NewHighScorePage::onReviewClicked()
{
    emit invokeTargetWithUri("sys.appworld", "appworld://content/35618894");
}

void NewHighScorePage::onShareClicked()
{
    emit shareNewHighScore();
}
