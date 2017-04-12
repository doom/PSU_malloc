/*
** malloc.h for malloc in /home/doom/rendu/PSU_2016_malloc
** 
** Made by Doom
** Login   <doom@epitech.eu>
** 
** Started on  Tue Jan 31 15:39:15 2017 Doom
** Last update Thu Feb  2 13:36:30 2017 Doom
*/

#ifndef MALLOC_H_
# define MALLOC_H_

# include <stdlib.h>
# include <stdbool.h>

#define MALLOC_THREAD_SAFE

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

typedef struct		s_block
{
  struct s_block	*next;
  struct s_block	*prev;
  size_t		size;
  size_t		status;
}			t_block;

# define FREE_MAGIC	0x175F233
# define ALLOC_MAGIC	0x175A110C

typedef struct		s_mem_info
{
  t_block		*first;
  t_block		*last;
# ifdef MALLOC_THREAD_SAFE
  pthread_mutex_t	lock;
# endif /* !MALLOC_THREAD_SAFE */
}			t_mem_info;

# define MEM_PAGE_SIZE	getpagesize()

/* # define MEM_PAGE_SIZE	sysconf(_SC_PAGESIZE) */

# define ALIGN(x, n)	(((x) + ((n) - 1)) & ~((n) - 1))

# if __x86_64__
#  define ALIGN_UP(x)	ALIGN(x, 8)
# else
#  define ALIGN_UP(x)	ALIGN(x, 4)
# endif

# define META_SIZE	sizeof(t_block)

# define MIN_SIZE	sizeof(void *)

# define GET_META(p)	((t_block *)p - 1)

extern t_mem_info	g_info;

void		show_alloc_mem(void);

#endif /* !MALLOC_H_ */
