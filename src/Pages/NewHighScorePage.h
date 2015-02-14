/*
 * NewHighScorePage.h
 *
 *  Created on: Nov 10, 2014
 *      Author: SuhairZain
 */

#ifndef NEWHIGHSCOREPAGE_H_
#define NEWHIGHSCOREPAGE_H_

#include <bb/cascades/Page>

using namespace bb::cascades;

class NewHighScorePage: public Page
{
Q_OBJECT
signals:
    void close();
    void invokeTargetWithUri(QString, QString);
    void shareNewHighScore();

private slots:
    void onReviewClicked();
    void onShareClicked();

public:
    NewHighScorePage(int, int);
};

#endif /* NEWHIGHSCOREPAGE_H_ */
