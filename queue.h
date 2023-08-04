
typedef struct
{
	char *elements;
	int size;
	int capacity;
} queue_t;

int init_queue(queue_t *, int);

int double_queue_capacity(queue_t *);

int add_queue_element(queue_t *, char);

char get_queue_element(queue_t *);

void print_queue(queue_t *);

void free_queue(queue_t *);
