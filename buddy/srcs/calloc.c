/*
** calloc.c for malloc in /home/doom/rendu/PSU_2016_malloc
** 
** Made by Doom
** Login   <doom@epitech.eu>
** 
** Started on  Fri Jan 27 16:06:15 2017 Doom
** Last update Sun Jan 29 01:16:38 2017 Doom
*/

#include <stdlib.h>
#include <string.h>

void	*calloc(size_t nmemb, size_t size)
{
  void	*ptr;

  if ((size && nmemb > (size_t)-1 / size)
      || !(ptr = malloc(nmemb * size)))
    return (NULL);
  bzero(ptr, nmemb * size);
  return (ptr);
}
