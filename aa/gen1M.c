#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    FILE *f;
    f = fopen("oneMillion.txt", "w");
    const int oneM = (int)1e7;
    srand(1);
    fprintf(f, "%d %d\n", oneM, 100);
    for(int i = 0; i < oneM; ++i){
        fprintf(f, "%d\n", rand()*oneM );
    }
    fclose(f);
    return 0;
}
