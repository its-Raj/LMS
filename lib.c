#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILE_NAME "data.bin"

typedef struct books
{
    int ass_no;
    char name[25];
    char author[30];
    int price;
    int flag;
} book;

book b[100];

void header();
void start();
void addbook(int *);
void display(int *);

int main()
{
    system("cls");
    start();
    return 0;
}

void header()
{
    printf("\n\n\n");
    printf("\t\t\t\t***************************************************************************");
    printf("\n\t\t\t\t************                                                   ************");
    printf("\n\t\t\t\t************           Library management System               ************");
    printf("\n\t\t\t\t************                                                   ************");
    printf("\n\t\t\t\t***************************************************************************");
}

void start()
{
    int count = 0;
    int ch;
    header();

    printf("\n\n\t\t\t\tEnter 1 to Add Book");
    printf("\n\t\t\t\tEnter 2 to Display Book Details");
    printf("\n\t\t\t\tEnter 3 to issue Book ");

    printf("\n\n\t\t\t\tEnter Choice : ");
    scanf("%d", &ch);

    switch (ch)
    {
    case 1:
        addbook(&count);
        break;
    case 2:
        display(&count);
        break;

    default:
        printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        break;
    }
}

void addbook(int *count)
{
    *count = 0;
    system("cls");
    int n;

    header();

    printf("\n\n\n");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");
    printf("\n\t\t\t\t                              Add Books                                   ");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");

    printf("\n\n\t\t\t\tHow many book do you want to add : ");
    scanf("%d", &n);

    FILE *fp = NULL;
    fp = fopen(FILE_NAME, "ab+");

    for (int i = 0; i < n; i++)
    {
        printf("\n\t\t\t\tEnter Accsation NO.: ");
        scanf("%d", &b[i].ass_no);
        getchar();

        printf("\n\t\t\t\tEnter Book Name : ");
        gets(b[i].name);
        getchar();

        printf("\t\t\t\tEnter Author Name : ");
        gets(b[i].author);
        getchar();

        printf("\n\t\t\t\tEnter Book Price : ");
        scanf("%d", &b[i].price);
        getchar();

        printf("\n\t\t\t\tEnter Flag (0 - issued / 1 - not issued ) : ");
        scanf("%d", &b[i].flag);
        *count++;
    }

    fclose(fp);

    printf("Book added Successfully.................");

    system("cls");
    start();
}

void display(int *count)
{
    printf("\n\n\n");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");
    printf("\n\t\t\t\t                         book Details                                     ");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");
    char str[20];

    for (int i = 0; i <= *count; i++)
    {
        printf("\n");
        printf("\n\t\t\t\tAccsation NO.: %d", b[i].ass_no);
        printf("\n\t\t\t\tBook Name : %s", b[i].name);
        printf("\n\t\t\t\tAuthor Name : %s", b[i].author);
        printf("\n\t\t\t\tBook Price : %d", b[i].price);

        if (b[i].flag == 1)
            strcpy(str, "Book is not issued");

        else
            strcpy(str, "Book is issued");

        printf("\n\t\t\t\tStatus : %s", str);
    }

    printf("\n\n\t\t\t\tCount = %d", *count);

    exit(1);
}
