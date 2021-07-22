#include <stdio.h>
#include <bitset>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <boost/multiprecision/gmp.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <iostream>
#include <iomanip>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/integer/common_factor.hpp>
#include <algorithm>
#include <boost/integer/mod_inverse.hpp>

class Rsa
{
    boost::multiprecision::cpp_int p,q,e,n,d,euler,random;
    static constexpr int size_1024 = 1024;
    static constexpr int size_512 = 512;
    boost::multiprecision::cpp_int generate_prime(int bit_length);
    boost::multiprecision::cpp_int mod_pow(boost::multiprecision::cpp_int base,
    boost::multiprecision::cpp_int exponent,
    boost::multiprecision::cpp_int mod);
    bool check_overflow(boost::multiprecision::cpp_int num1, boost::multiprecision::cpp_int num2);
    public:
    Rsa(int bit_length);
    Rsa(boost::multiprecision::cpp_int e, boost::multiprecision::cpp_int d, boost::multiprecision::cpp_int n);
    std::string decrypt(std::string input);
    std::string encrypt(std::string plaintext);
    
};