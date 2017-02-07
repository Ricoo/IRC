/*
** util.c for myirc in /home/hegedu_e/rendu/PSU_2014_myirc
** 
** Made by 
** Login   <hegedu_e@epitech.net>
** 
** Started on  Sun Apr 12 19:29:50 2015 
** Last update Sun Apr 12 20:11:12 2015 
*/

#include <stdlib.h>
#include <string.h>

char	*my_epur(char *str)
{
  char	*cpy;
  int	i;

  i = 0;
  if (!(cpy = malloc(sizeof(char) * strlen(str) + 1)))
    return (NULL);
  while (*str == ' ' && *str == '\t' && *str != '\0')
    str++;
  while (*str != '\0')
    {
      while (*str != ' ' && *str != '\t' && *str != '\0')
	{
	  cpy[i] = *str;
	  str++;
	  i++;
	}
      while (*str == ' ' && *str != '\t' && *str != '\0')
	str++;
      if (*str != '\0')
	cpy[i++] = ' ';
    }
  cpy[i] = '\0';
  return (cpy);
}
