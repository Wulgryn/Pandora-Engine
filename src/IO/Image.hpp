#include "../Core/Parameters.hpp"


class Image
{
    typedef unsigned char byte;
    byte* data;
    int data_length;
    Size size;
public:
    Image(byte* data, int data_length, Size size);
    byte* GetData();
    int GetDataLength();
    Size GetSize();
};