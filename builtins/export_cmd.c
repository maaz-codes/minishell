/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:39:14 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/30 17:31:01 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ap_env(t_env **env, char *res)
{
	t_env	*temp;

	temp = malloc(sizeof(t_env));
	if (!temp)
		return ;
	temp->env = res;
	temp->next = NULL;
	if (*env)
		lstlast_env(*env)->next = temp;
	else
		*env = temp;
}

void	export_t_env(t_path **paths, char *tmp_char, char *sep, char *str)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = (*paths)->env_struct;
	while (str[i] != '=' && str[i])
		i++;
	if (i == ft_strlen(str))
		return ;
	while (tmp)
	{
		if (!ft_strncmp(tmp_char, tmp->env, ft_strlen(tmp_char)))
		{
			free(tmp->env);
			tmp->env = ft_strjoin(tmp_char, sep);
			return ;
		}
		tmp = tmp->next;
	}
	ap_env(&(*paths)->env_struct, ft_strjoin(tmp_char, sep));
}

void	export_t_exp(t_path **paths, char *tmp_char, char *sep, char *str)
{
	t_exp	*tmp;
	int		check;
	int		len_char;
	char	*joined_str;
	char	*only_str;

	tmp = (*paths)->exp_struct;
	joined_str = ft_strjoin(tmp_char, sep);
	only_str = ft_strdup(tmp_char);
	printf("tmp char: %s\n",tmp_char);
	checker_which_mode(str, tmp_char, &check, &len_char);
	while (tmp)
	{
		if (!ft_strncmp(tmp_char, tmp->exp, len_char))
		{	
			printf("tmp char: %s\n",tmp_char);
			exp_loop(tmp, only_str, joined_str, check);
			return ;
		}
		tmp = tmp->next;
	}
	append_check_equals(paths, only_str, joined_str, check);
}

t_exp	*int_exp(char **env)
{
	t_exp	*node_new;
	int		i;

	i = 1;
	if (!env || !env[0])
		return (NULL);
	node_new = (t_exp *)malloc(sizeof(t_exp));
	if (node_new == NULL)
		return (NULL);
	node_new->exp = ft_strdup(env[0]);
	if (!node_new->exp)
		return (NULL);
	node_new->next = NULL;
	while (env[i])
		ap_exp(&node_new, env[i++]);
	return (node_new);
}

void	export_cmd(char **str, t_path **paths, t_shl *shl)
{
	char	**sep;
	int		i;
	int		check_for_plus;
	int		exit_status;

	exit_status = 0;
	i = 1;
	if (!ft_strncmp("export", str[0], 7) && str[1] == NULL)
		exp_print(paths, 0);
	else if (!ft_strncmp("export", str[0], 7) && str[1] != NULL)
	{
		while (str[i])
		{
			check_for_plus = plus_equals_check(str[i]);
			sep = separator(str[i], check_for_plus);
			check_sep_export(sep, &i, &exit_status);
			if (!check_for_plus && sep)
				normal_export(paths, sep, str[i], &i);
			else if (check_for_plus && sep)
				plus_equals_export(paths, sep, &i);
		}
	}
	shl->exit_status = exit_status;
}
