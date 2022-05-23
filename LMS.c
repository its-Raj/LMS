#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;

typedef struct books
{
    int book_id;
    char name[25];
    char author[30];
    int flag;
    char studentName[30];
    Date issue_date;
} book;

book data[100];

// Function Decleration
void header();
void start();
void addbook();
void display();
void searchBooks();
void issueBooks();
void deleteBooks();
void goto_start();

int main()
{
    system("cls");
    start();
    return 0;
}

void header()
{
    system("cls");
    printf("\n\n\n");
    printf("\t\t\t\t***************************************************************************");
    printf("\n\t\t\t\t************                                                   ************");
    printf("\n\t\t\t\t************           Library management System               ************");
    printf("\n\t\t\t\t************                                                   ************");
    printf("\n\t\t\t\t***************************************************************************");
}

void start()
{

    int ch;
    system("cls");
    header();

    printf("\n\n\t\t\t\tEnter 1 to Add Book");
    printf("\n\t\t\t\tEnter 2 to View Book Details");
    printf("\n\t\t\t\tEnter 3 to Search Book");
    printf("\n\t\t\t\tEnter 4 to Delete Book");
    printf("\n\t\t\t\tEnter 5 to Issue Book");

    printf("\n\n\t\t\t\tEnter 0 to Exit Application");

    printf("\n\n\t\t\t\tEnter Choice : ");
    scanf("%d", &ch);

    switch (ch)
    {
    case 1:
        addbook();
        break;
    case 2:
        display();
        break;
    case 3:
        searchBooks();
        break;
    case 4:
        deleteBooks();
        break;
    case 5:
        issueBooks();
        break;
    case 0:
        exit(1);

    default:
        printf("\n\n\n\t\t\t\tInvalid Input !!! Try again...");
        goto_start();
        break;
    }
}

void addbook()
{

    system("cls");

    header();

    printf("\n\n\n");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");
    printf("\n\t\t\t\t                              Add Book                                    ");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");

    FILE *fp = NULL;
    int i, n;
    printf("\n\n\t\t\t\tHow many books Do you want to Add : ");
    scanf("%d", &n);
    fp = fopen("test.bin", "ab+");

    printf("\n\n\t\t\t\tENTER YOUR DETAILS BELOW :");
    printf("\n\t\t\t\t---------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("\n\t\t\t\tBook ID NO  : ");
        fflush(stdin);
        scanf("%u", &data[i].book_id);

        printf("\n\t\t\t\tBook Name  : ");
        fflush(stdin);
        fgets(data[i].name, 50, stdin);

        printf("\n\t\t\t\tAuthor Name  : ");
        fflush(stdin);
        fgets(data[i].author, 30, stdin);
    }

    fwrite(&data, sizeof(data), 1, fp);
    fclose(fp);

    printf("\n\t\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\t\tBook added Successfully.................");

    goto_start();
}

void issueBooks()
{
    system("cls");

    header();

    printf("\n\n\n");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");
    printf("\n\t\t\t\t                              Issue Book                                   ");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");

    char bookName[30] = {0};
    int bookDelete = 0;
    int found = 0;
    int i = 0, n;
    char str[30];

    FILE *fp = NULL;
    FILE *tmpFp = NULL;

    fp = fopen("test.bin", "rb");
    if (fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    printf("\n\n\t\t\t\tEnter Book id to issue : ");
    scanf("%d", &i);

    printf("\n\t\t\t\tStudent Name : ");
    fflush(stdin);
    fgets(data[i].studentName, 50, stdin);

    printf("\n\t\t\t\tBook issue date(day/month/year) : ");
    fflush(stdin);
    scanf("%d/%d/%d", &data[i].issue_date.dd, &data[i].issue_date.mm, &data[i].issue_date.yyyy);

    fwrite(&data, sizeof(data), 1, fp);
    fclose(fp);

    printf("\n\t\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\t\tBook issued Successfully.................");

    goto_start();
}

void display()
{
    system("cls");

    header();

    printf("\n\n\n");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");
    printf("\n\t\t\t\t                              book Details                                ");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");

    int found = 0;

    int i = 0, n;

    FILE *fp = NULL;
    unsigned int countBook = 1;
    fp = fopen("test.bin", "rb");

    printf("\n\n\t\t\t\tHow many book to view : ");
    scanf("%d", &n);

    while (fread(&data, sizeof(data), 1, fp))
    {
        for (int i = 0; i < n; i++)
        {
            printf("\n\t\t\t\tBook Count = %d\n", countBook);
            printf("\n\t\t\t\tBook id : %u", data[i].book_id);
            printf("\n\t\t\t\tBook name : %s", data[i].name);
            printf("\n\t\t\t\tBook author : %s", data[i].author);
            printf("\n\t\t\t\tStudent Name : %s", data[i].studentName);
            printf("\n\t\t\t\tBook issue date(day/month/year) : (%d/%d/%d)\n\n", data[i].issue_date.dd, data[i].issue_date.mm, data[i].issue_date.yyyy);
            found = 1;
            ++countBook;
        }
    }

    fclose(fp);
    if (!found)
    {
        printf("\n\n\t\t\t\tNo Record Found... ");
    }

    goto_start();
}

void searchBooks()
{
    system("cls");

    header();

    printf("\n\n\n");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");
    printf("\n\t\t\t\t                              Search Book                                 ");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");

    int found = 0;
    int ch;
    int i = 0, n;
    char bookName[30] = {0};
    char AuthorName[30] = {0};

    FILE *fp = NULL;
    fp = fopen("test.bin", "rb");

    if (fp == NULL)
    {
        printf("\n\t\t\t\tFile is not opened\n");
        exit(1);
    }

    printf("\n\n\t\t\t\tEnter 1 to Search by Book Name ");
    printf("\n\t\t\t\tEnter 2 to Search by Author Name");
    printf("\n\n\t\t\t\tChoice : ");
    scanf("%d", &ch);

    if (ch == 1)
    {
        printf("\n\n\t\t\t\tEnter Book Name to search : ");
        fflush(stdin);
        fgets(bookName, 30, stdin);

        while (fread(&data, sizeof(data), 1, fp))
        {
            if (!strcmp(data[i].name, bookName))
            {
                found = 1;
            }

            if (found)
            {
                printf("\n\t\t\t\tBook id : %u", data[i].book_id);
                printf("\n\t\t\t\tBook name : %s", data[i].name);
                printf("\n\t\t\t\tBook authorName : %s", data[i].author);
                i++;
            }
            else
            {
                printf("\n\t\t\t\tNo Record Found....");
            }
        }
        goto_start();
    }
    else if (ch == 2)
    {
        printf("\n\n\t\t\t\tEnter Book Author Name to search : ");
        fflush(stdin);
        fgets(AuthorName, 30, stdin);

        while (fread(&data, sizeof(data), 1, fp))
        {
            if (!strcmp(data[i].author, AuthorName))
            {
                found = 1;
            }

            if (found)
            {
                printf("\n\t\t\t\tBook id : %u", data[i].book_id);
                printf("\n\t\t\t\tBook name : %s", data[i].name);
                printf("\t\t\t\tBook authorName : %s", data[i].author);
                i++;
            }
            else
            {
                printf("\n\t\t\t\tNo Record Found....");
            }
        }
        goto_start();
    }
}

void deleteBooks()
{
    system("cls");

    header();

    printf("\n\n\n");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");
    printf("\n\t\t\t\t                         Delete Books Details                             ");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");

    int found = 0;
    int i = 0, n;
    int bookDelete = 0;
    char bookName[30] = {0};

    FILE *fp = NULL;
    FILE *tmpFp = NULL;

    fp = fopen("test.bin", "rb");
    if (fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin", "wb");
    if (tmpFp == NULL)
    {
        fclose(fp);
        printf("File is not opened\n");
        exit(1);
    }

    printf("\n\t\t\t\tEnter Book ID NO. for delete : ");
    scanf("%d", &bookDelete);

    while (fread(&data, sizeof(data), 1, fp))
    {
        if (data[i].book_id != bookDelete)
        {
            fwrite(&data[i], sizeof(data[i]), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found) ? printf("\n\t\t\t\tRecord deleted successfully.....") : printf("\n\t\t\t\tRecord not found");
    fclose(fp);
    fclose(tmpFp);
    remove("test.bin");
    rename("tmp.bin", "test.bin");

    goto_start();
}

void goto_start()
{
    printf("\n\n\n\t\t\t\tPress Enter to go to main menu.....");
    fflush(stdin);
    getchar();

    system("cls");
    start();
}
