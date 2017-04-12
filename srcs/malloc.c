/*
** malloc.c for malloc in /home/doom/rendu/PSU_2016_malloc
** 
** Made by Doom
** Login   <doom@epitech.eu>
** 
** Started on  Tue Jan 31 17:31:35 2017 Doom
** Last update Wed Feb  8 14:10:59 2017 Doom
*/

#include <unistd.h>
#include "malloc.h"

static t_block	*get_from_heap(size_t size)
{
  t_block	*blk;

  size = ALIGN(size, MEM_PAGE_SIZE);
  blk = sbrk(0);
  if (UNLIKELY(sbrk(size) == (void *)-1))
    return (NULL);
  blk->next = NULL;
  blk->prev = g_info.last;
  if (!g_info.last)
    g_info.first = blk;
  else
    g_info.last->next = blk;
  g_info.last = blk;
  blk->size = size - META_SIZE;
  blk->status = FREE_MAGIC;
  return (blk);
}

static t_block	*split_block(t_block *blk, size_t need_size)
{
  t_block	*new;

  if (blk->size >= need_size + META_SIZE + MIN_SIZE)
    {
      new = (t_block *)(((char *)(blk + 1)) + need_size);
      new->next = blk->next;
      new->prev = blk;
      if (blk == g_info.last)
	g_info.last = new;
      else
	blk->next->prev = new;
      blk->next = new;
      new->size = blk->size - need_size - META_SIZE;
      blk->size = need_size;
      new->status = FREE_MAGIC;
    }
  return (blk);
}

static void	*find_block(size_t size)
{
  t_block	*blk;

  MALLOCK(&g_info.lock);
  blk = g_info.first;
  while (blk && (blk->size < size || blk->status == ALLOC_MAGIC))
    blk = blk->next;
  if (!blk && !(blk = get_from_heap(size + META_SIZE)))
    {
      MALLUNLOCK(&g_info.lock);
      return (NULL);
    }
  blk = split_block(blk, size);
  blk->status = ALLOC_MAGIC;
  MALLUNLOCK(&g_info.lock);
  return (blk + 1);
}

void		*malloc(size_t size)
{
  if (UNLIKELY(!size))
    return (NULL);
  return (find_block(ALIGN_UP(size)));
}
