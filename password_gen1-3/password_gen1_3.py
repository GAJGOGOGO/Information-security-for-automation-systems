import string
import random

# Custom alphabet containing 10 letters, 10 numbers, and 10 symbols
custom_alphabet = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'M', 'N',
                   '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                   '!', '@', '#', '$', '%', '^', '&', '*', '(', ')']

def generate_password():
    # Ensure at least one letter, one digit, and one symbol in the password
    password = [random.choice(custom_alphabet) for _ in range(4)]
    password.append(random.choice([char for char in custom_alphabet if char.isalpha()]))  # Ensure at least one letter
    password.append(random.choice([char for char in custom_alphabet if char.isdigit()]))  # Ensure at least one digit
    password.append(random.choice([char for char in custom_alphabet if char in string.punctuation]))  # Ensure at least one symbol
    random.shuffle(password)
    return ''.join(password)

def write_to_file(filename, passwords):
    with open(filename, 'w') as file:
        for password in passwords:
            file.write(password + '\n')

def main():
    # Input the number of passwords to generate
    num_passwords = int(input("Enter the number of passwords to generate: "))

    passwords = [generate_password() for _ in range(num_passwords)]

    write_to_file('passwords.txt', passwords)

    print(f"{num_passwords} passwords generated and saved to passwords.txt.")

if __name__ == "__main__":
    main()
