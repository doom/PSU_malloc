/*
** malloc.h<PSU_2016_malloc> for malloc in /home/doom/tools
** 
** Made by Doom
** Login   <doom@epitech.eu>
** 
** Started on  Mon Jan 23 18:41:00 2017 Doom
** Last update Tue Feb  7 16:51:40 2017 Doom
*/

#ifndef MALLOC_H_
# define MALLOC_H_

# define MALLOC_THREAD_SAFE

# ifdef MALLOC_THREAD_SAFE
#  include <pthread.h>
#  define MALLOCK(x)	pthread_mutex_lock(x)
#  define MALLUNLOCK(x)	pthread_mutex_unlock(x)
# else
#  define MALLOCK(x)
#  define MALLUNLOCK(x)
# endif /* !MALLOC_THREAD_SAFE */

# define LIKELY(x)	__builtin_expect(!!(x), 1)
# define UNLIKELY(x)	__builtin_expect(!!(x), 0)

# ifdef DEBUG
#  include "libprintf.h"
#  define DBG(x, ...)	my_printf(x, #__VA_ARGS__)
# else
#  define DBG(x, ...)
# endif

# include <stdlib.h>

typedef struct		s_block
{
  struct s_block	*next;
  struct s_block	*prev;
  size_t		idx;
  size_t		status;
}			t_block;

# define BUCKET_MAX	27

# define FREE_MAGIC	0x175F233
# define ALLOC_MAGIC	0x175A110C

typedef struct		s_mem_info
{
  t_block		*buckets[BUCKET_MAX];
  t_block		*alloced;
  void			*base;
# ifdef MALLOC_THREAD_SAFE
  pthread_mutex_t	lock;
# endif /* !MALLOC_THREAD_SAFE */
}			t_mem_info;

extern t_mem_info		g_info;

# define META_SIZE		sizeof(t_block)

# define MIN_SIZE		(META_SIZE * 2)

# define SIZE_FOR_IDX(idx)	(1UL << (idx + 6))

void	add_to_list(t_block **list, t_block *blk);
void	remove_from_list(t_block **list, t_block *blk);
void	show_alloc_mem(void);

#endif /* !MALLOC_H_ */
