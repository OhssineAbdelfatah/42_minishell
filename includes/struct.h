# ifndef STRUCT_H
#define STRUCT_H


typedef struct cmd t_cmd;



typedef enum ss
{
    NONE,
    SINGLE,
    DOUBLE
}ss;

typedef enum typenode
{
    EXEC,
    PIPE,
    RED,
    HERDOC,
    ENV_VAR,
    NONE_NODE
} t_typenode;


struct cmd
{
    int type;
};

struct exec_cmd
{
    int type;
    char *argv;
    char **env;
};

struct pipe
{
    int type;
    t_cmd *left;
    t_cmd *right;
};

struct red
{
    int type;
    int mode;
    int fd;
    char *file;
    t_cmd *cmd;
};

struct heredoc {
    int type;         
    struct cmd *cmd;  
    char *delimiter;   
    char *content; 
};

#endif