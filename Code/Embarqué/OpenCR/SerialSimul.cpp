/***
 * @author @trudelle200902
 * @file Dynamixel2ArduinoSimul.cpp
 * @date 22 mars 2023
***/

#include "SerialSimul.h"

void SerialSimul::begin(int baud_rate){
    //auto end = std::chrono::system_clock::now();
    //std::time_t time = std::chrono::system_clock::to_time_t(end);
    int hours, minutes, seconds, day, month, year;
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);

    char name[256];
    sprintf(name, "test_%02d-%02d-%d_%02d:%02d:%02d.log", local->tm_mday, local->tm_mon+1, local->tm_year+1900, local->tm_hour, local->tm_min, local->tm_sec);
    // = "test_" + std::ctime(&time) + ".log";
    fptr = fopen(name, "w");
}

void SerialSimul::print(std::string str){
    const int length = str.length();
    char char_array[length + 1];
    strcpy(char_array, str.c_str());
    printf("%s", char_array);
    fprintf(fptr, char_array);
}
void SerialSimul::println(std::string str){
    const int length = str.length();
    char char_array[length + 1];
    strcpy(char_array, str.c_str());
    printf("%s\n", char_array);
    fprintf(fptr, "%s\n", char_array);
}

void SerialSimul::print(float val){
    printf("%.2f", val);
    fprintf(fptr, "%.2f",val);
}
void SerialSimul::println(float val){
    printf("%.2f\n", val);
}

SerialSimul Serial;
SerialSimul Serial3;
