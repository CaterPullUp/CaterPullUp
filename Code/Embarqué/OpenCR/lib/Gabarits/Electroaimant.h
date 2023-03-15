/***
 * @author @etiger314
 * @file Electroaimant.h
 * @date 17 janvier 2023
***/

#ifndef ELECTROAIMANT_H
#define ELECTROAIMANT_H

class Electroaimant
{
private:

    bool etat;
    int pin;

public:

    Electroaimant(int pin_);

    virtual void activer()=0;
    virtual void desactiver()=0;
    virtual bool getEtat()=0;
    virtual int getPin()=0;
};

#endif