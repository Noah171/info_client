#include "LLNode.hpp"

// Default node size is zero (nlines and ncols)
LLNode::LLNode(WINDOW *super, char* dirName, int xpos, int ypos){
  this->nlines = 0;
  this->ncols = 0;
  this->x = xpos;
  this->y = ypos;
  this->cwd = dirName;
  this->curwin = subwin(super, nlines, ncols,x,y);
} // end LLNode

LLNode::~LLNode(){
  delwin(this->curwin);
  freeContent(&this->contents, nlines);
} // end ~LLNode

// Updates the node contents by going to its associated content source (files in a directory 
// or a file's content)
void LLNode::updateNodeContents(){
  int successp = OK;
  int longestIndex = 0;
  // reset the current content's memory to ensure that no sizing issues occur
  if(this->contents != NULL){
    LLNode::freeContent(&this->contents, this->nlines);
  }
  this->nlines = LLNode::getContent(&this->contents, cwd);
  longestIndex = LLNode::getLongestStrIndex(contents,nlines);
  this->ncols = strlen(this->contents[longestIndex]);
  // plus one to nlines because the final entry also has a newline character
  successp = wresize(this->curwin, this->nlines+1, this->ncols + LLNode::symbolLen+1);
  if(successp != OK){
    printf("Coudn't resize!\n");
  }
} // end updateNodeContents

// Prints column to this nodes curwin
void LLNode::printColumnToWindow(){
  char * str = prettyFormatStrings(this->contents, this->nlines);
  int successp = OK;
  werase(this->curwin);
  successp = waddnstr(this->curwin, str, strlen(str));
  if (successp != OK){
    printf("Something's wrong in printColumnToWindow with waddnstr!\n\r");
    printf("curwin %p str %p errno %d\n", this->curwin, str, successp);
  }
  wrefresh(this->curwin);
  free(str);
} // end prettyPrintColumn

// Pretty format's a list of strings to be printed out, likely to the curwin
char * LLNode::prettyFormatStrings( char ** strings, int numStrs)
/* Pretty prints the strings into window. */
{
  /* update the windows so far just the media window */
  int total_len = 0; //buffer's current length
  char buffer[LLNODE_BUFFLEN] = {};
  char * pretty_string = NULL;

  // Adding the strings to buffer in a "pretty" way. numstrs j is decremented for formatting reasons (order of file names looks better this way)
  for(int j = numStrs-1; j >= 0; j--){
    int whitespace = 0;
    int curlen = strnlen(strings[j], LLNODE_BUFFLEN);
    int longestIndex = LLNode::getLongestStrIndex(strings, numStrs);
    int longestLen = strlen(strings[ longestIndex]);

    total_len += curlen;
    whitespace = longestLen - curlen;
    strncat(buffer ,strings[j], LLNODE_BUFFLEN);

    for(int k = 0; k < whitespace; ++k){
      strncat(buffer, " ", LLNODE_BUFFLEN-1);
      total_len++;
    }
    // Adding in the symbols. notice the symbol, "|\n" is of length 2
    strncat(buffer , LLNode::symbol, LLNODE_BUFFLEN-1);
    total_len += LLNode::symbolLen;
  }
  // Add one to amount to be malloced to account for NULL byte
  pretty_string = (char *) malloc(total_len + 1);

  bzero(pretty_string, total_len+1);
  strncpy(pretty_string,buffer,total_len+1);
  pretty_string[total_len] = '\0';

  return pretty_string;
} // end prettyFormatString

int LLNode::getContent(char *** content, char * directory)
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
  char ** tcontent = NULL;// atemporary way to refer to the list of strings char **tcontent = *content;p
  int objCount= 0;// Will be number of files in argument "directory"
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
    strcpy(temp[objCount], dirInfo->d_name);
    ++objCount;
  }
  // Start filling tcontent from the temporary buffer of adequate
  // malloced
  tcontent = (char **) malloc(objCount * sizeof(char*));
  for(int i = 0; i < objCount; ++i){
    tcontent[i] = (char *)malloc(strlen(temp[i]+1));
    strcpy(tcontent[i], temp[i]); 
  }
  //REASSIGN what content points to, otherwise *content is NULL
  // and this works because ALL of tcontent is malloced
  *content = tcontent;
  closedir(dir);
  return objCount;
} // end getContent

// Frees content acquired from getContent
short LLNode::freeContent(char ***content, int contentCount)
// Frees file content malloced in getFileContent
{
  if (*content == NULL){
    return -1;
  }

  for(int i = 0; i < contentCount ; ++i){
    free((*content)[i]);
  }

  free(*content);
  return 1;
} // end freeContent

// Simply finds the longest string in a list (the list is unordered so linear search it)
int LLNode::getLongestStrIndex(char ** strings, int numStrs)
// Gets the longest string in an array of strings
{
  int index = 0;
  int longest = 0;
  for(int i = 0; i < numStrs; ++i){
    int strl = strlen(strings[i]);
    if(strl > longest){
      index = i;
      longest = strl;
    }
  }
  return index;
} // end getLongestStr
// Getter for cwd
char * LLNode::getCwd() { return this->cwd; }
int LLNode::getNLines(){ return this->nlines; }
