NAME = Materia

SOURCES = src/AMateria.cpp \
		  src/Character.cpp \
		  src/Cure.cpp \
		  src/Ice.cpp \
		  src/main.cpp \
		  src/MateriaSource.cpp

OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.cpp=.o))
DEPS = $(OBJECTS:.o=.d)

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I includes/
RM = rm -f
