#include "../minishell.h"

int count_array(char **array)
{
	int len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

void add_node(t_tree **tree, t_tree *node, int side)
{
	if (!node)
		return ;
	if (*tree == NULL)
	{
		*tree = node;
		return ;
	}
	if ((*tree)->left == NULL && side == LEFT)
		(*tree)->left = node;
	else if ((*tree)->right == NULL)
		(*tree)->right = node;
}

void print_data(t_tree *tree)
{
	int i = -1;
	while (++i < tree->level)
		printf("	");
	if (tree->type == NODE_EXPRESSION)
		printf("%c: %s type: exp\n", tree->pos, tree->data.expression);
	else if (tree->type == NODE_LOG_OPERATOR)
		printf("%c: %s type: log_operator\n", tree->pos, tree->data.log_operator);
	else if (tree->type == NODE_OPERATOR)
		printf("%c: %c type: operator\n", tree->pos, tree->data.operator);
	else if (tree->type == NODE_REDIRECTION)
		printf("%c: %s type: redir^\n", tree->pos, tree->data.redirection);
	else if (tree->type == NODE_FILE)
		printf("%c: %s type: file\n", tree->pos, tree->data.file);
	else if (tree->type == NODE_HEREDOC)
		printf("%c: %d type: here_doc\n", tree->pos, tree->data.here_doc);
	else if (tree->type == NODE_LIMITER)
		printf("%c: %s type: limiter\n", tree->pos, tree->data.file);
	else if (tree->type == NODE_COMMAND)
		printf("%c: %s type: cmd\n", tree->pos, tree->data.command);
	else if (tree->type == NODE_ARGUMENT)
	{
		printf("%c: ", tree->pos);
		i = -1;
		while(tree->data.argument[++i])
			printf("%s, ", tree->data.argument[i]);
		printf("type: args\n");
	}
	printf("\n");
}

void print_tree(t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->left != NULL)
	{
		tree->left->level += tree->level;
		tree->left->pos = 'l';
		
		print_tree(tree->left);
	}
	if (tree->right != NULL)
	{
		tree->right->level += tree->level;
		tree->right->pos = 'r';
		print_tree(tree->right);
	}
	print_data(tree);
}
