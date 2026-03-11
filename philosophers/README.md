# philosophers

*This project has been created as part of the 42 curriculum by sbonneau.*

## Description

`philosophers` is a concurrency project based on the dining philosophers problem.

- Mandatory version (`philo`) uses **threads** and **mutexes**.
- Bonus version (`philo_bonus`) uses **processes** and **semaphores**.

Goal: avoid deadlocks/starvation while respecting timing constraints.

## Program Arguments

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

All times are in milliseconds.

## Build

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

## What Was Refactored

### Build system

- Root `Makefile` was refactored into:
  - `mk/variables.mk`
  - `mk/colors.mk`
  - `mk/rules.mk`
- Include paths were normalized to compile with explicit include directories, avoiding relative include directives in source files.

### Mandatory fixes (`philo`)

- Fixed potential segfault in `ft_print_error` when called with `NULL` mutex.
- Added a dedicated `meal` mutex to protect shared fields:
  - `last_meal_time`
  - `meals_eaten`
  - `done`
- Fixed lock-order issues by always locking forks in deterministic pointer order.
- Improved thread-create failure handling (set death flag, join already-started threads, then clean).
- Avoided global cleanup from `ft_timestamp` error path inside worker context.

### Bonus fixes (`philo_bonus`)

- Fixed potential segfault in `ft_print_error` with `NULL` semaphore.
- Added safety checks for `sem_open` failures.
- Guarded `sem_close` against `NULL`/`SEM_FAILED` handles.
- Removed unsafe cleanup calls from child monitor/routine exit paths.
- Detached monitor thread in child to avoid thread-resource leak.
- Fixed `must_eat` completion condition (`>=` instead of `>`).
- Added fork failure handling and child reaping in kill path to reduce zombie leaks.

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

AI assistance (GitHub Copilot) was used for:

1. Concurrency review (mutex/lock-order/race fixes)
2. Build refactor (`mk/` split and include normalization)
3. Documentation generation

Core project implementation and algorithmic behavior remain aligned with the original design.
