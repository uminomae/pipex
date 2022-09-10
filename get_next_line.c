//#include "get_next_line.h"
#include "pipex.h"
# define BUFFER_SIZE 4

static const char *to_empty(const char *s)
{
    if (s == NULL)
        return ("");
    else
        return (s);
}

static char *get_string(int fd, char *save_str, ssize_t *len_byte)
{
    char    *buf;
    char    *tmp;

    buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (buf == NULL)
        return (NULL);
    *len_byte = read(fd, buf, BUFFER_SIZE);
    if (*len_byte < 0)
    {
        free(buf);
        return (NULL);
    }
    else if (*len_byte == 0)
    {
        free(buf);
        return (save_str);
    }
    buf[*len_byte] = '\0';
    tmp = save_str;
    save_str = ft_strjoin(to_empty(save_str), to_empty(buf));
    free(tmp);
    free(buf);
    return (save_str);
}

//TODO  tmp = save_str;//不要? free(tmp);//不要
static char *save_buffer(char *lf_ptr, char *save_str, ssize_t len_byte)
{
    ssize_t len_trim;
    ssize_t len_to_null_c;
    char    *ret_str;
    char    *tmp;

    if (len_byte == 0)
        return (NULL);
    len_trim = lf_ptr - save_str + 1;
    len_to_null_c = ft_strlen(to_empty(save_str)) - len_trim;
    if (len_to_null_c == 0)
    {
        free(save_str);
        return (NULL);
    }
    tmp = save_str;
    ret_str = ft_substr(save_str + len_trim, 0, len_to_null_c);
    free(tmp);
    return (ret_str);
}

static char *get_output_line(char *save_str, char *lf_ptr, ssize_t len_byte)
{
    ssize_t len_trim;

    len_trim = lf_ptr - save_str + 1;
    if (len_byte == 0)
        return (save_str);
    else
        return (ft_substr(save_str, 0, len_trim));
}

char    *get_next_line(int fd)
{
    static char *save_str;
    char        *lf_ptr;
    char        *ret_str;
    ssize_t     len_byte;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    len_byte = 1;
    lf_ptr = NULL;
    while (len_byte != 0)
    {
        lf_ptr = ft_strchr(save_str, '\n');
        if (lf_ptr == NULL)
        {
            save_str = get_string(fd, save_str, &len_byte);
            if (save_str == NULL)
                return (NULL);
        }
        else
            break ;
    }
    ret_str = get_output_line(save_str, lf_ptr, len_byte);
    save_str = save_buffer(lf_ptr, save_str, len_byte);
    return (ret_str);
}