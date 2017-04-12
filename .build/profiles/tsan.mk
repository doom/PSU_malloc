##
## tsan.mk for build in /home/doom
## 
## Made by Doom
## Login   <doom@epitech.eu>
## 
## Started on  Tue Jan 31 19:27:27 2017 Doom
## Last update Tue Jan 31 19:27:28 2017 Doom
##

CC		=	clang
CXX		=	clang++
CFLAGS		+=	-fsanitize=thread -fno-omit-frame-pointer
CXXFLAGS	+=	-fsanitize=thread -fno-omit-frame-pointer
LDFLAGS		+=	-fsanitize=thread
