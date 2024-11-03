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

void malloc_everything(char **res, char *s,int tokens,int position)
{
    int len;
    char symbol;
    int closed;

    char *temp;
    char *joined_str;
    char *holder;

    int i = 0;

    while(s[i])
    {
        joined_str = ft_strdup("");
        len = 0;
        while(s[i] == ' ' && s[i])
            i++;
        if(s[i] == '"' || s[i] == '\'')
        {   
            symbol = symbol_checker(s[i]);
            if(s[i + 1] == symbol)
            {
                printf("pass here double '\"\"'\n");
                (i += 2);
            }
        }
        while(s[i] != ' ' && s[i])
        {   
            len = 0;
            if(s[i] == '"' || s[i] == '\'')
            {   
                printf("pass new if\n");
                symbol = symbol_checker(s[i]);
                if(s[i + 1] == symbol)
                    break;
            }
            if(s[i] == '"' || s[i] == '\'')
            {   
                closed = -1;
                symbol = symbol_checker(s[i]);
                i += 1;
                while(s[i])
                {   
                    if(s[i] == symbol)
                    {
                        closed *= -1;
                        break;
                    }
                    printf("%c",s[i]);
                    len++;
                    i++;
                }
                if(closed == -1)
                    return ;
                printf("\npos: %d\n",i);
                printf("len: %d\n",len);
                filler(res,s + i,position,len,symbol);
                temp = ft_strjoin(joined_str,res[position]);
                (free(joined_str),free(res[position]));
                joined_str = temp;
                i += 1;
                if(s[i] == symbol && s[i + 1] == symbol)
                {
                    i += 2;
                    break;
                }
            }
            else if(s[i])
            {   
                printf("go here no quote\n");
                while(s[i] != ' ' && s[i])
                {   
                    if(s[i] == '\'' || s[i] == '"')
                    {
                        symbol = symbol_checker(s[i]);
                        break;
                    }
                    printf("%c",s[i]);
                    i++;
                    len++;
                }
                printf("\nlen without quote: %d\n",len);
                filler(res,s + i,position,len,'\0');
                temp = ft_strjoin(joined_str,res[position]);
                (free(joined_str),free(res[position]));
                joined_str = temp;
            }
        }
        printf("the len: %d\n",len);
        if(len && position < tokens)
        {   
            printf("malloc'd: %s\n",joined_str);
            position += filler_last(res,joined_str,position,ft_strlen(joined_str));
            free(joined_str);
        }
        else 
        {
            printf("no string: %s freeing.. \n",joined_str);
            free(joined_str);
        }
    } 
    
}

int checker_tokens(char *s, char symbol, int tokens, int inside)
{   
    int closed;
    int i = 0;
    while(s[i])
    {   
        inside = 0;
        symbol = symbol_checker(s[i]);
        while(s[i] == ' ' && s[i])
            i++;
        if(s[i] == '"' || s[i] == '\'')
        {   
            symbol = symbol_checker(s[i]);
            if(s[i + 1] == symbol)
                i += 2;
        }
        while(s[i] != ' ' && s[i])
        {   
            // printf("%c",s[i]);
            if(s[i] == '"' || s[i] == '\'')
            {   
                symbol = symbol_checker(s[i]);
                if(s[i + 1] == symbol)
                    break;
            }
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
    // printf("\ntotal len: %d\n",i);
    // printf("ft_strlen: %ld\n",ft_strlen(s));
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