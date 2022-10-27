#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "avlbst.h"

#define FLDSIZ 256

char printmenu();
void stripnl(char *);
void report(struct node *);

int main(int argc, char *argv[])
{
    int n = 0, alt = 0;
    char ans, c;
    char key[FLDSIZ], value[FLDSIZ];
    struct node *target = (struct node *) NULL;
    struct node *bst = (struct node *) NULL;
    FILE *fp;

    if (argc > 1) {
        if ((fp = fopen(argv[1], "r")) != (FILE *) NULL) {
            bst = deserialize(fp, bst);
            fclose(fp);
            report(bst);
        }
        else {
            fprintf(stderr, "error opening file %s\n", argv[1]);
            return(1);
        }
    }
    else {
        if ((fp = fopen("bst.dat", "r")) != (FILE *) NULL) {
            bst = deserialize(fp, bst);
            fclose(fp);
            report(bst);
        }
    }

    while ((ans = printmenu()) != 'E') {
        if (alt == 0 && (ans == 'C' || ans == 'U' || ans == 'D'))
            alt = 1;
        memset(key, 0, sizeof(key));
        memset(value, 0, sizeof(value));
        printf(" key: ");
        fgets(key, sizeof(key), stdin);
        stripnl(key);
        if (ans == 'C') {
            while (strlen(key)) {
                printf(" value: ");
                fgets(value, sizeof(value), stdin);
                stripnl(value);
                bst = insert(bst, key, value);
                printf(" key: ");
                fgets(key, sizeof(key), stdin);
                stripnl(key);
            }
        }
        else if (ans == 'R') {
            while (strlen(key)) {
                target = retrieve(bst, key);
                printf(" value: ");
                if (target != (struct node *) NULL)
                    puts(target->value);
                else
                    putchar('\n');
                printf(" key: ");
                fgets(key, sizeof(key), stdin);
                stripnl(key);
            }
        }
        else if (ans == 'U') {
            while (strlen(key)) {
                printf(" value: ");
                fgets(value, sizeof(value), stdin);
                stripnl(value);
                bst = erase(bst, key);
                bst = insert(bst, key, value);
                printf(" key: ");
                fgets(key, sizeof(key), stdin);
                stripnl(key);
            }
        }
        else if (ans == 'D') {
            while (strlen(key)) {
                bst = erase(bst, key);
                printf(" key: ");
                fgets(key, sizeof(key), stdin);
                stripnl(key);
            }
        }
    }

    if (alt) {
        report(bst);
        fp = fopen("bst.dat", "w");
        serialize(fp, bst);
        fclose(fp);
    }
    bst = deallocate(bst);
    return(0);
}

char printmenu()
{
    char ch;
    char ans[25];

    do {
        printf(" (c)reate records\n");
        printf(" (r)etrieve records\n");
        printf(" (u)pdate records\n");
        printf(" (d)elete records\n");
        printf(" (e)xit\n");
        printf(" -> ");
        memset(ans, 0, sizeof(ans));
        fgets(ans, sizeof(ans), stdin);
        ch = toupper(ans[0]);
    } while (ch != 'C' && ch != 'R' && ch != 'U' && ch != 'D' && ch != 'E');
    return(ch);
}

void stripnl(char *str)
{
    int n = strlen(str);

    if (str[n - 2] == '\r' && str[n - 1] == '\n') {
        str[n - 2] = '\0';
        return;
    }
    if (str[n - 1] == '\n')
        str[n - 1] = '\0';
    return;
}

void report(struct node *bst)
{
    /* inorder(bst); */
    printf("nodes = %d\n", size(bst));
    printf("leaves = %d\n", leaves(bst));
    printf("height = %d\n", height(bst));
}
