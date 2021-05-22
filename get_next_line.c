/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:27:41 by gcollet           #+#    #+#             */
/*   Updated: 2021/05/21 16:43:56 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Retourne une ligne lue depuis un fd, sans le retour à la ligne */
/* Valeur de retour : 
1 : Une ligne a été lue
0 : La fin de fichier a été atteinte
-1 : Une erreur est survenue */

#include "get_next_line.h"

#define BUFFER_SIZE 42

/* fonction qui avance le pointeur de tab  */
static int	newline_to_tab(char **tab, int fd, char *ptr_newline)
{
	char	*temp;
	size_t	longueur;

	if (ptr_newline == NULL || (ptr_newline + 1 == '\0'))
	{
		free(tab[fd]);
		tab[fd] = NULL;
		return (0);
	}
	longueur = ft_strlen(ptr_newline + 1);
	temp = malloc(sizeof(char) * (longueur + 1));
	if (temp == NULL)
		return (-1);
	ft_memcpy(temp, ptr_newline, longueur);
	free(tab[fd]);
	tab[fd] = temp;
	return (0);
}

/* fonction pour trouver la ligne dans tab */
static int	find_newline(char **tab, int fd, char **line)
{
	size_t	longueur;
	char	*ptr_newline;

	if (tab[fd] != NULL)
	{
		ptr_newline = ft_strchr(tab[fd], '\n');
		if (ptr_newline == NULL)
			longueur = ft_strlen(tab[fd]);
		else
			longueur = ptr_newline - tab[fd];
		*line = malloc(sizeof(char) * (longueur + 1));
		if (*line == NULL)
			return (-1);
		*line[longueur] = '\0';
		ft_memcpy(*line, tab[fd], longueur);
		if (newline_to_tab(tab, fd, ptr_newline))
			return (-1);
		if (ptr_newline == NULL)
			return (0);
		else
			return (1);
	}
	ptr_newline = malloc(sizeof(char) * 1);
	if (ptr_newline == NULL)
		return (-1);
	ptr_newline = '\0';
	return (0);
}

/* fonction qui free le buffer */
static void	free_buffer(char **tab, char **line)
{
	
}

/* fonction principale */
int	get_next_line(int fd, char **line)
{
	static char	*tab[1024];
	char		buffer[BUFFER_SIZE + 1];
	int			retour;

	if (fd < 0 || fd > 1024 || *line == NULL)
		return (-1);
	retour = find_newline(tab, fd, line);
	if (retour != 0)
	{
		if (retour == -1)
			free_buffer(tab, line);
		return (1);
	}
	while (read )
}
