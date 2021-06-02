#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define OFFSETBITS 15
#define LENGTHBITS 5

#define OFFSETMASK ((1 << (OFFSETBITS)) - 1)
#define LENGTHMASK ((1 << (LENGTHBITS)) - 1)

#define GETOFFSET(x) (x >> LENGTHBITS)
#define GETLENGTH(x) (x & LENGTHMASK)
#define OFFSETLENGTH(x,y) (x << LENGTHBITS | y)

struct token {
    char c;
    uint8_t uzu;
};


struct token *encode(char *metin, int max, int *aff)
{
     char * ara;
     struct token t;
    int a = 1 << 3;
    struct token *sonn = malloc(a * sizeof(struct token));
    int afff = 0;

    char * aramaileri;


    for (aramaileri = metin; aramaileri < metin + max; aramaileri++){
        ara = aramaileri - OFFSETMASK;
        if (ara < metin)
            ara = metin;

        int benzermax = 0;

        char *en = aramaileri;

        for (; ara < aramaileri; ara++)
        {


            int benzeradet = benzerbul(ara, aramaileri);



            if (benzeradet > benzermax){
                benzermax = benzeradet;
                en = ara;
            }
        }


        if (aramaileri + benzermax >= metin + max){
            benzermax = metin + max - aramaileri - 1;
        }


        t.uzu = OFFSETLENGTH(aramaileri - en, benzermax);
        aramaileri += benzermax;
        t.c = *aramaileri;

        if (afff + 1 > a)
        {
            a = a << 1;
            sonn = realloc(sonn, a * sizeof(struct token));
        }

        sonn[afff++] = t;
    }

    if (aff)
        *aff = afff;

    return sonn;
}
int benzerbul(char *arama, char *bas)
{
    int benzeradet = 0;

    while (*arama++ == *bas++ && benzeradet < LENGTHMASK)
        benzeradet++;

    return benzeradet;
}


int main()
{   int output;
    int oran;
    int uzunluk=99 ;
    int tokenadet ;
    char * txt;
    struct token * outputtxt;

    FILE * fp;

    if (fp = fopen("metin.txt", "rb"))
    {

        fseek(fp, 0, SEEK_END);
        uzunluk = ftell(fp);
        txt = malloc(uzunluk);
        fseek(fp, 0, SEEK_SET);
        fread(txt, 1, uzunluk, fp);
        fclose(fp);
    }
     else
        printf("\n Projenin konumunda metin.txt adli bir dosyaniz bunumamaktadir.\n");



    outputtxt = encode(txt, uzunluk, &tokenadet);

    if (fp = fopen("output.txt", "wb"))
    {
        fwrite(outputtxt, sizeof(struct token), tokenadet, fp);
        printf("DOSYANIZ BASARILI BIR SEKILDE SIKISTIRILIP output.txt OLARAK DOSYA KONUMUNA YAZDIRILMISTIR.");
        fclose(fp);
    }
    else
        printf("\n Projenin konumunda output.txt adl� dosya a��lamad�.\n");

    output=tokenadet * sizeof(struct token);
    printf("\n\n");
    float kb1=((float)uzunluk/1024);
    float kb2=((float)output/1024);
    float orankb=(kb2/kb1)*100;

    printf("Orjinal Boyut: %.2f KB\n",kb1 );
    printf("Encode Boyutu: %.2f KB\n",kb2);
    printf("Basari Orani: %%%.2f \n",orankb);
    printf("\n\n");
    return 0;
}
