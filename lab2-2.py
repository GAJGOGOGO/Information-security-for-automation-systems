import random

# 资源和权限
resources = ['Resource1', 'Resource2', 'Resource3', 'Resource4', 'Resource5', 'Resource6']
permissions = ['read', 'write', 'execute']

# 用户信息
users = {
    'admin': {resource: permissions for resource in resources},
    'user1': {resources[random.randint(0, 5)]: random.sample(permissions, random.randint(0, 3)) for _ in range(3)},
    'user2': {resources[random.randint(0, 5)]: [random.choice(permissions)] for _ in range(2)}
}

# 当前用户
current_user = None

# 函数：显示用户信息和权限
def display_user_info(user):
    print(f"User: {user}")
    print("Permissions:")
    for resource, perms in users[user].items():
        print(f"{resource}: {', '.join(perms)}")

# 函数：切换用户
def switch_user():
    global current_user
    username = input("Enter username (or 'quit' to exit): ")
    if username == 'quit':
        return False
    elif username in users:
        current_user = username
        print(f"Switched to user: {username}")
        display_user_info(username)
    else:
        print("Invalid username. Please try again.")
    return True

# 函数：执行权限操作
def perform_permission_operation():
    global current_user
    resource = input("Enter the resource you want to operate on: ")
    permission = input("Enter the permission you want to check: ").strip().lower()

    if current_user in users and resource in users[current_user]:
        if permission in users[current_user][resource]:
            print(f"{current_user} has {permission} permission for {resource}.")
        else:
            print(f"{current_user} does not have {permission} permission for {resource}.")
    else:
        print(f"{current_user} does not have access to {resource}.")

# 主程序
def main():
    global current_user
    print("Welcome to the resource management program!")

    while True:
        if not current_user:
            if not switch_user():
                break

        command = input("Enter a command (switch/operate/quit): ").strip().lower()

        if command == 'switch':
            if not switch_user():
                break
        elif command == 'operate':
            perform_permission_operation()
        elif command == 'quit':
            break
        else:
            print("Invalid command. Please try again.")

if __name__ == "__main__":
    main()
