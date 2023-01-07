#include <iostream>
#include <vector>

class Exponential_notation {
        
    protected:

    double long num{1};

    std::vector<uint64_t>* pow = new std::vector<uint64_t>{0}; 

    public:

    ~Exponential_notation();

    void operator*=(const size_t& mul_num);

    void print();
};