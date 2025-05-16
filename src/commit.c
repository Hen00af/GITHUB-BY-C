#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include "mygit.h"

static void generate_fake_hash(char *buf, size_t size)
{
    const char *hex = "abcdef0123456789";
    for(size_t i = 0; i < size - 1; i++)
        buf[i] = hex[rand() % 16];
    buf[size - 1] = '\0';
}

int mygit_commit(const char *message)
{
    t_commit commit;
    FILE    *head;
    FILE    *out;
    char    path[256];


    srand(time(NULL));
    generate_fake_hash(commit.hash, sizeof(commit.hash));
    //コミット時、ヘッドの中身を書き換えている。
    //commitディレクトリに入っているファイルのなかに
    head = fopen(".mygit/HEAD","r");
    if(!head)
    {
        perror("fopen HEAD");
        return (1);
    }
    fgets(commit.parent,  sizeof(commit.parent), head);
    commit.parent[strcspn(commit.parent,"\n")] = 0;
    fclose(head);
    strncpy(commit.message, message, sizeof(commit.message));
    commit.timestamp = time(NULL);

	snprintf(path, sizeof(path), ".mygit/commits/%s", commit.hash);
	out = fopen(path, "w");
	if (!out)
	{
		perror("fopen commit");
		return (1);
	}
	fwrite(&commit, sizeof(commit), 1, out);
	fclose(out);
	head = fopen(".mygit/HEAD", "w");
	if (!head)
	{
		perror("fopen HEAD");
		return (1);
	}
	fprintf(head, "%s\n", commit.hash);
	fclose(head);
	printf("Committed: %s\n", commit.hash);
	return (0);
}




