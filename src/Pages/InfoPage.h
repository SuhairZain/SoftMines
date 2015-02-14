/*
 * InfoPage.h
 *
 *  Created on: Nov 10, 2014
 *      Author: SuhairZain
 */

#ifndef INFOPAGE_H_
#define INFOPAGE_H_

#include <bb/cascades/Page>

using namespace bb::cascades;

class InfoPage: public Page
{
Q_OBJECT
signals:
    void close();
    void invokeTargetWithUri(QString, QString);
private slots:
    void goToGameOnFB();
    void goToGamePage();
    void goToPP();
    void goToRubus();
    void goToSV();
public:
    InfoPage();
};

#endif /* INFOPAGE_H_ */
