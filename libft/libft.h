/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyu <seyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 15:55:03 by seyu              #+#    #+#             */
/*   Updated: 2020/06/12 03:25:52 by seyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>

/*
**	PART1 FUNCTIONS
*/

void		*ft_memset(void *s, int c, size_t size);
void		ft_bzero(void *s, size_t size);
void		*ft_memcpy(void *dst, void *src, size_t size);
void		*ft_memccpy(void *dst, const void *src, int constant, size_t size);
void		*ft_memmove(void *dst, const void *src, size_t n);
void		*ft_memchr(const void *space, int constant, size_t size);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dest, char *src, size_t size);
char		*ft_strchr(const char *str, int character);
char		*ft_strrchr(const char *str, int character);
char		*ft_strnstr(const char *big, const char *little, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *nptr);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strdup(const char *str);

/*
**	PART2 FUNCTIONS
*/

char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_putchar_fd(unsigned char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

/*
**	BONUS PART FUNSTIONS
*/

struct		s_list
{
	void			*content;
	struct s_list	*next;
};
typedef struct s_list	t_list;

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *newlst);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *newlst);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*
**	EXTRA FUNCTIONS
*/

int			ft_isspace(int c);
int			ft_isupper(int c);
int			ft_islower(int c);
int			ft_isodigit(int c);
int			ft_isxdigit(int c);
long		ft_strtol(const char *nptr, const char **endptr, int base);
long long	ft_strtoll(const char *nptr, const char **endptr, int base);
char		*ft_itostr(int numb, char *base);
char		*ft_ltostr(long int	numb, char *base);
char		*ft_lltostr(long long int numb, char *base);
char		*ft_ulltostr(unsigned long long int numb, char *numstr, char *base);
void		*ft_print_memory(void *addr, unsigned int size);
int			ft_intmax(int a, int b);
int			ft_intlogn(size_t numb, int base);
int			ft_intlog(size_t n);

#endif
