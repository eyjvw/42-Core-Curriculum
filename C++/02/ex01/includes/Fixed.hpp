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

        int getRawBits(void) const;
        void setRawBits(int raw);
        Fixed& operator=(const Fixed& other);
        int toInt(void) const;
        float toFloat(void) const;
};

std::ostream &operator << (std::ostream &i, const Fixed &rhs);