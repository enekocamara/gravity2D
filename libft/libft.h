/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 16:20:19 by eperaita          #+#    #+#             */
/*   Updated: 2022/09/01 17:45:27 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	int				chunk;
	struct s_list	*next;
}	t_list;

int				ft_isalpha(int a);
int				ft_isdigit(int a);
int				ft_isalnum(int a);
int				ft_isascii(int a);
int				ft_isprint(int a);
size_t			ft_strlen(const char *str);
size_t			ft_strlen2d(const char **str);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_c_str_cmp(char c, char *str);
int				ft_toupper(int a);
int				ft_tolower(int a);
char			*ft_strnstr(const char *str, const char *to_find, size_t n);
int				ft_atoi(const char *str);
char			*ft_strchr(const char *str, int c);
char			*ft_strrchr(const char *str, int c);
void			*ft_memset(void *str, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_calloc(size_t num, size_t size);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			**ft_split_str(char const *s, char *str);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
//////////LINKED LIST////////
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
/////////NEW UTILS////////
int				ft_strcmp(const char *s1, const char *s2);
double			ft_atoi_double(const char *str);
char			*ft_dtoa(double value);
/////////GET NEXT LINE////////
char			*get_next_line(int fd);
char			*ft_read_to_temp(int fd, char *temp);
char			*update_temp(char *temp, char *buff);
char			*ft_final(char *final, char *temp);
char			*ft_remain(char *temp, char *final);
char			*ft_join(char *temp, char *buff);
char			*ft_line_break(char *str);
char			*ft_substr_gnl(char *str, int start, size_t len);
///////PRINTF///////////
int				ft_printf(const char *str, ...);
int				ft_printf_c(int c);
int				ft_printf_s(char *str);
int				ft_printf_di(int dec);
int				ft_printf_u(unsigned int u);
int				ft_printf_xxp(uintptr_t x, char type);

#endif
