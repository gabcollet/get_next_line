/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:27:41 by gcollet           #+#    #+#             */
/*   Updated: 2021/05/24 12:40:30 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Retourne une ligne lue depuis un fd, sans le retour à la ligne */
/* Valeur de retour : 
1 : Une ligne a été lue
0 : La fin de fichier a été atteinte
-1 : Une erreur est survenue */

#include "get_next_line.h"

/* fonction qui avance le pointeur de tab  */
static int	newline_to_tab(char **tab, int fd, char *ptr_newline)
{
	char	*temp;
	size_t	longueur;

	temp = NULL;
	if (ptr_newline == NULL || *(ptr_newline + 1) == '\0')
	{
		free(tab[fd]);
		tab[fd] = NULL;
		return (0);
	}
	longueur = ft_strlen(ptr_newline + 1);
	temp = ft_memcpy(temp, ptr_newline + 1, longueur + 1);
	if (temp == NULL)
		return (-1);
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
		*line = ft_memcpy(*line, tab[fd], longueur);
		if (*line == NULL)
			return (-1);
		(*line)[longueur] = '\0';
		if (newline_to_tab(tab, fd, ptr_newline))
			return (-1);
		if (ptr_newline == NULL)
			return (0);
		return (1);
	}
	*line = malloc(sizeof(char) * 1);
	if (*line == NULL)
		return (-1);
	**line = '\0';
	return (0);
}

/* fonction qui free tab et line */
static void	free_buffer(char **tab, char **line)
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		if (tab[i] != NULL)
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		i++;
	}
	if (*line != NULL)
	{
		free(*line);
		*line = NULL;
	}
}

/* fonction qui écrit le reste du buffer */
static int	buffer_to_tab(char **tab, int fd, char **line, char *buffer)
{
	char	*ptr_newline;
	char	*temp;

	ptr_newline = ft_strchr(buffer, '\n');
	if (ptr_newline == NULL)
	{
		temp = ft_strjoin(*line, buffer);
		if (temp == NULL)
			return (-1);
		*line = temp;
		return (0);
	}
	*ptr_newline = '\0';
	temp = ft_strjoin(*line, buffer);
	if (temp == NULL)
		return (-1);
	*line = temp;
	if (*(ptr_newline + 1) != '\0')
	{
		tab[fd] = ft_strdup(ptr_newline + 1);
		if (tab[fd] == NULL)
			return (-1);
	}
	return (1);
}

/* fonction principale */
int	get_next_line(int fd, char **line)
{
	static char	*tab[1024] = {NULL};
	char		buffer[BUFFER_SIZE + 1];
	int			retour;

	if (fd < 0 || fd > 1023 || line == NULL)
		return (-1);
	retour = find_newline(tab, fd, line);
	if (retour != 0)
	{
		if (retour == -1)
			free_buffer(tab, line);
		return (retour);
	}
	retour = read(fd, buffer, BUFFER_SIZE);
	while (retour > 0)
	{
		buffer[retour] = '\0';
		retour = buffer_to_tab(tab, fd, line, buffer);
		if (retour != 0)
			break ;
		retour = read(fd, buffer, BUFFER_SIZE);
	}
	if (retour == -1)
		free_buffer(tab, line);
	return (retour);
}
