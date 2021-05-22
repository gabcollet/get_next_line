/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:27:41 by gcollet           #+#    #+#             */
/*   Updated: 2021/05/22 18:45:35 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Retourne une ligne lue depuis un fd, sans le retour à la ligne */
/* Valeur de retour : 
1 : Une ligne a été lue
0 : La fin de fichier a été atteinte
-1 : Une erreur est survenue */

#include "get_next_line.h"
/* #define BUFFER_SIZE 42
 */
/* fonction qui avance le pointeur de tab  */
static int	newline_to_tab(char **tab, int fd, char *ptr_newline)
{
	char	*temp;
	size_t	longueur;

	if (ptr_newline == NULL || *(ptr_newline + 1) == '\0')
	{
		free(tab[fd]);
		tab[fd] = NULL;
		return (0);
	}
	longueur = ft_strlen(ptr_newline + 1);
	temp = malloc(sizeof(char) * (longueur + 1));
	if (temp == NULL)
		return (-1);
	ft_memcpy(temp, ptr_newline + 1, longueur + 1);
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
		(*line)[longueur] = '\0';
		ft_memcpy(*line, tab[fd], longueur);
		if (newline_to_tab(tab, fd, ptr_newline))
			return (-1);
		if (ptr_newline == NULL)
			return (0);
		else
			return (1);
	}
	*line = malloc(sizeof(char) * 1);
	if (*line == NULL)
		return (-1);
	**line = '\0';
	return (0);
}

/* fonction qui free le buffer */
static void	free_buffer(char **tab, char **line)
{
	int	i;
	
	i = 0;
	while (i < 1024)
	{
		if (tab != NULL)
		{
			free(tab);
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

/* fonction qui écrit le reste du tableau */
static int	reste_du_tableau(char **tab, int fd, char **line, char *buffer)
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
		return (1);
	}
	while ((retour = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[retour] = '\0';
		retour = reste_du_tableau(tab, fd, line, buffer);
		if (retour != 0)
			break ;
	}
	if (retour == -1)
		free_buffer(tab, line);
	return (retour);
}

// #include "get_next_line.h"

// static int		write_to_table(char **fd_tab, int fd, char *nl_ptr)
// {
// 	size_t	len;
// 	char	*new;

// 	if (nl_ptr == NULL || *(nl_ptr + 1) == '\0')
// 	{
// 		free(fd_tab[fd]);
// 		fd_tab[fd] = NULL;
// 		return (0);
// 	}
// 	len = ft_strlen(nl_ptr + 1);
// 	if (!(new = (char *)malloc(len + 1)))
// 		return (-1);
// 	ft_memcpy(new, nl_ptr + 1, len + 1);
// 	free(fd_tab[fd]);
// 	fd_tab[fd] = new;
// 	return (0);
// }

// static int		get_tab_line_and_write_reminder(char **fd_tab, \
// 		int fd, char **line)
// {
// 	char	*nl_ptr;
// 	size_t	len;

// 	if (fd_tab[fd] != NULL)
// 	{
// 		nl_ptr = ft_strchr(fd_tab[fd], '\n');
// 		if (nl_ptr == NULL)
// 			len = ft_strlen(fd_tab[fd]);
// 		else
// 			len = nl_ptr - fd_tab[fd];
// 		if (!(*line = (char *)malloc(len + 1)))
// 			return (-1);
// 		(*line)[len] = '\0';
// 		ft_memcpy(*line, fd_tab[fd], len);
// 		if (write_to_table(fd_tab, fd, nl_ptr))
// 			return (-1);
// 		return ((nl_ptr == NULL) ? 0 : 1);
// 	}
// 	if (!(*line = (char *)malloc(1)))
// 		return (-1);
// 	**line = '\0';
// 	return (0);
// }

// static int		write_reminder_from_table(char **fd_tab, int fd, \
// 		char **line, char *buffer)
// {
// 	char	*nl_ptr;
// 	char	*new;

// 	nl_ptr = ft_strchr(buffer, '\n');
// 	if (nl_ptr == NULL)
// 	{
// 		if (!(new = ft_strjoin(*line, buffer)))
// 			return (-1);
// 		free(*line);
// 		*line = new;
// 		return (0);
// 	}
// 	*nl_ptr = '\0';
// 	if (!(new = ft_strjoin(*line, buffer)))
// 		return (-1);
// 	free(*line);
// 	*line = new;
// 	if (*(nl_ptr + 1) != '\0')
// 		if (!(fd_tab[fd] = ft_strdup(nl_ptr + 1)))
// 			return (-1);
// 	return (1);
// }

// static void		free_buffers(char **fd_tab, char **line)
// {
// 	int		i;

// 	i = 0;
// 	while (i < 1024)
// 	{
// 		if (fd_tab[i] != NULL)
// 		{
// 			free(fd_tab[i]);
// 			fd_tab[i] = NULL;
// 		}
// 		++i;
// 	}
// 	if (*line != NULL)
// 	{
// 		free(*line);
// 		*line = NULL;
// 	}
// }

// int				get_next_line(int fd, char **line)
// {
// 	static char		*fd_tab[1024] = {NULL};
// 	char			buffer[BUFFER_SIZE + 1];
// 	int				ret;

// 	if (fd < 0 || fd > 1023 || line == NULL)
// 		return (-1);
// 	ret = get_tab_line_and_write_reminder(fd_tab, fd, line);
// 	if (ret != 0)
// 	{
// 		if (ret == -1)
// 			free_buffers(fd_tab, line);
// 		return (ret);
// 	}
// 	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
// 	{
// 		buffer[ret] = '\0';
// 		ret = write_reminder_from_table(fd_tab, fd, line, buffer);
// 		if (ret != 0)
// 			break ;
// 	}
// 	if (ret == -1)
// 		free_buffers(fd_tab, line);
// 	return (ret);
// }

/* int main()
{
	printf("BUFFER_SIZE=%d\n", BUFFER_SIZE);
	char *line1 = NULL;
	char *line2 = NULL;
	int fd = open("test", O_RDONLY);
	int fd2 = open("test2", O_RDONLY);
	int i = 0;
	while (i++ < 5)
	{
		get_next_line(fd, &line1);
		get_next_line(fd2, &line2);
		printf("%s:%s\n", line1, line2);
	}
	close(fd);
	close(fd2);
}
 */