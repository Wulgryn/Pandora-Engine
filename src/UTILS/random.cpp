#include "random.hpp"
#include <stdlib.h>

using namespace utils;

Random::Random()
{
    
}

int random::getInt(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

float random::getFloat(float min, float max)
{
    return (float)rand() / RAND_MAX * (max - min) + min;
}

double random::getDouble(double min, double max)
{
    return (double)rand() / RAND_MAX * (max - min) + min;
}

byte random::getByte(byte min, byte max)
{
    return (byte)rand() % (max - min + 1) + min;
}