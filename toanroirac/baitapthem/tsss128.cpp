#include <cstdint>
#include <iostream>
#include <iomanip>
#define U64 uint_fast64_t
#define U32 uint_fast32_t
#define U16 uint_fast16_t
#define U8 uint_fast8_t
using namespace std;
struct Int128
{
    uint64_t lower;
    uint64_t upper;

    // Constructor
    Int128(uint64_t upper = 0, uint64_t lower = 0) : upper(upper), lower(lower) {}

    // Addition
    Int128 operator+(const Int128 &other) const
    {
        Int128 result;
        result.lower = lower + other.lower;
        result.upper = upper + other.upper + (result.lower < lower);
        return result;
    }

    // Subtraction
    Int128 operator-(const Int128 &other) const
    {
        Int128 result;
        result.lower = lower - other.lower;
        result.upper = upper - other.upper - (result.lower > lower);
        return result;
    }

    // Comparison (Equal)
    bool operator==(const Int128 &other) const
    {
        return (lower == other.lower) && (upper == other.upper);
    }

    // Comparison (Not Equal)
    bool operator!=(const Int128 &other) const
    {
        return !(*this == other);
    }
    Int128 operator<<(unsigned int numBit) const
    {
        Int128 result(upper, lower);
        U64 lastBitLower = 0;
        for (U64 idx1 = 0; idx1 < numBit; idx1++)
        {
            lastBitLower = lower >> 63;
            lastBitLower ^= lastBitLower << 63;
            result.lower = lower << 1;
            result.upper = upper << 1;
            result.upper ^= lastBitLower;
        }
        return result;
    }
    Int128 operator>>(unsigned int numBit) const
    {
        Int128 result(upper, lower);
        U64 firstBitUpper = 0;
        for (U64 idx1 = 0; idx1 < numBit; idx1++)
        {
            firstBitUpper = upper & 0b1;
            result.upper >>= 1;
            result.lower = lower >> 1;
            result.lower ^= firstBitUpper << 63;
        }
        return result;
    }
    Int128 operator^(const Int128 &other) const
    {
        Int128 result;
        result.lower = lower ^ other.lower;
        result.upper = upper ^ other.upper;
        return result;
    }
    Int128 operator|(const Int128 &other) const
    {
        Int128 result;
        result.lower = lower | other.lower;
        result.upper = upper | other.upper;
        return result;
    }
    Int128 operator&(const Int128 &other) const
    {
        Int128 result;
        result.lower = lower & other.lower;
        result.upper = upper & other.upper;
        return result;
    }
    // Insertion operator to print the value
    friend std::ostream &operator<<(std::ostream &os, const Int128 &value)
    {
        os << "Upper: " << value.upper << ", Lower: " << value.lower;
        return os;
    }

    Int128 operator*(const Int128 &other) const
    {
        // Split the numbers into halves to handle the multiplication
        // chỉ nhân được 1 số có upper thôi nếu 2 số có upper thì sẽ vượt 128 bit
        if (upper * other.upper)
            return Int128(0, 0);
        Int128 result;
        if (upper > 0)
        {
            result.upper = upper * other.lower;
            result.lower = lower * other.lower;
        }
        else
        {
            result.upper = other.upper * lower;
            result.lower = other.lower * lower;
        }
        return result;
    }
};

int main()
{
    Int128 num1(1, 2);
    Int128 num2(5, 4);
    Int128 sum = num1 << 2;
    cout << sum << endl;
    sum = num1 >> 2;
    cout << hex << sum << endl;
    sum = num1 | num2;
    cout << hex << sum << endl;
    return 0;
}
