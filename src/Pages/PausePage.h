/*
 * PausePage.h
 *
 *  Created on: Nov 10, 2014
 *      Author: SuhairZain
 */

#ifndef PAUSEPAGE_H_
#define PAUSEPAGE_H_

#include <bb/cascades/Page>

using namespace bb::cascades;

class PausePage: public Page
{
Q_OBJECT
signals:
    void close();
public:
    PausePage(int, int, int);
};

#endif /* PAUSEPAGE_H_ */
