#include "minishell.h"

int malloc_everything(char **res, char *s,int tokens)
{
    int len;
    char symbol;
    int position;

    position = 0;
    while(*s)
    {   
        len = 0;
        symbol = symbol_checker(*s);
        if(*s == symbol && *(s + 1) == symbol)
        {
            res[position] = NULL;
            s += 2;
        }
        else if((*s == symbol) && *(s + 1) != symbol)
        {   
            s += 1;
            while(*s != symbol && *s)
            {   
                if(*s == '\0')
                    return 0;
                len++;
                s++;
            }
        }
        while(*s != ' ' && !(*s == '"' || *s == '\'') && *s)
        {
            s++;
            len++;
        }
        if(len && position < tokens)
        {
            if(!malloc_safe(res,position,len + 1))
                return 0;
            ft_strlcpy(res[position],s - len,len + 1);
            position++;
        }
        s++;
    }
    return 1;
}


int checker_tokens(char *s)
{
    int i;
    char symbol;
    int tokens;
    int inside;

    i = 0;
    tokens = 0;
    while(s[i])
    {   
        inside = 0;
        while(s[i] != ' ' && !(s[i] == '"' || s[i] == '\'') && s[i])
        {   
            if(!inside)
            {
                inside = 1;
                tokens++;
            }
            i++;
        }
        if(s[i] == '"' || s[i] == '\'')
        {   
            symbol = symbol_checker(s[i]);
            i += 1;
            tokens += 1;
            while(s[i] != symbol)
            {   
                if(s[i] == '\0')
                    return 0;
                i++;
            }
        }
        i++;
    }
    return tokens;
}

char **tokenization_char(char *input)
{
    char **res;
    int tokens;

    if(!input)
        return (NULL);
    tokens = checker_tokens(input);
    res = (char **)malloc(sizeof(char *) * (tokens + 1));
    if(!res)
        return (NULL);
    res[tokens] = NULL;
    if(!malloc_everything(res,input,tokens))
    {
        printf("error malloc everything");
        return (NULL);
    }
    return(res);
}