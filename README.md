# assignment1
This is my feeble attempt on completing this (late) :')

# CS 3503 – Assignment 1  
Number Base Conversion Utility

## Files
- **main.c** – Test runner program. Reads the test file, calls the functions, compares outputs, prints PASS/FAIL, and shows a summary.  
- **convert.c** – Implementation of required functions:
  - `div_convert` – converts numbers using the repeated division algorithm.
  - `sub_convert` – converts numbers using the subtraction (powers) algorithm.
  - `print_tables` – prints binary, octal, decimal, and hexadecimal values for:
    - the original number
    - the number left-shifted by 3
    - the number ANDed with 0xFF
- **a1_test_file.txt** – Provided test file with all test cases.
- **Makefile** – Automates building the project.

---

## Build & Run Instructions

To build and run the project, you can use either **gcc directly**, **the Makefile**, or run the executable on **Windows**:

### Bash (Linux/macOS/Codespaces)
Build with gcc:
```bash
gcc -std=c17 -Wall -Wextra -O2 convert.c main.c -o assignment1
