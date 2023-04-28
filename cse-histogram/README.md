# Part B: Histogram (5 pts)

Write a program that reads a series of positive integers from stdin and prints
out a histogram. There should be 16 bins in your histogram. The catch? You
don't know in advance the range of input values; assume the integers range
from O to some unknown positive maximum. Thus, you will need to dynamically
scale the bin size for your histogram. An example is below.

## Usage:
There are no command-line arguments.

## Requirements

You must begin with bin size 1, and double it as needed so all positive integers
observed on input fit within the histogram.

You must have 16 bins. The number '16' should appear only once in your code.

You will need an array of 16 bins to represent the number of integers observed
in each bin. You'll need to keep track of the bin size and the range of the
histogram. If you observe a value outside the range, you should double the bin
size and range - but first you need to compress the current 16 bins into the
first 8 bins. You'll likely need one loop to compute the new values for the
lower half of the bins (each bin receiving the sum of two bins' counts), and
then another to assign the new value (0) to the upper half of the bins.

(Again: the number '16' may only occur once in your code; scattering hard-coded
numbers around your code is bad style.)

Notice that in the examples below the number of bins, bin size, and histogram
range are all powers of 2.

## Input

Input is read from stdin, whether from the keyboard, redirected from a file, or
piped in from another command. Assume the input contains only integers,
separated by white space (space, tab, newline). Assume the smallest integer is
zero; ignore any negative integers. (These assumptions make it easy to use
`scanf` for your input.)

## Output

See examples at the bottom. Note that since this program reads in from stdin
until told to stop, they are not separated into inputs and outputs. Also note
that `^D` (control-D) signals end of file, and is used to indicate to the
program that there will be no further input.

## Exit
This program has no arguments and does not check its input for errors. so it
should always exit with zero status.

## Testing
Write a short bash script that demonstrates

(a) that your implementation works, and

(b) that you have thoughtfully designed test cases for both normal
operations and errors.

Running your test script as:
```
§ bash -v testing.sh ›& testing.out
```

will print each command as it runs (-v means verbose) and save the stdout and
stderr as well.

## Compilation

Again, provide a Makefile for your code. You can use the one from Part A as a
template.

## Submission

Your finished code should include:
  .gitignore
  histogram.c
  testing.out
  testing.sh
  Makefile
  README

Note: Please do not submit executables or .o files. We will generate them
ourselves with the Makefile when grading.

## Examples

Here run the program, and type a set of numbers (spread over three lines, but
it doesn't matter as long as I put space or newline between numbers), ending
with ctrI-D on the beginning of a line. (That sends OF to the program.) It then
prints a histogram, nicely labeling each line with the range of values assigned
to that bin, and printing the count of values that fell into that bin.

```
§./histogram
16 bins of size 1 for range [0, 16)
3 -4 5 1 7 0
8 0 15 12 3 5
3 3 3 3 3
^D
[ 0: 07 **
[ 1: 1] *
[ 2:
2]
[3: 3] *******
[
4:
47
Г 5: 57 **
[ 6:
67
[ 7: 77 *
[ 8: 8] *
[9: 97
[ 10: 10]
[ 11: 117
[ 12: 12] *
[ 13: 137
[ 14: 147
[ 15: 157 *
```

Now watch what happens if I input a number outside the original range of [0,16).

```
$ ./histogram
16 bins of size 1 for range [0, 16)
3 -4 5 1 7 0
8 0 15 12 3 5
18
16 bins of size 2 for range [0,32)
19 20 30 7 12
50
16 bins of size 4 for range [0, 64)
34
32
19
44
AD
「
0: 3] *****
4: 77 ****
г
8: 117 *
Г 12: 157 ***
Г 16: 197 ***
[ 20: 23⅞ *
[ 24: 27]
[28: 311 *
[ 32: 357 **
[ 36: 39]
г 40: 437
~ 44 • 477 *
[48: 51] *
г 52: 557
г 56: 597
[ 60: 637
```

Each time it sees a number outside the current range, it doubles the range and
doubles the size of each bin. (Notice also the [low:highl labels in the histogram:
