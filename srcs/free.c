/*
** free.c for malloc in /home/doom/rendu/PSU_2016_malloc
** 
** Made by Doom
** Login   <doom@epitech.eu>
** 
** Started on  Tue Jan 31 18:00:01 2017 Doom
** Last update Wed Feb  8 14:12:18 2017 Doom
*/

#include <unistd.h>
#include <stdint.h>
#include "malloc.h"

t_mem_info	g_info =
  {
    .first = NULL,
    .last = NULL,
#ifdef MALLOC_THREAD_SAFE
    .lock = PTHREAD_MUTEX_INITIALIZER
#endif /* !MALLOC_THREAD_SAFE */
  };

t_block		*merge_blocks(t_block *a, t_block *b)
{
  a->size += META_SIZE + b->size;
  a->next = b->next;
  if (b == g_info.last)
    g_info.last = a;
  else
    b->next->prev = a;
  return (a);
}

static void	break_down(void)
{
  intptr_t	diff;

  diff = (intptr_t)sbrk(0) - (intptr_t)g_info.last;
  if (diff > MEM_PAGE_SIZE)
    {
      g_info.last = g_info.last->prev;
      if (g_info.last)
	g_info.last->next = NULL;
      else
	g_info.first = NULL;
      diff = ALIGN(diff, MEM_PAGE_SIZE) - MEM_PAGE_SIZE;
      sbrk(-diff);
    }
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
      blk = GET_META(ptr);
      if (UNLIKELY(blk > g_info.last || blk < g_info.first
		   || (blk->status != ALLOC_MAGIC
		       && blk->status != FREE_MAGIC)))
	return (put_free_err("Invalid pointer\n", 16));
      if (blk->status == FREE_MAGIC)
	return (put_free_err("Double free\n", 12));
      blk->status = FREE_MAGIC;
      while (blk->prev && blk->prev->status == FREE_MAGIC)
	blk = merge_blocks(blk->prev, blk);
      while (blk->next && blk->next->status == FREE_MAGIC)
	blk = merge_blocks(blk, blk->next);
      if (g_info.last && g_info.last->status == FREE_MAGIC)
      	break_down();
      MALLUNLOCK(&g_info.lock);
    }
}
