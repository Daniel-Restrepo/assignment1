// convert.c
// has three main functions
//  div_convert: convert using repeated division (remainders)
//  sub_convert: convert using safe powers
//  print_tables: show values
// -----------------------------------------------------------
// ** Important variable names **
//  n: the input number
//  base: target base
//  out: output buffer to write the digits into
//  temp/indx: small helpers when building strings

#include <stdio.h>
#include <stdint.h>
#include <string.h>

// maps a single digit
static char digit_to_char(int value) {
    return (value < 10) ? (char)('0' + value) : (char)('A' + (value - 10));
}

// div_convert
// keep dividing n by base, store remainders (reversed), then flip them.
void div_convert(uint32_t n, int base, char *out) {
    char temp[64];   // holds digits in reverse
    int  indx = 0;   // tracks how many digits stored in tmp or current indx of temp

    if (base < 2 || base > 16) { strcpy(out, ""); 
        return;
    }
    if (n == 0) { strcpy(out, "0"); 
        return;
    }

    while (n > 0) {
        int r = (int)(n % (uint32_t)base);     // remainder in [0, base-1]
        n /= (uint32_t)base;                   // reduce n
        temp[indx++] = digit_to_char(r);         // store reversed
    }

    // reverse into 'out'
    for (int i = 0; i < indx; ++i) out[i] = temp[indx - 1 - i];
    out[indx] = '\0';
}

// sub_convert (overflow-safe):
//   finds largest power 'pw'
//   for each power down to 1, take digit = n / pw, subtract digit*pw, move on.
void sub_convert(uint32_t n, int base, char *out) {
    if (base < 2 || base > 16) { strcpy(out, "");
        return;
    }
    if (n == 0) { strcpy(out, "0");
        return;
    }

    // step 1: grow pw safely so pw*base never exceeds n
    uint32_t pw = 1;                     // current power of base
    while (pw <= n / (uint32_t)base) {    // only grow if next <= n
        pw *= (uint32_t)base;
    }

    // step 2: walk powers downward and build digits
    int wrote_any = 0;
    int idx = 0;
    while (pw > 0) {
        int digit = (int)(n / pw);
        n -= (uint32_t)digit * pw;
        if (digit != 0 || wrote_any) {
            out[idx++] = digit_to_char(digit);
            wrote_any = 1;
        }
        pw /= (uint32_t)base;
    }

    if (!wrote_any) out[idx++] = '0';
    out[idx] = '\0';
}

// print_tables:
void print_tables(uint32_t n) {
    char bin[33];   // up to 32 bits + '\0'
    char oct[16];   // enough for 32-bit in base 8
    char hex[16];   // enough for 32-bit in base 16

    div_convert(n, 2,  bin);
    div_convert(n, 8,  oct);
    div_convert(n, 16, hex);
    printf("Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, n, hex);

    // Left shift by 3
    uint32_t shifted = (n << 3);
    div_convert(shifted, 2,  bin);
    div_convert(shifted, 8,  oct);
    div_convert(shifted, 16, hex);
    printf("Left Shift by 3: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, shifted, hex);

    // AND with 0xFF
    uint32_t masked = (n & 0xFFu);
    div_convert(masked, 2,  bin);
    div_convert(masked, 8,  oct);
    div_convert(masked, 16, hex);
    printf("AND with 0xFF: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, masked, hex);
}