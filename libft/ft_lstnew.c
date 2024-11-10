#include "../minishell.h"

t_path	*ft_lstnew(char *content)
{
	t_path	*node_new;

	node_new = (t_path *)malloc(sizeof(t_path));
	if (node_new == NULL)
		return (NULL);
	node_new->pwd = content;
	node_new->next = NULL;
	return (node_new);
}