#ifndef mygit_H
#define MYGIT_H

#include <time.h>
typedef struct s_commit {
    char hash[41];
    char parent[41];
    char message[256];
    time_t timestamp;
} t_commit;

int mygit_init(void);
int mygit_log(void);
int	mygit_commit(const char *message);
int	mygit_branch(const char *name);

#endif