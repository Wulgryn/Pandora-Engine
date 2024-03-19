#include "Image.hpp"

Image::Image(byte* data, int data_length, Size size)
{
    this->data = data;
    this->data_length = data_length;
    this->size = size;
}

unsigned char* Image::GetData()
{
    return data;
}

int Image::GetDataLength()
{
    return data_length;
}

Size Image::GetSize()
{
    return size;
}