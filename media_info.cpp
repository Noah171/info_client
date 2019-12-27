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
	 * Returns: 0 upon failure, -1 if the directory is empty, 
	 * otherwise the number of files in the directory
	 */
{
	const int buffer = 100; // constant temporary buffer length
	// temporary array of strings with buffer length
	char temp[buffer][buffer] = {}; 
	// this is effectively a temporary way to refer to the list of
	// strings
	char **tnames = *names;
	// Will be number of files in argument "directory"
	int fileCount = 0;

	struct dirent * dirInfo;// holds information about a file
	// Holds info about "directory"
	DIR * dir = opendir(directory); 
	// dir is NULL if opendir fails
	if(dir == NULL){
		// in which case return fileCount, which is 0
		return fileCount;
	}
	// Fill the temporary buffer with the directory's contents
	// and increment the fileCount
	for(fileCount = 0;(fileInfo = readdir(dir)) != NULL; ++fileCount)
		strcpy(temp[fileCount], dirInfo->d_name);
	// if file count is still 0, then the directory is empty so return -1
	if(fileCount == 0)
		return -1;

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
	
	return fileCount;
}
