/*
 * SuccessPage.cpp
 *
 *  Created on: Nov 10, 2014
 *      Author: SuhairZain
 */

#include <src/Pages/SuccessPage.h>

#include <bb/cascades/ActionItem>
#include <bb/cascades/Container>
#include <bb/cascades/DockLayout>
#include <bb/cascades/ImageView>
#include <bb/cascades/TitleBar>

SuccessPage::SuccessPage()
{
    ImageView *rootImage = ImageView::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center).
            image("asset:///images/resultsPage/success.jpg");

    Container *rootC = Container::create().
            layout(DockLayout::create()).
            add(rootImage);

    ActionItem *close = ActionItem::create().
            title("Close").
            connect(SIGNAL(triggered()), this, SIGNAL(close()));

    ActionItem *review = ActionItem::create().
            image("asset:///images/icons/ic_review.png").
            title("Review").
            connect(SIGNAL(triggered()), this, SLOT(onReviewClicked()));

    TitleBar *tBar = TitleBar::create().
            title("You Won!").
            dismissAction(close).
            acceptAction(review);

    this->setContent(rootC);
    this->setTitleBar(tBar);
    //this->addAction(review, ActionBarPlacement::OnBar);
}

void SuccessPage::onReviewClicked()
{
    emit invokeTargetWithUri("sys.appworld", "appworld://content/35618894");
}
