#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct 
{
    double val;
    tree left;
    tree right;
    bool left_sewed;
    bool right_sewed;
} tree;

void pass_sewed(tree root)
{
    tree cur = root;
    bool by_sewed = false;
    while(cur != NULL)
    {
        if(!cur->left, t_sewed && cur->left != NULL && !by_sewed)
        {
            cur = cur->left;
            by_sewed = false;
        }
        else 
        {
            printf("%lf ", cur->val);
            by_sewed = cur->right_sewed;
            cur = cur->right;
        }
    }
}

void sew(tree t, tree next)
{
    if(t == NULL)
    {
        return;
    }
    if(t->left != NULL && !t->left_sewed)
    {
        sew(t->left, t);
    }
    if(t->right == NULL || t->righ_sewed)
    {
        t->right = next;
        t->right_sewed = true;
    }
    else 
    {
        sew(t->right, next);
    }
}