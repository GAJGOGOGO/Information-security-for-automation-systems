//
//  main.cpp
//  Test1712
//
//  Created by 高澳杰 on 2023/12/17.
//

#include <iostream>
#include <dlfcn.h>
#include <cstring>

int main() {
    // 1. Load the dynamic library
    void* libHandle = dlopen("/Users/gaoaojie/Desktop/Debug/Test1712/libmylib1712.dylib", RTLD_LAZY);

    // Check if the library loaded successfully
    if (!libHandle) {
        std::cerr << "Error loading the library: " << dlerror() << std::endl;
        return 1;
    }

    // 2. Get function pointers
    using CaesarEncryptFunc = const char* (*)(const char*, int);
    using CaesarDecryptFunc = const char* (*)(const char*, int);
    using AffineEncryptFunc = const char* (*)(const char*, int, int);
    using AffineDecryptFunc = const char* (*)(const char*, int, int);

    CaesarEncryptFunc caesarEncrypt = reinterpret_cast<CaesarEncryptFunc>(dlsym(libHandle, "caesar_encrypt"));
    CaesarDecryptFunc caesarDecrypt = reinterpret_cast<CaesarDecryptFunc>(dlsym(libHandle, "caesar_decrypt"));
    AffineEncryptFunc affineEncrypt = reinterpret_cast<AffineEncryptFunc>(dlsym(libHandle, "affine_encrypt"));
    AffineDecryptFunc affineDecrypt = reinterpret_cast<AffineDecryptFunc>(dlsym(libHandle, "affine_decrypt"));

    // Check if function pointers are obtained successfully
    if (!caesarEncrypt || !caesarDecrypt || !affineEncrypt || !affineDecrypt) {
        std::cerr << "Error getting function pointers: " << dlerror() << std::endl;
        dlclose(libHandle);
        return 1;
    }

    while (true) {
        // 3. Display menu
        std::cout << "Select an option:\n"
                  << "1. Caesar Encrypt\n"
                  << "2. Caesar Decrypt\n"
                  << "3. Affine Encrypt\n"
                  << "4. Affine Decrypt\n"
                  << "5. Exit\n";

        int choice;
        std::cout << "Enter your choice (1-5): ";
        std::cin >> choice;

        if (choice == 5) {
            // 4. Exit the program
            break;
        }

        const char* text;
        const char* result;

        switch (choice) {
              case 1:
                  // Caesar Encrypt
                  {
                      // 使用字符数组接收用户输入
                      char inputText[256];
                      std::cout << "Enter the text to encrypt: ";
                      std::cin >> inputText;

                      int caesarOffset;
                      std::cout << "Enter the Caesar offset: ";
                      std::cin >> caesarOffset;

                      // 将字符数组转换为 const char*
                      text = strdup(inputText);
                      result = caesarEncrypt(text, caesarOffset);

                      std::cout << "Caesar Encrypted: " << result << std::endl;

                      // 释放动态分配的内存
                      free(const_cast<char*>(text));
                  }
                  break;

              case 2:
                  // Caesar Decrypt
                  {
                      char inputText[256];
                      std::cout << "Enter the text to decrypt: ";
                      std::cin >> inputText;

                      int caesarDecryptOffset;
                      std::cout << "Enter the Caesar offset for decryption: ";
                      std::cin >> caesarDecryptOffset;

                      text = strdup(inputText);
                      result = caesarDecrypt(text, caesarDecryptOffset);

                      std::cout << "Caesar Decrypted: " << result << std::endl;

                      free(const_cast<char*>(text));
                  }
                  break;

              case 3:
                  // Affine Encrypt
                  {
                      char inputText[256];
                      std::cout << "Enter the text to encrypt: ";
                      std::cin >> inputText;

                      int affineA, affineB;
                      std::cout << "Enter the Affine parameters (a b): ";
                      std::cin >> affineA >> affineB;

                      text = strdup(inputText);
                      result = affineEncrypt(text, affineA, affineB);

                      std::cout << "Affine Encrypted: " << result << std::endl;

                      free(const_cast<char*>(text));
                  }
                  break;

              case 4:
                  // Affine Decrypt
                  {
                      char inputText[256];
                      std::cout << "Enter the text to decrypt: ";
                      std::cin >> inputText;

                      int affineDecryptA, affineDecryptB;
                      std::cout << "Enter the Affine parameters (a b) for decryption: ";
                      std::cin >> affineDecryptA >> affineDecryptB;

                      text = strdup(inputText);
                      result = affineDecrypt(text, affineDecryptA, affineDecryptB);

                      std::cout << "Affine Decrypted: " << result << std::endl;

                      free(const_cast<char*>(text));
                  }
                  break;

            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 5." << std::endl;
        }
    }

    // 5. Unload the dynamic library
    dlclose(libHandle);

    return 0;
}

