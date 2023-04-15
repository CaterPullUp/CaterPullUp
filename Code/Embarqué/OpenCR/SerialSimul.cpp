/***
 * @author @trudelle200902
 * @file SerialSimul.cpp
 * @date 22 mars 2023
***/

#ifndef ARDUINO_OpenCR
#include "SerialSimul.h"

/**
 * @brief Creer un nouveau port serial simuler. determine le nom du fichier log selonla date et heure
 * 
 * @param name nom pour differencier les messages des different port serie
 */
SerialSimul::SerialSimul(std::string name){
    int hours, minutes, seconds, day, month, year;
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);

    sprintf(file_name, "test_%s_%02d-%02d-%d_%02d:%02d:%02d.log", name.c_str(), local->tm_mday, local->tm_mon+1, local->tm_year+1900, local->tm_hour, local->tm_min, local->tm_sec);
}

/**
 * @brief print un string dans le fichier log associer et dans la console
 * 
 * @param str valeur a print
 */
void SerialSimul::print(std::string str){
    const int length = str.length();
    char char_array[length + 1];
    strcpy(char_array, str.c_str());
    printf("%s",char_array);
    FILE* fptr = fopen(file_name, "a");
    fprintf(fptr, "%s",char_array);
    fclose(fptr);
}

/**
 * @brief print un string dans le fichier log associer et dans la console et change de ligne
 * 
 * @param str valeur a print
 */
void SerialSimul::println(std::string str){
    const int length = str.length();
    char char_array[length + 1];
    strcpy(char_array, str.c_str());
    printf("%s\n",char_array);
    FILE* fptr = fopen(file_name, "a");
    fprintf(fptr, "%s\n",char_array);
    fclose(fptr);
}

/**
 * @brief print un float dans le fichier log associer et dans la console
 * 
 * @param val valeur a print
 */
void SerialSimul::print(float val){
    printf("%f",val);
    FILE* fptr = fopen(file_name, "a");
    fprintf(fptr, "%f",val);
    fclose(fptr);
}

/**
 * @brief print un float dans le fichier log associer et dans la console et ajoute un \n a la fin
 * 
 * @param val valeur a print
 */
void SerialSimul::println(float val){
    printf("%f\n",val);
    FILE* fptr = fopen(file_name, "a");
    fprintf(fptr, "%f\n",val);
    fclose(fptr);
}

/**
 * @brief print un int dans le fichier log associer et dans la console
 * 
 * @param val valeur a print
 */
void SerialSimul::print(int val){
    printf("%d",val);
    FILE* fptr = fopen(file_name, "a");
    fprintf(fptr, "%d",val);
    fclose(fptr);
}

/**
 * @brief print un int dans le fichier log associer et dans la console et ajoute un \n a la fin
 * 
 * @param val valeur a print
 */
void SerialSimul::println(int val){
    printf("%d\n",val);
    FILE* fptr = fopen(file_name, "a");
    fprintf(fptr, "%d\n",val);
    fclose(fptr);
}

void SerialSimul::print(int val, int mode){}
void SerialSimul::println(int val, int mode){}
void SerialSimul::begin(int baud_rate){}
bool SerialSimul::availableForWrite(){return true;}
int SerialSimul::available(){return 0;}
void SerialSimul::readBytes(uint8_t* buff, int nb_byte){}
void SerialSimul::write(int i){}

SerialSimul Serial("debug");
SerialSimul Serial1("uart");
SerialSimul Serial3("dxl");

#endif