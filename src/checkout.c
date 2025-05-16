#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include "mygit.h"

int	mygit_checkout(const char *branch)
{
	char branch_path[256];
	char hash[41];

	// ブランチファイルの存在確認
	snprintf(branch_path, sizeof(branch_path), ".mygit/refs/heads/%s", branch);
	FILE *branch_file = fopen(branch_path, "r");
	if (!branch_file)
	{
		fprintf(stderr, "Branch '%s' does not exist.\n", branch);
		return (1);
	}

	// ハッシュの取得（未使用だけど確認として読んでおく）
	fgets(hash, sizeof(hash), branch_file);
	fclose(branch_file);

	// HEAD をブランチ参照に書き換える
	FILE *head = fopen(".mygit/HEAD", "w");
	if (!head)
	{
		perror("fopen HEAD");
		return (1);
	}
	fprintf(head, "ref: %s\n", branch_path);
	fclose(head);

	printf("Switched to branch '%s'\n", branch);
	return (0);
}
