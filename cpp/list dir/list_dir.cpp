
// only works in cpp
#ifdef __cplusplus
extern "C"{
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int list_dir_name(char* dirname, int tabs)
{
    DIR* dp;
    struct dirent* dirp;
    struct stat st;
    char tab[tabs + 1];

    /* open dirent directory */
    if((dp = opendir(dirname)) == NULL)
    {
        perror("opendir");
        return -1;
    }

    /* fill tab array with tabs */
    memset(tab, '\t', tabs);
    tab[tabs] = 0;

    /**
     * read all files in this dir
     **/
    while((dirp = readdir(dp)) != NULL)
    {
        char fullname[255];
        memset(fullname, 0, sizeof(fullname));

        /* ignore hidden files */
        if(dirp->d_name[0] == '.')
            continue;

        /* display file name with proper tab */
        printf("%s%s\n", tab, dirp->d_name);

        strncpy(fullname, dirname, sizeof(fullname));
        strncat(fullname, "/", sizeof(fullname));
        strncat(fullname, dirp->d_name, sizeof(fullname));
        /* get dirent status */
        if(stat(fullname, &st) == -1)
        {
            perror("stat");
            fputs(fullname, stderr);
            return -1;
        }

        /* if dirent is a directory, call itself */
        if(S_ISDIR(st.st_mode) && list_dir_name(fullname, tabs + 1) == -1)
            return -1;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("please type directory name.\n");
        return -1;
    }

    printf("%s\n", argv[1]);
    list_dir_name(argv[1], 1);

    return 0;
}
}/* end extern "C" */
#endif
