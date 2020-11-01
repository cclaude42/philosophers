# philosophers

42 project about inter-process communication. A program that can monitor multiple instances of itself, either processes or threads, using semaphores or mutexes.

## Final grade : 100/100

Mandatory part : 100/100

### Concept

Philosophers (represented by parts of a program) sit around a table, with a big plate of spaghetti at its center. They each have a fork, but they need two forks to eat ; so they need to borrow their neighbor's fork to eat.

Of course, if they borrow a neighbor's fork, the neighbor can't use the fork. The processes / threads must communicate, to know the state of the forks (and of the other philosophers) at all times. There must also be a parent process that monitors everything.

### One, Two, Three...

**philo_one** does this using **threads** as philosophers, and **mutexes** as forks.

**philo_two** uses **threads** as well, but uses **semaphores** as forks instead.

**philo_three** forks itself, making philosophers **processes**. Its forks are **semaphores**. It uses threads too, but only for monitoring.

<p align="center">
  <img src="https://i.imgur.com/OFhqnqw.png" width="100%" />
</p>

### How to use it

Using ``make`` in the philo_one directory will create the ``philo_one`` executable. Same for philo_two and philo_three.

You run it specifying, in order :
* The number of philosophers
* The time in milliseconds until a philosopher dies from starvation
* The time in milliseconds it takes for a philosopher to eat
* The time in milliseconds it takes for a philosopher to sleep
* (Optional) The number of meals before the program stops

```
./philo_one 6 400 200 100 5
```

Here, the program will create 6 philosophers, who will die if they go without eating for 400 milliseconds. It takes them 200 milliseconds to eat, and 100 milliseconds to sleep. The program will stop after each philosopher has had 5 meals (or if any one of them dies prematurely).

### Output

The program outputs every action with a timestamp (in milliseconds) and the philosopher's number. For example, if Philosopher 2 starts eating 412 milliseconds after the beginning of the program, it will output :

```
412 #2 is eating
```

### Tester : aristotle.sh

This is Work In Progress. Use at your own risk !

Theoretically it's supposed to try a wide range of different parameters to save you the hassle of doing so. Still need to fine tune a few things.
