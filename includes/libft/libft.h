/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:20:53 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/15 16:58:31 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h> // for malloc
# include <unistd.h> // for write
# include <stdint.h> // for SIZE_MAX
# include <stdarg.h> // for viadic functions handling
# include <limits.h> // NULL, MAX_INT, etc...

/* GNL */

# define MAX_FD	1024
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
/* PRINT_F */
# define LOWER_HEXA "0123456789abcdef"
# define UPPER_HEXA "0123456789ABCDEF"
# define DEC "0123456789"

# define DEL 127

#define _ULLONG unsigned long long int

/* Simple chained list*/
typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}	t_list;

/* libc like */
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_atoi(char *nptr);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit_negative(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_lstsize(t_list *lst);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_tolower(int c);
int		ft_toupper(int c);
long	ft_atoi_intmax(char *nptr);
_ULLONG	ft_atoll(char *nptr);
size_t	ft_arrlen(char **arr);
size_t	ft_dstrlen(char **s);
size_t	ft_isspace(char c);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
ssize_t	ft_putchar_fd(char c, int fd);
ssize_t	ft_putendl_fd(char *s, int fd);
ssize_t	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	ft_putnbr_fd(int n, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/* ft_printf */
ssize_t	read_str(char flag, va_list arg_list);
ssize_t	ft_parse_format(const char *s, va_list arg_list,
				size_t *count, ssize_t *len);
int		ft_printf(const char *str, ...)
		__attribute__ ((format (printf, 1, 2)));
ssize_t	ft_p_putnbr(size_t nbr, int *count);
ssize_t	ft_putnbr_base(int long nbr, char *base, int *count);
ssize_t	ft_u_putnbr_base(unsigned int nbr, char *base, int *count);
ssize_t	printc(va_list arg_list);
ssize_t	printd(va_list arg_list, char flag);
ssize_t	printp(va_list arg_list);
ssize_t	printpercent(void);
ssize_t	printstr(va_list arg_list);
ssize_t	printx(va_list arg_list, char flag);

/* get_next_line */
// char	*ft_buffer_alloc(void);
char	*ft_free(char *s1, char *s2);
char	*ft_join_buff(char *buff, char *read);
char	*ft_read(char *buff, int *check, int fd);
char	*ft_split_buff(char *buff, char *leftover);
char	*get_next_line(int fd);
ssize_t	ft_len(const char *s, char c);

/* Chained Lists */
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstfree(t_list **lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), \
		void (*del)(void *));
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));

/* Utils */
void	free_dtab(char **dtab);

#endif