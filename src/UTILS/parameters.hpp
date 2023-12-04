#pragma once

#include "DLL/dll.hpp"
namespace utils
{
    namespace _2D_
    {
        typedef struct Location
        {
            /**
             * @brief Constructor with coordinates x, y.
             * @note The x and y coordinates are default 0.
             */
            Location() : dx(0), dy(0), ix(0), iy(0) {}
            /**
             * @brief Constructor with x and y of the Size object.
             * @param x The x of the Size object.
             * @param y The y of the Size object.
             */
            Location(int x, int y) : dx(x), dy(y), ix(x), iy(y) {}
            /**
             * @brief Constructor with x and y of the Size object.
             * @param x The x of the Size object.
             * @param y The y of the Size object.
             */
            Location(double x, double y) : dx(x), dy(y), ix((int)x), iy((int)y) {}

            /**
             * @brief Get the x of the Size object.
             * @return The x of the Size object.
             */
            double getDX() { return dx; }

            /**
             * @brief Get the y of the Size object.
             * @return The y of the Size object.
             */
            double getDY() { return dy; }

            /**
             * @brief Get the x of the Size object.
             * @return The x of the Size object.
             */
            int getIX() { return ix; }

            /**
             * @brief Get the y of the Size object.
             * @return The y of the Size object.
             */
            int getIY() { return iy; }

            /**
             * @brief Set the x of the Size object.
             * @param x The x of the Size object.
             * @return The location object.
             */
            Location setX(double x)
            {
                dx = x;
                ix = (int)x;
                return *this;
            }

            /**
             * @brief Set the y of the Size object.
             * @param y The y of the Size object.
             * @return The location object.
             */
            Location setY(double y)
            {
                dy = y;
                iy = (int)y;
                return *this;
            }

            /**
             * @brief Set the x of the Size object.
             * @param x The x of the Size object.
             * @return The location object.
             */
            Location setX(int x)
            {
                ix = x;
                dx = (double)x;
                return *this;
            }

            /**
             * @brief Set the y of the Size object.
             * @param y The y of the Size object.
             * @return The location object.
             */
            Location setY(int y)
            {
                iy = y;
                dy = (double)y;
                return *this;
            }

            /**
             * @brief Set the x and y of the Size object.
             * @param x The x of the Size object.
             * @param y The y of the Size object.
             * @return The location object.
             */
            Location set(double x, double y)
            {
                dx = x;
                dy = y;
                ix = (int)x;
                iy = (int)y;
                return *this;
            }

            /**
             * @brief Set the x and y of the Size object.
             * @param x The x of the Size object.
             * @param y The y of the Size object.
             * @return The location object.
             */
            Location set(int x, int y)
            {
                ix = x;
                iy = y;
                dx = (double)x;
                dy = (double)y;
                return *this;
            }

            /**
             * @brief Add x to the x of the Size object.
             * @param x The x of the Size object.
             * @return The location object.
             */
            Location addX(double x)
            {
                dx += x;
                ix = (int)dx;
                return *this;
            }

            /**
             * @brief Add y to the y of the Size object.
             * @param y The y of the Size object.
             * @return The location object.
             */
            Location addY(double y)
            {
                dy += y;
                iy = (int)dy;
                return *this;
            }

            /**
             * @brief Add x to the x of the Size object.
             * @param x The x of the Size object.
             * @return The location object.
             */
            Location addX(int x)
            {
                ix += x;
                dx = (double)ix;
                return *this;
            }

            /**
             * @brief Add y to the y of the Size object.
             * @param y The y of the Size object.
             * @return The location object.
             */
            Location addY(int y)
            {
                iy += y;
                dy = (double)iy;
                return *this;
            }

            /**
             * @brief Add x and y to the x and y of the Size object.
             * @param x The x of the Size object.
             * @param y The y of the Size object.
             * @return The location object.
             */
            Location add(double x, double y)
            {
                dx += x;
                dy += y;
                ix = (int)dx;
                iy = (int)dy;
                return *this;
            }

            /**
             * @brief Add x and y to the x and y of the Size object.
             * @param x The x of the Size object.
             * @param y The y of the Size object.
             * @return The location object.
             */
            Location add(int x, int y)
            {
                ix += x;
                iy += y;
                dx = (double)ix;
                dy = (double)iy;
                return *this;
            }

            /**
             * @brief Subtract x from the x of the Size object.
             * @param x The x of the Size object.
             * @return The location object.
             */
            Location subX(double x)
            {
                dx -= x;
                ix = (int)dx;
                return *this;
            }

            /**
             * @brief Subtract y from the y of the Size object.
             * @param y The y of the Size object.
             * @return The location object.
             */
            Location subY(double y)
            {
                dy -= y;
                iy = (int)dy;
                return *this;
            }

            /**
             * @brief Subtract x from the x of the Size object.
             * @param x The x of the Size object.
             * @return The location object.
             */
            Location subX(int x)
            {
                ix -= x;
                dx = (double)ix;
                return *this;
            }

            /**
             * @brief Subtract y from the y of the Size object.
             * @param y The y of the Size object.
             * @return The location object.
             */
            Location subY(int y)
            {
                iy -= y;
                dy = (double)iy;
                return *this;
            }

            /**
             * @brief Subtract x and y from the x and y of the Size object.
             * @param x The x of the Size object.
             * @param y The y of the Size object.
             * @return The location object.
             */
            Location sub(double x, double y)
            {
                dx -= x;
                dy -= y;
                ix = (int)dx;
                iy = (int)dy;
                return *this;
            }

            /**
             * @brief Subtract x and y from the x and y of the Size object.
             * @param x The x of the Size object.
             * @param y The y of the Size object.
             * @return The location object.
             */
            Location sub(int x, int y)
            {
                ix -= x;
                iy -= y;
                dx = (double)ix;
                dy = (double)iy;
                return *this;
            }

            /**
             * @brief Multiply x with the x of the Size object.
             * @param x The x of the Size object.
             * @return The location object.
             */
            Location mulX(double x)
            {
                dx *= x;
                ix = (int)dx;
                return *this;
            }

            /**
             * @brief Multiply y with the y of the Size object.
             * @param y The y of the Size object.
             * @return The location object.
             */
            Location mulY(double y)
            {
                dy *= y;
                iy = (int)dy;
                return *this;
            }

            /**
             * @brief Multiply x with the x of the Size object.
             * @param x The x of the Size object.
             * @return The location object.
             */
            Location mulX(int x)
            {
                ix *= x;
                dx = (double)ix;
                return *this;
            }

            /**
             * @brief Multiply y with the y of the Size object.
             * @param y The y of the Size object.
             * @return The location object.
             */
            Location mulY(int y)
            {
                iy *= y;
                dy = (double)iy;
                return *this;
            }

            /**
             * @brief Multiply x and y with the x and y of the Size object.
             * @param x The x of the Size object.
             * @param y The y of the Size object.
             * @return The location object.
             */
            Location mul(double x, double y)
            {
                dx *= x;
                dy *= y;
                ix = (int)dx;
                iy = (int)dy;
                return *this;
            }

            /**
             * @brief Multiply x and y with the x and y of the Size object.
             * @param x The x of the Size object.
             * @param y The y of the Size object.
             * @return The location object.
             */
            Location mul(int x, int y)
            {
                ix *= x;
                iy *= y;
                dx = (double)ix;
                dy = (double)iy;
                return *this;
            }

            /**
             * @brief Divide x with the x of the Size object.
             * @param x The x of the Size object.
             * @return The location object.
             */
            Location divX(double x)
            {
                dx /= x;
                ix = (int)dx;
                return *this;
            }

            /**
             * @brief Divide y with the y of the Size object.
             * @param y The y of the Size object.
             * @return The location object.
             */
            Location divY(double y)
            {
                dy /= y;
                iy = (int)dy;
                return *this;
            }

            /**
             * @brief Divide x with the x of the Size object.
             * @param x The x of the Size object.
             * @return The location object.
             */
            Location divX(int x)
            {
                ix /= x;
                dx = (double)ix;
                return *this;
            }

            /**
             * @brief Divide y with the y of the Size object.
             * @param y The y of the Size object.
             * @return The location object.
             */
            Location divY(int y)
            {
                iy /= y;
                dy = (double)iy;
                return *this;
            }

            /**
             * @brief Divide x and y with the x and y of the Size object.
             * @param x The x of the Size object.
             * @param y The y of the Size object.
             * @return The location object.
             */
            Location div(double x, double y)
            {
                dx /= x;
                dy /= y;
                ix = (int)dx;
                iy = (int)dy;
                return *this;
            }

            /**
             * @brief Divide x and y with the x and y of the Size object.
             * @param x The x of the Size object.
             * @param y The y of the Size object.
             * @return The location object.
             */
            Location div(int x, int y)
            {
                ix /= x;
                iy /= y;
                dx = (double)ix;
                dy = (double)iy;
                return *this;
            }

            Location operator=(float other) { return Location(other, other); }
            Location operator=(double other) { return Location(other, other); }
            Location operator=(int other) { return Location(other, other); }

            Location operator+(float other) { return Location(dx + other, dy + other); }
            Location operator+(double other) { return Location(dx + other, dy + other); }
            Location operator+(int other) { return Location(dx + other, dy + other); }
            Location operator+(Location other) { return Location(dx + other.dx, dy + other.dy); }

            Location operator-(float other) { return Location(dx - other, dy - other); }
            Location operator-(double other) { return Location(dx - other, dy - other); }
            Location operator-(int other) { return Location(dx - other, dy - other); }
            Location operator-(Location other) { return Location(dx - other.dx, dy - other.dy); }

            Location operator*(float other) { return Location(dx * other, dy * other); }
            Location operator*(double other) { return Location(dx * other, dy * other); }
            Location operator*(int other) { return Location(dx * other, dy * other); }
            Location operator*(Location other) { return Location(dx * other.dx, dy * other.dy); }

            Location operator/(float other) { return Location(dx / other, dy / other); }
            Location operator/(double other) { return Location(dx / other, dy / other); }
            Location operator/(int other) { return Location(dx / other, dy / other); }
            Location operator/(Location other) { return Location(dx / other.dx, dy / other.dy); }

            Location operator+=(float other)
            {
                dx += other;
                dy += other;
                ix = (int)dx;
                iy = (int)dy;
                return *this;
            }
            Location operator+=(double other)
            {
                dx += other;
                dy += other;
                ix = (int)dx;
                iy = (int)dy;
                return *this;
            }
            Location operator+=(int other)
            {
                dx += other;
                dy += other;
                ix = (int)dx;
                iy = (int)dy;
                return *this;
            }
            Location operator+=(Location other)
            {
                dx += other.dx;
                dy += other.dy;
                ix = (int)dx;
                iy = (int)dy;
                return *this;
            }

            Location operator-=(float other)
            {
                dx -= other;
                dy -= other;
                ix = (int)dx;
                iy = (int)dy;
                return *this;
            }
            Location operator-=(double other)
            {
                dx -= other;
                dy -= other;
                ix = (int)dx;
                iy = (int)dy;
                return *this;
            }
            Location operator-=(int other)
            {
                dx -= other;
                dy -= other;
                ix = (int)dx;
                iy = (int)dy;
                return *this;
            }
            Location operator-=(Location other)
            {
                dx -= other.dx;
                dy -= other.dy;
                ix = (int)dx;
                iy = (int)dy;
                return *this;
            }

            Location operator*=(float other)
            {
                dx *= other;
                dy *= other;
                ix = (int)dx;
                iy = (int)dy;
                return *this;
            }
            Location operator*=(double other)
            {
                dx *= other;
                dy *= other;
                ix = (int)dx;
                iy = (int)dy;
                return *this;
            }
            Location operator*=(int other)
            {
                dx *= other;
                dy *= other;
                ix = (int)dx;
                iy = (int)dy;
                return *this;
            }
            Location operator*=(Location other)
            {
                dx *= other.dx;
                dy *= other.dy;
                ix = (int)dx;
                iy = (int)dy;
                return *this;
            }

            Location operator/=(float other)
            {
                dx /= other;
                dy /= other;
                ix = (int)dx;
                iy = (int)dy;
                return *this;
            }
            Location operator/=(double other)
            {
                dx /= other;
                dy /= other;
                ix = (int)dx;
                iy = (int)dy;
                return *this;
            }
            Location operator/=(int other)
            {
                dx /= other;
                dy /= other;
                ix = (int)dx;
                iy = (int)dy;
                return *this;
            }
            Location operator/=(Location other)
            {
                dx /= other.dx;
                dy /= other.dy;
                ix = (int)dx;
                iy = (int)dy;
                return *this;
            }

            bool operator==(Location other) { return dx == other.dx && dy == other.dy; }
            bool operator!=(Location other) { return dx != other.dx || dy != other.dy; }

            bool operator==(double other) { return dx == other && dy == other; }
            bool operator!=(double other) { return dx != other || dy != other; }

            bool operator==(int other) { return dx == other && dy == other; }
            bool operator!=(int other) { return dx != other || dy != other; }

            bool operator==(float other) { return dx == other && dy == other; }
            bool operator!=(float other) { return dx != other || dy != other; }

            bool operator<(Location other) { return dx < other.dx && dy < other.dy; }
            bool operator>(Location other) { return dx > other.dx && dy > other.dy; }
            bool operator<=(Location other) { return dx <= other.dx && dy <= other.dy; }
            bool operator>=(Location other) { return dx >= other.dx && dy >= other.dy; }

            bool operator<(double other) { return dx < other && dy < other; }
            bool operator>(double other) { return dx > other && dy > other; }
            bool operator<=(double other) { return dx <= other && dy <= other; }
            bool operator>=(double other) { return dx >= other && dy >= other; }

            bool operator<(int other) { return dx < other && dy < other; }
            bool operator>(int other) { return dx > other && dy > other; }
            bool operator<=(int other) { return dx <= other && dy <= other; }
            bool operator>=(int other) { return dx >= other && dy >= other; }

            bool operator<(float other) { return dx < other && dy < other; }
            bool operator>(float other) { return dx > other && dy > other; }
            bool operator<=(float other) { return dx <= other && dy <= other; }
            bool operator>=(float other) { return dx >= other && dy >= other; }

            Location operator-() { return Location(-dx, -dy); }

            Location operator++()
            {
                dx++;
                dy++;
                ix = (int)dx;
                iy = (int)dy;
                return *this;
            }
            Location operator--()
            {
                dx--;
                dy--;
                ix = (int)dx;
                iy = (int)dy;
                return *this;
            }

            Location operator++(int)
            {
                Location temp = *this;
                dx++;
                dy++;
                ix = (int)dx;
                iy = (int)dy;
                return temp;
            }
            Location operator--(int)
            {
                Location temp = *this;
                dx--;
                dy--;
                ix = (int)dx;
                iy = (int)dy;
                return temp;
            }

            Location operator!() { return Location(!dx, !dy); }

            Location operator&&(Location other) { return Location(dx && other.dx, dy && other.dy); }
            Location operator||(Location other) { return Location(dx || other.dx, dy || other.dy); }

            Location operator&&(double other) { return Location(dx && other, dy && other); }
            Location operator||(double other) { return Location(dx || other, dy || other); }

            Location operator&&(int other) { return Location(dx && other, dy && other); }
            Location operator||(int other) { return Location(dx || other, dy || other); }

            Location operator&&(float other) { return Location(dx && other, dy && other); }
            Location operator||(float other) { return Location(dx || other, dy || other); }

            Location operator&&(bool other) { return Location(dx && other, dy && other); }
            Location operator||(bool other) { return Location(dx || other, dy || other); }

            /*
             * @warning If you set this directly, the other coordinates will not be updated.
             */
            int ix;

            /*
             * @warning If you set this directly, the other coordinates will not be updated.
             */
            int iy;

            /*
             * @warning If you set this directly, the other coordinates will not be updated.
             */
            double dx;

            /*
             * @warning If you set this directly, the other coordinates will not be updated.
             */
            double dy;
        } Location;

        typedef struct Size
        {
            /**
             * @brief Represents the size of an object.
             * @note The width and height coordinates are default 0.
             */
            Size() : dWidth(0), dHeight(0), iWidth(0), iHeight(0) {}

            /**
             * @brief Represents the size of an object.
             * @param width The width of the Size object.
             * @param height The height of the Size object.
             */
            Size(int width, int height) : dWidth(width), dHeight(height), iWidth(width), iHeight(height) {}
            /**
             * @brief Represents the size of an object.dinates.
             * @param width The width of the Size object.
             * @param height The height of the Size object.
             */
            Size(double width, double height) : dWidth(width), dHeight(height), iWidth((int)width), iHeight((int)height) {}

            /**
             * @brief Get the width of the Size object.
             * @return The width of the Size object.
             */
            double getdWidth() { return dWidth; }

            /**
             * @brief Get the height of the Size object.
             * @return The height of the Size object.
             */
            double getdHeight() { return dHeight; }

            /**
             * @brief Get the width of the Size object.
             * @return The width of the Size object.
             */
            int getiWidth() { return iWidth; }

            /**
             * @brief Get the height of the Size object.
             * @return The height of the Size object.
             */
            int getIheight() { return iHeight; }

            /**
             * @brief Set the width of the Size object.
             * @param width The width of the Size object.
             * @return The Size object.
             */
            Size setwidth(double width)
            {
                dWidth = width;
                iWidth = (int)width;
                return *this;
            }

            /**
             * @brief Set the height of the Size object.
             * @param height The height of the Size object.
             * @return The Size object.
             */
            Size setheight(double height)
            {
                dHeight = height;
                iHeight = (int)height;
                return *this;
            }

            /**
             * @brief Set the width of the Size object.
             * @param width The width of the Size object.
             * @return The Size object.
             */
            Size setwidth(int width)
            {
                iWidth = width;
                dWidth = (double)width;
                return *this;
            }

            /**
             * @brief Set the height of the Size object.
             * @param height The height of the Size object.
             * @return The Size object.
             */
            Size setheight(int height)
            {
                iHeight = height;
                dHeight = (double)height;
                return *this;
            }

            /**
             * @brief Set the width and height of the Size object.
             * @param width The width of the Size object.
             * @param height The height of the Size object.
             * @return The Size object.
             */
            Size set(double width, double height)
            {
                dWidth = width;
                dHeight = height;
                iWidth = (int)width;
                iHeight = (int)height;
                return *this;
            }

            /**
             * @brief Set the width and height of the Size object.
             * @param width The width of the Size object.
             * @param height The height of the Size object.
             * @return The Size object.
             */
            Size set(int width, int height)
            {
                iWidth = width;
                iHeight = height;
                dWidth = (double)width;
                dHeight = (double)height;
                return *this;
            }

            /**
             * @brief Add width to the width of the Size object.
             * @param width The width of the Size object.
             * @return The Size object.
             */
            Size addWidth(double width)
            {
                dWidth += width;
                iWidth = (int)dWidth;
                return *this;
            }

            /**
             * @brief Add height to the height of the Size object.
             * @param height The height of the Size object.
             * @return The Size object.
             */
            Size addHeight(double height)
            {
                dHeight += height;
                iHeight = (int)dHeight;
                return *this;
            }

            /**
             * @brief Add width to the width of the Size object.
             * @param width The width of the Size object.
             * @return The Size object.
             */
            Size addWidth(int width)
            {
                iWidth += width;
                dWidth = (double)iWidth;
                return *this;
            }

            /**
             * @brief Add height to the height of the Size object.
             * @param height The height of the Size object.
             * @return The Size object.
             */
            Size addHeight(int height)
            {
                iHeight += height;
                dHeight = (double)iHeight;
                return *this;
            }

            /**
             * @brief Add width and height to the width and height of the Size object.
             * @param width The width of the Size object.
             * @param height The height of the Size object.
             * @return The Size object.
             */
            Size add(double width, double height)
            {
                dWidth += width;
                dHeight += height;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return *this;
            }

            /**
             * @brief Add width and height to the width and height of the Size object.
             * @param width The width of the Size object.
             * @param height The height of the Size object.
             * @return The Size object.
             */
            Size add(int width, int height)
            {
                iWidth += width;
                iHeight += height;
                dWidth = (double)iWidth;
                dHeight = (double)iHeight;
                return *this;
            }

            /**
             * @brief Subtract width from the width of the Size object.
             * @param width The width of the Size object.
             * @return The Size object.
             */
            Size subwidth(double width)
            {
                dWidth -= width;
                iWidth = (int)dWidth;
                return *this;
            }

            /**
             * @brief Subtract height from the height of the Size object.
             * @param height The height of the Size object.
             * @return The Size object.
             */
            Size subheight(double height)
            {
                dHeight -= height;
                iHeight = (int)dHeight;
                return *this;
            }

            /**
             * @brief Subtract width from the width of the Size object.
             * @param width The width of the Size object.
             * @return The Size object.
             */
            Size subwidth(int width)
            {
                iWidth -= width;
                dWidth = (double)iWidth;
                return *this;
            }

            /**
             * @brief Subtract height from the height of the Size object.
             * @param height The height of the Size object.
             * @return The Size object.
             */
            Size subheight(int height)
            {
                iHeight -= height;
                dHeight = (double)iHeight;
                return *this;
            }

            /**
             * @brief Subtract width and height from the width and height of the Size object.
             * @param width The width of the Size object.
             * @param height The height of the Size object.
             * @return The Size object.
             */
            Size sub(double width, double height)
            {
                dWidth -= width;
                dHeight -= height;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return *this;
            }

            /**
             * @brief Subtract width and height from the width and height of the Size object.
             * @param width The width of the Size object.
             * @param height The height of the Size object.
             * @return The Size object.
             */
            Size sub(int width, int height)
            {
                iWidth -= width;
                iHeight -= height;
                dWidth = (double)iWidth;
                dHeight = (double)iHeight;
                return *this;
            }

            /**
             * @brief Multiple width with the width of the Size object.
             * @param width The width of the Size object.
             * @return The Size object.
             */
            Size mulwidth(double width)
            {
                dWidth *= width;
                iWidth = (int)dWidth;
                return *this;
            }

            /**
             * @brief Multiple height with the height of the Size object.
             * @param height The height of the Size object.
             * @return The Size object.
             */
            Size mulheight(double height)
            {
                dHeight *= height;
                iHeight = (int)dHeight;
                return *this;
            }

            /**
             * @brief Multiple width with the width of the Size object.
             * @param width The width of the Size object.
             * @return The Size object.
             */
            Size mulwidth(int width)
            {
                iWidth *= width;
                dWidth = (double)iWidth;
                return *this;
            }

            /**
             * @brief Multiple height with the height of the Size object.
             * @param height The height of the Size object.
             * @return The Size object.
             */
            Size mulheight(int height)
            {
                iHeight *= height;
                dHeight = (double)iHeight;
                return *this;
            }

            /**
             * @brief Multiple width and height with the width and height of the Size object.
             * @param width The width of the Size object.
             * @param height The height of the Size object.
             * @return The Size object.
             */
            Size mul(double width, double height)
            {
                dWidth *= width;
                dHeight *= height;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return *this;
            }

            /**
             * @brief Multiple width and height with the width and height of the Size object.
             * @param width The width of the Size object.
             * @param height The height of the Size object.
             * @return The Size object.
             */
            Size mul(int width, int height)
            {
                iWidth *= width;
                iHeight *= height;
                dWidth = (double)iWidth;
                dHeight = (double)iHeight;
                return *this;
            }

            /**
             * @brief Divide width with the width of the Size object.
             * @param width The width of the Size object.
             * @return The Size object.
             */
            Size divwidth(double width)
            {
                dWidth /= width;
                iWidth = (int)dWidth;
                return *this;
            }

            /**
             * @brief Divide height with the height of the Size object.
             * @param height The height of the Size object.
             * @return The Size object.
             */
            Size divheight(double height)
            {
                dHeight /= height;
                iHeight = (int)dHeight;
                return *this;
            }

            /**
             * @brief Divide width with the width of the Size object.
             * @param width The width of the Size object.
             * @return The Size object.
             */
            Size divwidth(int width)
            {
                iWidth /= width;
                dWidth = (double)iWidth;
                return *this;
            }

            /**
             * @brief Divide height with the height of the Size object.
             * @param height The height of the Size object.
             * @return The Size object.
             */
            Size divheight(int height)
            {
                iHeight /= height;
                dHeight = (double)iHeight;
                return *this;
            }

            /**
             * @brief Divide width and height with the width and height of the Size object.
             * @param width The width of the Size object.
             * @param height The height of the Size object.
             * @return The Size object.
             */
            Size div(double width, double height)
            {
                dWidth /= width;
                dHeight /= height;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return *this;
            }

            /**
             * @brief Divide width and height with the width and height of the Size object.
             * @param width The width of the Size object.
             * @param height The height of the Size object.
             * @return The Size object.
             */
            Size div(int width, int height)
            {
                iWidth /= width;
                iHeight /= height;
                dWidth = (double)iWidth;
                dHeight = (double)iHeight;
                return *this;
            }

            Size operator=(float other) { return Size(other, other); }
            Size operator=(double other) { return Size(other, other); }
            Size operator=(int other) { return Size(other, other); }

            Size operator+(float other) { return Size(dWidth + other, dHeight + other); }
            Size operator+(double other) { return Size(dWidth + other, dHeight + other); }
            Size operator+(int other) { return Size(dWidth + other, dHeight + other); }
            Size operator+(Size other) { return Size(dWidth + other.dWidth, dHeight + other.dHeight); }

            Size operator-(float other) { return Size(dWidth - other, dHeight - other); }
            Size operator-(double other) { return Size(dWidth - other, dHeight - other); }
            Size operator-(int other) { return Size(dWidth - other, dHeight - other); }
            Size operator-(Size other) { return Size(dWidth - other.dWidth, dHeight - other.dHeight); }

            Size operator*(float other) { return Size(dWidth * other, dHeight * other); }
            Size operator*(double other) { return Size(dWidth * other, dHeight * other); }
            Size operator*(int other) { return Size(dWidth * other, dHeight * other); }
            Size operator*(Size other) { return Size(dWidth * other.dWidth, dHeight * other.dHeight); }

            Size operator/(float other) { return Size(dWidth / other, dHeight / other); }
            Size operator/(double other) { return Size(dWidth / other, dHeight / other); }
            Size operator/(int other) { return Size(dWidth / other, dHeight / other); }
            Size operator/(Size other) { return Size(dWidth / other.dWidth, dHeight / other.dHeight); }

            Size operator+=(float other)
            {
                dWidth += other;
                dHeight += other;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return *this;
            }
            Size operator+=(double other)
            {
                dWidth += other;
                dHeight += other;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return *this;
            }
            Size operator+=(int other)
            {
                dWidth += other;
                dHeight += other;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return *this;
            }
            Size operator+=(Size other)
            {
                dWidth += other.dWidth;
                dHeight += other.dHeight;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return *this;
            }

            Size operator-=(float other)
            {
                dWidth -= other;
                dHeight -= other;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return *this;
            }
            Size operator-=(double other)
            {
                dWidth -= other;
                dHeight -= other;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return *this;
            }
            Size operator-=(int other)
            {
                dWidth -= other;
                dHeight -= other;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return *this;
            }
            Size operator-=(Size other)
            {
                dWidth -= other.dWidth;
                dHeight -= other.dHeight;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return *this;
            }

            Size operator*=(float other)
            {
                dWidth *= other;
                dHeight *= other;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return *this;
            }
            Size operator*=(double other)
            {
                dWidth *= other;
                dHeight *= other;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return *this;
            }
            Size operator*=(int other)
            {
                dWidth *= other;
                dHeight *= other;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return *this;
            }
            Size operator*=(Size other)
            {
                dWidth *= other.dWidth;
                dHeight *= other.dHeight;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return *this;
            }

            Size operator/=(float other)
            {
                dWidth /= other;
                dHeight /= other;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return *this;
            }
            Size operator/=(double other)
            {
                dWidth /= other;
                dHeight /= other;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return *this;
            }
            Size operator/=(int other)
            {
                dWidth /= other;
                dHeight /= other;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return *this;
            }
            Size operator/=(Size other)
            {
                dWidth /= other.dWidth;
                dHeight /= other.dHeight;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return *this;
            }

            bool operator==(Size other) { return dWidth == other.dWidth && dHeight == other.dHeight; }
            bool operator!=(Size other) { return dWidth != other.dWidth || dHeight != other.dHeight; }

            bool operator==(double other) { return dWidth == other && dHeight == other; }
            bool operator!=(double other) { return dWidth != other || dHeight != other; }

            bool operator==(int other) { return dWidth == other && dHeight == other; }
            bool operator!=(int other) { return dWidth != other || dHeight != other; }

            bool operator==(float other) { return dWidth == other && dHeight == other; }
            bool operator!=(float other) { return dWidth != other || dHeight != other; }

            bool operator<(Size other) { return dWidth < other.dWidth && dHeight < other.dHeight; }
            bool operator>(Size other) { return dWidth > other.dWidth && dHeight > other.dHeight; }
            bool operator<=(Size other) { return dWidth <= other.dWidth && dHeight <= other.dHeight; }
            bool operator>=(Size other) { return dWidth >= other.dWidth && dHeight >= other.dHeight; }

            bool operator<(double other) { return dWidth < other && dHeight < other; }
            bool operator>(double other) { return dWidth > other && dHeight > other; }
            bool operator<=(double other) { return dWidth <= other && dHeight <= other; }
            bool operator>=(double other) { return dWidth >= other && dHeight >= other; }

            bool operator<(int other) { return dWidth < other && dHeight < other; }
            bool operator>(int other) { return dWidth > other && dHeight > other; }
            bool operator<=(int other) { return dWidth <= other && dHeight <= other; }
            bool operator>=(int other) { return dWidth >= other && dHeight >= other; }

            bool operator<(float other) { return dWidth < other && dHeight < other; }
            bool operator>(float other) { return dWidth > other && dHeight > other; }
            bool operator<=(float other) { return dWidth <= other && dHeight <= other; }
            bool operator>=(float other) { return dWidth >= other && dHeight >= other; }

            Size operator-() { return Size(-dWidth, -dHeight); }

            Size operator++()
            {
                dWidth++;
                dHeight++;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return *this;
            }
            Size operator--()
            {
                dWidth--;
                dHeight--;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return *this;
            }

            Size operator++(int)
            {
                Size temp = *this;
                dWidth++;
                dHeight++;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return temp;
            }
            Size operator--(int)
            {
                Size temp = *this;
                dWidth--;
                dHeight--;
                iWidth = (int)dWidth;
                iHeight = (int)dHeight;
                return temp;
            }

            Size operator!() { return Size(!dWidth, !dHeight); }

            Size operator&&(Size other) { return Size(dWidth && other.dWidth, dHeight && other.dHeight); }
            Size operator||(Size other) { return Size(dWidth || other.dWidth, dHeight || other.dHeight); }

            Size operator&&(double other) { return Size(dWidth && other, dHeight && other); }
            Size operator||(double other) { return Size(dWidth || other, dHeight || other); }

            Size operator&&(int other) { return Size(dWidth && other, dHeight && other); }
            Size operator||(int other) { return Size(dWidth || other, dHeight || other); }

            Size operator&&(float other) { return Size(dWidth && other, dHeight && other); }
            Size operator||(float other) { return Size(dWidth || other, dHeight || other); }

            Size operator&&(bool other) { return Size(dWidth && other, dHeight && other); }
            Size operator||(bool other) { return Size(dWidth || other, dHeight || other); }

            /*
             * @warning If you set this directly, the other coordinates will not be updated.
             */
            int iWidth;

            /*
             * @warning If you set this directly, the other coordinates will not be updated.
             */
            int iHeight;

            /*
             * @warning If you set this directly, the other coordinates will not be updated.
             */
            double dWidth;

            /*
             * @warning If you set this directly, the other coordinates will not be updated.
             */
            double dHeight;
        } Size;
    }
}