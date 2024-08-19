#include"../includes/minishell.h"

// chdir()

void cd(void)
{
    char buffer[256];
	while(read(0, buffer, 256) > 0 && ft_strncmp(buffer,"exit",4))
	{
		pid_t fd;
        
        if(chdir(buffer) != 0)
            printf("cd failed\n");
        else if(chdir(buffer) == 0)
            printf("cd ok\n");
		fd = fork();
		if(fd == 0){
            char l[11]= "/bin/pwd -L";
			execv("/bin/pwd",l);
        }
		else if(fd > 0){
			wait(NULL);
			printf("parent\n");
		}
	}
  
}