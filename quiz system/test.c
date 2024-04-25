#include <stdio.h>
#include <stdio.h>
#include <strings.h>
#include <time.h>
#include <openssl/sha.h>

int testfunc(const char filename[])
{
    FILE *fp = fopen(filename, "a");
    char *str = "Hello World";
    fprintf(filename, "%s", str);
    fclose(fp);
    return 0;
}
int main()
{

    testfunc("test1file");
    return 0;
}