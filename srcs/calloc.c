/*
** calloc.c for malloc in /home/doom/rendu/PSU_2016_malloc
** 
** Made by Doom
** Login   <doom@epitech.eu>
** 
** Started on  Tue Jan 31 17:31:18 2017 Doom
** Last update Tue Jan 31 19:32:22 2017 Doom
*/

#include <stdlib.h>
#include <strings.h>

void	*calloc(size_t nmemb, size_t size)
{
  void	*ptr;

  if ((size && nmemb > (size_t)-1 / size)
      || !(ptr = malloc(nmemb * size)))
    return (NULL);
  bzero(ptr, nmemb * size);
  return (ptr);
}
