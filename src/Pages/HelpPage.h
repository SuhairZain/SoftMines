/*
 * HelpPage.h
 *
 *  Created on: Nov 10, 2014
 *      Author: SuhairZain
 */

#ifndef HELPPAGE_H_
#define HELPPAGE_H_

#include <bb/cascades/ActionItem>
#include <bb/cascades/ImageView>
#include <bb/cascades/Label>
#include <bb/cascades/Page>
#include <bb/cascades/ScrollView>

using namespace bb::cascades;

class HelpPage: public Page
{
Q_OBJECT
signals:
    void close();
private slots:
    void nextClicked();
    //void onTouch(bb::cascades::TouchEvent*);
    void prevClicked();

private:
    int pageIndex, maxIndex;
    int startX;

    ActionItem *next, *prev;
    ImageView *helpImage;
    Label *helpLabel;
    QList<QString> imageNames;
    QList<QString> helpText;
    ScrollView *rootView;

public:
    HelpPage();
};

#endif /* HELPPAGE_H_ */
