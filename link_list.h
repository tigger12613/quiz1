#define bool int
#define true 1
#define false 0

typedef struct __node {                   
    int value;
    struct __node *next;
} node_t;

void list_add_node_t(node_t **list, node_t *node_t);

void list_concat(node_t **left, node_t *right);
void quicksort(node_t **list);
void quicksort_iterative(node_t **list);

bool list_is_ordered(node_t *list);

void list_display(node_t *list);

node_t *list_make_node_t(node_t *list, long num);

void list_free(node_t **list);