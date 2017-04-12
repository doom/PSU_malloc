/*
** show_alloc_mem.c for malloc in /home/doom/rendu/PSU_2016_malloc
** 
** Made by Doom
** Login   <doom@epitech.eu>
** 
** Started on  Tue Jan 31 17:40:52 2017 Doom
** Last update Thu Feb  2 13:37:25 2017 Doom
*/

#include <unistd.h>
#include <stdio.h>
#include "malloc.h"

void		show_alloc_mem(void)
{
  t_block	*cur;

  printf("Break : %p\n", sbrk(0));
  cur = g_info.first;
  while (cur)
    {
      if (cur->status == ALLOC_MAGIC)
	printf("%p - %p : %zu bytes\n", cur + 1,
	       (char *)(cur + 1) + cur->size, cur->size);
      cur = cur->next;
    }
}
