##
## asan.mk for build in /home/doom
## 
## Made by Doom
## Login   <doom@epitech.eu>
## 
## Started on  Tue Jan 31 19:27:06 2017 Doom
## Last update Tue Jan 31 19:27:07 2017 Doom
##

CC		=	clang
CXX		=	clang++
CFLAGS		+=	-fsanitize=address -fno-omit-frame-pointer
CXXFLAGS	+=	-fsanitize=address -fno-omit-frame-pointer
LDFLAGS		+=	-fsanitize=address -lstdc++
