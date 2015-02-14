/*
 * HighScoresPage.h
 *
 *  Created on: Nov 10, 2014
 *      Author: SuhairZain
 */

#ifndef HIGHSCORESPAGE_H_
#define HIGHSCORESPAGE_H_

#include <bb/cascades/Page>

using namespace bb::cascades;

class HighScoresPage: public Page
{
Q_OBJECT
signals:
    void close();
    void invokeTargetWithUri(QString, QString);
    void shareAllHighScores();

private slots:
    void onReviewClicked();

public:
    HighScoresPage(int, int, int, int);
};

#endif /* HIGHSCORESPAGE_H_ */
