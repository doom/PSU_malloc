/*
** realloc.c for malloc in /home/doom/stuff/c/PSU_2016_malloc/test
** 
** Made by Doom
** Login   <doom@epitech.eu>
** 
** Started on  Fri Jan 27 11:46:47 2017 Doom
** Last update Sat Jan 28 18:23:54 2017 Doom
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
  blk = (t_block *)ptr - 1;
  if (SIZE_FOR_IDX(blk->idx) < new_size)
    {
      new = malloc(new_size);
      if (new)
	{
	  memcpy(new, ptr, SIZE_FOR_IDX(blk->idx));
	  free(ptr);
	  ptr = new;
	}
    }
  return (ptr);
}
