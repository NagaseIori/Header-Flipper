#include <cstdio>
#include <ctime>
#include <string>
#include <cstring>
using namespace std;

FILE *flog;
void OutLog(string contains)
{
    time_t now = time(0);
    char *dt = ctime(&now);
    *(dt + strlen(dt) - 1) = 0;
    contains = string("[") + dt + string("] ") + contains;
    fprintf(flog, "%s", contains.c_str());
}
void OutLogln(string contains)
{
    time_t now = time(0);
    char *dt = ctime(&now);
    *(dt + strlen(dt) - 1) = 0;
    contains = string("[") + dt + string("] ") + contains;
    fprintf(flog, "%s\n", contains.c_str());
}

int main(int argc, char *argv[])
{
    flog = fopen("log.txt", "a");
    char con[61] = {0};
    for (int i = 1; i < argc; i++)
    {
        OutLogln(string("Flipping file: ") + argv[i]);
        FILE *fp = fopen(argv[i], "r+b");
        fseek(fp, 0, SEEK_SET);
        unsigned char x;
        for (int i = 0; i < 60; i++)
        {
            fread(&x, 1, 1, fp);
            fseek(fp, -1, SEEK_CUR);
            sprintf(con + i * 2, "%02x", x);
            x = ~x;
            fwrite(&x, 1, 1, fp);
            fseek(fp, 0, SEEK_CUR);
        }

        fclose(fp);
        OutLogln(string("Read: ") + con);
        OutLogln(string("Flipping Done."));
    }
    return 0;
}
