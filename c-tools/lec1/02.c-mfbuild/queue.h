/* queue.h:		a queue of strings				*/
/*			(enque at the end, and deque from the front..	*/


typedef enum {FALSE, TRUE} bool;


struct qnode;
typedef struct qnode *queue;
struct qnode {
		char *string;			
		queue next;
	    };

	
extern bool queue_empty( queue q );
/*	Is the queue q empty?  
	Returns TRUE if it is empty, FALSE otherwise.			*/


extern bool in_queue( queue q, char *s );
/*	Is a given string s in the queue q?  
	Returns TRUE if string is present, FALSE otherwise.		*/


extern void print_queue( queue q, FILE *stream );
/*	Writes the queue q of strings as output to stream.		*/


extern queue new_queue( void );
/*	Creates a new empty queue.					*/


extern queue enque( queue q, char *s );
/*	Attach a new string s to the tail of the queue q.  
	Returns new queue if successful.  
	Aborts if the request cannot be satisfied.			*/


extern char *deque( queue *pq );
/*	Detach the string at the head of the queue pointed to by pq.
	Returns the detached string.  
	Aborts if the queue is already empty.				*/


extern void free_queue( queue q );
/*	Free a queue							*/

extern char *head( queue q );
/*	Nondestructive "give me the head of q", Abort if q is empty     */

extern queue tail( queue q );
/*	Nondestructive "give me the tail of q". Abort if q is empty	*/
