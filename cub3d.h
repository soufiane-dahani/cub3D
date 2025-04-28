/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/28 10:57:27 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>


# define FT_ALLOC 1
# define FT_CLEAR 0


typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;


void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
t_list	*ft_lstnew(void *content);
char	**ft_split2(char *str, char *charset);
char	*ft_strcpy(char *dest, char const *src);
char	*ft_strcat(char *dest, char const *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *src);
size_t	ft_strlen(const char *c);
void	*ft_memset(void *s, int c, size_t n);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char    *ft_strndup(const char *s, size_t n);
t_list	*mem_alloc(size_t size);
void	*ft_malloc(size_t size, short option);



#endif