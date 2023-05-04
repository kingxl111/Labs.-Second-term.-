#include<stdio.h>
#include<stdbool.h>

bool eq(int x, int y, int z, int a, int b, int c, int d, int e, int f)
{
    int part_left = 2*(1e5*x + 1e4*y + 1e3*z + 1e2*y + 10*a + b);
    int part_right = 1e5*c + 1e4*d + 1e3*y + 1e2*e + 10*f + y;
    return part_left == part_right;
}

bool is_different_digits(int x, int y, int z, int a, int b, int c, int d, int e, int f)
{
    if(x==y || x == z || x == a || x==b || x == c || x==d || x == e || x==f)
    {
        return false;
    }
    if( y == z || y == a || y==b || y == c || y==d || y == e || y==f)
    {
        return false;
    }
    if(z == a || z==b || z == c || z==d || z == e || z==f)
    {
        return false;
    }
    if(  a==b || a == c || a==d || a == e || a==f)
    {
        return false;
    }
    if( b == c || b==d || b == e || b==f)
    {
        return false;
    }
    if( c==d || c == e || c==f)
    { 
        return false;
    }
    if( d == e || d==f)
    { 
        return false;
    }
    if( e==f)
    { 
        return false;
    }
    return true;
}

int main()
{

    int x,y,z,a,b,c,d,e,f;
    for(x = 0;x<10;++x)
    {
        for(y = 0;y<10;++y)
        {
            for(z = 0;z<10;++z)
            {
                for(a = 0;a<10;++a)
                {
                    for(b = 0;b<10;++b)
                    {
                        for(c = 0;c<10;++c)
                        {
                            for(d = 0;d<10;++d)
                            {
                                for(e = 0;e<10;++e)
                                {
                                    for(f = 0; f < 10;++f)
                                    {
                                        if(is_different_digits(x,y,z,a,b,c,d,e,f))
                                        {
                                            if(eq(x,y,z,a,b,c,d,e,f))
                                            {
                                                printf("%d %d %d %d %d %d %d %d %d\n", x,y,z,a,b,c,d,e,f);
                                                return 0;
                                            }
                                        }
                                        
                                    }
                                } 
                            }
                        } 
                    }
                } 
            }
        } 
    }

    return 0;
}