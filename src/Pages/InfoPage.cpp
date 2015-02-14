/*
 * InfoPage.cpp
 *
 *  Created on: Nov 10, 2014
 *      Author: SuhairZain
 */

#include <src/Pages/InfoPage.h>

#include <bb/cascades/ActionItem>
#include <bb/cascades/Container>
#include <bb/cascades/DockLayout>
#include <bb/cascades/ImageButton>
#include <bb/cascades/ImageView>
#include <bb/cascades/Label>
#include <bb/cascades/ScrollView>
#include <bb/cascades/StackLayout>
#include <bb/cascades/TapHandler>
#include <bb/cascades/TextStyle>
#include <bb/cascades/TitleBar>

InfoPage::InfoPage()
{
    ImageButton *infoLogo = ImageButton::create().
            horizontal(HorizontalAlignment::Center).
            defaultImage("asset:///images/logos/logo.png").
            pressedImage("asset:///images/logos/logoPressed.png").
            connect(SIGNAL(clicked()), this, SLOT(goToGameOnFB()));

    TextStyle textStyle;
    textStyle.setFontWeight(FontWeight::W300);
    textStyle.setFontSize(FontSize::XLarge);
    textStyle.setTextAlign(TextAlign::Center);

    Label *infoLabel = Label::create().multiline(TRUE).
            horizontal(HorizontalAlignment::Center).
            textStyle(textStyle).
            text("built by STAW\nwith help from\nRubus Labs\nand\nStartup Village, Kochi");

    textStyle.setFontSize(FontSize::Medium);
    textStyle.setColor(Color::Blue);

    Label *privacyPolicy = Label::create().
            vertical(VerticalAlignment::Bottom).
            horizontal(HorizontalAlignment::Center).
            textStyle(textStyle).
            text("View privacy policy").
            addGestureHandler(TapHandler::create().onTapped(this, SLOT(goToPP())));

    ImageButton *svLogo = ImageButton::create().
            defaultImage("asset:///images/logos/sv.png").
            pressedImage("asset:///images/logos/svPressed.png").
            connect(SIGNAL(clicked()), this, SLOT(goToSV()));

    ImageButton *rubusLogo = ImageButton::create().
            defaultImage("asset:///images/logos/rubus.png").
            pressedImage("asset:///images/logos/rubusPressed.png").
            connect(SIGNAL(clicked()), this, SLOT(goToRubus()));

    Container *svAndRubus = Container::create().
            layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
            horizontal(HorizontalAlignment::Center).
            add(svLogo).
            add(rubusLogo);

    Container *contentC = Container::create().
            vertical(VerticalAlignment::Center).
            horizontal(HorizontalAlignment::Center).
            add(infoLogo).
            add(infoLabel).
            add(svAndRubus).
            add(privacyPolicy);

    Container *rootC = Container::create().
            horizontal(HorizontalAlignment::Fill).
            vertical(VerticalAlignment::Fill).
            layout(DockLayout::create()).
            add(contentC);

    ScrollView *rootView = ScrollView::create().
            scrollMode(ScrollMode::Vertical).
            content(rootC);

    ActionItem *close = ActionItem::create().
            title("Close").
            connect(SIGNAL(triggered()), this, SIGNAL(close()));

    ActionItem *review = ActionItem::create().
            image("asset:///images/icons/ic_review.png").
            title("Review").
            connect(SIGNAL(triggered()), this, SLOT(goToGamePage()));

    TitleBar *tBar = TitleBar::create().
            title("Info").
            dismissAction(close).
            acceptAction(review);

    this->setContent(rootView);
    this->setTitleBar(tBar);
}

void InfoPage::goToGameOnFB()
{
    emit invokeTargetWithUri("sys.browser", "http://www.facebook.com/pages/Soft-Mines/622041597853338");
}

void InfoPage::goToGamePage()
{
    emit invokeTargetWithUri("sys.appworld", "appworld://content/35618894");
}

void InfoPage::goToPP()
{
    emit invokeTargetWithUri("sys.browser", "http://www.aassk.in/staw/privacypolicy.html");
}

void InfoPage::goToRubus()
{
    emit invokeTargetWithUri("sys.browser", "http://startupvillage.in/rubuslabs");
}

void InfoPage::goToSV()
{
    emit invokeTargetWithUri("sys.browser", "http://startupvillage.in");
}
