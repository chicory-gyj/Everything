#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include "list.h"

void listdir(const char *name, int level, struct list_head *head)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;
    if (!(entry = readdir(dir)))
        return;

    do {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            int len = snprintf(path,
                               sizeof(path)-1,
                               "%s/%s", name, entry->d_name);
            path[len] = 0;
            if (strcmp(entry->d_name, ".") == 0 ||
                strcmp(entry->d_name, "..") == 0)
                continue;
            //printf("%*s[%s]\n", level*2, "", entry->d_name);
            //listdir(path, level + 1);
        } else {
            //printf("%*s- %s\n", level*2, "", entry->d_name);
            add_file_list(entry->d_name, head);
        }
    } while (entry = readdir(dir));
    closedir(dir);
}

typedef struct {
    char *localfilename;
    struct list_head stList;
}FILE_LIST_T;

int add_file_list(char *filename, struct list_head *head)
{
    FILE_LIST_T *node;
    node = (FILE_LIST_T*)malloc(sizeof(FILE_LIST_T));
    memset(node, 0, sizeof(FILE_LIST_T));
    node->localfilename = strdup(filename);
    list_add(&(node->stList), head);
    return 0;
}

int dump_file_list(struct list_head *head)
{
    printf("dump");
    struct list_head *pos, *q;
    FILE_LIST_T *tmp;
    list_for_each_safe(pos, q, head) {
        tmp = list_entry(pos, FILE_LIST_T, stList);
        printf("%s\n", tmp->localfilename);
        free(tmp->localfilename);
        list_del(pos);
        free(tmp);
    }
}
int main(void)
{
    FILE_LIST_T file_list_head;
    INIT_LIST_HEAD(&file_list_head.stList);
    listdir("/home/fabius8/", 0, &file_list_head.stList);
    dump_file_list(&file_list_head.stList);
    return 0;
}
