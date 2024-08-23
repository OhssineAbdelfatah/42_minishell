#include "../includes/minishell.h"


//hadi ghi bach nvisualisiw chejra dyalna a batal 



void check_mode(struct red *s)
{
    if (s)
    {
        if (s->mode == 4)
            printf("<");
        else if (s->mode == 77 )
            printf(" >> ");
        else if (s->mode ==  7)
            printf(" > ");
    }
}

void print_tree(t_cmd *res)
{
    struct exec_cmd *p1;
    struct pipe *p2;
    struct red *p3;
    struct heredoc *p4;

    if (res->type == RED)
    {
        p3 = (struct red*)res;
        printf("(");
        print_tree(p3->cmd);
        check_mode(p3);
        printf("%s)", p3->file);    
    }
    else if (res->type == EXEC)
    {
        p1 = (struct exec_cmd *)res;
        // write(1, "SEGV\n", 6);
        printf("%s",p1->argv);
        // write(1, "SEGV4\n", 7);
    }
    else if (res->type == PIPE)
    {
        p2 = (struct pipe *)res;
        printf("(");
        print_tree(p2->left);
        printf("|");
        print_tree(p2->right);
        printf(")");
    }
    else if (res->type == HERDOC)
    {
        p4 = (struct heredoc *)res;
        printf("(");
        print_tree(p4->cmd);
        printf("<<");
        printf(" %s", p4->delimiter);
        printf(")");
    }
    else
    {
        p3 = (struct red *)res;
        printf("undefined :/ type:%d, file:%s, mode: %d", res->type,p3->file, p3->mode);
    }
}