//
//  mylib1712.cpp
//  mylib1712
//
//  Created by 高澳杰 on 2023/12/17.
//

#include "mylib1712.hpp"
#include <string>

// 凯撒密码
extern "C" const char* caesar_encrypt(const char* plain_text, int offset) {
    std::string cipher_text;
    for (const char* p = plain_text; *p; ++p) {
        cipher_text += char((*p - 'a' + offset) % 26 + 'a');
    }
    return strdup(cipher_text.c_str());
}

extern "C" const char* caesar_decrypt(const char* cipher_text, int offset) {
    std::string plain_text;
    for (const char* p = cipher_text; *p; ++p) {
        plain_text += char((*p - 'a' - offset + 26) % 26 + 'a');
    }
    return strdup(plain_text.c_str());
}

// 仿射密码
extern "C" const char* affine_encrypt(const char* plain_text, int a, int b) {
    std::string cipher_text;
       for (const char* p = plain_text; *p; ++p) {
           if ('a' <= *p && *p <= 'z') {
               cipher_text += char((a * (*p - 'a') + b) % 26 + 'a');
           } else {
               // 如果字符不是小写字母，直接保留
               cipher_text += *p;
           }
       }
       return strdup(cipher_text.c_str());
}

extern "C" const char* affine_decrypt(const char* cipher_text, int a, int b) {
    std::string plain_text;
       int a_inv = -1;
       for (int i = 0; i < 26; ++i) {
           // 寻找加法逆元
           if ((a * i) % 26 == 1) {
               a_inv = i;
               break;
           }
       }

       if (a_inv == -1) {
           // 没有找到加法逆元，无法解密
           return strdup("");
       }

       for (const char* p = cipher_text; *p; ++p) {
           if ('a' <= *p && *p <= 'z') {
               plain_text += char((a_inv * (*p - 'a' - b + 26)) % 26 + 'a');
           } else {
               // 如果字符不是小写字母，直接保留
               plain_text += *p;
           }
       }
       return strdup(plain_text.c_str());
}
