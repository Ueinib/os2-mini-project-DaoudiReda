OS2 Mini Project — PlayStation Threads & Synchronisation   (test tp):

  This project was developed for the Operating Systems 2 mini project.

  It contains two exercises using POSIX Threads (pthread) and Semaphores in C.

Exercise 1 — Parallel Threads

In this exercise, we simulate players playing different games on a PlayStation console.

We create:

8 Football players
4 Super Mario players
4 Need For Speed players

Each player is represented by a thread.

Every thread:

Prints a waiting message
Sleeps for a random time between 1 and 3 seconds
Prints a finish message

All threads are created in parallel and joined before the program exits.

Exercise 2 — Synchronisation with Semaphores

In this exercise, we add synchronisation rules using semaphores.

Rules:

Different games cannot use the PlayStation at the same time
Players of the same game can play together
Maximum simultaneous players:
Football → 4
Super Mario → 2
Need For Speed → 1

We use:

pthread for threads
semaphore.h for semaphores
Mutex semaphore to protect shared variables
Counting semaphores to limit player capacity
 
Technologies Used:
Language: C
POSIX Threads (pthread)
POSIX Semaphores


Daoudi REDA L3 Grp 3 24/05/2026
