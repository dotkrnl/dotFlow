#include <cstdio>

void fprintLocation(FILE *f, int l, int loc);

int main(void)
{
    int level, id, count;
    while (scanf("%d,%*d,%d,%d;", &level, &id, &count) != EOF) {
        if (level > 7) break;
        char filename[100];
        sprintf(filename, "./dest/%d.%02d", level, id);
        FILE *f = fopen(filename, "w");
        fprintf(f, "%d %d\n", level, level);
        for (int i = 0; i < count; i++) {
            int first; scanf("%d", &first);
            fprintLocation(f, level, first);
            fprintf(f, " ");
            int last = 0;
            while (getchar() != ';')
                scanf("%d", &last);
            fprintLocation(f, level, last);
            fprintf(f, "\n");
        }
        fclose(f);
    }
}

void fprintLocation(FILE *f, int l, int loc)
{
    int x = loc % l;
    int y = loc / l;
    fprintf(f, "%d %d", x, y);
}
