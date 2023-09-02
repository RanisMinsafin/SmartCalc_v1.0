# SmartCalc v1.0

## Introduction

SmartCalc v1.0 is a versatile calculator program developed in C language following the C11 standard. This program allows users to perform arithmetic calculations, plot graphs of functions, and includes additional features like a credit calculator and a deposit profitability calculator. The code is structured and follows the Google style guide.

## Features

### Basic Calculator

- SmartCalc v1.0 can handle both integer and real numbers with a decimal point and supports exponential notation.
- Users can input arithmetic expressions in infix notation.
- Arithmetic expressions can be arbitrarily complex and include brackets.
- Arithmetic operations and mathematical functions supported:
  
  | Operator/Function | Infix Notation (Classic) | Prefix Notation (Polish) | Postfix Notation (Reverse Polish) |
  | ------------------ | ------------------------ | ------------------------ | --------------------------------- |
  | Brackets           | (a + b)                  | (+ a b)                  | a b +                           |
  | Addition           | a + b                    | + a b                    | a b +                           |
  | Subtraction        | a - b                    | - a b                    | a b -                           |
  | Multiplication     | a * b                    | * a b                    | a b *                           |
  | Division           | a / b                    | / a b                    | a b /                           |
  | Power              | a ^ b                    | ^ a b                    | a b ^                           |
  | Modulus            | a mod b                  | mod a b                  | a b mod                         |
  | Unary plus         | +a                       | +a                       | a+                              |
  | Unary minus        | -a                       | -a                       | a-                              |

- The program calculates expressions with precision up to 7 decimal places.
- Users can input up to 255 characters.
- Domain and codomain of a function are limited to at least numbers from -1,000,000 to 1,000,000.

### Graph Plotting

- SmartCalc v1.0 can plot graphs of functions given by expressions in infix notation with the variable _x_.
- The graphs include coordinate axes, scale marks, and an adaptive grid.
- Users can specify the domain and codomain for plotting.

### Credit Calculator

- SmartCalc v1.0 includes a credit calculator that allows users to calculate various aspects of a credit.
- Input parameters include the total credit amount, term, interest rate, and type (annuity or differentiated).
- Output includes the monthly payment, overpayment on credit, and total payment.

### Deposit Profitability Calculator

- SmartCalc v1.0 includes a deposit profitability calculator for calculating the profitability of a deposit.
- Input parameters include deposit amount, deposit term, interest rate, tax rate, periodicity of payments, capitalization of interest, replenishments list, and partial withdrawals list.
- Output includes accrued interest, tax amount, and deposit amount by the end of the term.

## Building and Running

- SmartCalc v1.0 is built using the C11 standard with the gcc compiler.
- The code is organized in the 'src' folder.
- A Makefile is provided with standard targets for GNU programs: all, install, uninstall, clean, dvi, dist, test, gcov_report.
- Users can build and run the program with the provided Makefile.

## GUI Framework

- SmartCalc v1.0 features a GUI implementation based on a GUI library with API support for C89/C99/C11.
- For Linux, supported libraries include GTK+, CEF, and Qt.
- For macOS, supported libraries include GTK+, Nuklear, raygui, microui, libagar, libui, IUP, LCUI, CEF, and Qt.

## Conclusion

SmartCalc v1.0 is a powerful calculator program that combines ease of use with advanced features, making it a versatile tool for various mathematical needs, including calculations, graph plotting, and financial calculations.