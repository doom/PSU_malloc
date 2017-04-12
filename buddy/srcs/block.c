/*
** block.c for malloc in /home/doom/rendu/PSU_2016_malloc/bonus
** 
** Made by Doom
** Login   <doom@epitech.eu>
** 
** Started on  Sun Feb  5 02:31:30 2017 Doom
** Last update Fri Feb 10 17:11:14 2017 Doom
*/

#include <unistd.h>
#include <stdio.h>
#include "malloc.h"

void	add_to_list(t_block **list, t_block *blk)
{
  blk->prev = NULL;
  blk->next = *list;
  if (*list)
    (*list)->prev = blk;
  *list = blk;
}

void    remove_from_list(t_block **list, t_block *blk)
{
  if (blk->prev)
    blk->prev->next = blk->next;
  else
    *list = blk->next;
  if (blk->next)
    blk->next->prev = blk->prev;
  blk->prev = NULL;
  blk->next = NULL;
}
