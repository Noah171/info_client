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

	// Get contents of media directory because that will decide the size of media window
	contentCount = getFileNames(&contents, DIRECTORY);
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
