
#ifndef LOG_SERVICE_H
#define LOG_SERVICE_H

#include <iostream>
#include <sstream>
#include <iomanip>

using std::cout;
using std::string;
using std::stringstream;
using std::ofstream;
using std::to_string;
using std::hex;
using std::endl;
using std::setw;
using std::setfill;

string addrToStr(uint32_t addr);
string regToStr(uint8_t num);
string immToStr(uint32_t imm);
string tagToStr(uint8_t tag);

#endif  // LOG_SERVICE_H
