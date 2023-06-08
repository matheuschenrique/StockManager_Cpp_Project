#ifndef CURRENT_TIME_H
#define CURRENT_TIME_H

#include <ctime>

constexpr int YEAR_IN_DAYS = 365;

void insert_date(std::tm *destiny);
struct tm *get_current_time();


#endif