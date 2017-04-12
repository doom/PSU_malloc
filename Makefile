##
## Makefile for malloc in /home/doom/tools
## 
## Made by Doom
## Login   <doom@epitech.eu>
## 
## Started on  Mon Jan 23 18:36:00 2017 Doom
## Last update Sat Feb  4 12:34:01 2017 Doom
##

NAME				=	libmy_malloc.so

CPPFLAGS			=	-Iinclude

CFLAGS				=	-Wall -Wextra -Wno-unused-result -O3 -fno-optimize-strlen

libmy_malloc.so_SRCS		=	srcs/malloc.c \
					srcs/free.c \
					srcs/calloc.c \
					srcs/realloc.c \
					srcs/show_alloc_mem.c

include .build/build.mk
