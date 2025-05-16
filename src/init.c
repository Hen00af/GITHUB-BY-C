// init.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define MYGIT_DIR ".mygit"
#define COMMITS_DIR ".mygit/commits"
#define HEAD_FILE ".mygit/HEAD"

int mygit_init(void)
{
    if(access(MYGIT_DIR, F_OK) == 0)
    {
        printf("Repository already initialized. \n");
        return(1);
    }

    if(mkdir(MYGIT_DIR,0755) != 0)
    {
       perror("mkdir .mygit");
       return (1); 
    }

    if (mkdir(COMMITS_DIR, 0755) != 0)
	{
		perror("mkdir commits");
		return (1);
	}

    FILE  *head = fopen(HEAD_FILE, "w");
    if(!head)
    {
        perror("fopen HEAD");
        return(1);
    }
    fprintf(head,"null\n");
    fclose(head);

    printf("Initialized empty mygit repository in %s \n", MYGIT_DIR);
    return(0);
}