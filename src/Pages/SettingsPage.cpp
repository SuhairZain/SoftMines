/*
 * SettingsPage.cpp
 *
 *  Created on: Nov 10, 2014
 *      Author: SuhairZain
 */

#include <src/Pages/SettingsPage.h>

#include <bb/cascades/ActionItem>
#include <bb/cascades/DockLayout>
#include <bb/cascades/RadioGroup>
//#include <bb/cascades/ScrollView>
#include <bb/cascades/StackLayout>
#include <bb/cascades/StackLayoutProperties>
#include <bb/cascades/TitleBar>
#include <bb/cascades/ToggleButton>

SettingsPage::SettingsPage(bool isActive, int sLevel, bool mEnabled/*, int iR, int iC, int iM*/)
{
    gameIsActive = isActive;
    initialLevel = finalLevel = sLevel;
    /*initialR = iR;
    initialC = iC;
    initialM = iM;*/

    loseGameWarning = Label::create().
            horizontal(HorizontalAlignment::Center).
            text("If you change the level now, you will lose the current game. "
                    "Else please change after completing this game.").
                    multiline(TRUE).
                    visible(FALSE);
    loseGameWarning->textStyle()->setFontSize(FontSize::Large);
    loseGameWarning->textStyle()->setFontWeight(FontWeight::W300);
    loseGameWarning->textStyle()->setColor(Color::Red);
    loseGameWarning->textStyle()->setTextAlign(TextAlign::Center);

    Label *musicLabel = Label::create().
            layoutProperties(StackLayoutProperties::create().spaceQuota(1)).
            text("Enable music");

    ToggleButton *musicEnabled = ToggleButton::create().
            connect(SIGNAL(checkedChanged(bool)), this, SIGNAL(musicEnabledChanged(bool))).
            checked(mEnabled);

    Container *musicC = Container::create().
            layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
            add(musicLabel).
            add(musicEnabled);

    Label *levelChooserLabel = Label::create().
            text("Choose a level:");
    levelChooserLabel->textStyle()->setColor(Color::Blue);
    levelChooserLabel->textStyle()->setFontSize(FontSize::XLarge);
    levelChooserLabel->textStyle()->setFontWeight(FontWeight::W400);

    RadioGroup *levelChooser = RadioGroup::create().
            add(Option::create().text("Easy").description("Rows: 10, Columns: 10, Mines: 10")).
            add(Option::create().text("Medium").description("Rows: 15, Columns: 15, Mines: 36")).
            add(Option::create().text("Hard").description("Rows: 15, Columns: 30, Mines: 90")).
            add(Option::create().text("Insane").description("Rows: 15, Columns: 25, Mines: 120")).
            //add(Option::create().text("Custom")).
            dividers(TRUE);

    /*rowStepper = new Stepper("Rows", 5, 30, iR);
    connect(rowStepper, SIGNAL(valueChanged(int)), this, SLOT(onValuesChanged()));
    rowStepper->setHorizontalAlignment(HorizontalAlignment::Center);
    Container *rowStepperC = Container::create().
            layoutProperties(StackLayoutProperties::create().spaceQuota(1)).
            add(rowStepper);

    columnStepper = new Stepper("Columns", 5, 30, iC);
    connect(columnStepper, SIGNAL(valueChanged(int)), this, SLOT(onValuesChanged()));
    columnStepper->setHorizontalAlignment(HorizontalAlignment::Center);
    Container *columnStepperC = Container::create().
            layoutProperties(StackLayoutProperties::create().spaceQuota(1)).
            add(columnStepper);

    mineStepper = new Stepper("Mines", 5, 150, iM);
    mineStepper->setHorizontalAlignment(HorizontalAlignment::Center);
    Container *mineStepperC = Container::create().
            layoutProperties(StackLayoutProperties::create().spaceQuota(1)).
            add(mineStepper);

    customC = Container::create().
            visible(sLevel==4).
            layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
            add(rowStepperC).
            add(columnStepperC).
            add(mineStepperC);*/

    Container *contentC = Container::create().
            vertical(VerticalAlignment::Top).
            horizontal(HorizontalAlignment::Center).
            add(musicC).
            add(levelChooserLabel).
            add(levelChooser).
            //add(customC).
            add(loseGameWarning);

    Container *rootC = Container::create().
            layout(DockLayout::create()).
            add(contentC);

    /*ScrollView *rootScroll = ScrollView::create().
            content(rootC);*/

    ActionItem *close = ActionItem::create().
            title("Close").
            connect(SIGNAL(triggered()), this, SLOT(onCloseClicked()));

    TitleBar *tBar = TitleBar::create().
            title("Settings").
            dismissAction(close);

    this->setContent(rootC);
    this->setTitleBar(tBar);

    connect(levelChooser, SIGNAL(selectedIndexChanged(int)), this, SLOT(onSelectedIndexChanged(int)));
    levelChooser->setSelectedIndex(sLevel);
}

void SettingsPage::onCloseClicked()
{
    emit close(finalLevel);
}

void SettingsPage::onSelectedIndexChanged(int index)
{
    finalLevel = index;

    if(gameIsActive)
        loseGameWarning->setVisible(initialLevel!=finalLevel);
    else
        loseGameWarning->setVisible(FALSE);
    /*if(index==4)
    {
        customC->setVisible(TRUE);

        if(gameIsActive)
        {
            if(rowStepper->value()!=initialR || columnStepper->value()!=initialC ||
                    mineStepper->value()!=initialM || initialLevel!=4)
            {
                loseGameWarning->setVisible(TRUE);
            }
            else
                loseGameWarning->setVisible(FALSE);
        }
    }
    else
    {
        if(gameIsActive)
            loseGameWarning->setVisible(index!=initialLevel);
        else
            loseGameWarning->setVisible(FALSE);

        customC->setVisible(FALSE);
    }*/
}

/*void SettingsPage::onValuesChanged()
{
    if(gameIsActive)
    {
        if(rowStepper->value()!=initialR || columnStepper->value()!=initialC || mineStepper->value()!=initialM)
        {
            loseGameWarning->setVisible(TRUE);
        }
        else
            loseGameWarning->setVisible(FALSE);
    }

    mineStepper->setMaxValue(rowStepper->value()*columnStepper->value() - 20);
}*/

/*
void SettingsPage::onValueColumnsChanged()
{
    if(gameIsActive &&
            (rowStepper->value()!=initialR || columnStepper->value()!=initialC || mineStepper->value()!=initialM))
    {
        loseGameWarning->setVisible(TRUE);
    }
    else
        loseGameWarning->setVisible(FALSE);

    if(mineStepper->value() > rowStepper->value()*columnStepper->value() - 20)
    {
        mineStepper->setMaxValue(rowStepper->value()*columnStepper->value() - 20);
    }
}

void SettingsPage::onValueMinesChanged()
{

}

void SettingsPage::onValueRowsChanged()
{
    if(gameIsActive &&
            (rowStepper->value()!=initialR || columnStepper->value()!=initialC || mineStepper->value()!=initialM))
    {
        loseGameWarning->setVisible(TRUE);
    }
    else
        loseGameWarning->setVisible(FALSE);

    if(mineStepper->value() > rowStepper->value()*columnStepper->value() - 20)
    {
        mineStepper->setMaxValue(rowStepper->value()*columnStepper->value() - 20);
    }
}
 */
