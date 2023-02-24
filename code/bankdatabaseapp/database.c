/*****************************************************************
//
//  NAME:        Nicholas Beydler
//
//  HOMEWORK:    3b
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        October 29, 2022
//
//  FILE:        database.c
//
//  DESCRIPTION:
//   The main driver of code that handles a bank customer's
//   record.
//
//  REFERENCES:
//   https://stackoverflow.com/questions/45938222/how-to-peek-ahead-when-processing-an-input-file-processing-2-lines 
//
****************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "record.h"

extern int debugmode;

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   Adds a new record.
//
//  Parameters:    start (struct record **) : the starting record
//                 accountno (int) : the account number to add
//                 name (char []) : the name to add
//                 address (char []) : the address to add
//
//  Return values:  None
//
****************************************************************/

void addRecord (struct record ** start, int accountno, char name[], char address[])
{
    if (debugmode)
    {
        int i;
        printf("\n------------------\n");
        printf("\nFunction name: addRecord\n");
        printf("\nThe accountno parameter has initial value: %d\n", accountno);
        printf("\nThe name parameter has initial value:\n");
        printf("Name: %s\n", name);
        printf("\nThe address parameter has initial value:\n");
        printf("Address: ");
        for (i = 0; i < strlen(address); i++)
        {
            if (address[i] != '+')
            {
                printf("%c",address[i]);
            }
        }
        printf("\n");
        printf("\n------------------\n");
    }
    if ((*start) != NULL) 
    {
        struct record *current;
        struct record *temp;
        int currentaccountno;
        int sentinel;
        current = (struct record*)malloc(sizeof(struct record));
        temp = (struct record*)malloc(sizeof(struct record));
        current = *start;
        sentinel = 1;
        while (sentinel)
        {
            currentaccountno = current->accountno;
            if (accountno < currentaccountno && current->next == NULL)
            {
                current->next = temp;
                temp->accountno = accountno;
                strcpy(temp->name, name);
                strcpy(temp->address, address);
                temp->next = NULL;
                sentinel = 0;
            }
            else if (accountno >= currentaccountno)
            {
                temp->accountno = current->accountno;
                strcpy(temp->name, current->name);
                strcpy(temp->address, current->address);
                temp->next = current->next;
                current->accountno = accountno;
                strcpy(current->name, name);
                strcpy(current->address, address);
                current->next = temp;
                sentinel = 0;
            }
            current = current->next;
        }
    }
    else
    {
        *start = (struct record*)malloc(sizeof(struct record));
        (*start)->accountno = accountno;
        strcpy((*start)->name, name);
        strcpy((*start)->address, address);
        (*start)->next = NULL;
    }
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   Prints all records.
//
//  Parameters:    start : (struct record *) : The starting record
//
//  Return values:  None
//
****************************************************************/

void printAllRecords(struct record * start)
{
    struct record *temp;
    int i;
    temp = (struct record*)malloc(sizeof(struct record));
    if (debugmode)
    {
        printf("\n------------------\n");
        printf("\nFunction name: printallRecords\n");
        printf("\n------------------\n");
    }
    temp = start;
    while (temp != NULL)
    {
        printf("\nAccount number: %d\n", temp->accountno);
        printf("Name: %s\n", temp->name);
        printf("Address: ");
        for (i = 0; i < strlen(temp->address); i++)
        {
            if (temp->address[i] != '+')
            {
                printf("%c",temp->address[i]);
            }
        }
        printf("\n");
        temp = temp->next;
    }
    if (start == NULL)
    {
        printf("There are no records to print.\n");
    }
}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   Finds a record.
//
//  Parameters:    start : (struct record *) : The starting record
//                 accountno : (int) : The account number.
//
//  Return values:  0 : success
//                  -1 : failure
//
****************************************************************/

int findRecord (struct record * start, int accountno)
{
    int returnValue;
    int i;
    struct record *temp;
    temp = (struct record*)malloc(sizeof(struct record));
    if (debugmode)
    {
        printf("\n------------------\n");
        printf("\nFunction name: findRecord\n");
        printf("\nThe accountno parameter has initial value: %d\n", accountno);
        printf("\n------------------\n");
    }
    temp = start;
    returnValue = -1;
    while (temp != NULL)
    {
        if (temp->accountno == accountno)
        {
            printf("\nAccount number: %d\n", temp->accountno);
            printf("Name: %s\n", temp->name);
            printf("Address: ");
            for (i = 0; i < strlen(temp->address); i++)
            {
                if (temp->address[i] != '+')
                {
                    printf("%c",temp->address[i]);
                }
            }
            printf("\n");
            returnValue = 0;
        }
        temp = temp->next;
    }
    return returnValue;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   Deletes a record.
//
//  Parameters:    start (struct record **) : Starting record
//                 accountno (int) : The account number to delete
//                                   the associated records with it
//
//  Return values:  -1 : no record with the account number as
//                       accountno
//                   0 : a record with the account number as
//                       accountno was deleted
//
****************************************************************/

int deleteRecord(struct record ** start, int accountno)
{
    struct record *current;
    struct record *temp;
    struct record *previous;
    int sentinel;
    int returnValue;
    if (debugmode)
    {
        printf("\n------------------\n");
        printf("\nFunction name: deleteRecord\n");
        printf("\nThe accountno parameter has initial value: %d\n", accountno);
        printf("\n------------------\n");
    }
    current = (struct record*)malloc(sizeof(struct record));
    temp = (struct record*)malloc(sizeof(struct record));
    previous = (struct record*)malloc(sizeof(struct record));
    current = *start;
    previous = *start;
    sentinel = 1;
    returnValue = -1;
    if ((*start) != NULL)
    {
        if ((*start)->accountno == accountno && (*start)->next == NULL)
        {
            returnValue = 0;
            sentinel = 0;
            free((*start));
            (*start) = NULL;
        }
        while (sentinel)
        {
            if (current != NULL && current->accountno != accountno)
            {
                previous = current;
                current = current->next;
            }
            if ((*start)->accountno == accountno)
            {
                returnValue = 0;
                temp = current;
                (*start) = current->next;
                free(temp);
                current = (*start);
            }
            if (current != NULL && current->accountno == accountno)
            {
                returnValue = 0;
                temp = current;
                previous->next = current->next;
                free(temp);
                current = previous->next;
            }
            if (current == NULL || current->accountno < accountno)
            {
                sentinel = 0;
            }
        }
    }
    return returnValue;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   Writes the data stored into a text file.
//
//  Parameters:    start (struct record *) : The starting record.
//                 filename (char []) : The name of the file.
//
//  Return values:  0 : success to open file
//                  -1 : failure to open file
//
****************************************************************/

int writefile(struct record * start, char filename[])
{
    int returnvalue;
    FILE *outfileptr;
    struct record *temp;
    returnvalue = 0;
    remove(filename);
    temp = (struct record*)malloc(sizeof(struct record));
    temp = start;
    outfileptr = fopen(filename, "w");
    if ( outfileptr )
    {
        while (temp != NULL)
        {
            if (temp->accountno != 0)
            {
                if (temp->next == NULL)
                {
                    fprintf(outfileptr, "%d\n", temp->accountno);
                    fprintf(outfileptr, "%s\n", temp->name);
                    fprintf(outfileptr, "%s", temp->address);
                }
                else
                {
                    fprintf(outfileptr, "%d\n", temp->accountno);
                    fprintf(outfileptr, "%s\n", temp->name);
                    fprintf(outfileptr, "%s\n", temp->address);
                }
                temp = temp->next;
            }
        }
        fclose(outfileptr);
    }
    else
    {
        returnvalue = -1;
    }

    if (start == NULL)
    {
        remove(filename);
    }

    return returnvalue;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   Reads data from a text file and stores it.
//
//  Parameters:    start (struct record **) : The starting record.
//                 filename (char []) : The name of the file.
//
//  Return values:  0 : success to open file
//                  -1 : failure to open file
//
****************************************************************/

int readfile(struct record ** start, char filename[])
{
    int character;
    int sentinel;
    int i;
    int returnvalue;
    int clear_input_buffer;
    FILE *infileptr;
    char name[30];
    char address[60];
    int accountno;
    character = 0;
    sentinel = 1;
    returnvalue = 0;
    infileptr = fopen(filename, "r");
    if ( infileptr )
    {
        while (!feof(infileptr))
        {
            fscanf(infileptr, "%d\n", &accountno);
            fgets(name, 30, infileptr);
            clear_input_buffer = strlen(name) - 1;
            if (name[clear_input_buffer] == '\n') 
            {
                name[clear_input_buffer] = '\0';
            }
            i = 0;
            sentinel = 1;
            while (sentinel && i < 60)
            {
                character = fgetc(infileptr);
                if (character != '+')
                {
                    address[i] = character;
                    i++;
                }
                else
                {
                    address[i] = character;
                    while (sentinel)
                    {
                        character = fgetc(infileptr);
                        if (character == '\n' || character == EOF)
                        {
                            sentinel = 0;
                        }
                    }
                }
            }
            addRecord(start, accountno, name, address);
            for (i = 0; i < 30; i++) 
            {
                name[i] = '\0';
            }

            for (i = 0; i < 60; i++) 
            {
                address[i] = '\0';
            }
            accountno = 0;
        }
        fclose(infileptr);
    }
    else
    {
        returnvalue = -1;
    }
    return returnvalue;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   Releases all allocated space in heap memory.
//
//  Parameters:    start (struct record **) : the starting record
//
//  Return values:  None
//
****************************************************************/

void cleanup(struct record ** start)
{
    struct record *temp;
    struct record *next;
    temp = (struct record*)malloc(sizeof(struct record));
    next = (struct record*)malloc(sizeof(struct record));
    while (temp != NULL)
    {
        next = temp->next;
        free(temp);
        temp = next;
    }
    free(*start);
    *start = NULL;
}