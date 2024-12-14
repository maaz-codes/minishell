#include "minishell.h"

void mini_fuk(t_ancient *ancient_one)
{
	ft_lstclear_env(&ancient_one->paths->env_struct);
	ft_lstclear_exp(&ancient_one->paths->exp_struct);
	ft_lstclear_path(&ancient_one->paths);
	lumberjack(ancient_one->head);
	close(ancient_one->std_fds->std_in);
	close(ancient_one->std_fds->std_out);
	close(ancient_one->std_fds->std_err);
	free(ancient_one);
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

    set_signals(ancient_one);
    input = readline("minishell> ");
	if(signal_caught == SIGINT)
		ancient_one->exit_status = 1;
	else if(signal_caught == 0)
		ancient_one->exit_status = 0;
	// if(*input != '\0') // this is what causes segfault
	// 	signal_caught = 0;
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

	find_docs(tree,ancient_one);
	tree->level = 0;
	if (tree->type == NODE_OPERATOR)
		ancient_one->inside_pipe = TRUE;
	gallows(tree, env, ancient_one->inside_pipe, ancient_one);
}


int	main(int ac, char **av, char **env)
{
	char		*input;
	t_tree		*tree;
	t_std_fds 	std_fds;
	t_ancient 	*ancient_one;
    t_path *paths;

	if (ac != 1)
		return (write(2, "This shell doesn't take any args\n", 34), 1);
    paths = int_cd();
    paths->env_struct = int_env(env);
    paths->exp_struct = int_exp(env);
	ancient_one = malloc(sizeof(t_ancient));
	if (!ancient_one)
		print_exit(ERR_MALLOC); // free the paths...
	ancient_one->paths = paths;
	ancient_one->exit_status = 0;
	dup_fds(&std_fds);
	while (1)
	{
		ancient_one->inside_pipe = FALSE;
        input = signal_checkpoint(&std_fds, ancient_one);
		if (input)
		{
			add_history(input);
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
