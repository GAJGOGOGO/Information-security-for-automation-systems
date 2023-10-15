import string
import random

def generate_password(length, alphabet):
    return ''.join(random.choice(alphabet) for _ in range(length))

def write_to_file(filename, passwords):
    with open(filename, 'w') as file:
        for password in passwords:
            file.write(password + '\n')

def main():
    # Combine uppercase and lowercase letters to create the alphabet
    alphabet = string.ascii_uppercase + string.ascii_lowercase

    password_length = 7

    # Input the number of passwords to generate
    num_passwords = int(input("Enter the number of passwords to generate: "))

    passwords = [generate_password(password_length, alphabet) for _ in range(num_passwords)]

    write_to_file('passwords.txt', passwords)

    print(f"{num_passwords} passwords generated and saved to passwords.txt.")

if __name__ == "__main__":
    main()

