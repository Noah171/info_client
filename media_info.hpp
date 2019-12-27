#ifndef MEDIA_INFO_HPP
#define MEDIA_INFO_HPP

#include <dirent.h>
#include <stdio.h>
#include <cstring>
#include <cstdlib>


#define DIRECTORY "/home/ncs/.local/media_list/"

int getFileNames(char *** names, const char * directory);

#endif
