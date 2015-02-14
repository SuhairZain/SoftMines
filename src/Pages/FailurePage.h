/*
 * FailurePage.h
 *
 *  Created on: Nov 10, 2014
 *      Author: SuhairZain
 */

#ifndef FAILUREPAGE_H_
#define FAILUREPAGE_H_

#include <bb/cascades/Page>

using namespace bb::cascades;

class FailurePage: public Page
{
Q_OBJECT
signals:
    void close();
public:
    FailurePage();
};

#endif /* FAILUREPAGE_H_ */
