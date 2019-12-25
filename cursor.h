typedef struct {
    int x;
    int y;
    char * value;

} cursor;

char init_cursor(cursor * c, WINDOW * w, int x, int y)
