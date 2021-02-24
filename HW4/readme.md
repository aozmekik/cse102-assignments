# CSE102 – Computer Programming (Spring 2018)

# Homework #

## Handed out : 23:00 Tuesday March 27, 2018.

## Due : 23:55 Friday April 6, 2018.

**Hand-in Policy** : Via Moodle. No late submissions will be accepted.
**Collaboration Policy** : No collaboration is permitted.
**Grading** : This homework will be graded on the scale of 100.
**Contact:** Tugbagul Altan Akin (tualtan@gtu.edu.tr)

**Description** : In this homework, you will implement several functions as described below. You are
expected to reflect what you have learned in class up to this point.

You are provided with six separate files (in HW4_Src.rar):

- **main.c:** Contains the main function. You are not expected to modify this file in your
    submission. You may modify it for your own testing and debugging needs.
- **hw4_io.h:** Contains the declarations of input and output related functions for this homework.
    You are not expected to modify this file in your submission. You may modify it for your own
    testing and debugging needs.
- **hw4_io.c:** This file will contain your implementation of the functions declared in the associated
    header file. The details of these functions’ behaviors are provided below.
- **hw4_lib.h:** Contains the declarations of some more functions for this homework. You are not
    expected to modify this file in your submission. You may modify it for your own testing and
    debugging needs.
- **hw4_lib.c:** This file will contain your implementation of the functions declared in the
    associated header file. The details of these functions’ behaviors are provided below.
- **makefile:** This is a makefile provided for you to use for compiling and testing your code.

The following provides the details of the functions to be implemented:

- **int read_polynomial3(double * a0, double * a1, double * a2, double * a3)** : Reads four
    numbers from the user as the coefficients of a degree-3 polynomial of the form:
       푝(푥)=푎 3 푥^3 +푎 2 푥^2 +푎 1 푥+푎 0
- **int read_polynomial4(double * a0, double * a1, double * a2, double * a3, double * a4)** : Reads
    five numbers from the user as the coefficients of a degree-4 polynomial of the form:
       푝(푥)=푎 4 푥^4 +푎 3 푥^3 +푎 2 푥^2 +푎 1 푥+푎 0
- **void write_polynomial3(double a0, double a1, double a2, double a3)** : Writes the polynomial
    in a pretty format. No sign replications should be allowed. For example:
       write_polynomial3(-1.0,1.0,-3.2,0.0);
    should print:
       - x^3+x^2-3.2x
- **void write_polynomial4(double a0, double a1, double a2, double a3, double a4)** : Writes the
    polynomial in a pretty format like write_polynomial3.


- **double integral(double f(double x), double xs, double xe, double delta)** : Numeric calculation
    of the integral of the function f within the range [xs,xe]. The given parameter delta provides
    the step size for the integration.
- **double integral2(double f(double x, double y), double xs, double xe, double ys, double ye,**
    **double delta)** : Numeric calculation of the integral of a two input function within the given
    range [xs,xe] and [ys,ye].
- **int derivatives(double f(double a), double x, double eps, double * d1, double * d2)** : Numeric
    calculation of first (d1) and second (d2) derivative of a given function (note that the argument
    eps stands for 휖). The function will return -1 if there is a problem (such as division by 0), 1
    otherwise.
    For the first derivative, use the central difference as follows:

```
푓′(푥)≈
```
### 푓(푥+휖)−푓(푥−휖)

### 2 휖^

```
For the second derivative, use the central difference as follows:
```
```
푓′′(푥)≈
```
### 푓(푥+휖)− 2 푓(푥)+푓(푥−휖)

### 휖^2

- **int compare_derivatives(double f(double a), double d1(double b), double d2(double b),**
    **double x, double eps, double * e1, double *e2)** : Tests the error in numeric calculation of
    derivatives vs. actual derivatives given by functions d1 and d2. It returns the absolute
    difference between the calculated derivatives and analytically provided ones in arguments e
    and e2.
- **int find_roots(double f(double x), double * x1, double * x2, double * x3, double * x4)** : Finds
    the real root of the function returning the number of roots found and the roots in the
    arguments x1, x2, x3 and x4. If less than four real roots are found, for example only three is
    found, the parameter x4 should return 0.0.

**Useful Hints:** Here are some things that might make your development a bit easier.

- For testing your code use files for inputing data and getting the output. For example:
    $ hw4 < input.txt > output.txt
will get the input from the file “input.txt” and will write the output to the file “output.txt”. This
way you can easily make a lot of entries to test your code without using the keyboard again
and again.
- Use the makefile to compile your code. You can add a run case to your makefile to do the
    compilation and testing with one simple make command.

**What to hand in:** You are expected to hand in a zip or rar file including the six files above. Your
implementations should be completed in “hw4_io.c” and “hw4_lib.c”. The rest of the files should not
be modified from their original versions.

- **HW4_lastname_firstname_studentno.rar / HW4_lastname_firstname_studentno.zip**


