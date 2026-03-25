NAME = Zombie

SOURCES = src/main.cpp src/newZombie.cpp src/randomChump.cpp src/Zombie.cpp

OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.cpp=.o))

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I includes/
RM = rm -f
