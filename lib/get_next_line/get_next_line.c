#include "get_next_line.h"
#include "libft.h"

static char *read_into_stash(int fd, char *stash)
{
    char    buffer[BUFFER_SIZE + 1];
    ssize_t bytes;
    char    *tmp;

    bytes = 1;
    while (bytes > 0 && (!stash || !ft_strchr(stash, '\n')))
    {
        bytes = read(fd, buffer, BUFFER_SIZE);
        if (bytes < 0)
        {
            if (stash)
                free(stash);
            return (NULL);
        }
        if (bytes == 0)
            break ;
        buffer[bytes] = '\0';
        if (!stash)
            stash = ft_strdup("");
        tmp = ft_strjoin(stash, buffer);
        free(stash);
        stash = tmp;
        if (!stash)
            return (NULL);
    }
    return (stash);
}

static char *extract_line(char *stash)
{
    size_t  i;
    char    *line;

    if (!stash || !*stash)
        return (NULL);
    i = 0;
    while (stash[i] && stash[i] != '\n')
        i++;
    if (stash[i] == '\n')
        i++;
    line = (char *)ft_calloc(i + 1, sizeof(char));
    if (!line)
        return (NULL);
    ft_memcpy(line, stash, i);
    line[i] = '\0';
    return (line);
}

static char *trim_stash(char *stash)
{
    size_t  i;
    size_t  len;
    char    *new_stash;

    i = 0;
    while (stash[i] && stash[i] != '\n')
        i++;
    if (!stash[i])
    {
        free(stash);
        return (NULL);
    }
    i++;
    len = ft_strlen(stash + i);
    new_stash = (char *)ft_calloc(len + 1, sizeof(char));
    if (!new_stash)
    {
        free(stash);
        return (NULL);
    }
    ft_memcpy(new_stash, stash + i, len);
    new_stash[len] = '\0';
    free(stash);
    return (new_stash);
}

char    *get_next_line(int fd)
{
    static char *stash[1024];
    char        *line;

    if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
        return (NULL);
    stash[fd] = read_into_stash(fd, stash[fd]);
    if (!stash[fd])
        return (NULL);
    line = extract_line(stash[fd]);
    stash[fd] = trim_stash(stash[fd]);
    return (line);
}
