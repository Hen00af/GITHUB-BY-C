#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define MYGIT_DIR ".mygit"
#define COMMITS_DIR ".mygit/commits"
#define REFS_DIR ".mygit/refs"
#define HEADS_DIR ".mygit/refs/heads"
#define MAIN_BRANCH ".mygit/refs/heads/main"
#define HEAD_FILE ".mygit/HEAD"

int mygit_init(void)
{
    if (access(MYGIT_DIR, F_OK) == 0)
    {
        printf("Repository already initialized.\n");
        return (1);
    }

    if (mkdir(MYGIT_DIR, 0755) != 0)
    {
        perror("mkdir .mygit");
        return (1);
    }

    if (mkdir(COMMITS_DIR, 0755) != 0 ||
        mkdir(REFS_DIR, 0755) != 0 ||
        mkdir(HEADS_DIR, 0755) != 0)
    {
        perror("mkdir refs");
        return (1);
    }

    FILE *branch = fopen(MAIN_BRANCH, "w");
    if (!branch)
    {
        perror("fopen main branch");
        return (1);
    }
    fprintf(branch, "null\n");
    fclose(branch);

    FILE *head = fopen(HEAD_FILE, "w");
    if (!head)
    {
        perror("fopen HEAD");
        return (1);
    }
    fprintf(head, "ref: %s\n", MAIN_BRANCH);  // ブランチへのポインタを記録
    fclose(head);

    printf("Initialized empty mygit repository in %s\n", MYGIT_DIR);
    return (0);
}
