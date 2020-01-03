#include "media_info.hpp"

int getFileNames(char *** names, const char * directory)
	/*
	 * Args:
	 * - names: empty memory, will be malloced and must be freed. 
	 *   Will be the address of a "char **"
	 *   Will be filled with file names from directory. notice
	 *   it is a triple pointer, because what is altered is a list
	 *   of strings, just sending a double pointer only allows the
	 *   strings to be altered. We need to alter the list's size.
	 * - directory: directory where we will get the filen names from 
	 *   to fill names
	 * Returns: 0 upon failure, otherwise the number of files in the directory
	 */
{
	const int buffer = 100; // constant temporary buffer length
	char temp[buffer][buffer] = {};// temporary array of strings with buffer length
	char ** tnames = NULL;// atemporary way to refer to the list of strings char **tnames = *names;
	int fileCount = 0;// Will be number of files in argument "directory"
	struct dirent * dirInfo;// holds information about a file holds info about "directory"
	DIR * dir = opendir(directory);

	// dir is NULL if opendir fails
	if(dir == NULL){
		printf("%s\n", directory);
		if(mkdir(directory, S_IRWXU) == -1){
			perror(strerror(errno));
			return 0;
		}

		dir = opendir(directory);
		if(dir == NULL)
			return 0;
	}

	// Fill the temporary buffer with the directory's contents
	// and increment the fileCount
	while((dirInfo=readdir(dir)) != NULL){
		strcpy(temp[fileCount], dirInfo->d_name);
		++fileCount;
	}

	// Start filling tnames from the temporary buffer of adequate
	// malloced size
	tnames = (char **) malloc(fileCount * sizeof(char*));
	for(int i = 0; i < fileCount; ++i){
		tnames[i] = (char *)malloc(strlen(temp[i]+1));
		strcpy(tnames[i], temp[i]); 
	}

	//REASSIGN what names points to, otherwise *names is NULL
	// and this works because ALL of tnames is malloced
	*names = tnames;

	closedir(dir);
	return fileCount;
}

short freeFileNames(char ***names, int nameCount){
	if (*names == NULL)
		return -1;

	for(int i = 0; i < nameCount; ++i)
		free((*names)[i]);
	free(*names);
	return 1;
}

