# ifndef STRUCT_H
#define STRUCT_H


typedef struct s_env_var t_env;
typedef struct exec_cmd t_exec_cmd;

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
    NONE_NODE,
    NAN
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
    t_env *ennv ;
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

struct s_env_var {
    char *key;
    char *value;
    t_env *next;
};

#endif