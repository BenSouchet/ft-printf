/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 22:28:00 by bsouchet          #+#    #+#             */
/*   Updated: 2017/05/03 22:28:03 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>

typedef enum		e_bool
{
	True, False
}					t_bool;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_rgb
{
	float			r;
	float			g;
	float			b;
}					t_rgb;

typedef struct		s_hsb
{
	float			h;
	float			s;
	float			b;
}					t_hsb;

typedef struct		s_vector
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_vector;

int					ft_atoi(char *str);
void				ft_bzero(void *s, size_t n);

void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);

double				ft_pow(double n, int pow);

void				ft_putstr(const char *str);

char				*ft_strchr(const char *s, int c);
int					ft_strchri(char *s, int c, int i);
int					ft_strchri_lu(char *s, int c, int i);

size_t				ft_strlen(const char *str);

int					ft_strncmp(const char *s1, const char *s2, size_t n);

size_t				ft_wcharlen(unsigned c);
size_t				ft_wstrlen(unsigned *s);

#endif
