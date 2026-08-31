# philosophers

*This project has been created as part of the 42 curriculum by sbonneau.*

## Description

`philosophers` is a concurrency project based on the dining philosophers problem.

- Mandatory version (`philo`) uses **threads** and **mutexes**.
- Bonus version (`philo_bonus`) uses **processes** and **semaphores**.

Goal: avoid deadlocks/starvation while respecting timing constraints.

## Instructions

### Program Arguments

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

All times are in milliseconds.

### Build

```bash
make
make bonus
```

### Makefile rules

- `make` / `make all` : build `philo`
- `make bonus` : build `philo_bonus`
- `make clean` : remove object files
- `make fclean` : remove binaries and objects
- `make re` : rebuild mandatory
- `make re_bonus` : rebuild bonus

## Algorithm & Design

### Deadlock avoidance — ordered fork acquisition

Every philosopher needs two forks, so the naive "left then right" order lets all
`N` philosophers hold their left fork and wait forever on their right one. Each
philosopher instead locks the two mutexes in ascending **address** order
(`ft_check()` in `src/philo/ft_routine.c`). That imposes a global resource
hierarchy: the cycle in the wait-for graph is broken, so a deadlock is
impossible by construction — no timeouts or `trylock` retries needed.

### Starvation avoidance — parity start + a real thinking phase

Deadlock freedom is not enough: a philosopher that re-grabs its forks the moment
it releases them can keep a neighbour from ever eating. Two things space them
out:

- **Parity stagger.** Even-numbered philosophers wait `time_to_eat` before their
  first meal, so odd and even philosophers settle into two alternating groups
  and every philosopher is served roughly every `2 * time_to_eat`.
- **Non-zero thinking.** After sleeping, a philosopher thinks for half of the
  slack in its cycle, `(time_to_die - time_to_eat - time_to_sleep) / 2`, before
  competing for forks again.

Without these, `200 800 200 200` starves a philosopher within the first 800 ms.

### Death detection

A single monitor loop (the main thread in the mandatory part, one thread per
process in the bonus) polls every 800 µs — well inside the 10 ms the subject
allows for reporting a death. Timestamps and meal counters are read under the
`meal` mutex/semaphore, never unsynchronised.

### Log integrity

The death flag is tested **while the print lock is held**, so a philosopher that
was already queued on the lock when the simulation ended cannot print after the
`died` line. Each line is emitted with a single `write()` call: logs can never
interleave, and nothing is lost in a stdio buffer when the bonus philosophers —
separate processes — are killed at the end of the simulation.

### Single philosopher

With one philosopher there is only one fork. They take it, wait, and die: the
special case is handled explicitly instead of blocking forever on a second fork
that does not exist.

## Concurrency Invariants

| Shared state | Guarded by | Notes |
|---|---|---|
| `last_meal_time`, `meals_eaten`, `done` | `meal` mutex (bonus: `meal` semaphore) | Written by the philosopher, read by the monitor |
| `someone_died` | `dead` mutex | Bonus signals the parent through the `dead` semaphore |
| stdout | `print` mutex / semaphore | Death check happens inside the critical section |

Both parts are verified clean under ThreadSanitizer, and the mandatory part
under AddressSanitizer/UBSan as well.

## Project Structure

- `philosophers/` : mandatory (threads/mutex)
- `philosophers_bonus/` : bonus (processes/semaphores)
- `mk/` : shared Makefile fragments

## Notes

- Output timing naturally varies depending on scheduler timing.
- Concurrency correctness is prioritized (safe lock order + synchronized shared-state checks).

## Resources

- [pthread_create(3)](https://man7.org/linux/man-pages/man3/pthread_create.3.html)
- [pthread_mutex_lock(3p)](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [sem_open(3)](https://man7.org/linux/man-pages/man3/sem_open.3.html)
- [fork(2)](https://man7.org/linux/man-pages/man2/fork.2.html)
- [42 Norminette](https://github.com/42School/norminette)

## AI Usage

AI assistance was used for:

1. Concurrency review — locating data races with ThreadSanitizer, and reviewing
   lock ordering and the starvation behaviour at high philosopher counts.
2. Build refactor (`mk/` split and include normalization).
3. Documentation.

The design decisions above, the algorithm, and the implementation are the
author's; AI was used to review and stress-test them, not to generate them.
