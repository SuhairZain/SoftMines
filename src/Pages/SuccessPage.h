/*
 * SuccessPage.h
 *
 *  Created on: Nov 10, 2014
 *      Author: SuhairZain
 */

#ifndef SUCCESSPAGE_H_
#define SUCCESSPAGE_H_

#include <bb/cascades/Page>

using namespace bb::cascades;

class SuccessPage: public Page
{
Q_OBJECT
signals:
    void close();
    void invokeTargetWithUri(QString, QString);

private slots:
    void onReviewClicked();

public:
    SuccessPage();
};

#endif /* SUCCESSPAGE_H_ */
