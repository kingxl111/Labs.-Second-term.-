typedef struct
{
    tree new_t;
    double removed_val;
} rm_min_res;

typedef struct node node;

typedef node* tree;

struct node
{
    double val;
    tree left;
    tree right;
};
