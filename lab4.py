def is_prime(num):
    """Check if a number is prime"""
    if num < 2:
        return False
    for i in range(2, int(num**0.5) + 1):
        if num % i == 0:
            return False
    return True

def gcd(a, b):
    """Calculate the greatest common divisor"""
    while b:
        a, b = b, a % b
    return a

def mod_inverse(a, m):
    """Calculate the mode inverse element"""
    m0, x0, x1 = m, 0, 1
    while a > 1:
        q = a // m
        m, a = a % m, m
        x0, x1 = x1 - q * x0, x0
    return x1 + m0 if x1 < 0 else x1

def generate_keypair(p, q):
    """Generate RSA key pairs"""
    if not (is_prime(p) and is_prime(q)):
        raise ValueError("p and q must be primes")
    
    n = p * q
    phi = (p - 1) * (q - 1)

    # 选择一个与phi互质的整数e
    e = 7  # 通常选择65537作为e

    # 计算e的模反元素d
    d = mod_inverse(e, phi)

 # 输出公钥和私钥
    print(f"公钥：(n={n}, e={e})")
    print(f"私钥：(n={n}, d={d})")
    
    # 返回公钥和私钥
    return ((n, e), (n, d))

def encrypt(message, public_key):
    """加密消息"""
    n, e = public_key
    cipher_text = [pow(ord(char), e, n) for char in message]
    return cipher_text,n

def decrypt(cipher_text, private_key, n):
    """解密消息"""
    _, d = private_key
    decrypted_message = ''.join([chr(pow(char, d, n)) for char in cipher_text])
    return decrypted_message


def main():
    p = int(input("enter prime p: "))
    q = int(input("enter prime q: "))

    if not (is_prime(p) and is_prime(q)):
        print("p and q must be primes.")
        return

    public_key, private_key = generate_keypair(p, q)

    while True:
        print("\nChoose a function:")
        print("1. Encrypt")
        print("2. Decrypt")
        print("3. Quit")

        choice = input("Choose(1/2/3): ")

        if choice == '1':
            message = input("Enter the text to be encrypted: ")
            cipher_text, n = encrypt(message, public_key)
            print(f"Encryption results: {cipher_text}, n={n}")
        elif choice == '2':
            cipher_text = eval(input("Enter to be decrypted (as a list): "))
            n = int(input("Enter n: "))
            decrypted_message = decrypt(cipher_text, private_key, n)
            print(f"Decryption results: {decrypted_message}")
        elif choice == '3':
            break
        else:
            print("Invalid choice.")

if __name__ == "__main__":
    main()
11