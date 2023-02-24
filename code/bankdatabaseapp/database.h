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
//  FILE:        database.h
//
//  DESCRIPTION:
//   The database header file that gives the functions declarations
//   for each of the functions in database.c.
//
//  REFERENCES:
//   None 
//
****************************************************************/

void addRecord (struct record **, int, char [ ],char [ ]);
void printAllRecords(struct record *);
int findRecord (struct record *, int);
int deleteRecord(struct record **, int);
int writefile(struct record *, char []);
int readfile(struct record **, char []);
void cleanup(struct record **);