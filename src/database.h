#ifndef __DATABASE_H
#define __DATABASE_H

#include <time.h>

#define DATABASE_OK 0
#define DATABASE_FAIL 1

/* Constraints */
#define NODE_NAMELEN 64

/* Error Functions */
#define failedToStart(s) ((s)->message & DATABASE_FAIL)

typedef struct databaseNode {
  time_t ntime; /* Time of database creation */
  char name; /* Name of the running database */
  time_t fail_time; /* Time it bugged out at (to be logged) */
  int port; /* Port it's running on */
} databaseNode;

typedef struct databaseState {
  databaseNode *me; /* This node */
  int state; /* DATABASE_OK, DATABASE_FAIL, ... */
  int size; /* Amount of data in use at this moment */
  char* data_location; /* data location */
} databaseState;

#endif
