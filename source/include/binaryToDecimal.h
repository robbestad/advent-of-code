//
// this function copied from https://www.geeksforgeeks.org/program-binary-decimal-conversion/
//

#ifndef AOC_BINARYTODECIMAL_H
#define AOC_BINARYTODECIMAL_H

int binaryToDecimal(int n) {
    int num = n;
    int dec_value = 0;
    // Initializing base value to 1, i.e 2^0
    int base = 1;
    int temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;
        dec_value += last_digit * base;
        base = base * 2;
    }
    return dec_value;
}
unsigned long long binaryToDecimal(unsigned long long n) {
    auto num = n;
    auto dec_value = 0;
    // Initializing base value to 1, i.e 2^0
    auto base = 1;
    auto temp = num;
    while (temp) {
        auto last_digit = temp % 10;
        temp = temp / 10;
        dec_value += last_digit * base;
        base = base * 2;
    }
    return dec_value;
}
#endif //AOC_BINARYTODECIMAL_H
