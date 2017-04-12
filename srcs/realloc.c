/*
** realloc.c for malloc in /home/doom/rendu/PSU_2016_malloc
** 
** Made by Doom
** Login   <doom@epitech.eu>
** 
** Started on  Tue Jan 31 17:32:49 2017 Doom
** Last update Tue Jan 31 19:32:34 2017 Doom
*/

#include <string.h>
#include "malloc.h"

void		*realloc(void *ptr, size_t new_size)
{
  t_block	*blk;
  void		*new;

  if (!new_size)
    {
      free(ptr);
      return (NULL);
    }
  if (!ptr)
    return (malloc(new_size));
  blk = GET_META(ptr);
  if (blk->size < new_size)
    {
      new = malloc(new_size);
      if (new)
	{
	  memcpy(new, ptr, blk->size);
	  free(ptr);
	  ptr = new;
	}
    }
  return (ptr);
}
