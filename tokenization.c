#include "minishell.h"

int filler(char **res,char *s,int position,int len)
{
    if(!malloc_safe(res,position,len + 1))
        return 0;
    ft_strlcpy(res[position],s - len,len + 1);
    return 1;
}

int null_check(char **res, char *s)
{   
    if(*s == '\0')
        (printf("exit now: null\n"),free_double(res),exit(EXIT_FAILURE));
    return 1;
}

void malloc_everything(char **res, char *s,int tokens,int position)
{
    int len;
    char symbol;
    
    while(*s)
    {   
        len = 0;
        symbol = symbol_checker(*s);
        if(*s == symbol && *(s + 1) == symbol)
            (res[position] = NULL,s += 2);
        else if((*s == symbol) && *(s + 1) != symbol)
        {   
            s += 1;
            while(*s != symbol && *s)
            {   
                len += null_check(res,s);
                s++;
            }
        }
        while(*s != ' ' && !(*s == '"' || *s == '\'') && *s)
            (s++,len++);
        if(len && position < tokens)
            position += filler(res,s,position,len);
        s++;
    }
}

int inside_check(int inside, int tokens)
{
    if(!inside)
    {
        inside = 1;
        tokens++;
    }
    return tokens;
}

int checker_tokens(char *s, char symbol, int tokens, int inside)
{
    while(*s)
    {   
        inside = 0;
        while(*s != ' ' && !(*s == '"' || *s == '\'') && *s)
        {   
            tokens += inside_check(inside,tokens);
            s++;
        }
        if(*s == '"' || *s == '\'')
        {   
            symbol = symbol_checker(*s);
            s += 1;
            tokens += 1;
            while(*s != symbol)
            {   
                if(*s == '\0')
                    return 0;
                s++;
            }
        }
        s++;
    }
    return tokens;
}

char **tokenization_char(char *input)
{
    char **res;
    char symbol;
    int t_holder;
    int inside;
    int tokens;
    int position;

    inside = 0;
    symbol = '\0';
    t_holder = 0;
    position = 0;
    if(!input)
        return (NULL);
    tokens = checker_tokens(input,symbol,t_holder,inside);
    res = (char **)malloc(sizeof(char *) * (tokens + 1));
    if(!res)
        return (NULL);
    res[tokens] = NULL;
    malloc_everything(res,input,tokens,position);
    return(res);
}

