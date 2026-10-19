NAME = Base

SOURCES = src/A.cpp \
		  src/Base.cpp \
		  src/B.cpp \
		  src/C.cpp \
		  src/main.cpp

OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.cpp=.o))
DEPS = $(OBJECTS:.o=.d)

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I includes/
RM = rm -f
