NAME = ircserv

SOURCES = srcs/main.cpp \
		  srcs/Server.cpp \
		  srcs/Client.cpp \
		  srcs/Channel.cpp \
		  srcs/RPL.cpp \
		  srcs/MSG.cpp \
		  srcs/Package.cpp \
		  srcs/Ft.cpp \
		  srcs/Errors.cpp \
		  srcs/cmds/CMD.cpp \
		  srcs/cmds/Mode.cpp \
		  srcs/cmds/Join.cpp \
		  srcs/cmds/Invite.cpp \
		  srcs/cmds/Kick.cpp \
		  srcs/cmds/Part.cpp \
		  srcs/cmds/Topic.cpp \
		  srcs/cmds/Priv.cpp \
		  srcs/cmds/Nick.cpp \
		  srcs/cmds/User.cpp

OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.cpp=.o))
DEPS = $(OBJECTS:.o=.d)

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I headers/ -I headers/cmds/
RM = rm -f
