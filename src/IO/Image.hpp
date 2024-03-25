#include "../Core/Parameters.hpp"


class Image
{
    typedef unsigned char byte;
    byte* data;
    int data_length;
    ParametersApp::Size size;
public:
    Image(byte* data, int data_length, ParametersApp::Size size);
    byte* GetData();
    int GetDataLength();
    ParametersApp::Size GetSize();
};