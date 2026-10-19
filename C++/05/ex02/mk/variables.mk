NAME = Bureaucrat

SOURCES = src/AForm.cpp \
		  src/Bureaucrat.cpp \
		  src/main.cpp \
		  src/PresidentialPardonForm.cpp \
		  src/RobotomyRequestForm.cpp \
		  src/ShrubberyCreationForm.cpp

OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.cpp=.o))
DEPS = $(OBJECTS:.o=.d)

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I includes/
RM = rm -f
