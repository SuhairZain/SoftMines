/*
 * FailurePage.cpp
 *
 *  Created on: Nov 10, 2014
 *      Author: SuhairZain
 */

#include <src/Pages/FailurePage.h>

#include <bb/cascades/ActionItem>
#include <bb/cascades/Container>
#include <bb/cascades/DockLayout>
#include <bb/cascades/ImageView>
#include <bb/cascades/TitleBar>

FailurePage::FailurePage()
{
    ImageView *rootImage = ImageView::create().
            horizontal(HorizontalAlignment::Center).
            vertical(VerticalAlignment::Center).
            image("asset:///images/resultsPage/failure.jpg");

    Container *rootC = Container::create().
            layout(DockLayout::create()).
            add(rootImage);

    ActionItem *close = ActionItem::create().
            title("Close").
            connect(SIGNAL(triggered()), this, SIGNAL(close()));

    TitleBar *tBar = TitleBar::create().
            title("Game Over!").
            dismissAction(close);

    this->setContent(rootC);
    this->setTitleBar(tBar);
}

