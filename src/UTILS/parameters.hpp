#pragma once

#include "DLL/dll.hpp"
namespace utils
{
        typedef struct Size
        {
            /**
             * @brief Represents the size of an object.
             * @note The width and height coordinates are default 0.
             */
            Size() : Width(0), Height(0), Length(0) {}

            /**
             * @brief Represents the size of an object.dinates.
             * @param width The width of the Size object.
             * @param height The height of the Size object.
             */
            Size(double width, double height, double length = 0) : Width(width), Height(height), Length(length) {}

            /**
             * Calculates the rate of a position relative to the window size.
             * 
             * @param windowSize The size of the window.
             * @return The rate of the position relative to the window size.
             */
            Size toWindowRate(struct Size windowSize)
            {
                return Size(Width / windowSize.Width,
                        Height / windowSize.Height);
            }
            double Width;
            double Height;
            double Length;
        } Size;

        
        //typedef struct Position Position;
        typedef struct Position
        {
            /**
             * @brief Constructor with coordinates x, y, y.
             * @note The x, y and z coordinates are default 0.
             */
            Position() : x(0), y(0), z(0) {}
  
            /**
             * @brief Constructor with coordinates x, y, y.
             * @param x The x of the Position object.
             * @param y The y of the Position object.
             * @param z The z of the Position object(default 0).
             */
            Position(double x, double y, double z = 0)
            {
                this->x = x;
                this->y = y;
                this->z = z;
            }

            /**
             * Calculates the rate of a position relative to the window size.
             * 
             * @param windowSize The size of the window.
             * @return The rate of the position relative to the window size.
             */
            Position toWindowRate(struct Size windowSize)
            {
                return Position((x - windowSize.Width / 2) / (windowSize.Width / 2),
                                (y - windowSize.Height / 2) / (windowSize.Height / 2));
            }

            /**
             * Calculates the real position of a position relative to the window size.
             * 
             * @param windowSize The size of the window.
             * @return The real position of the position relative to the window size.
             */
            Position getRealPosition(struct Size windowSize)
            {
                return Position(x, windowSize.Height - y);
            }

            //Position getCoordinatePosition(struct Size windowSize)
            //{
            //    return Position(x, windowSize.Height - y);
            //}

            double x;
            double y;
            double z;
        } Position;

        typedef struct Rotation
        {
            /**
             * @brief Constructor with rotation angles x, y, y.
             * @note The x, y and z coordinates are default 0.
             */
            Rotation() : x(0), y(0), z(0) {}

            /**
             * @brief Constructor with rotation angles x, y, y.
             * @param x The x of the Rotation object.
             * @param y The y of the Rotation object.
             * @param z The z of the Rotation object(default 0).
             */
            Rotation(double x, double y, double z = 0)
            {
                this->x = x;
                this->y = y;
                this->z = z;
            }

            double x;
            double y;
            double z;
        } Rotation;


    typedef unsigned char byte;

    typedef struct Color
    {
        /**
         * @brief Constructor with red, green, blue and alpha.
         * @note The red, green, blue are default 0. Alpha is default 155.
         */
        Color() : red(0), green(0), blue(0), alpha(255) {}
        /**
         * @brief Constructor with red, green, blue and alpha.
         * @param red The red of the Color object.
         * @param green The green of the Color object.
         * @param blue The blue of the Color object.
         * @param alpha The alpha of the Color object.
         */
        Color(byte red, byte green, byte blue, byte alpha = 255) : red(red), green(green), blue(blue), alpha(alpha) {}
        /**
         * @brief Constructor with red, green, blue and alpha.
         * @param red The red of the Color object (0 - 1.0f).
         * @param green The green of the Color object (0 - 1.0f).
         * @param blue The blue of the Color object (0 - 1.0f).
         * @param alpha The alpha of the Color object (0 - 1.0f).
         */
        Color(float red, float green, float blue, float alpha = 1.0) 
        {
            this->red = (byte)(red * 255);
            this->green = (byte)(green * 255);
            this->blue = (byte)(blue * 255);
            this->alpha = (byte)(alpha * 255);
        }

        /**
         * @brief Get the red of the Color object.
         * @return The red of the Color object.
         */
        byte getRed() { return red; }

        /**
         * @brief Get the green of the Color object.
         * @return The green of the Color object.
         */
        byte getGreen() { return green; }

        /**
         * @brief Get the blue of the Color object.
         * @return The blue of the Color object.
         */
        byte getBlue() { return blue; }

        /**
         * @brief Get the alpha of the Color object.
         * @return The alpha of the Color object.
         */
        byte getAlpha() { return alpha; }

        /**
         * @brief Returns the red component as a normalized float value.
         * 
         * @return The red component divided by 255.0f.
         */
        float getRedF() { return red / 255.0f; }

        /**
         * @brief Returns the green component as a normalized float value.
         * 
         * @return The green component divided by 255.0f.
         */
        float getGreenF() { return green / 255.0f; }

        /**
         * @brief Returns the blue component as a normalized float value.
         * 
         * @return The blue component divided by 255.0f.
         */
        float getBlueF() { return blue / 255.0f; }

        /**
         * @brief Returns the alpha component as a normalized float value.
         * 
         * @return The alpha component divided by 255.0f.
         */
        float getAlphaF() { return alpha / 255.0f; }

        /**
         * @brief Set the red of the Color object.
         * @param red The red of the Color object.
         * @return The Color object.
         */
        Color setRed(int red)
        {
            this->red = red;
            return *this;
        }

        /**
         * @brief Set the green of the Color object.
         * @param green The green of the Color object.
         * @return The Color object.
         */
        Color setGreen(int green)
        {
            this->green = green;
            return *this;
        }

        /**
         * @brief Set the blue of the Color object.
         * @param blue The blue of the Color object.
         * @return The Color object.
         */
        Color setBlue(int blue)
        {
            this->blue = blue;
            return *this;
        }

        /**
         * @brief Set the alpha of the Color object.
         * @param alpha The alpha of the Color object.
         * @return The Color object.
         */
        Color setAlpha(int alpha)
        {
            this->alpha = alpha;
            return *this;
        }

        byte red, green, blue, alpha;
    } Color;
}