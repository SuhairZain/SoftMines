/*
 * Square.h
 *
 *  Created on: Nov 9, 2014
 *      Author: SuhairZain
 */

#ifndef SQUARE_H_
#define SQUARE_H_

#include <bb/cascades/ImageButton>

using namespace bb::cascades;

class Mine: public ImageButton
{
Q_OBJECT
signals:
    void mineDoubleTapped(int, int);
    void mineFlagged(int, int);
    void mineTapped(int, int);

public slots:
    void onDoubleTapped();
    void onLongPressed();
    void onTapped();

public:
    Mine(int, int);

    //void setFlagged();
    //void disableAndSetImage(int);
    //void setDisabledOnSuccess();

private:
    int posI, posJ;
};

#endif /* SQUARE_H_ */
