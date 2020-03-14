#include <stdio.h>
#include "array.h"
ARRAY_TYPE_SET(int );





int main() {
    array(int ) arr=new(array(int ));
    int a,b,c;
    scanf("%d%d%d",&a,&b,&c);
    arr.push_back(a);
    arr.push_back(b);
    arr.push_back(c);
    printf("%d",arr.sort().pop_front());

    return 0;
}
