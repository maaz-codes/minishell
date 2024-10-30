#include "minishell.h"

int filler(char **res,char *s,int position,int len,char symbol)
{
    if(!malloc_safe(res,position,len + 1))
        return 0;
    ft_strlcpy_modif(res[position],s - len,len + 1,symbol);
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
        if(*s == symbol && *(s + 1) == symbol)
            (res[position] = NULL,s += 2);
        while(*s != ' ' && *s)
        {   
            if(*s == '\'' || *s == '"')
            {   
                symbol = symbol_checker(*s);
                printf("symbol is: %c\n",symbol);
                s += 1;
                while(*s)
                {   
                    len++;
                    printf("%c",*s);
                    if(*(s + 1) == symbol)
                        break;
                    s++;
                }
                printf("\n");
                printf("len: %d\n",len);
            }
            len++;
            s++;
        }
        if(len && position < tokens)
            position += filler(res,s,position,len,symbol);
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
    int closed;

    while(*s)
    {   
        inside = 0;
        symbol = symbol_checker(*s);
        if(*s == symbol && *(s + 1) == symbol)
            s += 2;
        while(*s != ' ' && *s)
        {   
            printf("%c",*s);
            if(*s == '"' || *s == '\'')
            {   
                closed = -1;
                symbol = symbol_checker(*s);
                s += 1;
                while(*s)
                {   
                    printf("%c",*s);
                    if(*s == symbol)
                    {
                        closed *= -1;
                        break;
                    }
                    s++;
                }
                if(closed == -1)
                    return -1;
            }
            if(!inside)
            {
                inside = 1;
                tokens++;
            }
            s++;
        }
        s++;
    }
    printf("\ntokens total: %d\n",tokens);
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
    if(tokens == -1)
        printf("\nbruh not valid\n");
    res = (char **)malloc(sizeof(char *) * (tokens + 1));
    if(!res)
        return (NULL);
    res[tokens] = NULL;
    malloc_everything(res,input,tokens,position);
    return(res);
}

