#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "get_next_line.h"

static bool reserve(t_buffer *buffer, size_t size)
{
	char *reallocated;

	if (buffer->capacity - buffer->length < size) {
		reallocated = malloc(buffer->length + size);
		if (reallocated == NULL)
			return false;
		if (buffer->data)
			ft_memmove(reallocated, buffer->data, buffer->capacity);
		free(buffer->data);
		buffer->data = reallocated;
		buffer->capacity = buffer->length + size;
	}
	return true;
}

char *get_next_line(int fd)
{
	static t_buffer	buffer;
	ssize_t			read_count;
	char			*line;
	char			*eol_pos;
	size_t			line_length;

	read_count = BUFFER_SIZE;
	line = NULL;
	eol_pos = NULL;
	line_length = 0;
	while ((eol_pos = ft_memchr(buffer.data, '\n', buffer.length)) == NULL && read_count == BUFFER_SIZE) {
		if (!reserve(&buffer, BUFFER_SIZE)) {
			read_count = -1;
			break;
		}
		read_count = read(fd, buffer.data + buffer.length, BUFFER_SIZE);
		if (read_count == -1)
			break;
		buffer.length += read_count;
	}
	if (read_count != -1 && buffer.length > 0) {
		if (eol_pos != NULL)
			line_length = eol_pos - buffer.data + 1; // +1 for \n
		else if (buffer.length > 0)
			line_length = buffer.length;
		line = ft_strndup(buffer.data, line_length);
		if (!line)
			read_count = -1;
		buffer.length -= line_length;
		ft_memmove(buffer.data, buffer.data + line_length, buffer.length);
	}
	if (read_count <= 0) {
		free(buffer.data);
		buffer.data = NULL;
		buffer.length = 0;
		buffer.capacity = 0;
		if (read_count == -1) {
			free(line);
			line = NULL;
			return NULL;
		}
	}
	return line;
}
