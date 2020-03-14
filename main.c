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

void print_char(char c) {
    printf("%c ", c);
}

void print_person(Person one) {
    printf("<%s,%s,%d>\n", one.name, one.sex, one.age);
}

int agecmp(const void *one, const void *two) {
    return ((Person *) one)->age > ((Person *) two)->age;
}