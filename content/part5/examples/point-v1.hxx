#pragma once  ///< ignore this

#include <ostream>
#include <utility>

namespace v1
{
    class Point
    {
    public:
        /// Default Constructor (Compiler Created)
        constexpr Point() = default;

        explicit constexpr
        Point(int x, int y) noexcept
            : x{ x }, y{ y }
        { }

        constexpr Point(const Point& p) noexcept
        : x{ p.x }, y{ p.y }
        { }

        constexpr Point(Point&& p) noexcept
            : x{ std::move(p.x) }
            , y{ std::move(p.y) }
        { p = Point(); }

        constexpr auto
        operator= (const Point& p) noexcept -> Point&
        {
            if (p != *this)
            {
                x = p.x;
                y = p.y;
            }

            return *this;
        }

        constexpr auto
        operator= (Point&& p) noexcept -> Point&
        {
            if (p != *this)
            {
                x = std::move(p.x);
                y = std::move(p.y);
            }

            return *this;
        }

        ~Point() noexcept = default;

        constexpr auto
        operator+ (const Point& p) noexcept -> Point
        { return Point{ x + p.x, y + p.y }; }

        constexpr auto
        operator- (const Point& p) noexcept -> Point
        { return Point{ x - p.x, y - p.y }; }

        constexpr auto
        operator== (const Point& p)
            noexcept -> bool
        { return (x == p.x) && (y == p.y); }

        constexpr auto
        operator!= (const Point& p)
        noexcept -> bool
        { return !(*this == p); }

        friend auto
        operator<< (std::ostream& os, const Point& p)
            noexcept -> std::ostream&
        { 
            os << "( "
            << p.x
            << ", "
            << p.y
            << " )";

            return os;
        }

    private:
        int x;
        int y;

    };  /// class Point

}  /// namespace v1

