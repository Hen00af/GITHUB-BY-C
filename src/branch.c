#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include "mygit.h"

int	mygit_branch(const char *name)
{
	FILE	*head, *cur_branch_file, *new_branch_file;
	char	head_ref[256];
	char	cur_branch[256];
	char	hash[41];
	char	new_path[256];

	head = fopen(".mygit/HEAD", "r");
	if (!head)
	{
		perror("fopen HEAD");
		return (1);
	}
	fgets(head_ref, sizeof(head_ref), head);
	head_ref[strcspn(head_ref, "\n")] = 0;
	fclose(head);
	if (strncmp(head_ref, "ref: ", 5) != 0)
	{
		fprintf(stderr, "Invalid HEAD format\n");
		return (1);
	}
	strcpy(cur_branch, head_ref + 5);
	cur_branch_file = fopen(cur_branch, "r");
	if (!cur_branch_file)
	{
		perror("fopen current branch");
		return (1);
	}
	fgets(hash, sizeof(hash), cur_branch_file);
	hash[strcspn(hash, "\n")] = 0;
	fclose(cur_branch_file);
	snprintf(new_path, sizeof(new_path), ".mygit/refs/heads/%s", name);
	new_branch_file = fopen(new_path, "w");
	if (!new_branch_file)
	{
		perror("fopen new branch");
		return (1);
	}
	fprintf(new_branch_file, "%s\n", hash);
	fclose(new_branch_file);
	printf("Branch '%s' created at %s\n", name, hash);
	
    return (0);
}
