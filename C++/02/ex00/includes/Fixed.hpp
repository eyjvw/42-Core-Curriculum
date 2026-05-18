#include <iostream>

class Fixed
{
    private:
        int raw;
        static const int bits = 8;
    public:
        Fixed(void);
        Fixed(int raw);
        Fixed(const Fixed& other);
        ~Fixed(void);

        int getRawBits(void) const;
        void setRawBits(int raw);
        Fixed& operator=(const Fixed& other);
};