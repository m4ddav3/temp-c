#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct bar {
    int a;
    int b;
    char *c;
    char *d;
};

struct foo {
    int a;
    int b;
    struct bar *c;
};

int main(int argc, char *argv[]) {

    printf("foo is %ld bytes\n", sizeof(struct foo));
    printf("bar is %ld bytes\n", sizeof(struct bar));

    struct foo *s = malloc(sizeof(struct foo));
    s->c = (struct bar*) malloc(sizeof(struct bar));

    s->a = 123;
    s->b = 456;

    s->c->a = 789;
    s->c->b = 91;

    s->c->c = (char*) malloc(255);
    s->c->d = (char*) malloc(255);

    strncpy(s->c->c, "This is a string\0", 255);
    printf("s->c->c length: %ld\n", sizeof(s->c->c));
    s->c->c[254] = 0;

    strncpy(s->c->d, "This is another string abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstUVWXyz\0", 255);
    s->c->d[254] = 0;

    printf( "s is %ld bytes\n",      sizeof(*s)       );
    printf( "s->c.c is %ld bytes\n", sizeof(*s->c->c) );

    char* filename = "foo.db";

    FILE *f = fopen(filename, "w");

    fwrite(s,    sizeof(struct foo), 1, f);
    fwrite(s->c, sizeof(struct bar), 1, f);
    //fwrite(s->c->c, 255, 1, f);
    //fwrite(s->c->d, 255, 1, f);
    fputs(s->c->c, f);
    //fputc(0, f);
    fputs(s->c->d, f);
    //fputc(0, f);

    fflush(f);
    fclose(f);

    free(s->c->c);
    free(s->c->d);
    free(s->c);
    free(s);

    FILE *infh = fopen(filename, "r+");
    printf("Opened infh\n");

    fread(s, sizeof(struct foo), 1, infh);
    printf("%d : fread struct foo\n", ftell(infh));
    printf("s->a = %d\n", s->a);
    printf("s->b = %d\n", s->b);

    fread(s->c, sizeof(struct bar), 1, infh);
    printf("%d : fread struct bar\n", ftell(infh));
    printf("s->c->a = %d\n", s->c->a);
    printf("s->c->b = %d\n", s->c->b);

    s->c->c = (char*) malloc(255);
    fread(s->c->c, 255, 1, infh);
    printf("%d : fread s->c->c\n", ftell(infh));

    s->c->d = (char*) malloc(255);
    fread(s->c->d, 255, 1, infh);
    printf("%d : fread s->c->d\n", ftell(infh));
/*
    printf("s->c->c = %s\n", s->c->c);
    s->c->c = (char*) malloc(255);
    printf("s->c->c = %s\n", s->c->c);
    fgets(s->c->c, 255, infh);
    printf("%d : fgets s->c->c\n", ftell(infh));

    s->c->d = (char*) malloc(255);
    fgets(s->c->d, 255, infh);
    printf("%d : fgets s->c->d\n", ftell(infh));
*/
    printf("s->c->b = %d\n", s->c->b);
    printf("s->c->c = %s\n", s->c->c);
    printf("s->c->d = %s\n", s->c->d);
    return 0;
}
