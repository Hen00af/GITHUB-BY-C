#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mygit.h"

int	mygit_log(void)
{
	char hash[41];
	FILE *head = fopen(".mygit/HEAD", "r");
	if (!head)
	{
		perror("fopen HEAD");
		return (1);
	}
	fgets(hash, sizeof(hash), head);
	hash[strcspn(hash, "\n")] = 0;
	fclose(head);

	while (strcmp(hash, "null") != 0)
	{
		char path[256];
		snprintf(path, sizeof(path), ".mygit/commits/%s", hash);

		FILE *f = fopen(path, "r");
		if (!f)
		{
			perror("fopen commit");
			return (1);
		}

		t_commit commit;
		fread(&commit, sizeof(t_commit), 1, f);
		fclose(f);

		struct tm *timeinfo = localtime(&commit.timestamp);
		char timestr[64];
		strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", timeinfo);

		printf("[%s] hash: %s\n  message: %s\n\n", timestr, commit.hash, commit.message);
		strcpy(hash, commit.parent);
	}
	return (0);
}
