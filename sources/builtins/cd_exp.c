/*
chdir will change the current directory of your program, probably a command shell you are trying to implement.

Absolute and relative paths such as /, .., subdir pose no problem and can be passed directly to the chdir system call.

- is a special argument for the cd command: cd - means to go back to the previous current directory. 
To implement this functionality, you need to keep track of the last directory cd changed to.
Use the getcwd() function for that before calling chdir and if successful, 
keep this previous directory in a global array.

~ is another special thing: it should be expanded to the home directory (the value of the HOME environment variable) 
before dispatching to the command handler, so one can type cd ~, or just cd to change to the home directory but cd "~" 
to change to a directory named "~". ~ should expand to $(HOME), either as a stand alone string or as the initial portion 
of a path: ~/bin. Note that ~name should expand to the home directory of the user name.

Here is a partial and simplistic version:
*/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syslimits.h>
#include <string.h>
#include <unistd.h>

char lastdir[PATH_MAX];  // initialized to zero

int exec_cd(char *arg) {
    char curdir[PATH_MAX];
    char path[PATH_MAX];

    if (getcwd(curdir, sizeof curdir)) {
        /* current directory might be unreachable: not an error */
        *curdir = '\0';
    }
    if (arg == NULL) {
        arg = getenv("HOME");
    }
    if (!strcmp(arg, "-")) {
        if (*lastdir == '\0') {
            fprintf(stderr, "no previous directory\n");
            return 1;
        }
        arg = lastdir;
    } else {
        /* this should be done on all words during the parse phase */
        if (*arg == '~') {
            if (arg[1] == '/' || arg[1] == '\0') {
                snprintf(path, sizeof path, "%s%s", getenv("HOME"), arg + 1);
                arg = path;
            } else {
                /* ~name should expand to the home directory of user with login `name` 
                   this can be implemented with getpwent() */
                fprintf(stderr, "syntax not supported: %s\n", arg);
                return 1;
            }
        }
    }
    if (chdir(arg)) {
        fprintf(stderr, "chdir: %s: %s\n", strerror(errno), path);
        return 1;
    }
}