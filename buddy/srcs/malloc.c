/*
** malloc.c for malloc in /home/doom/tools
** 
** Made by Doom
** Login   <doom@epitech.eu>
** 
** Started on  Mon Jan 23 19:47:22 2017 Doom
** Last update Fri Feb 10 17:04:32 2017 Doom
*/

#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include "malloc.h"

t_mem_info	g_info =
  {
    .base = NULL,
    .alloced = NULL,
    .buckets = {0},
#ifdef MALLOC_THREAD_SAFE
    .lock = PTHREAD_MUTEX_INITIALIZER,
#endif /* !MALLOC_THREAD_SAFE */
  };

static size_t	__attribute__((const))	get_log_idx(size_t size)
{
  size_t				bsize;
  size_t				idx;

  bsize = MIN_SIZE;
  idx = 0;
  while (bsize < size)
    {
      bsize <<= 1;
      idx += 1;
    }
  return (idx);
}

static t_block	*get_from_heap(size_t idx)
{
  t_block	*new;

  new = sbrk(0);
  if (UNLIKELY(!g_info.base))
    g_info.base = new;
  if (idx < 6)
    idx = 6;
  else if (idx < 16)
    idx += 1;
  if (sbrk(SIZE_FOR_IDX(idx)) == (void *)-1)
    {
      errno = ENOMEM;
      return (NULL);
    }
  new->idx = idx;
  new->status = FREE_MAGIC;
  add_to_list(&g_info.buckets[idx], new);
  return (new);
}

static t_block	*split_block(t_block *blk, size_t to)
{
  t_block	*other;

  while (blk->idx > to)
    {
      blk->idx -= 1;
      other = (t_block *)((char *)blk + SIZE_FOR_IDX(blk->idx));
      other->idx = blk->idx;
      other->status = FREE_MAGIC;
      add_to_list(&g_info.buckets[other->idx], other);
    }
  return (blk);
}

static void	*find_block(size_t idx)
{
  t_block	*block;
  size_t	cur;

  MALLOCK(&g_info.lock);
  block = NULL;
  cur = idx;
  while (!block && cur < BUCKET_MAX)
    block = g_info.buckets[cur++];
  if (!block && !(block = get_from_heap(idx)))
    {
      MALLUNLOCK(&g_info.lock);
      return (NULL);
    }
  remove_from_list(&g_info.buckets[block->idx], block);
  block = split_block(block, idx);
  block->status = ALLOC_MAGIC;
  add_to_list(&g_info.alloced, block);
  MALLUNLOCK(&g_info.lock);
  return (block + 1);
}

void		*malloc(size_t size)
{
  if (!size)
    return (NULL);
  size += META_SIZE;
  if (size < MIN_SIZE)
    size = MIN_SIZE;
  return (find_block(get_log_idx(size)));
}
