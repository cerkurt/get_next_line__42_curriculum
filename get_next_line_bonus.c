/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: Ceren Kurt <cerkurt@student.codam.nl>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/11 19:13:58 by Ceren Kurt    #+#    #+#                 */
/*   Updated: 2025/11/28 16:26:02 by cerkurt       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file: get_next_line_bonus.c
 * @note: Last 4 of the helper functions for the main function. 
 */
#include "get_next_line_bonus.h"

/**
 * @name: gnl_line_search
 * @brief: Reads from the file until either a newline is found,
 * or end of the file.
 * @return: New buffer that contains everything up to and including
 * the next newline, or the rest of the file if no newline exists.
 */
char	*gnl_line_search(int fd, char *content)
{
	char	*temp_buf;
	int		read_data;

	temp_buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp_buf)
		return (gnl_safety_free(content));
	read_data = 1;
	while ((!gnl_strchr(content, '\n') && read_data > 0))
	{
		read_data = read(fd, temp_buf, BUFFER_SIZE);
		if (read_data == -1)
			return (free(temp_buf), gnl_safety_free(content));
		temp_buf[read_data] = '\0';
		content = gnl_join_and_free(content, temp_buf);
		if (!content)
			return (free(temp_buf), NULL);
	}
	temp_buf[read_data] = '\0';
	return (free(temp_buf), content);
}

/**
 * @name: gnl_line_distilation
 * @brief: Extracts the first full line from the accumulated
 * buffer and allocate and return only that line.
 * @return: '\n' terminated line ready to be used in main function.
 */
char	*gnl_line_distilation(char *buffer)
{
	char	*line;
	size_t	len;
	size_t	i;

	if (!buffer || !buffer[0])
		return (NULL);
	len = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	if (buffer[len] == '\n')
		len++;
	line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = buffer[i];
		i++;
	}
	line[len] = '\0';
	return (line);
}

/**
 * @name: gnl_buffer_update
 * @brief: Removes the line just distiled and keep only
 * the leftover part after the newline.
 * @return: New buffer that contains rest of the file after
 * the returned (distiled) line.
 */
char	*gnl_buffer_update(char *buffer)
{
	char	*new_buffer;
	size_t	i1;
	size_t	i2;

	if (!buffer)
		return (NULL);
	i1 = 0;
	while (buffer[i1] && buffer[i1] != '\n')
		i1++;
	if (!buffer[i1])
		return (gnl_safety_free(buffer));
	new_buffer = malloc((gnl_strlen(buffer) - i1 + 1) * sizeof(char));
	if (!new_buffer)
		return (gnl_safety_free(buffer));
	i1++;
	i2 = 0;
	while (buffer[i1] != '\0')
		new_buffer[i2++] = buffer[i1++];
	new_buffer[i2] = '\0';
	free(buffer);
	return (new_buffer);
}

/**
 * @name: gnl_join_and_free
 * @brief: Appends the leftover data to the buffer during
 * the calls and frees the previous one.
 * @return: A new allocated string which contains buffer
 * and the remainig data from the previous call.
 */
char	*gnl_join_and_free(char *buffer, char *append)
{
	char	*new_str;

	new_str = gnl_strjoin(buffer, append);
	if (!new_str)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (new_str);
}

/**
 * @name: get_next_line
 * @brief: reads from the file descriptor until the end
 * of the line/new line found. 
 * @return: a complete new line or null (nothing to display)
 * if there is no new lines. handles file descriptor errors
 * on the first call then uses line_search to look for a complete
 * new line. when a proper complete line is found, extracts it
 * from the rest, and updates the buffer with the new value. prints
 * the line and does the process again.
 */
char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		buffer[fd] = gnl_safety_free(buffer[fd]);
		return (NULL);
	}
	buffer[fd] = gnl_line_search(fd, buffer[fd]);
	if (!buffer[fd] || !buffer[fd][0])
	{
		buffer[fd] = gnl_safety_free(buffer[fd]);
		return (NULL);
	}
	line = gnl_line_distilation(buffer[fd]);
	if (!line)
	{
		buffer[fd] = gnl_safety_free(buffer[fd]);
		return (NULL);
	}
	buffer[fd] = gnl_buffer_update(buffer[fd]);
	return (line);
}
