#ifndef MEDIA_INFO_HPP
#define MEDIA_INFO_HPP

#include <sys/stat.h> // For mkdir in getFileNames
#include <dirent.h> // for DIR and struct dir_ent in getFileNames
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <errno.h>


#define DIRECTORY "/home/ncs/.local/media_list/"
#define EMPTY_DIR 2 // The number of files in the directory if it is empty (. and .. are there)

extern int errno; 

int getFileNames(char *** names, const char * directory);
short freeFileNames(char *** names, int nameCount);

#endif
