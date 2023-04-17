/***
 * @author @trudelle200902
 * @file SerialSimul.cpp
 * @date 22 mars 2023
***/
#ifndef ARDUINO_OpenCR
#include "SerialSimul.h"

SerialSimul::SerialSimul(std::string name){
    int hours, minutes, seconds, day, month, year;
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);

    sprintf(file_name, "test_%s_%02d-%02d-%d_%02d:%02d:%02d.log", name.c_str(), local->tm_mday, local->tm_mon+1, local->tm_year+1900, local->tm_hour, local->tm_min, local->tm_sec);
    // = "test_" + std::ctime(&time) + ".log";
    //fptr = fopen(file_name, "w");
}

SerialSimul::~SerialSimul(){
    //fclose(fptr);
}

void SerialSimul::begin(int baud_rate){
    //auto end = std::chrono::system_clock::now();
    //std::time_t time = std::chrono::system_clock::to_time_t(end);
    
}

void SerialSimul::print(std::string str){
    /*const int length = str.length();
    char char_array[length + 1];
    strcpy(char_array, str.c_str());
    printf("%s", char_array);
    fprintf(fptr, "%s", char_array);*/
    const int length = str.length();
    char char_array[length + 1];
    strcpy(char_array, str.c_str());
    printf("%s",char_array);
    FILE* fptr = fopen(file_name, "a");
    fprintf(fptr, "%s",char_array);
    fclose(fptr);
    //print_to_file("%s",char_array);
}

void SerialSimul::println(std::string str){
    /*const int length = str.length();
    char char_array[length + 1];
    strcpy(char_array, str.c_str());
    printf("%s\n", char_array);
    fprintf(fptr, "%s\n", char_array);*/
    const int length = str.length();
    char char_array[length + 1];
    strcpy(char_array, str.c_str());
    printf("%s\n",char_array);
    FILE* fptr = fopen(file_name, "a");
    fprintf(fptr, "%s\n",char_array);
    fclose(fptr);
    //print_to_file("%s\n",char_array);
}

void SerialSimul::print(float val){
    /*printf("%.2f", val);
    fprintf(fptr, "%.2f",val);*/
    printf("%f",val);
    FILE* fptr = fopen(file_name, "a");
    fprintf(fptr, "%f",val);
    fclose(fptr);
    //print_to_file("%.2f", val);
}
void SerialSimul::println(float val){
    printf("%f\n",val);
    FILE* fptr = fopen(file_name, "a");
    fprintf(fptr, "%f\n",val);
    fclose(fptr);
    //print_to_file("%.2f\n", val);
}

void SerialSimul::println(int val){
    printf("%d\n",val);
    FILE* fptr = fopen(file_name, "a");
    fprintf(fptr, "%d\n",val);
    fclose(fptr);
    //print_to_file("%d\n", val);
}

void SerialSimul::print(int val){
    printf("%d",val);
    FILE* fptr = fopen(file_name, "a");
    fprintf(fptr, "%d",val);
    fclose(fptr);
    //print_to_file("%d", val);
}

void SerialSimul::print_to_file(const char* fmt, ...){
    FILE* fptr = fopen(file_name, "a");
    va_list arg;
    va_start(arg,fmt);
    vprintf(fmt, arg);
    vfprintf(fptr, fmt, arg);
    va_end(arg);
    fclose(fptr);
}

void SerialSimul::print(int val, int mode){}
void SerialSimul::println(int val, int mode){}
bool SerialSimul::availableForWrite(){return true;}
int SerialSimul::available(){return 0;}
void SerialSimul::readBytes(uint8_t* buff, int nb_byte){}
void SerialSimul::write(int i){}

SerialSimul Serial("debug");
SerialSimul Serial1("uart");
SerialSimul Serial3("dxl");
#endif
