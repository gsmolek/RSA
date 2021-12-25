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
bool Rsa::check_overflow(const boost::multiprecision::cpp_int& num1,const boost::multiprecision::cpp_int& num2)
{
    boost::multiprecision::cpp_int value = num1 * num2;
    return (value < num1);
}
boost::multiprecision::cpp_int Rsa::mod_pow(boost::multiprecision::cpp_int base,
    boost::multiprecision::cpp_int exponent,
    const boost::multiprecision::cpp_int mod)
    {
        if( mod == 1 )
        {
            return 0;
        }
        if(!check_overflow(mod-1,mod-1))
        {
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
Rsa::Rsa(const boost::multiprecision::cpp_int& e,const boost::multiprecision::cpp_int& d,const boost::multiprecision::cpp_int& n)
{
        this->d=d;
        this->e=e;
        this->n=n;
}
std::string Rsa::encrypt(const std::string& plaintext)
{
    std::string str = "";
    std::string&& ref {char_string_to_ascii_value_string(plaintext)};
    boost::multiprecision::cpp_int output(ref);
    std::stringstream stream;
    output = mod_pow(output,e,n);
    stream << output;
    stream >> str;
    return str;
}
std::string Rsa::decrypt(const std::string& cyphertext)
{
    std::string str = "";
    boost::multiprecision::cpp_int output(cyphertext);
    std::stringstream stream;
    output = mod_pow(output,d,n);
    stream << output;
    stream >> str;
    str = ascii_value_string_to_char_string(str);
    return str;
}
boost::multiprecision::cpp_int Rsa::generate_prime(int bit_length)
{
    typedef boost::multiprecision::cpp_int int_type;
    boost::random::mt11213b base_gen(clock());
    boost::random::independent_bits_engine<boost::random::mt11213b, size_2048, int_type> gen2048(base_gen);
    boost::random::independent_bits_engine<boost::random::mt11213b, size_1024, int_type> gen1024(base_gen);
    boost::random::independent_bits_engine<boost::random::mt11213b, size_512, int_type> gen512(base_gen);
    boost::random::independent_bits_engine<boost::random::mt11213b, size_256, int_type> gen256(base_gen);
    
    boost::random::mt19937 gen2(clock());
    for(unsigned i = 0; i < 100000; ++i)
    {
      int_type num;
      switch(bit_length)
      {
        case size_2048:
            num = gen2048();
            break;
        case size_1024:
            num = gen1024();
            break;
        case size_512:
            num = gen512();
            break;
        case size_256:
            num = gen256();
      }
      if(miller_rabin_test(num, 25, gen2))
      {
        return num;
      }
    }
    return 0;
}
std::string Rsa::static_encryption(const std::string& plaintext, boost::multiprecision::cpp_int& e, boost::multiprecision::cpp_int& n)
{
    std::string str{};
    std::string&& ascii_value_ref = char_string_to_ascii_value_string(plaintext);
    boost::multiprecision::cpp_int output(ascii_value_ref);
    std::stringstream stream;
    output = mod_pow(output,e,n);
    stream << output;
    stream >> str;
    return str; 
}
std::string Rsa::static_decryption(const std::string& cipher, boost::multiprecision::cpp_int& d, boost::multiprecision::cpp_int& n)
{
    std::string str{};
    boost::multiprecision::cpp_int output(cipher);
    std::stringstream stream;
    output = mod_pow(output,d,n);
    stream << output;
    stream >> str;
    str = ascii_value_string_to_char_string(str);
    return str;
}
std::string Rsa::char_string_to_ascii_value_string(const std::string& char_string)
{
    std::string output{};
    std::stringstream string_stream{};
    int number = 0;
    for (auto c : char_string)
    {
        string_stream << int(c); 
    }
    output= std::move(string_stream.str());
    return output;

}
std::string Rsa::ascii_value_string_to_char_string(const std::string& ascii_string)
{
    std::string output{};
    int number = 0;
    for(auto c : ascii_string)
    {
        number = number * 10 + (c - '0');
        if(number >= 32 && number <= 122)
        {
            char ch = (char)number;
            output  += static_cast<char>(ch);
            number = 0;
        }
    }
    return output;
}
int main()
{
    Rsa t(1024);
    std::string text = t.encrypt("a1b2c3");
    std::cout<< text << std::endl;
    std::cout<< t.decrypt(text) << std::endl;

    std::cout<<"" << std::endl;
    std::string a = Rsa::encrypt("a1b2c3", t.e, t.n);
    std::cout<<"a: "<<a<< std::endl;
    std::cout<<"b: "<<Rsa::decrypt(a, t.d, t.n)<< std::endl;
    return 0;
}
