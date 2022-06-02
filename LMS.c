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

    book data = {0};
    FILE *fp = NULL;
    char ch;
    fp = fopen("data.bin", "ab+");

    printf("\n\n\t\t\t\tENTER  DETAILS BELOW :");
    printf("\n\t\t\t\t---------------------------------------------------------------------------\n");

    printf("\n\t\t\t\tBook ID NO  : ");
    fflush(stdin);
    scanf("%u", &data.book_id);

    printf("\n\t\t\t\tBook Name  : ");
    fflush(stdin);
    fgets(data.name, 50, stdin);

    printf("\n\t\t\t\tAuthor Name  : ");
    fflush(stdin);
    fgets(data.author, 30, stdin);

    fwrite(&data, sizeof(data), 1, fp);
    fclose(fp);

    printf("\n\t\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\t\tBook added Successfully.................");

    printf("\n\n\n\t\t\t\tDo you want add another Book [Y/N] : ");
    fflush(stdin);
    scanf("%c", &ch);

    if (ch == 'Y' || ch == 'y')
    {
        addbook();
    }
    else
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

    book data = {0};
    char bookName[30] = {0};
    int bookDelete = 0;
    int issuebook = 0;
    int found = 0;
    char str[30];

    FILE *fp = NULL;
    FILE *tmpFp = NULL;

    fp = fopen("data.bin", "rb");
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

    printf("\n\t\t\t\tEnter Book ID NO. for Issue: ");
    scanf("%d", &issuebook);

    while (fread(&data, sizeof(data), 1, fp))
    {
        if (data.book_id != issuebook)
        {
            fwrite(&data, sizeof(data), 1, tmpFp);
        }

        else
        {
            found = 1;
        }
    }
    (found == 1) ? printf("\n\t\t\t\tEnter Details.....") : printf("\n\t\t\t\tRecord not found");
    fclose(fp);
    fclose(tmpFp);
    remove("data.bin");
    rename("tmp.bin", "data.bin");

    fp = fopen("data.bin", "ab+");

    printf("\n\t\t\t\tBook ID NO  : ");
    fflush(stdin);
    scanf("%u", &data.book_id);

    printf("\n\t\t\t\tBook Name  : ");
    fflush(stdin);
    fgets(data.name, 50, stdin);

    printf("\n\t\t\t\tAuthor Name  : ");
    fflush(stdin);
    fgets(data.author, 30, stdin);

    data.flag = 1;

    printf("\n\t\t\t\tStudent Name : ");
    fflush(stdin);
    fgets(data.studentName, 50, stdin);

    printf("\n\t\t\t\tBook issue date(day/month/year) : ");
    fflush(stdin);
    scanf("%d/%d/%d", &data.issue_date.dd, &data.issue_date.mm, &data.issue_date.yyyy);

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
    book data = {0};

    FILE *fp = NULL;
    unsigned int countBook = 1;
    fp = fopen("data.bin", "rb");

    while (fread(&data, sizeof(data), 1, fp))
    {
        printf("\n\t\t\t\tBook Count = %d\n\n", countBook);
        printf("\t\t\t\tBook id : %u", data.book_id);
        printf("\n\t\t\t\tBook name : %s", data.name);
        printf("\t\t\t\tBook author : %s", data.author);
        if (data.flag == 1)
        {
            printf("\t\t\t\tStatus : Book issued");
            printf("\n\t\t\t\tStudent Name : %s", data.studentName);
            printf("\t\t\t\tBook issue date(day/month/year) : (%d/%d/%d)\n\n", data.issue_date.dd, data.issue_date.mm, data.issue_date.yyyy);
        }
        else
        {
            printf("\t\t\t\tStatus : Not issued \n");
        }

        found = 1;
        ++countBook;
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

    int found = 0, ch;
    char bookName[50] = {0};
    book data = {0};
    FILE *fp = NULL;

    printf("\n\n\t\t\t\tEnter 1 to Search by Book Name ");
    printf("\n\t\t\t\tEnter 2 to Search by Author Name");
    printf("\n\n\t\t\t\tChoice : ");
    scanf("%d", &ch);

    fp = fopen("data.bin", "rb");
    if (fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }

    if (ch == 1)
    {
        printf("\n\n\t\t\t\tEnter Book Name to search : ");
        fflush(stdin);
        fgets(bookName, 50, stdin);
        while (fread(&data, sizeof(data), 1, fp))
        {
            if (!strcmp(data.name, bookName))
            {
                found = 1;
                break;
            }
        }
        if (found)
        {
            printf("\n\t\t\t\tBook id : %u", data.book_id);
            printf("\n\t\t\t\tBook name : %s", data.name);
            printf("\t\t\t\tBook authorName : %s", data.author);
        }
        else
        {
            printf("\n\t\t\tNo Record");
        }
        fclose(fp);
        goto_start();
    }
    else if (ch == 2)
    {
        printf("\n\n\t\t\t\tEnter Book Author to search : ");
        fflush(stdin);
        fgets(bookName, 50, stdin);

        while (fread(&data, sizeof(data), 1, fp))
        {
            if (!strcmp(data.author, bookName))
            {
                found = 1;
                break;
            }
        }
        if (found)
        {
            printf("\n\t\t\t\tBook id : %u", data.book_id);
            printf("\n\t\t\t\tBook name : %s", data.name);
            printf("\t\t\t\tBook authorName : %s", data.author);
        }
        else
        {
            printf("\n\t\t\tNo Record");
        }

        fclose(fp);
        goto_start();
    }

    else
        searchBooks();
}

void deleteBooks()
{
    system("cls");

    header();

    printf("\n\n\n");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");
    printf("\n\t\t\t\t                         Delete Books Details                             ");
    printf("\n\t\t\t\t--------------------------------------------------------------------------");

    int found = 0, i;
    int bookDelete = 0;
    char bookName[30] = {0};
    book data = {0};

    FILE *fp = NULL;
    FILE *tmpFp = NULL;

    fp = fopen("data.bin", "rb");
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
        if (data.book_id != bookDelete)
        {
            fwrite(&data, sizeof(data), 1, tmpFp);
        }

        else
        {
            found = 1;
        }
    }
    (found == 1) ? printf("\n\t\t\t\tRecord deleted successfully.....") : printf("\n\t\t\t\tRecord not found");
    fclose(fp);
    fclose(tmpFp);
    remove("data.bin");
    rename("tmp.bin", "data.bin");

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
