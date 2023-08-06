#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "queue.h"

#define MAXLINLEN 256

#define MAKEFILENAME		"Makefile"
#define PERSDEFSFILENAME	"mfbuilddefs"
#define THISPROGNAME		"mfbuild"

#define MAIN_C_FILE_MISSING	 1
#define FILE_OPENING_REFUSED	 3
#define STRING_SPACE_REFUSED	 5

queue todos;
queue dones;
queue nocs;

/* Create a copy, in memory, of a given string.  Return a pointer to the copy.	*/
char *copy_str_mem (char *pgivstring)
{
	char *pmemstring = strdup(pgivstring);
	if( pmemstring == NULL )
		exit( STRING_SPACE_REFUSED );

	/* memory chunk is now initialised */
	return pmemstring;
}

/* Check whether or not a file exists.			*/
/* Return TRUE if it does, FALSE if it does not.	*/
bool file_exists( char *pfilename )
{
	FILE *infile;

	infile = fopen( pfilename, "r" );
	if( infile != NULL )
	{
		fclose( infile );
	}
	return infile != NULL;
}

/* Copy the contents of one file to another. */
void copy_file( char *pinfilename, FILE *outfile )
{
	FILE *infile;
	int c;

	infile = fopen( pinfilename, "r" );
	if( infile == NULL )
	{
		fprintf( stderr, "File '%s' not found.  ", pinfilename);
		fprintf( stderr, "We will continue without it.\n");
	}
	else
	{
		/* Read the input file character-by-character */
		while( (c = fgetc(infile)) != EOF )
		{
			/* and write it to the output file */
			fputc(c, outfile);
		}
		fclose (infile);
	}
}

/* Convert file name strings in queue to .o. */
void convert_queue_to_dot_o( queue conqueue )
{
	char *pfilename;
	int fnlen;

	#if 0
	/* attach marker to tail of queue */
	conqueue = enque( conqueue, "marker" );

	/* detach next file name from head of queue */
	pfilename = deque( &conqueue );

	while( strcmp(pfilename, "marker") != 0 )	/* marker not reached yet */
	{
		/* change file name ending to .o */
		fnlen = strlen(pfilename);
		pfilename[fnlen-1] = 'o';

		/* attach file name to tail of queue */
		conqueue = enque( conqueue, pfilename );

		/* detach next file name from head of queue */
		pfilename = deque( &conqueue );
	}
	#else
	while( ! queue_empty(conqueue) )
	{
		pfilename = head(conqueue);
		conqueue = tail(conqueue);

		/* change file name ending to .o */
		fnlen = strlen(pfilename);
		pfilename[fnlen-1] = 'o';
	}
	#endif
}

/* Check whether or not we have a #include "________.h" line.
 * If we do then return pointer to name of .h file within it.
 * If we do NOT then return NULL.
 */
char *look_at_line( char *pfileline )
{
	char *o, *p, *q, *r;

	/* copy original file line string to memory to save it for use later */
	o = copy_str_mem( pfileline );

	/* now tidy up the original! */
	p = pfileline;
	for( q = pfileline; *q != '\0'; q++ )
	{
		if( ! isspace(*q) )		/* char is NOT space */
		{
			*p++ = *q;
		}
	}
	*p = '\0';

	/* spaces now eliminated from line */
	p = pfileline;
	q = pfileline;
	p = strstr( pfileline, "/*" );
	if( p != NULL )					/* aha! a comment */
	{
		/* p now points to start of comment */
		q = strstr( pfileline, "*/" );
		if( q != NULL )				/* comment end found */
		{
			q++;
			/* q now points to end of comment */
			q++;
			while( *q != '\0' )
			{
				*p++ = *q++;
			}
		}
		*p = '\0';
	}

	/* any comment is now eliminated from line */
	p = strstr( pfileline, "#include\"" );
	if( p == NULL )			       /* #include" line NOT found */
	{
		r = p;
	}
	else					/* #include" line found */
	{
		p += 9;

		/* p now points to start of filename */
		q = strstr( p, ".h" );
		if( q == NULL )				/* .h NOT found */
		{
			q = strchr(p, '"');
			if( q != NULL )			/* " found */
				*q = '\0';
			fprintf (stderr,
				 "%s: Invalid include line '%s'\n",
				 THISPROGNAME, o);
			r = (char *) NULL;
		}
		else					/* .h found */
		{
			q += 2;
			*q = '\0';

			/* p now points to .h filename in string form */
			r = p;
		}
	}

	free(o);
	return r;
}

/* queue all the includes found in a given .c file.
 * Return the include queue created.
 */
queue find_includes( char *pcfilename )
{
	FILE *infile;
	char inputline[MAXLINLEN];
	char *pincfilename, *pmemfilename;
	int lcv;

	queue includes = new_queue();			/* start include queue */

	infile = fopen( pcfilename, "r" );		/* open .c file */
	if( infile == NULL )
		exit( FILE_OPENING_REFUSED );		/* cannot proceed */

	for( lcv = 0; fgets(inputline, MAXLINLEN-1, infile) != NULL; lcv++ )
	{
		/* chop off newline at end.. */
		inputline[strlen(inputline)-1] = '\0';

		/* we have a line to check */
		pincfilename = look_at_line( inputline );  /* does it #include "__.h"? */
		if( pincfilename != NULL )		/* yes, it does! */
		{
			/* N.B. pincfilename points to .h file name
			 * string in inputline
			 */

			/* copy .h file name string to memory and attach copy
			 * to tail of include queue
			 */
			pmemfilename = copy_str_mem( pincfilename );
			includes = enque( includes, pmemfilename );
		}
	}
	fclose( infile );

	return includes;
}

/* Write a makefile dependency line in a file. */
void print_makeline( char *pcfilename, queue includes, FILE *outfile )
{
	int cfnlen;

	/* write '.o' line to makefile */
	cfnlen = strlen(pcfilename);
	fprintf( outfile, "\n%.*s.o:", cfnlen-2, pcfilename );/* .o filename */
	fprintf( outfile, "\t%s", pcfilename );
	print_queue( includes, outfile );
	fprintf( outfile, "\n" );
	fflush( outfile );
}

/*
 * Extract name of main .c file from a given argument and add it to to do queue.
 * Return a pointer to the main .c file name.
 */
char *get_main( char *parg )
{
	int arglen;
	char *pmainfilename;
	char *pcfilename;
	int lcv;

	arglen = strlen(parg);

	if( parg[arglen-2] == '.'
	&&  parg[arglen-1] == 'c' )		 /* main file name ends '.c' */
	{
		/* copy main .c file name string to memory */
		pmainfilename = copy_str_mem(parg);
	}
	else				      /* main file name omits '.c' */
	{
		/* create a copy, in memory, of main .c file name	*/
		/* with omitted '.c' restored				*/
		pmainfilename = (char *) malloc(arglen+3);
		if( pmainfilename == NULL )
			exit( STRING_SPACE_REFUSED );	/* cannot proceed */

		/* memory chunk is supplied UNinitialised */
		for( lcv = 0; lcv < arglen; lcv++ )
			pmainfilename[lcv] = parg[lcv];/* copy string */
		pmainfilename[arglen]   = '.';	/* add .c to name */
		pmainfilename[arglen+1] = 'c';
		pmainfilename[arglen+2] = '\0';

		/* memory chunk is now initialised */
	}

	if( ! file_exists(pmainfilename) )	/* main .c file NOT found */
	{
		fprintf( stderr,
			 "%s: file '%s' not found.\n",
			 THISPROGNAME, pmainfilename );	/* warn user */
		exit( MAIN_C_FILE_MISSING );		/* cannot proceed */
	}

	/* copy main .c file name string to memory and attach copy to	*/
	/* tail of to do queue						*/
	pcfilename = copy_str_mem( pmainfilename );
	todos = enque( todos, pcfilename );

	return pmainfilename;
}

/*
 * Dismantle include queue, convert filenames from .h to .c and add any that
 * are not yet in the to do, done or no .c queues to the to do queue.  Finally,
 * kill off include queue.
 */
void kill_includes_extend_todos( char *pcfilename, queue includes )
{
	char *pincfilename;
	int ifnlen;

	while ( ! queue_empty(includes) )		/* more in include queue */
	{
		/* detach next file name from head of include queue */
		pincfilename = deque(&includes );

		/* change file name ending from .h to .c */
		ifnlen = strlen(pincfilename);
		pincfilename[ifnlen-1] = 'c';

/* ---------------- text block moved left to keep it on page ! ------------------- */
if( !in_queue (todos, pincfilename) 			/* not in to do queue */
&&  !in_queue (dones, pincfilename) 			/* not in done queue */
&&  !in_queue (nocs, pincfilename) 			/* not in no .c queue */
&&  strcmp(pcfilename, pincfilename) != 0)		/* not this .c file */
/* ------------------------------------------------------------------------------- */
		{
			/* attach .c file name to tail of to do queue */
			todos = enque( todos, pincfilename );
		}
		else
		{
			free( pincfilename );
		}
	}

	/* queue is now empty */
	if( queue_empty(includes) )
	{
		free(includes);
	}
}

/* ------------------------------------------------------------------------- */
/* argv[1] points to 'main' .c file name */
int main( int argc, char **argv )
{
	queue includes;
	char *pmainfilename;
	char *pcfilename;
	int  mfnlen;
	FILE *output;

	if( argc == 1 || argc > 2 )
	{
		fprintf( stderr,
			 "Usage: %s: program_name (or main .c file name).\n",
			 THISPROGNAME);
		exit(2);
	}

	/* now for the real work */

	output = fopen( MAKEFILENAME, "w" );		/* start makefile */
	if( output == NULL )
		exit( FILE_OPENING_REFUSED );		/* cannot proceed */

	todos = new_queue();				/* start to do queue */
	dones = new_queue();				/* start done queue */
	nocs = new_queue();				/* start no .c queue */

	/* copy defsfile to makefile */
	if( file_exists(PERSDEFSFILENAME) )	       /* personal defs file found */
	{
		copy_file( PERSDEFSFILENAME, output);
	}
	else if( file_exists(LIBRDEFSFILENAME) )	/* library defs file found */
	{
		copy_file( LIBRDEFSFILENAME, output );
	}

	/* argv[1] points to main .c file name */
	/* obtain main .c file name from argument and add it to to do queue */
	pmainfilename = get_main( argv[1] );

	/* write 'BUILD' line to makefile */
	mfnlen = strlen( pmainfilename );
	fprintf( output,
		 "BUILD\t=\t%.*s\n", mfnlen-2,
		 pmainfilename);

	/* write 'all' line to makefile */
	fprintf( output, "\nall:\t$(BUILD)\n" );

	/* write 'clean' line to makefile */
	fprintf( output,
		 "\nclean:\n\t/bin/rm -f $(BUILD) *.o core a.out .nfs*\n");


	while( ! queue_empty(todos) )		/* more to do */
	{
		/* detach next .c file name from head of to do queue */
		pcfilename = deque( &todos );

		if( file_exists(pcfilename) )		/* .c file found */
		{
			includes = find_includes( pcfilename );
			print_makeline( pcfilename, includes, output );
			kill_includes_extend_todos( pcfilename, includes );

			/* add .c file name to tail of done queue */
			dones = enque( dones, pcfilename );
		}
		else					/* .c file NOT found */
		{
			/* add .c file name to tail of no-.c queue */
			nocs = enque( nocs, pcfilename );
		}
	}

	/* to do queue is now empty, so kill it */
	free_queue( todos );

	/* convert file names in done queue from .c to .o */
	convert_queue_to_dot_o( dones );

	/* write 'OBJS' line to makefile */
	fprintf( output, "\nOBJS\t=\t" );
	print_queue( dones, output );
	fprintf( output, "\n" );

	free_queue( dones );

	free_queue( nocs );

	/* write 'prog' line to makefile */
	fprintf( output,
		"\n%.*s:\t\t$(OBJS)\n\t$(CC) $(OBJS) -o %.*s $(LDFLAGS)\n",
		 mfnlen-2, pmainfilename, mfnlen-2, pmainfilename);

	free( pmainfilename );

	fclose( output );				/* end of main */
	return 0;
}
