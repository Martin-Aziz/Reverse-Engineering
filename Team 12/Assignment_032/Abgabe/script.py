import subprocess
import os

def run_crackme_2(password):
    def run_crackme(executable_path, input_text):
        try:
            result = subprocess.run([executable_path], input=f'{input_text}\n', capture_output=True, encoding='utf-8', timeout=10)
            return result.stdout.strip().split(':')

        except FileNotFoundError:
            print("Error: Executable not found.")
        except subprocess.TimeoutExpired:
            print("Error: Process timed out.")
        except subprocess.CalledProcessError as e:
            print(f"Error: {e}")
        except Exception as e:
            print(f"Error: {e}")

    if __name__ == "__main__":
        script_path = os.path.abspath(__file__)
        script_dir = os.path.dirname(script_path)
        executable_path = os.path.join(script_dir, 'crackme')

        input_text = str(password)
        output_lines = run_crackme(executable_path, input_text)

        if output_lines:
            input_entered = False
            for line in output_lines:
                if not input_entered:
                    print(f'{line}: {password}')
                    input_entered = True
                    continue
                print(line)

def run_crackme_1(password, binary_code):
    def run_crackme(executable_path, input1, input2):
        try:
            result = subprocess.run([executable_path], input=f'{input1}\n{input2}\n', capture_output=True, encoding='utf-8', check=True)
            lines = result.stdout.strip().splitlines()

            input1_entered = False
            for line in lines:
                if not input1_entered:
                    print(f'{line}: {input1}')
                    input1_entered = True
                else:
                    output_parts = line.split("?", 1)
                    output_part1 = output_parts[0] if len(output_parts) > 0 else ''
                    output_part2 = output_parts[1] if len(output_parts) > 1 else ''
                    print(f'{output_part1}: {input2}')
                    print(output_part2)
        except subprocess.CalledProcessError as e:
            print(f"Error running '{executable_path}': {e}")
        except FileNotFoundError as e:
            print(f"File not found: {e}")
        except Exception as e:
            print(f"An error occurred: {e}")

    if __name__ == "__main__":
        script_path = os.path.abspath(__file__)
        script_dir = os.path.dirname(script_path)
        executable_path = os.path.join(script_dir, 'crackme')

        input1 = str(password)
        input2 = str(binary_code)
        run_crackme(executable_path, input1, input2)

def main_menu():
    print(
'''
                             / \\  //\\
                  |\\___/|      /   \\//  .\\
                  /O  O  \\__  /    //  | \\ \\           * Reverse Engineering! *
                 /     /  \\/_/    //   |  \\  \\ 
                 @___@'    \\/_   //    |   \\   \\ 
                    |       \\_|/   ,/\\,,_______\\
                    |    \    /   |    /    |   \\
                    |     \\_ /  |  \\//    \   |
                   \\  /  __  \\   /  /   __/   /
                    \\  /   \\_\\_  /  |  /_____/  |
                     \\____\\___/  |  /          /
                      \\_       \\/  /          |
                      | \\  |/  \\/  |          |
                      |  \\//\\__/    \\         /  
                     _|  /  \\/   |  \\       /\\
                    /   /   /  |   \\  \\_   /
                   /_____/   |____|\\   \\ |
                   |   \\______|----|_\\   \\  \\
                   |_________   \\_____|   \\   \\
                              \\__\\  \\__\\    \\   \\
                                 |   |       \\   \\
                                 |   |        \\___\\
'''
)
    print("Select the information you have:")
    print("1. Input")
    print("2. Password and Binary Access Code")
    print("3. Exit")
    choice = input("Enter your choice: ")

    if choice == '1':
        password = input("Enter your Input: ")
        run_crackme_2(password)
    elif choice == '2':
        password = input("Enter password: ")
        binary_code = input("Enter binary access code: ")
        run_crackme_1(password, binary_code)
    elif choice == '3':
        print("Exiting...")
    else:
        print("Invalid choice. Please enter a valid option.")

if __name__ == "__main__":
    main_menu()
