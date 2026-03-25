NAME = megaphone

SOURCES = src/megaphone.cpp

OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.cpp=.o))

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -f
