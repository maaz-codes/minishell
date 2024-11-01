#include "minishell.h"

int filler(char **res,char *s,int position,int len,char symbol)
{
    if(!malloc_safe(res,position,len + 1))
        return 0;
    ft_strlcpy_modif(res[position],s - len,len + 1,symbol);
    return 1;
}

int filler_last(char **res,char *s,int position,int len)
{
    if(!malloc_safe(res,position,len + 1))
        return 0;
    ft_strlcpy(res[position],s,len + 1);
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
    char *temp;
    char *joined_str;
    char *holder; 

    while(*s)
    {   
        joined_str = ft_strdup("");
        len = 0;
        while(*s == ' ' && *s)
            s++;
        if(*s == symbol && *(s + 1) == symbol)
            (res[position++] = NULL,s += 2);
        while(*s != ' ' && *s)
        {   
            len = 0;
            symbol = symbol_checker(*s);
            if(*s == '\'' || *s == '"')
            {   
                s += 1;
                while(*s)
                {   
                    if(*s == symbol)
                    {
                        s++;
                        break;
                    }
                    len++;
                    s++;
                }
                printf("\n");
                filler(res,s - 1,position,len,symbol);
                temp = ft_strjoin(joined_str,res[position]);
                (free(joined_str),free(res[position]));
                joined_str = temp;
            }
            else
            {
                while(*s != ' ' && *s != '\'' && *s != '"')
                {   
                    s++;
                    len++;
                }
                filler(res,s,position,len,symbol);
                temp = ft_strjoin(joined_str,res[position]);
                (free(joined_str),free(res[position]));
                joined_str = temp;
            }
        }
        if(position < tokens)
        {
            position += filler_last(res,joined_str,position,ft_strlen(joined_str));
            free(joined_str);
        }
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
    int i = 0;
    while(s[i])
    {   
        inside = 0;
        symbol = symbol_checker(s[i]);
        if(s[i] == symbol && s[i + 1] == symbol)
            i += 2;
        while(s[i] == ' ' && s[i])
            i++;
        while(s[i] != ' ' && s[i])
        {   
            printf("%c",s[i]);
            if(s[i] == '"' || s[i] == '\'')
            {   
                closed = -1;
                symbol = symbol_checker(s[i]);
                i += 1;
                while(s[i])
                {   
                    printf("%c",s[i]);
                    if(s[i] == symbol)
                    {
                        closed *= -1;
                        break;
                    }
                    i++;
                }
                if(closed == -1)
                    return -1;
            }
            if(!inside)
            {
                inside = 1;
                tokens++;
            }
            i++;
        }
    }
    printf("\ntotal len: %d\n",i);
    printf("ft_strlen: %ld\n",ft_strlen(s));
    printf("tokens total: %d\n",tokens);
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
    {
        printf("\nbruh not valid\n");
        exit(EXIT_FAILURE);
    }
    res = (char **)malloc(sizeof(char *) * (tokens + 1));
    if(!res)
        return (NULL);
    res[tokens] = NULL;
    malloc_everything(res,input,tokens,position);
    return(res);
}

