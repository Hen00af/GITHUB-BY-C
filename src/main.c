#include <stdio.h>
#include <string.h>
#include "mygit.h"

int main(int ac,char **av)
{
    if(ac < 2)
    {
        fprintf(stderr, "Usage: mygit <command>\n");
        return(1);
    }
    if(strcmp(av[1],"init") == 0)
        return(mygit_init());
    else if(strcmp(av[1], "log") == 0)
        return(mygit_log());
    else if(strcmp(av[1],"commit") == 0)
    {
        if(ac < 3)
        {
            fprintf(stderr, "Usage: mygit commit \"message\"\n");
            return(1);
        }
        return(mygit_commit(av[2]));
    }
    else if (strcmp(av[1], "branch") == 0)
    {
	if (ac < 3)
	{
		fprintf(stderr, "Usage: mygit branch <name>\n");
		return (1);
	}
    else if (strcmp(av[1], "checkout") == 0)
    {
        if (ac < 3)
        {
            fprintf(stderr, "Usage: mygit checkout <branch>\n");
            return (1);
        }
        return (mygit_checkout(av[2]));
    }
	return (mygit_branch(av[2]));
}


    fprintf(stderr, "Unknown command: %s\n", av[1]);
    return (1);
}
