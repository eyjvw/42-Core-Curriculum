NAME = philo
NAME_BONUS = philo_bonus

SRC = philosophers
SRC_BONUS = philosophers_bonus

SOURCES = $(SRC)/main.c \
		  $(SRC)/sources/philo/ft_death.c \
		  $(SRC)/sources/philo/ft_join.c \
		  $(SRC)/sources/philo/ft_monitor.c \
		  $(SRC)/sources/philo/ft_routine.c \
		  $(SRC)/sources/philo/ft_sleep.c \
		  $(SRC)/sources/philo/ft_timestamp.c \
		  $(SRC)/sources/utils/ft_ato.c \
		  $(SRC)/sources/utils/ft_clean.c \
		  $(SRC)/sources/utils/ft_init.c \
		  $(SRC)/sources/utils/ft_parsing.c \
		  $(SRC)/sources/utils/ft_prints.c

BONUS_SOURCES = $(SRC_BONUS)/main.c \
				$(SRC_BONUS)/sources/philo/ft_fork.c \
				$(SRC_BONUS)/sources/philo/ft_kill_all.c \
				$(SRC_BONUS)/sources/philo/ft_monitor.c \
				$(SRC_BONUS)/sources/philo/ft_routine.c \
				$(SRC_BONUS)/sources/philo/ft_sleep.c \
				$(SRC_BONUS)/sources/philo/ft_timestamp.c \
				$(SRC_BONUS)/sources/philo/ft_wait.c \
				$(SRC_BONUS)/sources/utils/ft_ato.c \
				$(SRC_BONUS)/sources/utils/ft_clean.c \
				$(SRC_BONUS)/sources/utils/ft_init.c \
				$(SRC_BONUS)/sources/utils/ft_parsing.c \
				$(SRC_BONUS)/sources/utils/ft_prints.c

OBJ_DIR = obj
BONUS_OBJ_DIR = obj_bonus

OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.o))
BONUS_OBJECTS = $(addprefix $(BONUS_OBJ_DIR)/,$(BONUS_SOURCES:.c=.o))

CFLAGS = -Wall -Wextra -Werror -pthread -O3
PHILO_INC = -I philosophers/includes/
BONUS_INC = -I philosophers_bonus/includes/
RM = rm -f
CC = cc
