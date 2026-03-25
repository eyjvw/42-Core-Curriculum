NAME = Violence

SOURCES = src/main.cpp src/HumanA.cpp src/HumanB.cpp src/Weapon.cpp

OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.cpp=.o))

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I includes/
RM = rm -f
