/*
** free.c<PSU_2016_malloc> for malloc in /home/doom/stuff/c/PSU_2016_malloc/test
** 
** Made by Doom
** Login   <doom@epitech.eu>
** 
** Started on  Fri Jan 27 10:18:30 2017 Doom
** Last update Fri Feb 10 17:30:45 2017 Doom
*/

#include <unistd.h>
#include <stdint.h>
#include "malloc.h"

static t_block	*find_buddy(t_block *blk)
{
  t_block	*buddy;

  buddy = (t_block *)((uintptr_t)blk ^ SIZE_FOR_IDX(blk->idx));
  return (((uintptr_t)buddy < (uintptr_t)sbrk(0)
	   && (uintptr_t)buddy >= (uintptr_t)g_info.base
	   && buddy->status == FREE_MAGIC
	   && buddy->idx == blk->idx) ? buddy : NULL);
}

static t_block	*merge_buddies(t_block *cur)
{
  t_block	*buddy;

  while ((buddy = find_buddy(cur)))
    {
      remove_from_list(&g_info.buckets[buddy->idx], buddy);
      if ((uintptr_t)buddy < (uintptr_t)cur)
	cur = buddy;
      cur->idx += 1;
    }
  return (cur);
}

static void	put_free_err(const char *msg, size_t size)
{
  (void)write(STDERR_FILENO, msg, size);
  MALLUNLOCK(&g_info.lock);
}

void		free(void *ptr)
{
  t_block	*blk;

  if (ptr)
    {
      MALLOCK(&g_info.lock);
      blk = (t_block *)ptr - 1;
      if (UNLIKELY((intptr_t)blk > (intptr_t)sbrk(0)
		   || (intptr_t)blk < (intptr_t)g_info.base
		   || (blk->status != ALLOC_MAGIC
		       && blk->status != FREE_MAGIC)))
	return (put_free_err("Invalid pointer\n", 16));
      if (blk->status == FREE_MAGIC)
	return (put_free_err("Double free\n", 12));
      remove_from_list(&g_info.alloced, blk);
      blk = merge_buddies(blk);
      blk->status = FREE_MAGIC;
      add_to_list(&g_info.buckets[blk->idx], blk);
      MALLUNLOCK(&g_info.lock);
    }
}
