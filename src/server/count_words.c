/*
** count_words.c for myirc in /home/terran_j/rendu/PSU_2014_myirc/src/server
**
** Made by terran_j
** Login   <terran_j@epitech.net>
**
** Started on  Tue Apr  7 17:26:09 2015 terran_j
** Last update Tue Apr  7 17:41:09 2015 terran_j
*/

#include <stdio.h>
#include "myirc.h"

int     my_count_word(char *str)
{
  int   count;
  int   word;

  if (str == NULL)
    return (0);
  word = 0;
  count = 0;
  while (str[count] != '\0')
    {
      if (str[count] && str[count + 1] == ' ')
        ++word;
      ++count;
    }
  return (word);
}
