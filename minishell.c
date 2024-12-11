#include "minishell.h"

void mini_fuk(t_ancient *ancient_one)
{
	ft_lstclear_env(&ancient_one->paths->env_struct);
	ft_lstclear_exp(&ancient_one->paths->exp_struct);
	ft_lstclear_path(&ancient_one->paths);
	lumberjack(ancient_one->head);
	free(ancient_one);
	printf("nuked everything\n");
}

char *get_cwd(void)
{
    char cwd[1024];
    char *res;
    if(getcwd(cwd,sizeof(cwd)) == NULL)
        printf("error");
    res = new_path(cwd,0);
    return(res);
}

t_path	*int_cd(void)
{
	t_path	*node_new;
    char    *str1;
    char    *str2;

    str1 = get_cwd();
    str2 = get_cwd();
	node_new = (t_path *)malloc(sizeof(t_path));
	if (node_new == NULL)
		return (NULL);
	node_new->pwd = str1;
	node_new->pwd_old = str2;
	node_new->next = NULL;
	return (node_new);
}

void dup_fds(t_std_fds *std_fds)
{
	std_fds->std_in = dup(STDIN_FILENO);
	std_fds->std_out = dup(STDOUT_FILENO);
	std_fds->std_err = dup(STDERR_FILENO);
}

void reset_std_fds(t_std_fds *std_fds)
{
	dup2(std_fds->std_in, STDIN_FILENO);
	dup2(std_fds->std_out, STDOUT_FILENO);
	dup2(std_fds->std_err, STDERR_FILENO);
	close(std_fds->std_in);
	close(std_fds->std_out);
	close(std_fds->std_err);
}

char  *signal_checkpoint(t_std_fds *std_fds, t_ancient *ancient_one)
{
    char *input;

    set_signals();
    input = readline("minishell> ");
	set_signals_after();
    if(!input)
    {
        printf("\nexiting now...\n");
		reset_std_fds(std_fds);
		mini_fuk(ancient_one);
        exit(0);
    }
    return (input);
}

void execution(t_tree *tree, char **env, t_ancient *ancient_one)
{
	pid_t pid;

	find_docs(tree);
	tree->level = 0;
	gallows(tree, env, tree->type == NODE_OPERATOR, ancient_one);
}


int	main(int ac, char **av, char **env)
{
	char		*input;
	t_tree		*tree;
	t_std_fds 	std_fds;
	t_ancient 	*ancient_one;

    t_path *paths;

    paths = int_cd();
    paths->env_struct = int_env(env);
    paths->exp_struct = int_exp(env);
	ancient_one = malloc(sizeof(t_ancient));
	if (!ancient_one)
		print_exit(ERR_MALLOC); // free the paths...
	ancient_one->paths = paths;

	dup_fds(&std_fds);
	while (1)
	{
        input = signal_checkpoint(&std_fds, ancient_one);
		if (input)
		{
			add_history(input);
			// printf("old_str = -%s-\n", input);
			// printf("expanded_str = -%s-\n", env_expansion(input, env_vars));
			tree = tokenization(input);
			ancient_one->head = tree;
			ancient_one->std_fds = &std_fds;
			if (tree)
				execution(tree, env, ancient_one);
			ancient_one->head = lumberjack(ancient_one->head);
			reset_std_fds(&std_fds);
		}
		else
		{
			printf("readline failure\n");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}
