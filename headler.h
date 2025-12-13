#ifndef UNTITLED2_HEADLER_H
#define UNTITLED2_HEADLER_H
#include <string>
#include <vector>
#include <windows.h>
std::string inputFromKeyboard();
std::vector<std::string> readFromFile();
std::string generateRandomString();
std::string inputHexFromKeyboard();
int inputNumberFromKeyboard();

void string44(const std::string& str);
void string44_2(const std::vector<std::string>& lines);
void Str16(const std::string& str);
void Str16_2(const std::vector<std::string>& lines);
void Str25(int number);
void Str40(const std::string& str);
void Str40_2(const std::vector<std::string>& lines);
std::string hexCharToBinary(char hexChar);
bool isValidHex(const std::string& hexStr);
void hexToBinary(const std::string& hexStr);
void generatePassword();
void checkMathHomework();
#endif
