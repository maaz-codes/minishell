#include "minishell.h"

// int signal_caught;

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

char  *signal_checkpoint()
{
    char *input;

    set_signals();
    input = readline("minishell> ");
	set_signals_after();
    if(!input)
    {
        printf("\nexiting now...\n");
        exit(0);
    }
    return (input);
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
	ancient_one->paths = paths;
	ancient_one->catch_signal = 0;

	dup_fds(&std_fds);
	while (1)
	{
        input = signal_checkpoint();
		if (input)
		{
			add_history(input);
			tree = tokenization(&input);
			ancient_one->head = tree;
			if (tree)
				execution(tree, env, ancient_one);
			lumberjack(tree);
			reset_std_fds(&std_fds);
		}
		else
		{
			printf("readline failure\n");
			exit(1);
		}
	}
	return (0);
}
