# Calculator

This is a versatile calculator program written in C that supports various mathematical operations, including standard mathematical calculations, trigonometric functions and others, matrix operations,  and basic operations on complex numbers.

## Features

- [Arithmetic opreatins](#Arithmetic-operation)
- [Mathematical unctions](#Mathematical-Functions)
- [Matrix operations](#Matrix-oprations)
- [Basic operations on complex numbers](#Complex-numbers)



### Arithmetic-operations

This calculator can perform the simple mathematical operations on numbers such as: 

* `+` Addition
* `-` Subtraction
* `*` Multiplication
* `/` Division
* `%` Modulus
* `^` Exponent

wich are entered in infix notations then converted to postfix notation before being computed (RPN).

### Mathematical-Functions

Computes trigonometric functions, and other functions listed below.

* `sin(...)` Sine.
* `cos(...)` Cosine.
* `tan(...)` Tangent.
* `arcsin(...)` Arcsine.
* `arccos(...)` Arccosine.
* `arctan(...)` Arctangent.
* `sqrt(...)` Square root.
* `cbrt(...)` Cube root.
* `log(...)` Logarithm.
* `exp(...)` Exponentiation (e^x).
* `abs(...)` Absolute value.
* `roundup(...)` Round up.
* `rounddown(...)` Round down.
* `min(...)` Minimum.
* `max(...)` Maximum.
* `sum(...)` Summation.
* `mean(...)` Mean.
* `var(...)` Variance.
* `avg(...)` Mean.
* `median(...)` Median.

This functions can be evaluated alongside the arithmetic oprations. eg. you can compute `6*(2^4) - 3*cbrt(9 * tan(3.14 / 2))`.

### Matrix

Suppots operations on matrix which are: 

* `Addition`
* `Subtraction`
* `Multiplication`
* `Determinant`
* `Transpose`
* `Inverse`

Can also perform matrix algorithms like
* `Reduced row echelon form.`
* `Solving simultaneous equatons.`
(more)

### Complex-numbers

Supports basic oprations on complex numbers such as

* `Addition`
* `Subtraction`
* `Multiplication`
* `Division`

### Prerequisites

- Ensure that you have a C compiler installed on your system (e.g., GCC).

## Extra Information
For extra informations on usage, check the man page.