//
//  mylib1712.hpp
//  mylib1712
//
//  Created by 高澳杰 on 2023/12/17.
//

#ifndef mylib1712_hpp
#define mylib1712_hpp

#include <stdio.h>

#include <string>


extern "C" const char* caesar_encrypt(const char* plain_text, int offset);
extern "C" const char* caesar_decrypt(const char* cipher_text, int offset);

// 仿射密码
extern "C" const char* affine_encrypt(const char* plain_text, int a, int b);
extern "C" const char* affine_decrypt(const char* cipher_text, int a, int b);


#endif /* mylib1712_hpp */
