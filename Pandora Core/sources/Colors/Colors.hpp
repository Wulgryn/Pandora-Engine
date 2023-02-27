#pragma once
using byte = unsigned char;
namespace Colors
{
    //A class to store RGBA values.
    class RGBA
    {
        public:
        //Value from 0 to 255.
        byte red;
        //Value from 0 to 255.
        byte green;
        //Value from 0 to 255.
        byte blue;
        //Value from 0.0 to 1.0 represents the percentage. 1.0 equals to 100%.
        double alpha;

        RGBA();
        /**
         * @param red value from 0 to 255.
         * @param green value from 0 to 255.
         * @param blue value from 0 to 255.
        */
        RGBA(byte red, byte green, byte blue);
        /**
         * @param red value from 0 to 255.
         * @param green value from 0 to 255.
         * @param blue value from 0 to 255.
         * @param alpha value from 0.0 to 1.0 represents the percentage. 1.0 equals to 100%.
        */
        RGBA(byte red, byte green, byte blue, double alpha);

        //Returns this class.
        RGBA GetRGBA();
    };
    //A class to store RGB values.
    class RGB
    {
        public:
        //Value from 0 to 255.
        byte red;
        //Value from 0 to 255.
        byte green;
        //Value from 0 to 255.
        byte blue;

        RGB();
        /**
         * @param red value from 0 to 255.
         * @param green value from 0 to 255.
         * @param blue value from 0 to 255.
        */
        RGB(byte red, byte green, byte blue);

        //Returns this class.
        RGB GetRGB();
        //Returns a new *RGBA* class.
        RGBA GetRGBA();
    };
};