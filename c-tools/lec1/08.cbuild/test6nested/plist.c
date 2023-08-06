#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "plist.h"


plist empty_plist( void )
{
	plist p = malloc( sizeof(struct plist) );
	assert( p != NULL );
	p->np = 0;
	return p;
}


void add_person( plist p, person one )
{
	assert( p->np < MAXPEOPLE );
	p->arr[ p->np++ ] = one;
}


void show_plist( FILE *out, plist p )
{
	int n = p->np;
	for( int i=0; i<n; i++ )
	{
		show_person( out, p->arr[i] );
	}
}
