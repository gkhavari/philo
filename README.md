*This project has been created as part of the 42 curriculum by gkhavari*

# Philosophers

## Description
This project implements the classic Dining Philosophers problem, a fundamental synchronization problem in computer science introduced by Edsger W. Dijkstra. The goal is to simulate a group of philosophers who must alternate between thinking, sleeping and eating, sharing a limited number of forks. The challenge lies in preventing deadlock (where all philosophers hold one fork and wait indefinitely) and starvation (where some philosophers never get to eat).

The implementation is written in C and uses POSIX threads (pthreads) for concurrency and mutexes for synchronization. Each philosopher is represented by a thread, and forks are protected by mutexes to ensure mutual exclusion. The program monitors the philosophers' states to detect death from starvation and manages the simulation lifecycle. The simulation stops once a philosopher dies or when all philosophers have eaten the required number of times (if the `times_must_eat` parameter is specified).

## Key Features
- **Deadlock Prevention**: Forks are acquired in a consistent order (lower index first) to avoid circular waiting.
- **Starvation Prevention**: Even-numbered philosophers have a small initial delay to stagger fork access and promote fair eating opportunities.
- **Real-time Monitoring**: A dedicated monitor thread continuously checks for philosopher deaths.
- **Thread-safe Output**: All status messages are printed using a mutex to prevent output interleaving.
- **Edge Case Handling**: Special logic for single philosopher scenarios.

## Instructions

### Compilation
To compile the program, navigate to the `philo` directory and run the following command:
```
make
```
This will generate the executable `philo`.

### Execution
Run the program with the following command:
```
./philo <num_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [times_must_eat]
```
Use `./philo --help` to display usage information.

Parameters:
- `num_philosophers`: The number of philosophers and forks.
- `time_to_die`: Time in milliseconds after which a philosopher dies if they haven't started eating.
- `time_to_eat`: Time in milliseconds it takes for a philosopher to eat.
- `time_to_sleep`: Time in milliseconds a philosopher spends sleeping.
- `times_must_eat` (optional): The number of times each philosopher must eat before the simulation stops. If not provided, the simulation runs until a philosopher dies.

Example:
```
./philo 5 800 200 200 7
```

### Debugging
To compile the program with debug symbols for use with debugging tools like gdb, run:
```
make debug
```
This adds the `-g` flag to the compiler options, allowing you to step through the code and inspect variables during execution.

## Edge Cases
- **Single Philosopher**: With only one philosopher, they can only pick up one fork and will inevitably die, as they cannot eat without two forks.
- **High Number of Philosophers**: The program handles up to approx. 200 philosophers efficiently.

## Resources
- **POSIX Threads Programming**: Official documentation for pthreads, available at [pubs.opengroup.org](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/pthread.h.html).
- **Concurrency and Synchronization Tutorials**: Articles on mutexes, threads, and deadlock prevention, such as those on GeeksforGeeks or IBM Developer.
- **Peers at the 42 School Vienna**: This project is part of the 42 programming school curriculum, focusing on low-level programming and system concepts.

### AI Usage
ChatGPT was used throughout the development process for:
- Debugging assistance by suggesting potential fixes for thread synchronization issues.
- Interpreting and understanding output from Valgrind's Helgrind tool for faster debugging of thread-related issues.
