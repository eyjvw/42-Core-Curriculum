#include <iostream>
#include <cmath>
#include <iomanip>

class Fixed
{
    private:
        int raw;
        static const int bits = 8;
    public:
        Fixed(void);
        Fixed(const int raw);
        Fixed(const float raw);
        Fixed(const Fixed& other);
        ~Fixed(void);

        Fixed &operator++(void);
        Fixed operator++(int);
        Fixed &operator--(void);
        Fixed operator--(int);

        bool operator>(const Fixed &src) const;
        bool operator<(const Fixed &src) const;
        bool operator>=(const Fixed &src) const;
        bool operator<=(const Fixed &src) const;
        bool operator==(const Fixed &src) const;
        bool operator!=(const Fixed &src) const;

        Fixed operator+(const Fixed &src) const;
        Fixed operator-(const Fixed &src) const;
        Fixed operator*(const Fixed &src) const;
        Fixed operator/(const Fixed &src) const;

        static Fixed &min(Fixed &a, Fixed &b);
        static const Fixed &min(const Fixed &a, const Fixed &b);
        static Fixed &max(Fixed &a, Fixed &b);
        static const Fixed &max(const Fixed &a, const Fixed &b);

        int getRawBits(void) const;
        void setRawBits(int raw);
        Fixed& operator=(const Fixed& other);
        int toInt(void) const;
        float toFloat(void) const;
};

std::ostream &operator << (std::ostream &i, const Fixed &rhs);