#include <string>
#include <sstream>
#include <iostream>
#include <limits>
#include "digit_sep.h"
#include "bitops.h"
using namespace std;


void test_digit_sep(void)
{
    cout << digit_sep<uint64_t>(0x1234ff5678, 64, 5, "'") << endl;
    cout << digit_sep<uint32_t>(0x12345678, 32, 2, "_") << endl;
}

void test_bitops(void)
{
    uint64_t u64 = bit_extract<uint64_t, uint8_t>(7, 2, 6);
    uint32_t dst = 0x1000;
    uint32_t u32_1 = bit_insert<uint16_t, uint32_t>(dst, 0x3, 4, 3);
    uint32_t u32_2 = bit_replace<uint16_t, uint32_t>(dst, 0x3, 2, 15);
    uint32_t u32_3 = bit_ptn<uint8_t, uint32_t>(0xf, 4, 2);


    uint16_t u16 = bit_extract<uint16_t, uint32_t>(0x123456, 4, 15);

    auto disp = [](const string s, const auto d) {
        cout << s << " " << d << endl;
    };

    disp("u64", u64);
    disp("u16", u16);
    disp("u32_1", u32_1);
    disp("u32_2", u32_2);
    disp("u32_3", u32_3);
    

    for (int i = 0; i < 32; ++i) {
        uint32_t d = 1 << i;
        cout << d << " " << i << " ffs " << find_first_bit(d) << " ";
        cout << "popcnt" << population_count((uint64_t)(i)) << endl;
    }

    for (int i = 0; i < 64; ++i) {
        uint64_t d = 1 << i;
        cout << d << " " << i << " ffs " << find_first_bit(d) << " ";
        cout << "popcnt" << population_count((uint64_t)(i)) << endl;
    }
}

int main(int argc, const char *argv[])
{
    test_digit_sep();
    test_bitops();
}

