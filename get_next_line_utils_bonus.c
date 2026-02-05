/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Ceren Kurt <cerkurt@student.codam.nl>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/12 11:44:09 by Ceren Kurt    #+#    #+#                 */
/*   Updated: 2025/11/28 16:26:13 by cerkurt       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file: get_next_line_utils_bonus.c
 * @note: 4 helper functions for the main gnl function.
 */
#include "get_next_line_bonus.h"

/**
 * @name: gnl_strlen
 * @brief: counts the line lenght and prepares the ground for the allocation.
 */
size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		i++;
	}
	return (i);
}

/**
 * @name: gnl_strjoin
 * @brief: joins string a and b and returns as string c.
 */
char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (!s2)
		return (NULL);
	len1 = gnl_strlen(s1);
	len2 = gnl_strlen(s2);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		new_str[i] = s1[i];
		i++;
	}
	while (i - len1 < len2)
	{
		new_str[i] = s2[i - len1];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

/**
 * @name: gnl_strchr
 * @brief: looking for a certain character in the given string.
 * in this case it will be '\n'.
 */
char	*gnl_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

/**
 * @name: gnl_safety_free
 * @brief: helper function to make free and return null
 * in one line in between the functions.
 */
char	*gnl_safety_free(char *buf)
{
	free(buf);
	return (NULL);
}
