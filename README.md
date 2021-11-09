# RSA algorithm
 C++ implementation of the RSA asymetric algorithm.
 ## RSA
 Is a public-key algorithm used to encrypt data with a public key and decrypt it with a private key.
 ### Decryption and decryption
 If user A wants to send a message to user B, He must know the public key of user B and encrypt the message with it.
 When user B receives the encrypted message he can decrypt it with his private-key and view the original message.
 ### How to use
**1.** To create both the private-key and public-key pair use:

```Rsa rsa(int key_bit_length);```
This will create RSA objetc holding private and public key pairs.

**2.** To encrypt and decrypt using an already exists pairs:
```
using namespace boost::multiprecision;
Rsa rsa(cpp_int addressee_public_key, cpp_int user_private_key, cpp_int n);
rsa.encrypt(std::string message_to_encrypt_as_ascii);
rsa.decrypt(std::string encrypted_message);
```
Where n = ( prime number p ) * ( prime number q)
 ### Key size 
 Currently supports 512 and 1024 bits length keys.
 
 ### Dependencies
 Depandant on boost libararies.
