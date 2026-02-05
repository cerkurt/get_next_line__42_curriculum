/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: Ceren Kurt <cerkurt@student.codam.nl>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/12 11:44:40 by Ceren Kurt    #+#    #+#                 */
/*   Updated: 2025/11/28 16:26:05 by cerkurt       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file: get_next_line_bonus.h
 * @brief: header file for all the gnl function files.
 * @note: Project contains 10 functions in total. 4 from libft and 6 new for gnl.
 */
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# include <unistd.h> // for read function
# include <stdlib.h> // for malloc and free fucntions, and for NULL macro
# include <stddef.h> // for size_t return type

// libft functions
size_t	gnl_strlen(const char *s);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strjoin(char const *s1, char const *s2);

// new gnl functions
char	*get_next_line(int fd);
char	*gnl_safety_free(char *buf);
char	*gnl_buffer_update(char *buffer);
char	*gnl_line_distilation(char *buffer);
char	*gnl_line_search(int fd, char *content);
char	*gnl_join_and_free(char *buffer, char *append);

#endif