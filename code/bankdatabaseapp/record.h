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
//  FILE:        record.h
//
//  DESCRIPTION:
//   A customer's bank records that contains that customer's
//   account number, name, and address.
//
//  REFERENCES:
//   None 
//
****************************************************************/

struct record
{
    int                accountno;
    char               name[30];
    char               address[60];
    struct record*     next;
};
