*This project has been created as part of the 42 curriculum by tlogtenb*

# Codexion

## Description

A project mimicking the classic philosophers problem requiring to work with threads and mutexes and different algorithm strategies.
This project aims to visualize how different threads are able to access shared resources and go around race conditions.

## Instructions

### Building

Requirements:
- gcc or cc

To build, run:
```sh
make    # or make all
```

### Running

Simply run:
```sh
./codexion <number of coders> <time to burnout>
			<time to compile> <time to debug>
			<time to refactor> <number of compiles required>
			<dongle cooldown> <sheduler: "fifo"/"edf">
```

If wrong instructions are given a help usage message will be displayed telling what parameters are accepted.

## Resources

- Official man pages for threads
- Explanations on how philosophers problem works

## Blocking cases handled

Deadlock prevention using various different mutex' to make sure nothing ever reads stale shared resources as well as implementing `fifo` and `edf` correctly to prevent deadlocks that can occur with shared dongles.
Also by minimizing holding and waiting states with dongles as well as circular waits, this is all done together to not trigger Coffman conditions which explain when a deadlock will occur.
Further, `fifo` and `edf` algorithms will handle cooldowns and burnout detections to prevent unnecessary starvation of coders/threads.

## Thread synchronization mechanisms

I make use of the `pthread_mutex_t` type to define a shared resource lock and together with the `pthread_cond_t` to define when threads need to be restarted or stopped.
`pthread_mutex_t` creates a mutex type which in simple words is in a way a simple boolean lock, which together with threads that have to access the same resources can prevent read or writing at the same time across different threads.
The general workflow is as follows:
- Thread 1 needs to access a global variable called `count`
- Thread 1 first checks the mutex variable that specifies whether the global `count` is not currently being written to
  - If the mutex is already locked, it holds and waits the thread until the mutex is unlocked
  - If the mutex is not locked, it will lock that mutex making the mutex state define and tell other threads to not access the `count` variable
- Thread 1 will then increment, decrement or perform actions with the `count` variable
- Thread 1 will then unlock the mutex, which will allow any other thread that wants access to the `count` variable to then access it.
