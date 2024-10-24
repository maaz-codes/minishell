int tokenization(char *input)
{
    int i = 0;
    int len = checker_len(input);
    int tokens = checker_tokens(input);

    printf("len: %d\n",len);
    printf("tokens: %d\n",tokens);
    if(len > 0 && tokens > 0)
        return 1;
    else
        return 0;

}


int checker_len(char *s)
{
    int i;
    int len;
    char symbol;
    int position;

    i = 0;
    position = 0;
    while(s[i])
    {   
        len = 0;
        while(s[i] != ' ' && !(s[i] == '"' || s[i] == '\'') && s[i])
        {   
            i++;
            len++;
        }
        if(s[i] == '"' || s[i] == '\'')
        {   
            symbol = symbol_checker(s[i]);
            i += 1;
            while(s[i] != symbol)
            {   
                if(s[i] == '\0')
                    return 0;
                len++;
                i++;
            }
        }
        i++;
    }
    return len;
}


int malloc_everything(char **res,char *s)
{
    int i;
    int len;
    char symbol;
    int position;

    i = 0;
    position = 0;
    while(s[i])
    {   
        len = 0;
        while(s[i] != ' ' && !(s[i] == '"' || s[i] == '\'') && s[i])
        {   
            i++;
            len++;
        }
        if(s[i] == '"' || s[i] == '\'')
        {   
            symbol = symbol_checker(s[i]);
            i += 1;
            while(s[i] != symbol)
            {   
                if(s[i] == '\0')
                    return 0;
                len++;
                i++;
            }
        }
        if(len && fill_str(res,s,len,position))
            position++;
        else
            return 0;
        i++;
    }
    return 1;
}