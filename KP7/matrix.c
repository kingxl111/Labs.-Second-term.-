#include <vector.h>

// typedef struct {
//     int n, m;
//     int_vec idx;
//     dbl_vec val;
// } matrix1;

// matrix1 read_mtx() {
//     int n, m;
//     scanf("%d %d", &n, &m);
//     matrix1 mt;
//     mt.n = n;
//     mt.m = m;
//     dbl_init(&mt.val);
//     int_init(&mt.idx);
    
//     for(int i = 0; i < n; i++) {
//         for(int j = 0; j < m; j++) {
//             double cur;
//             scanf("%lf", &cur);
//             if(cur != 0) {
//                 dbl_vec_push_back(&mt.val, cur);
//                 int_vec_push_back(&mt.idx, i*n + j);
//             }
//         }
//     }
//     return mt;
// }

typedef struct {
    int n,m;
    int_vec CIP;
    int_vec PI;
    dbl_vec YE;
} matrix2;

void read_matrix(matrix2 *mt)
{
    int n,m;
    scanf("%d%d", &n, &m);
    dbl_vec_init(&(mt->YE));
    int_vec_init(&(mt->PI));
    int_vec_init(&(mt->CIP));
    mt->n = n;
    mt->m = m;
    for(int i=0;i<n;++i)
    {
        dbl_vec_push_back(&(mt->CIP),dbl_vec_get_size(&(mt->YE)));
        for(int j=0;j<m;++j)
        {
            double x;
            scanf("%lf", &x);
            if(x!=0)
            {   
                dbl_vec_push_back(&(mt->YE), x);
                int_vec_push_back(&(mt->PI), j);
            }
        }
    }
    int_vec_push_back(&(mt->CIP), dbl_vec_get_size(&(mt->YE)));

}

