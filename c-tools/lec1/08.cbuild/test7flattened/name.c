#include <ctype.h>

#include "name.h"


void capitalise( char *s )
{
	for( char *p=s; *p; p++ )
	{
		*p = toupper(*p);
	}
}
