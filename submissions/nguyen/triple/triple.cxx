/// Date: 11/01/23
///
/// Copyright: Copyright (c) 2023
/// \file triple.cxx

/// To run this in VS code: 
/// Check if g++ is available: g++ --version
/// Go to Terminal -> Run Build Section -> Choose C/C++: g++ build active file
/// When the file is executing, there will be output at the end asking for some input which must be in number, and can be whole or decimal number

#include <iostream>
using namespace std;

template <typename T>
struct Triple 
{
    T x;
    T y;
    T z;
   
    constexpr auto
    add(const Triple& o)
        const noexcept
        -> Triple
    { return Triple{x + o.x, y + o.y, z + o.z}; }

    constexpr auto
    subtract(const Triple& o)
        const noexcept
        -> Triple
    { return Triple{x - o.x, y - o.y, z - o.z}; }

    constexpr auto
    multiply(const Triple& o, const T scalar)
        const noexcept
        -> Triple
    { return Triple{x*scalar, y*scalar, z*scalar}; }

    constexpr auto
    divide(const Triple& o, const T scalar)
        const noexcept
        -> Triple
    { return Triple{x/scalar, y/scalar, z/scalar}; }
    
    friend auto
    operator<< (std::ostream& os, const Triple& v)
        -> std::ostream&
    {
        os << "(.x: " << v.x << ", .y: " << v.y << ", .z: " << v.z <<")";
        return os; 
    }

    friend istream&
    operator>> (std::istream& is, Triple& v)
    {
        std::cout << "Enter x ";
        is >> v.x;
        std::cout << "Enter y ";
        is >> v.y;
        std::cout << "Enter z ";
        is >> v.z;
        return is;
    }
};

auto main() -> int 
{
    Triple<float> a;
    a.x = 5;
    a.y = 7;
    a.z = 9;
    Triple<float> b;
    b.x = 2;
    b.y = 5;
    b.z = 15;
    std::cout << "a.add(b) = " << a.add(b) << std::endl; 
    std::cout << "a.subtract(b) = " << a.subtract(b) << std::endl;
    std::cout << "a.multiply(b) = " << a.multiply(b,5) << std::endl;
    std::cout << "a.divide(b) = " << a.divide(b,5) << std::endl;

    Triple<float> p;
    std::cin >> p;
    cout << "p is " << p;


    return 0;
}

