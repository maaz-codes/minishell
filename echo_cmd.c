#include "minishell.h"

// int *space_pos(char *s,int symbol,int token,int inside)
// {
//     int *pos_check;
//     int tokens;

//     tokens = checker_tokens(s,symbol,token,inside);
//     pos_check = malloc(tokens + 1);
//     pos_check[tokens] = 0;
//     // while(*s)

// }
// int space_checker(char *s,int inside, char symbol)
// {   
//     int spaces = 0;
//     while(*s)
//     {   
//         inside = 0;
//         while(*s != ' ' && !(*s == '"' || *s == '\'') && *s)
//             s++;
//         if(*s == '"' || *s == '\'')
//         {   
//             symbol = symbol_checker(*s);
//             s += 1;
//             while(*s != symbol)
//                 s++;
//         }
//         while(*s == ' ')
//         {
//             if(!inside)
//             {   
//                 inside = 1;
//                 spaces += 1;
//             }
//             s++;
//         }
//         s++;
//     }
//     return(spaces);
// }
void echo_cmd(char **str,char *input)
{
    int i;
    int spaces;
    char symbol;
    int token;
    int inside;
    int malloc_tokens;

    symbol = '\0';
    token = 0;
    inside = 0;
    

    i = 1;
    while(str[i])
        printf("%s ",str[i++]);
    printf("\n");
    // printf("space checker: %d\n",space_checker(input,inside,symbol));
   
}