#ifndef PARSER_H
#define PARSER_H

#include <getopt.h>

extern int numThreads;
extern int numIter;

static struct option long_options[] = 
{
	{"threads",		optional_argument,  0,  't' }, 
    {"iterations",	optional_argument,  0,  'i' },
    {"yield",		optional_argument,  0,  'y' }, 
    {"sync",      	optional_argument,  0,  's' },  
    {0,             0,                  0,   0  } 
};

int parser(int argc, char** argv);

#endif