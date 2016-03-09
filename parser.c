#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>

#include "parser.h"
#include "addtest.h"

int numThreads = 1;
int numIter = 1;
char sync = 'a';

int exitStatus = 0;

int parser(int argc, char** argv)
{
	while (1)
	{
		int a;
		int option_index = 0;

		a = getopt_long(argc, argv, "", long_options, &option_index);
        if (a == -1)
            break;

        switch(a)
        {
        	case 't':
        	{
        		if (optarg != NULL)
        		{
        			char* end;
        			if (strtol(optarg, &end, 0) < 1)
        			{
        				fprintf(stderr, "ERROR: number of threads must be positive\n");
        				exitStatus = 1;
        			}
					else
					{
        				char* endT;
        				numThreads = strtol(optarg, &endT, 0);
        			}
        		}
        		break;
        	}
        	case 'i':
        	{
        		if (optarg != NULL)
        		{
        			char* end2;
        			if (strtol(optarg, &end2, 0) < 1)
        			{
        				fprintf(stderr, "ERROR: number of iterations must be positive\n");
        				exitStatus = 1;
        			}
        			else
        			{
        				char* endI;
        				numIter = strtol(optarg, &endI, 0);
        			}
        		}
        		break;
        	}
        	case 'y':
        	{
        		if (optarg != NULL)
        		{
        			char* end3;
        			if (strtol(optarg, &end3, 0) != 1)
        			{
        				fprintf(stderr, "ERROR: yield must be set to 1\n");
        				exitStatus = 1;
        			}
        			else
        			{
        				opt_yield = 1;
        			}
        		}
        		break;
        	}
        	case 's':
        	{
        		if (optarg != NULL)
        		{
        			if ((strcmp(optarg, "m")) == 0 || (strcmp(optarg, "s")) == 0 || (strcmp(optarg, "c")) == 0)
        			{
        				sync = optarg[0];
        			}
        			else
        			{
        				fprintf(stderr, "ERROR: invalid option for sync\n");
        				exitStatus = 1;
        			}
        		}
        		break;
        	}
        	 case '?':
        	 {
                exitStatus = 1;
                break;
            }
        	default:
        	{
        		abort();
        	}

        }
	}

	pthread_t* threads = malloc(numThreads * sizeof(pthread_t));
	//do if else - not already 1 - dont overwrite 1
	if (createThreads(numThreads, numIter, threads, sync))
	{
		exitStatus = 1;
	}
	
	if (joinThreads(numThreads, numIter, threads))
	{
		exitStatus = 1;
	}

	return exitStatus;
}