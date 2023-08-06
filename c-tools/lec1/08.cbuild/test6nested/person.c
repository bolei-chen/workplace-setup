#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "person.h"


person new_person( int age, char *f, char *s )
{
	person p = malloc( sizeof(struct person) );
	assert( p != NULL );
	p->age = age;
	assert( strlen(f) < NAMELEN );
	assert( strlen(s) < NAMELEN );
	strcpy( p->forenames, f );
	capitalise( p->forenames );
	strcpy( p->surname, s );
	capitalise( p->surname );
	return p;
}


void show_person( FILE *out, person p )
{
	fprintf( out, "person: name=%s %s, age %d\n", p->forenames, p->surname, p->age );
}
