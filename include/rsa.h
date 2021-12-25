#include <stdio.h>
#include <bitset>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    
    static constexpr int size_2048 = 2048;
    static constexpr int size_1024 = 1024;
    static constexpr int size_512 = 512;
    static constexpr int size_256 = 256;
    boost::multiprecision::cpp_int generate_prime(int bit_length);
    static boost::multiprecision::cpp_int mod_pow(boost::multiprecision::cpp_int base,
    boost::multiprecision::cpp_int exponent,
    const boost::multiprecision::cpp_int mod);
    static bool check_overflow(const boost::multiprecision::cpp_int& num1, const boost::multiprecision::cpp_int& num2);
    public:
    boost::multiprecision::cpp_int p,q,e,n,d,euler,random;
    Rsa(int bit_length);
    Rsa(const boost::multiprecision::cpp_int& e, const boost::multiprecision::cpp_int& d,const boost::multiprecision::cpp_int& n);
    std::string decrypt(const std::string& input);
    std::string encrypt(const std::string& plaintext);
    static std::string static_encryption(const std::string& plaintext, boost::multiprecision::cpp_int& e, boost::multiprecision::cpp_int& n);
    static std::string static_decryption(const std::string& cipher, boost::multiprecision::cpp_int& d, boost::multiprecision::cpp_int& n);
    static std::string char_string_to_ascii_value_string(const std::string& char_string);
    static std::string ascii_value_string_to_char_string(const std::string& ascii_string);
};
