#include "pipex.h"

size_t	get_path_line_from_env(t_pipex *pipex)
{
	size_t i;
	
	i = 0;
	while(pipex->env[i] != NULL)
	{
		if (ft_strncmp(pipex->env[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (0);
}

char	**split_list_of_directry_from_path_line(t_pipex *pipex, size_t path_index)
{
	size_t	trim_len;
	char	**list;
	
	list = NULL;
	list = ft_split(pipex->env[path_index], ':');
	//malloc失敗時
	trim_len = ft_strlen("PATH=");
	//void *tmp;
	//tmp = list[0];
	//freeできない書き方してる
	list[0] = ft_substr(list[0] + trim_len, 0 ,ft_strlen(list[0]));
	//free(tmp);
	return (list);
}

char	**join_slash_path_of_directory(char **temp_devided_list)
{
	char	**list_of_directry;
	size_t	i;
	size_t	len;

	list_of_directry = NULL;
	len = count_pointer_including_null(temp_devided_list);
	list_of_directry = malloc(sizeof(char *) * len);
	//malloc失敗時
	i = 0;
	while (temp_devided_list[i] != NULL)
	{
		list_of_directry[i] = ft_strjoin(temp_devided_list[i], "/");
		//safe_free(&temp_devided_list[i]);
		i++;
	}
	list_of_directry[i] = NULL;
	//safe_free(&temp_devided_list[i]);
	//free(temp_devided_list);
	//temp_devided_list = NULL;
	return (list_of_directry);
}

size_t	count_pointer_including_null(char **list)
{
	size_t count;

	count = 0;
	while (list[count] != NULL)
		count++;
	count++;
	return (count);
}