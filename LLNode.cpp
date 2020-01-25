#include "LLNode.hpp"

LLNode::LLNode(WINDOW *super, const char* DIRNAME){
	this->nlines = 0;
	this->ncols = 0;
	this->cwd = DIRNAME;
	this->curwin = subwin(super, nlines-1, ncols,0,0);
} // end LLNode

LLNode::~LLNode(){
	delwin(this->curwin);
} // end ~LLNode

void LLNode::updateNodeContents(){
	char ** contents = NULL;
	int contentCount = 0;
	int nlines = 0;
	int longestIndex = 0;
	/// CURRENTLY WORKING HEREREREREREREREE
	// Get contents of media directory because that will decide the size of media window
	contentCount = getFileContent(&contents, this->cwd);
	longestIndex = getLongestStr(contents, contentCount);

	/* Make initial window to display current working directory */
	this->ncols = strlen(mediaTypes[longestIndex]) + ADDITIONAL_COL_SPACE;

} // end updateNodeContents

void LLNode::prettyPrintColumn(char ** contents,int len, int ncols){
//	char * str = prettyFormatStrings(contents, , );
	addnstr(, len);
	
} // end prettyPrintColumn

char * LLNode::prettyFormatStrings( char ** strings, int numstrs, int ncols)
/* Pretty prints the strings into window. */
{
	/* update the windows so far just the media window */
	int curlen = 0;
	int whitespace = 0;
	int total_len = 0; //buffer's current length
	char buffer[BUFFLEN] = {};
	char * pretty_string = NULL;
	const int symbol_space = 2; // Space for "|\n"

	// Adding the strings to buffer in a "pretty" way. numstrs j is decremented for formatting reasons (order of file names looks better this way)
	for(int j = numstrs-1; j >= 0; j--){
		curlen = strnlen(strings[j], BUFFLEN);
		total_len += curlen;
		whitespace = ncols - curlen - symbol_space;

		strncat(buffer ,strings[j], BUFFLEN);

		for(int k = 0; k < whitespace; ++k){
			strncat(buffer, " ", BUFFLEN-1);
			total_len++;
		}
		// Adding in the symbols. notice the symbol, "|\n" is of length 2
		strncat(buffer ,"|\n", BUFFLEN-1);
		total_len += symbol_space;
	}
	// Add one to amount to be malloced to account for NULL byte
	pretty_string = (char *) malloc(total_len + 1);
	bzero(pretty_string, total_len+1);
	strncpy(pretty_string,buffer,total_len+1);

	return pretty_string;
} // end prettyFormatString


int LLNode::getFileContent(char *** content, const char * directory)
	/*
	 * Args:
	 * - content: empty memory, will be malloced and must be freed. 
	 *   Will be the address of a "char **"
	 *   Will be filled with file content from directory. notice
	 *   it is a triple pointer, because what is altered is a list
	 *   of strings, just sending a double pointer only allows the
	 *   strings to be altered. We need to alter the list's size.
	 * - directory: directory where we will get the filen content from 
	 *   to fill content
	 * Returns: 0 upon failure, otherwise the number of files in the directory
	 */
{
	const int buffer = 100; // constant temporary buffer length
	char temp[buffer][buffer] = {};// temporary array of strings with buffer length
	char ** tcontent = NULL;// atemporary way to refer to the list of strings char **tcontent = *content;
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

	// Start filling tcontent from the temporary buffer of adequate
	// malloced
	tcontent = (char **) malloc(fileCount * sizeof(char*));
	for(int i = 0; i < fileCount; ++i){
		tcontent[i] = (char *)malloc(strlen(temp[i]+1));
		strcpy(tcontent[i], temp[i]); 
	}

	//REASSIGN what content points to, otherwise *content is NULL
	// and this works because ALL of tcontent is malloced
	*content = tcontent;
	
	closedir(dir);
	return fileCount;
}

short LLNode::freeContent(char ***content, int contentCount)
	// Frees file content malloced in getFileContent
{
	if (*content == NULL){
		return -1;
	}

	for(int i = 0; i < contentCount ; ++i)
		free((*content)[i]);

	free(*content);
	return 1;
}
