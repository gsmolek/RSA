#include "rsa.h"

Rsa::Rsa(int bit_length)
{
    p = generate_prime(bit_length);
    q = generate_prime(bit_length);
    n = p * q ;
    euler = (p - 1) * (q - 1);
    e = generate_prime(bit_length/2);
    while ((boost::integer::gcd( euler, e ) > 1 ) && ( e < euler ))
    {
        e+=1;
    }
    d = boost::integer::mod_inverse( e, euler );
    
}
bool Rsa::check_overflow(boost::multiprecision::cpp_int num1, boost::multiprecision::cpp_int num2)
{
    boost::multiprecision::cpp_int value = num1 * num2;
    return (value < num1);
}
boost::multiprecision::cpp_int Rsa::mod_pow(boost::multiprecision::cpp_int base,
    boost::multiprecision::cpp_int exponent,
    boost::multiprecision::cpp_int mod)
    {
        if( mod == 1 )
        {
            return 0;
        }
        if(!check_overflow(mod-1,mod-1))
        {
            std::cout << "\n entered"<< std::endl;
            boost::multiprecision::cpp_int result = 1;
            base = base % mod;
            while( exponent > 0)
            {
                if( exponent % 2 == 1)
                {
                    result = (result * base) % mod;
                }
                exponent = exponent >> 1;
                base = (base * base) % mod ;
            }
            return result; 
        }
        return -11111;

    }
Rsa::Rsa(boost::multiprecision::cpp_int e, boost::multiprecision::cpp_int d, boost::multiprecision::cpp_int n)
{
        this->d=d;
        this->e=e;
        this->n=n;
}
std::string Rsa::encrypt(std::string plaintext)
{
    std::string str = "";
    boost::multiprecision::cpp_int output(plaintext);
    std::stringstream stream;
    output = mod_pow(output,e,n);
    stream << output;
    stream >> str;
    return str;
}
std::string Rsa::decrypt(std::string cyphertext)
{
    std::string str = "";
    boost::multiprecision::cpp_int output(cyphertext);
    std::stringstream stream;
    output = mod_pow(output,d,n);
    stream << output;
    stream >> str;
    return str;
}
boost::multiprecision::cpp_int Rsa::generate_prime(int bit_length)
{
    typedef boost::multiprecision::cpp_int int_type;
    boost::random::mt11213b base_gen(clock());
    boost::random::independent_bits_engine<boost::random::mt11213b, size_1024, int_type> gen1024(base_gen);
    boost::random::independent_bits_engine<boost::random::mt11213b, size_512, int_type> gen512(base_gen);
    
    boost::random::mt19937 gen2(clock());
    for(unsigned i = 0; i < 100000; ++i)
    {
      int_type num;
      if(bit_length == size_1024)
      {
          num = gen1024();
      }
      else if(bit_length == size_512)
      {
          num = gen512();
      }
      if(miller_rabin_test(num, 25, gen2))
      {
        return num;
      }
    }
    return 0;
}


int main()
{
    Rsa t(1024);
    std::string text = t.encrypt("123456789");
    std::cout<< text << std::endl;
    std::cout<< t.decrypt(text) << std::endl;
    return 0;
}