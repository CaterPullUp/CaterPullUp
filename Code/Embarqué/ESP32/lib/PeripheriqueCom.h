/***
 * @author @MarieClaude1234
 * @file PeripheriqueCom.h
 * @date 29 janvier 2023
***/

#ifndef PERIPHERIQUECOM_H
#define PERIPHERIQUECOM_H


class PeripheriqueCom 
{
    private:
        unsigned int baudrate;

    public:
        PeripheriqueCom();
        virtual ~PeripheriqueCom() = 0;

        virtual void envoyerOctet(char octet) = 0;
        virtual void envoyerBit(bool bit) = 0;
        virtual char recevoirOctet() = 0;
        virtual bool recevoirBit() = 0;
        virtual void envoyerStart() = 0;
        virtual void envoyerStop() = 0;
        virtual void envoyerAck() = 0;

        void setBaudRate(unsigned int _baudrate){baudrate = _baudrate;};
        unsigned int getBaudrate(){return baudrate;};
};


#endif