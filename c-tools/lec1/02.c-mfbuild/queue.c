/* queue.c:		a queue of strings				*/
/*			(enque at the end, and deque from the front..	*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "queue.h"

/* Is a queue empty? */
bool queue_empty( queue pqueue )
{
	return pqueue == NULL;
}

/* Is a given string in a queue? */
bool in_queue( queue pqueue, char *s )
{
	queue pnode;
	
	for( pnode = pqueue; pnode != NULL; pnode = pnode->next )
	{
		if( strcmp(pnode->string, s) == 0 ) return TRUE;
	}	
	return FALSE;
}

/* Print a queue of strings in a file */
void print_queue( queue pqueue, FILE *out )
{
	queue pnode;
	
	for( pnode = pqueue; pnode != NULL; pnode = pnode->next)
	{
		fprintf( out, " %s", pnode->string);
	}	
}

/* Create a new empty queue */
queue new_queue( void )
{
	return NULL;
}

/* Attach a string to the tail of a queue */
queue enque( queue q, char *s )
{
	queue last;

	/* create a newnode */
	queue newnode = (queue) malloc( sizeof(struct qnode) );
	assert( newnode != NULL );

	newnode->string = s;
	newnode->next = NULL;

	if( queue_empty(q) )
	{
		q = newnode;
	} else
	{
		/* find last node in queue */
		for( last = q; last->next != NULL; last = last->next)
			/*EMPTY*/;
		/* we are now at last node in queue */
		last->next = newnode;
	}

	return q;
}

/* Detach the string at the head of a queue, modifying the queue */
char *deque( queue *qp )
{
	queue q = *qp;
	queue pjunknode;
	char *retval;

	assert( ! queue_empty(q) );

	pjunknode = q;
	retval = q->string;
	q = q->next;
	free(pjunknode);
	*qp = q;

	return retval;
}

/* Free the whole queue */
void free_queue( queue q )
{
	while( q != NULL )
	{
		queue tmp = q;
		free( q->string );
		q = q->next;
		free( tmp );
	}	
}

/* Nondestructive "give me the head of q", Abort if q is empty */
char *head( queue q )
{
	assert( ! queue_empty(q) );
	return q->string;
}

/* Nondestructive "give me the tail of q". Abort if q is empty */
queue tail( queue q )
{
	assert( ! queue_empty(q) );
	return q->next;
}
