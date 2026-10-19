NAME = AnimalWithBrain

SOURCES = src/Animal.cpp \
		  src/Brain.cpp \
		  src/Cat.cpp \
		  src/Dog.cpp \
		  src/main.cpp \
		  src/WrongAnimal.cpp \
		  src/WrongCat.cpp

OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.cpp=.o))
DEPS = $(OBJECTS:.o=.d)

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I includes/
RM = rm -f
