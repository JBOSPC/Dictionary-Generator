#include "Exponential_notation.h"
#include <math.h>
#include <iomanip>

#define print_precision 3


Exponential_notation::~Exponential_notation() {delete this -> pow;}


void Exponential_notation::operator*=(const size_t& mul_num) {

    unsigned short int size_len = 0;
    double long d_mul_num = mul_num;

    while (d_mul_num >= 10) {d_mul_num /= 10; ++size_len;}
    
    this -> num *= d_mul_num;
    if (this -> num >= 10) {this -> num /= 10; ++size_len;}
    
    std::vector<uint64_t>::reverse_iterator ptr = this -> pow -> rbegin();
    uint64_t sum_el = *ptr + size_len;

    if (sum_el < *ptr) {
        *ptr = UINT64_MAX; 
        this -> pow -> push_back(sum_el);
    }
    else {*ptr = sum_el;}
}


void Exponential_notation::print() {

    std::cout << std::setprecision(print_precision) << std::fixed << (this -> num);
    for (const uint64_t& pow_itr : *(this -> pow)) {std::cout << " * 10^" << pow_itr;}
    std::cout << " Keys" << "\n";
}