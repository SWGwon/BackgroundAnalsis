#ifndef _functions_
#define _functions_

#include "hit.h"

//time sorting
bool tSort(Hit Hit1, Hit Hit2);

//time sorting smeared case
bool tSortSmear(Hit Hit1, Hit Hit2);

//a, b are vector
double GetAngle(float a[], float b[]);

//a, b are vector
double GetDistance(float a[], Hit hit);

#endif
