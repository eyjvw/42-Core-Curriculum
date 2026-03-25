/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 21:23:08 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/19 18:31:08 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>
# include <stdbool.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 255
# endif
# ifndef FD_MAX
#  define FD_MAX 1024
# endif
# ifndef FILE_BUFFER_SIZE
#  define FILE_BUFFER_SIZE 255
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

//Chars
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_isspace(int c);
size_t	ft_strlen(const char *s);
bool	ft_isset(char c, const char *set);

//Memory
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_realloc(void *old, size_t old_size, size_t new_size);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

//Search
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strtok(char *str, const char *delim);

//Strs
char	*ft_strdup(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(const char *str, const char *sep);
char	*ft_itoa(int n);

//Double strs
size_t	ft_strmaxlen(char **strs);
size_t	ft_doublelen(char **strs);
char	**ft_doubledup(char **srcs);
void	ft_double_free(char **strs);
void	ft_double_write(char **strs);
char	**ft_double_realloc(char **old, size_t old_ptr_n, size_t new_ptr_n);
char	**ft_add_row(char *new_row, char **strs);
char	**ft_delete_row(size_t id, char **strs);
char	**ft_replace_row(size_t id, char *new_row, char **strs);

//Puts
void	ft_write(char *s);
void	ft_write_error(char *s);
void	ft_write_errorn(char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

//Linked List
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//Get Next Line
char	*get_next_line(int fd);
char	*join_and_free(char *s1_tofree, char *buffer);
char	*kill_func(char *buffer, char **rest, int error);
int		ft_lento(char *s, char c);

//file
char	**ft_dump_file(char *file_path);

#endif
