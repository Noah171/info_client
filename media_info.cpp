#include "media_info.hpp"

int getFileNames(char *** names, const char * directory)
	/*
	 * Args:
	 * - names: empty memory, will be malloced and must be freed. 
	 *   Will be filled with file names
	 *   from directory.
	 * - directory: directory where we will get the filen names from 
	 *   to fill names
	 * Returns: 0 upon failure, -1 if the directory is empty, 
	 * otherwise the number of files in the directory
	 */
{
	const int buffer = 100;
	char temp[buffer][buffer] = {};
	char **tnames = *names;
	int dirCount = -1;

	struct dirent * dirInfo;
	DIR * dir = opendir(directory);
	if(dir == NULL){
		return dirCount;
	}

	for(dirCount = 0;(dirInfo = readdir(dir)) != NULL; ++dirCount)
		strcpy(temp[dirCount], dirInfo->d_name);

	tnames = (char **) malloc(dirCount * sizeof(char*));
	for(int i = 0; i < dirCount; ++i){
		tnames[i] = (char *)malloc(strlen(temp[i]+1));
		strcpy(tnames[i], temp[i]); 
	}

	*names = tnames;
	return dirCount;
}
