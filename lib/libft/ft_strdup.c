#include "libft.h"

char    *ft_strdup(const char *s1)
{
    size_t  len;
    char    *copy;

    if (!s1)
        return (NULL);
    len = ft_strlen(s1);
    copy = (char *)ft_calloc(len + 1, sizeof(char));
    if (!copy)
        return (NULL);
    ft_memcpy(copy, s1, len);
    copy[len] = '\0';
    return (copy);
}
