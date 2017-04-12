##
## build.mk for build in /home/doom
## 
## Made by Doom
## Login   <doom@epitech.eu>
## 
## Started on  Tue Jan 31 19:25:12 2017 Doom
## Last update Sat Feb  4 12:33:53 2017 Doom
##

CC		?=	gcc
CXX		?=	g++
ECHO		?=	/bin/echo -e
RM		?=	rm -f

NORMAL		=	"\033[00m"
BOLD		=	"\033[1m"
GREEN		=	"\033[32m"
RED		=	"\033[31m"
YELLOW		=	"\033[33m"
BLUE		=	"\033[34m"
PURPLE		=	"\033[35m"

TITLECOLOR 	?=	$(BOLD)$(PURPLE)
EXECCOLOR 	?=	$(BOLD)$(YELLOW)
SRCSCOLOR 	?=	$(BOLD)$(BLUE)

CPPFLAGS	+=	-Wundef
CFLAGS		+=	-Wall -Wextra

ifdef P
ifneq ($(wildcard .build/profiles/$(P).mk),)
include .build/profiles/$(P).mk
else
$(warning Profile $(P) not found)
endif
endif

ifeq ($(suffix $(NAME)),.so)
CFLAGS		+=	-fPIC
LDFLAGS		+=	-shared
endif

ifneq ($(findstring .cpp,$($(NAME)_SRCS))$(findstring .cc,$($(NAME)_SRCS)),)
COMP		=	$(CXX)
COMPFLAGS	=	$(CXXFLAGS) $(CPPFLAGS)
OBJS		=	$(patsubst %.cpp,%.o,$(patsubst %.cc,%.o,$($(NAME)_SRCS)))
else
COMP		=	$(CC)
COMPFLAGS	=	$(CFLAGS) $(CPPFLAGS)
OBJS		=	$($(NAME)_SRCS:%.c=%.o)
endif

LINKFLAGS	=	$(LDFLAGS) $(LDLIBS)

ifeq ($(suffix $(NAME)),.a)
$(NAME):	$(OBJS)
		@ar rc $(NAME) $(OBJS)
		@ranlib $(NAME)
		@$(ECHO) $(TITLECOLOR)[CC]$(EXECCOLOR) $(NAME)$(NORMAL)
else ifeq ($(suffix $(NAME)),.so)
$(NAME):	$(OBJS)
		@$(COMP) -o $(NAME) $(OBJS) $(LINKFLAGS)
		@$(ECHO) $(TITLECOLOR)[CC]$(EXECCOLOR) $(NAME)$(NORMAL)
else
$(NAME):	$(OBJS)
		@$(COMP) -o $(NAME) $(OBJS) $(LINKFLAGS)
		@$(ECHO) $(TITLECOLOR)[CC]$(EXECCOLOR) $(NAME)$(NORMAL)
endif

all:		$(NAME)

%.o:		%.c
		@$(COMP) -c $< -o $@ $(COMPFLAGS)
		@$(ECHO) $(TITLECOLOR)[CC]$(SRCSCOLOR) $<$(NORMAL)

%.o:		%.cpp
		@$(COMP) -c $< -o $@ $(COMPFLAGS)
		@$(ECHO) $(TITLECOLOR)[CC]$(SRCSCOLOR) $<$(NORMAL)

%.o:		%.cc
		@$(COMP) -c $< -o $@ $(COMPFLAGS)
		@$(ECHO) $(TITLECOLOR)[CC]$(SRCSCOLOR) $<$(NORMAL)

clean:
		@$(RM) $(OBJS)
		@$(ECHO) $(TITLECOLOR)[RM]$(SRCSCOLOR) $(OBJS)$(NORMAL)

fclean:		clean
		@$(RM) $(NAME)
		@$(ECHO) $(TITLECOLOR)[RM]$(EXECCOLOR) $(NAME)$(NORMAL)

re:		fclean all

.PHONY:		all clean fclean re
