#ifndef _LIST_DIR_HPP
#define _LIST_DIR_HPP

#include <vector>
#include <string>

// only works in cpp
#ifdef __cplusplus
extern "C"{
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int list_dir_name(char* dirname, std::vector<std::string>& res, bool bRecur = false) {
    DIR* dp;
    struct dirent* dirp;
    struct stat st;

    /* open dirent directory */
    if((dp = opendir(dirname)) == NULL) {
        perror("opendir");
        return -1;
    }

    /**
     * read all files in this dir
     **/
    while((dirp = readdir(dp)) != NULL) {
        char fullname[255];
        memset(fullname, 0, sizeof(fullname));
        /* ignore . .. */
        if(dirp->d_name[0] == '.' || 0 == strcmp(dirp->d_name, ".."))
            continue;

        strncpy(fullname, dirname, sizeof(fullname));
        strncat(fullname, "/", sizeof(fullname));
        strncat(fullname, dirp->d_name, sizeof(fullname));
        /* get dirent status */
        if(stat(fullname, &st) == -1) {
            perror("stat");
            fputs(fullname, stderr);
            return -1;
        }

        /* if dirent is a directory, call itself */
        if(S_ISDIR(st.st_mode) && bRecur)
			return list_dir_name(fullname, res);
		else if(S_ISREG(st.st_mode))
			res.push_back(std::string(dirp->d_name));
	}
    return 0;
}

}/* end extern "C" */
#endif

#endif
