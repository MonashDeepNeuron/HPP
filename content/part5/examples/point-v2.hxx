#pragma once  ///< ignore this

#include <ostream>
#include <utility>

namespace v2
{
    template<typename T>
    class Point
    {
    public:
        /// Default Constructor (Compiler Created)
        constexpr Point() = default;

        explicit constexpr
        Point(T x, T y) noexcept
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

        template<typename U>
        constexpr auto
        operator+ (const Point<U>& p) 
            noexcept -> Point<typename std::common_type<T, U>::type>
        { return Point<typename std::common_type<T, U>::type>{ x + p.x, y + p.y }; }

        template<typename U>
        constexpr auto
        operator- (const Point<U>& p) 
            noexcept -> Point<typename std::common_type<T, U>::type>
        { return Point<typename std::common_type<T, U>::type>{ x - p.x, y - p.y }; }

        template<typename U>
        constexpr auto
        operator== (const Point<U>& p)
            noexcept -> bool
        { return (x == p.x) && (y == p.y); }

        template<typename U>
        constexpr auto
        operator!= (const Point<U>& p)
        noexcept -> bool
        { return !(*this == p); }

        friend auto
        operator<< (std::ostream& os, const Point& p)
            noexcept -> std::ostream&
        { 
            os << "( " << p.x << ", " << p.y << " )";
            return os;
        }

    private:
        T x;
        T y;

    };  /// class Point

}  /// namespace v1

