#include <stdio.h>
#include "array.h"
ARRAY_TYPE_SET(char);

typedef struct person Person;
ARRAY_TYPE_SET(Person);
struct person{
    char name[8];
    char sex[4];
    int  age;
}person_3[]={
        {"南木","男",20},
        {"橙子","男",35},
        {"时光","男",16},
        {"岑子","男",22},
        {"附离","男",18},
};


int main() {

    /********array动态用法******************/
    array(char) test=new(array(char));
    for (char i = 'A'; i < 'H'; ++i) {
        test.push_back(i);
    }
    for (char i = 'A'; i < 'H'; ++i) {
        test.push_back(i);
    }
    void print_char(char c);
    test.traversal(print_char);
    test.sort().traversal(print_char).reverse().traversal(print_char);
    test.delete();

    /*********array静态用法***************/
    array(Person) _static=new(array(Person));
    _static.setArray(person_3, 5, 5,false);
    void print_person(Person one);
    _static.sort().traversal(print_person).reverse().traversal(print_person);

    /***修改默认比较函数,按年龄比较***/
    int agecmp(const void* one,const void* two);
    _static.setcmp(agecmp);
    _static.sort().traversal(print_person).reverse().traversal(print_person);

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