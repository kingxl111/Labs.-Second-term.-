typedef enum 
{
    START,
    LEFT_VISIT,
    RIGHT_VISIT,

} pass_state;

typedef struct 
{
    tree t;
    pass_state state;

} node_pass;


void pass(tree root)
{
    pass_stack s;
    stack_init(&s);
    if(root)
    {
        stack_push(&s, {.t = root, .state = START});
    }
    while(!pass_stack_empty(&s))
    {
        node_pass n = pass_stack_pop(&s);
        if(n.state == START)
        {
            n.state = LEFT_VISIT;
            pass_stack_push(&s, n);
            if(n.t->left)
            {
                pass_stack_push(&s, {.t = n.t->left, .state = START});
            }
            else if(n.state == LEFT_VISIT)
            {
                printf("%lf", n.t->val);
                n.state = RIGHT_VISIT;
                pass_stack_push(&s, n);
                if(n.t->right)
                {
                    pass_stack_push(&s, {.t = n.t->right, .state = START});
                }
                else if(n.state == RIGHT_VISIT){}
            }
        }
    }
    pass_stack_destroy(&s);
}


