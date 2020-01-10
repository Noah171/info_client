#ifndef LLWIN_NODE
#define LLWIN_NODE

// Node in doubly linked list
class WNODE {
public:
	WNODE();
	~WNODE();
private:
	WINDOW * window;
	WNODE *next;
	WNODE *prev;
};

#endif
