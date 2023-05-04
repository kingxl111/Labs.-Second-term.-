#include "tree.h"
#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"


bool is_empty(tree t)
{
    return t==NULL;
}

tree empty_tree()
{
    return NULL;
}

tree build_tree(double val, tree l, tree r)
{
    tree new_tree = malloc(sizeof(tree));
    new_tree->left = l;
    new_tree->right = r;
    new_tree->val = val;
    return new_tree;
}

double root_val(tree t)
{
    return t->val;
}

tree left(tree t)
{
    return t->left;
}

tree right(tree t)
{
    return t->right;
}


tree find(double val, tree t)
{
    if(is_empty(t))
    {
        return empty_tree();
    }
    if(val == root_val(t))
    {
        return t;
    }
    if(val < root_val(t))
    {
        return find(val, left(t));
    }
    else
        return find(val, right(t));
}


tree add(tree t, double val)
{
    if(is_empty(t))
    {
        return build_tree(val, empty_tree(), empty_tree());
    }
    if(val < root_val(t))
    {
        tree new_left = add(left(t), val);
        tree new_right = right(t);
        double new_val = root_val(t);
        destroy_root(t);
        return build_tree(new_val, new_left, new_right);
    }
    if(val > root_val(t))
    {
        tree new_right = left(t);
        tree new_left = add(right(t), val);
        double new_val = root_val(t);
        destroy_root(t);
        return build_tree(new_val, new_left, new_right);
    }
    else
    {
        return t;
    }
}

rm_min_res remove_min(tree t)
{
    rm_min_res r;
    return r;
}

tree delete(tree t, double val)
{
    if(is_empty(t))
    {
        return t;
    }
    if(val < root_val(t))
    {
        tree new_left = delete(left(t), val);
        tree new_right = right(t);
        double new_val = root_val(t);
        destroy_root(t);
        return build_tree(new_val, new_left, new_right);
    }
    else
    {
        if(is_empty(left(t)) && (is_empty(right(t))))
        {
            destroy_root(t);
            return empty_tree();
        }
        else if(is_empty(left(t)))
        {
            tree new_right = right(t);
            destroy_root(t);
            return new_right;
        } else if(is_empty(right(t)))
        {
            //дописать для правого
        }
        else 
        {
            rm_min_res r = remove_min(right(t));
            destroy_root(t);
            return build_tree(r.removed_val, new_left, r.new_t);
        }
    }
}





bool normal_add(tree *t, double val) {
    tree * place = find(t, val);
    if(*place != NULL) {
        return false;
    } else {
        tree new_node = malloc(sizeof(node));
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->val = val;
        *place = new_node;
        return true;
    }
}


bool delete(tree *t, double val)
{
    tree *place = find(t, val);
    if(*place == NULL)
        return false;
    if((*place)->left==NULL && (*place)->right==NULL)
    {
        free(*place);
        *place = NULL;
    }
    else if ((*place)->left == NULL)
    {
        tree new_right = (*place)->right;
        free(*place);
        *place=new_right;
    }
    else if((*place)->right == NULL)
    {
        tree new_left = (*place)->left;
        free(*place);
        *place=new_left;
    }
    else
    {
        tree *r = &((*place)->right);
        while((*r)->left != NULL)
        {
            r = &((*r)->left);
        }
        tree min_r = (*r);
        *r = (*r)->right;
        min_r->right = (*place)->right;
        min_r->left = (*place)->left;
        free(*place);
        *place=min_r;
    }
    return true;
}

int depth(tree t)
{
    if(t==NULL)
    {
        return 0;
    }
    return max(t->left+1, t->right+1);
}

void draw_tree(tree t, int level)
{
    if(t==NULL)
    {
        return;
    }
    //Обход правый -> корень -> левый 
    draw_tree(t->right, level+1);
    for(int i=0;i<level;++i)
    {
        printf("\t");
    }
    printf("%lf\n", t->val);
    draw_tree(t->left, level+1);
}

static void width_intern(tree t, int_vec *v, int depth)
{
    if(t==NULL)
    {
        return;
    }
    int_vec_setval(v, depth, v_get_val(v, depth)+1);
    width_intern(t->left, v, depth+1);
    width_intern(t->right, v, depth+1);
}

int width(tree t)
{
    int_vec cnt_width;//вектор ширин
    int_vec(&cnt_width);//на i-той позиции хранится ширина i-того уровня
    int depth = depth(t);
    int_v_set_size(&cnt_width, depth);
    width_intern(t, &cnt_width, 0);
    int max_width = 0;
    for(int i=0;i<depth;++i)
    {
        int wd = int_v_get_val(&cnt_width, i);
        if(wd > max_width)
        {
            max_width = wd;
        }
    }
    int_v_destroy(&cnt_width);
    return max_width;

}


int main()
{



    return 0;
}