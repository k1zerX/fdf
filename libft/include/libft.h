/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 17:48:49 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/01 10:50:25 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "get_next_line.h"

# define LOG_PR 0.000001
# define LOG_ADD_PR 1000000

# define ABS(x) (x < 0 ? -(x) : x)
# define SIGN(x) (x < 0 -1 : 1)
# define FT_MIN(a,b) (a < b ? a : b)
# define FT_MAX(a,b) (a > b ? a : b)

typedef struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}						t_list;

typedef struct			s_btree
{
	void				*content;
	size_t				content_size;
	char				color;
	struct s_btree		*left;
	struct s_btree		*right;
}						t_btree;

typedef struct			s_elem
{
	void				*content;
	size_t				content_size;
	struct s_elem		*next;
}						t_elem;

typedef struct			s_queue
{
	t_elem				*start;
	t_elem				*end;
	size_t				len;
}						t_queue;

typedef struct			s_stack
{
	t_elem				*start;
	size_t				len;
}						t_stack;

int						ft_atoi(const char *str);
void					ft_bzero(void *s, size_t n);
int						ft_isalnum(int c);
int						ft_isalpha(int c);
int						ft_isascii(int c);
int						ft_isdigit(int c);
int						ft_isprint(int c);
char					*ft_itoa(int n);
void					*ft_memalloc(size_t size);
void					*ft_memccpy(void *dst, \
							const void *src, int c, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memcpy(void *dst, \
							const void *src, size_t n);
void					ft_memdel(void **ap);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memset(void *b, int c, size_t len);
void					ft_putchar(char c);
void					ft_putchar_fd(char c, int fd);
void					ft_putendl(char const *s);
void					ft_putendl_fd(char const *s, int fd);
void					ft_putnbr(int n);
void					ft_putnbr_fd(int n, int fd);
void					ft_putstr(char const *s);
void					ft_putstr_fd(char const *s, int fd);
char					*ft_strcat(char *s1, const char *s2);
char					*ft_strchr(const char *s, int c);
void					ft_strclr(char *s);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strcpy(char *dst, const char *src);
void					ft_strdel(char **as);
char					*ft_strdup(const char *s1);
int						ft_strequ(char const *s1, char const *s2);
void					ft_striter(char *s, void (*f)(char *));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strjoin(char const *s1, char const *s2);
size_t					ft_strlcat(char *dst, \
							const char *src, size_t size);
size_t					ft_strlen(const char *s);
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s, \
							char (*f)(unsigned int, char));
char					*ft_strncat(char *s1, \
							const char *s2, size_t n);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strncpy(char *dst, const char *src, size_t len);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
char					*ft_strnew(size_t size);
char					*ft_strnstr(const char *haystack, \
							const char *needle, size_t len);
char					*ft_strrchr(const char *s, int c);
char					**ft_strsplit(char const *s, char c);
char					*ft_strstr(const char *haystack, const char *needle);
char					*ft_strsub(char const *s, \
							unsigned int start, size_t len);
char					*ft_strtrim(char const *s);
int						ft_tolower(int c);
int						ft_toupper(int c);
t_list					*ft_lstnew(void const *content, size_t content_size);
void					ft_lstdelone(t_list **alst, \
							void (*del)(void *, size_t));
void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void					ft_lstadd(t_list **alst, t_list *new);
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void					ft_btree_infix(t_btree *start, \
							void (*f)(t_btree *));
void					ft_btree_prefix(t_btree *start, \
							void (*f)(t_btree *));
void					ft_btree_suffix(t_btree *start, \
							void (*f)(t_btree *));
t_btree					*ft_btree_new(void const *content, \
							size_t content_size);
void					ft_btree_insert(t_btree **start, \
							void const *content, size_t content_size, \
							int (*cmp)(const void *, const void *, size_t));
void					ft_btree_bfs(t_btree *start, \
							void (*f)(t_btree *));
t_btree					ft_btree_search(t_btree *start, void *content, \
							size_t content_size);
t_elem					*ft_queue_pop(t_queue *queue);
void					ft_queue_push(t_queue *queue, t_elem *tmp);
t_queue					*ft_queue_new(void);
t_stack					*ft_stack_new(void);
t_elem					*ft_stack_pop(t_stack *stack);
void					ft_stack_push(t_stack *stack, t_elem *tmp);
t_elem					*ft_new_elem(void *content, \
							size_t content_size, char copy);
void					*ft_realloc(void *src, size_t size, long dif);
void					*ft_min(void *a, void *b, size_t size);
void					*ft_max(void *a, void *b, size_t size);
char					*ft_itoa_base(int n, int base);
void					ft_swap(void *a, void *b, size_t size);
int						ft_count_matches(const char *str, const char *match);

#endif
