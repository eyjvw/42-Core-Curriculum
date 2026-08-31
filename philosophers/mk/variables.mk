NAME = philo
NAME_BONUS = philo_bonus

SRC = philosophers
SRC_BONUS = philosophers_bonus

SOURCES = $(SRC)/main.c \
		  $(SRC)/src/philo/ft_death.c \
		  $(SRC)/src/philo/ft_join.c \
		  $(SRC)/src/philo/ft_monitor.c \
		  $(SRC)/src/philo/ft_routine.c \
		  $(SRC)/src/philo/ft_sleep.c \
		  $(SRC)/src/philo/ft_timestamp.c \
		  $(SRC)/src/utils/ft_ato.c \
		  $(SRC)/src/utils/ft_clean.c \
		  $(SRC)/src/utils/ft_error.c \
		  $(SRC)/src/utils/ft_init.c \
		  $(SRC)/src/utils/ft_parsing.c \
		  $(SRC)/src/utils/ft_prints.c

BONUS_SOURCES = $(SRC_BONUS)/main.c \
				$(SRC_BONUS)/src/philo/ft_fork.c \
				$(SRC_BONUS)/src/philo/ft_kill_all.c \
				$(SRC_BONUS)/src/philo/ft_monitor.c \
				$(SRC_BONUS)/src/philo/ft_routine.c \
				$(SRC_BONUS)/src/philo/ft_sleep.c \
				$(SRC_BONUS)/src/philo/ft_timestamp.c \
				$(SRC_BONUS)/src/philo/ft_wait.c \
				$(SRC_BONUS)/src/utils/ft_ato.c \
				$(SRC_BONUS)/src/utils/ft_clean.c \
				$(SRC_BONUS)/src/utils/ft_error.c \
				$(SRC_BONUS)/src/utils/ft_init.c \
				$(SRC_BONUS)/src/utils/ft_parsing.c \
				$(SRC_BONUS)/src/utils/ft_prints.c

OBJ_DIR = obj
BONUS_OBJ_DIR = obj_bonus

OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.o))
BONUS_OBJECTS = $(addprefix $(BONUS_OBJ_DIR)/,$(BONUS_SOURCES:.c=.o))

CFLAGS = -Wall -Wextra -Werror -pthread -O3
PHILO_INC = -I philosophers/includes/
BONUS_INC = -I philosophers_bonus/includes/
RM = rm -f
CC = cc
