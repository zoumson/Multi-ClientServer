#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include "Clock.h"

using namespace std;

string Clock::currentDateTime(){
        time_t     now = time(0);
        struct tm  tstruct;
        char       buf[15];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%X", &tstruct);

        return buf;
}

Clock::~Clock()
{
}

