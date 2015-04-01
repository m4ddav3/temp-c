#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct bar {
    int a;
    int b;
    char c[255];
    char d[255];
};

struct foo {
    int a;
    int b;
    struct bar c;
};

int main(int argc, char *argv[]) {

    struct foo *s = malloc(sizeof(struct foo));
    printf("foo is %ld bytes\n", sizeof(struct foo));

    printf("bar is %ld bytes\n", sizeof(struct bar));
    //s->c = (struct bar*) malloc(sizeof(struct bar));

    s->a = 123;
    s->b = 456;

    s->c.a = 789;
    s->c.b = 91;

    //s->c.c = (char*) malloc(255);
    //s->c.d = (char*) malloc(255);

    strncpy(s->c.c, "This is a string abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", 255);
    s->c.c[254] = 0;

    strncpy(s->c.d, "This is another string abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", 255);
    s->c.d[254] = 0;

    printf("s is %ld bytes\n", sizeof(*s));
    printf("s->c.c is %ld bytes\n", sizeof(*s->c.c));

    char* filename = "foo.db";

    FILE *f =fopen(filename, "w");
    fwrite(s, sizeof(struct foo) + sizeof(struct bar) + 255, 1, f);
    fflush(f);
    fclose(f);

    //free(s->c.c);
    //free(s->c.d);
    free(s);

    return 0;
}