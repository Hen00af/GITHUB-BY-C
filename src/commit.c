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
    FILE *head;
    FILE *out;
    char head_content[256];
    char branch_path[256];
    char path[256];

    srand(time(NULL));
    generate_fake_hash(commit.hash, sizeof(commit.hash));
    commit.timestamp = time(NULL);
    strncpy(commit.message, message, sizeof(commit.message));

    // HEAD を読む
    head = fopen(".mygit/HEAD", "r");
    if (!head)
    {
        perror("fopen HEAD");
        return (1);
    }
    fgets(head_content, sizeof(head_content), head);
    head_content[strcspn(head_content, "\n")] = 0;
    fclose(head);

    // HEAD が ref: の形式なら、実際のブランチファイルから親ハッシュを取得
    if (strncmp(head_content, "ref: ", 5) == 0)
    {
        const char *ref_path = head_content + 5;
        FILE *branch = fopen(ref_path, "r");
        if (!branch)
        {
            perror("fopen branch");
            return (1);
        }
        fgets(commit.parent, sizeof(commit.parent), branch);
        commit.parent[strcspn(commit.parent, "\n")] = 0;
        fclose(branch);

        // コミットを書き込む
        snprintf(path, sizeof(path), ".mygit/commits/%s", commit.hash);
        out = fopen(path, "w");
        if (!out)
        {
            perror("fopen commit");
            return (1);
        }
        fwrite(&commit, sizeof(commit), 1, out);
        fclose(out);

        // ブランチファイルに最新のハッシュを書き込む
        FILE *branch_out = fopen(ref_path, "w");
        if (!branch_out)
        {
            perror("fopen branch write");
            return (1);
        }
        fprintf(branch_out, "%s\n", commit.hash);
        fclose(branch_out);
    }
    else
    {
        // 旧来形式（HEAD に直接ハッシュが書かれていた場合）
        strcpy(commit.parent, head_content);

        // コミット保存
        snprintf(path, sizeof(path), ".mygit/commits/%s", commit.hash);
        out = fopen(path, "w");
        if (!out)
        {
            perror("fopen commit");
            return (1);
        }
        fwrite(&commit, sizeof(commit), 1, out);
        fclose(out);

        // HEAD にハッシュを直接書く
        head = fopen(".mygit/HEAD", "w");
        if (!head)
        {
            perror("fopen HEAD write");
            return (1);
        }
        fprintf(head, "%s\n", commit.hash);
        fclose(head);
    }

    printf("Committed: %s\n", commit.hash);
    return (0);
}
