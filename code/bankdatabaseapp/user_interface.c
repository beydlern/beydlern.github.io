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
//  FILE:        user_interface.c
//
//  DESCRIPTION:
//   The user interface manages user interactions and
//   communicates with the database.
//
//  REFERENCES:
//   The C Programming Language - class book
//   https://en.cppreference.com/w/cpp/header/cstring
//   My own homework2 assignment
//   https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
//
****************************************************************/

#include "record.h"
#include "database.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void getaddress(char address[], int length);

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   The main function that calls other functions.
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : success
//
****************************************************************/

int debugmode = 0;

int main(int argc, char* argv[])
{
    struct record *start;
    char input[9];
    int accountno;
    char name[30];
    char address[60];
    int clear_input_buffer;
    int sentinel;
    int exit_indicator = 1;
    int valid_input;
    int result;
    int premature_exit = 1;
    int i;
    int j;

    start = NULL;

    if (argc >= 2 && (strcmp(argv[1], "debug") == 0))
    {
        if (argc == 2 && (strcmp(argv[1], "debug") == 0))
        {
            debugmode = 1;
            printf("\n------------------\n");
            printf("Debug mode activated.");
            printf("\n------------------\n");
        }
        else
        {
            printf("Error: incorrect arguments - exiting program.\n");
            premature_exit = 0;
        }
    }

    if (premature_exit) 
    {
        printf("Welcome to the Bank Database Application.");
        readfile(&start, "data.txt");
        do
        {
            printf("\nPlease choose an option menu by typing the partial or full option name from the list below:\n");
            printf("add: Add a new record in the database. \n");
            printf("printall: Print all records in the database.\n");
            printf("find: Find record(s) with a specified account #.\n");
            printf("delete: Delete existing record(s) from the database using the account # as a key.\n");
            printf("quit: Quit the program.\n");
            printf("Enter:\n");

            scanf("%9s", input);

            accountno = 0;

            if (strstr("add\n",input) != NULL) 
            {
                sentinel = 1;

                do
                {
                    printf("Enter your account number:\n");
                    valid_input = scanf("%d", &accountno);
                    if (valid_input == 0)
                    {
                        printf("Error: enter an integer only.\n");
                        do
                        {
                            clear_input_buffer = getchar();
                        }
                        while (clear_input_buffer != '\n' && clear_input_buffer != EOF);
                    }
                    if (accountno <= 0)
                    {
                        printf("Error: enter a positive integer.\n");
                    }
                    if (valid_input == 1 && accountno > 0)
                    {
                        sentinel = 0;
                    }
                }
                while (sentinel);

                do
                {
                    clear_input_buffer = getchar();
                }
                while (clear_input_buffer != '\n' && clear_input_buffer != EOF);

                getaddress(address, 60);

                do
                {
                    clear_input_buffer = getchar();
                }
                while (clear_input_buffer != '\n' && clear_input_buffer != EOF);

                printf("Enter the name:\n");
                fgets(name, 30, stdin);

                clear_input_buffer = strlen(name) - 1;
                if (name[clear_input_buffer] == '\n') 
                {
                    name[clear_input_buffer] = '\0';
                }

                addRecord(&start, accountno, name, address);
                printf("\nAdded new record.\n");
                for (i = 0; i < 30; i++) 
                {
                    name[i] = '\0';
                }

                for (j = 0; i < 60; i++) 
                {
                    address[j] = '\0';
                }
            }

            else if (strstr("printall\n",input) != NULL)
            {
                printAllRecords(start);
            }

            else if (strstr("find\n",input) != NULL)
            {
                sentinel = 1;

                do
                {
                    printf("Enter your account number:\n");
                    valid_input = scanf("%d", &accountno);
                    if (valid_input == 0)
                    {
                        printf("Error: enter an integer only.\n");
                        do
                        {
                            clear_input_buffer = getchar();
                        }
                        while (clear_input_buffer != '\n' && clear_input_buffer != EOF);
                    }
                    if (accountno <= 0)
                    {
                        printf("Error: enter a positive integer.\n");
                    }
                    if (valid_input == 1 && accountno > 0)
                    {
                        sentinel = 0;
                    }
                }
                while (sentinel);
                
                result = findRecord(start, accountno);
                if (result == 0)
                {
                    printf("The record(s) with the account number %d were found.\n", accountno);
                }
                else
                {
                    printf("There were no record(s) with the account number %d found.\n", accountno);
                }
            }

            else if (strstr("delete\n",input) != NULL)
            {
                sentinel = 1;

                do
                {
                    printf("Enter your account number:\n");
                    valid_input = scanf("%d", &accountno);
                    if (valid_input == 0)
                    {
                        printf("Error: enter an integer only.\n");
                        do
                        {
                            clear_input_buffer = getchar();
                        }
                        while (clear_input_buffer != '\n' && clear_input_buffer != EOF);
                    }
                    if (accountno <= 0)
                    {
                        printf("Error: enter a positive integer.\n");
                    }
                    if (valid_input == 1 && accountno > 0)
                    {
                        sentinel = 0;
                    }
                }
                while (sentinel);

                result = deleteRecord(&start, accountno);
                if (result == 0)
                {
                    printf("The record(s) with the account number %d were deleted.\n", accountno);
                }
                else
                {
                    printf("There were no record(s) with the account number %d to delete.\n", accountno);
                }
            }

            else if (strstr("quit\n",input) != NULL)
            {
                exit_indicator = 0;
                writefile(start, "data.txt");
                cleanup(&start);
            }

            else
            {
                printf("Invalid option name, try again.\n");
            }

        } while (exit_indicator);
    }
    return 0;
}

/*****************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION:   Obtains the address of the customer.
//
//  Parameters: address (char []) : the address of the customer.
//              length (int) : the max length of the address array. 
//
//  Return values:  None
//
****************************************************************/

void getaddress(char address[], int length)
{
    int character;
    int sentinel = 1;
    int i = 0;

    if (debugmode) 
    {
        printf("\n------------------\n");
        printf("Function name: getaddress\n");
        printf("The length parameter has initial value: %d\n", length);
        printf("The address paramter has initial value:");
        printf("address: %s\n", address);
        printf("\n------------------\n");
    }

    printf("Enter your address (submit a '+' character at the end of your address submission): \n");

    do
    {
        character = getchar();
        if (character != '+')
        {
            address[i] = character;
            i++;
        } 
        else
        {
            address[i] = character;
            sentinel = 0;
        }
    }
    while (sentinel && character != EOF && i < length);
}
