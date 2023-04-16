# Random Exercises in C++

# oddeven
Main thread spawns two threads accessing a global resource, say an int variable
and then waits for both of those to exit and exits itself.

An "odd" thread waits (not consuming CPU) for the variable to become odd and
then increments it.  If the value of the variable becomes 100, thread exits.

An "even" thread waits (not consuming CPU) for the variable to become even and
then increments it.  If the value of the variable becomes 100, thread exits.

Done using c++ threads.

# The Rest

Exercises for https://www.coursera.org/learn/c-plus-plus-white/home/info
