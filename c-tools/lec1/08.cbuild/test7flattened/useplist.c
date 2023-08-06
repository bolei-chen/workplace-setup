#include <stdio.h>

#include "name.h"
#include "person.h"
#include "plist.h"


int main( void )
{
	plist l = empty_plist();
	add_person( l, new_person( 56, "Duncan", "White" ) );
	add_person( l, new_person( 42, "Will", "Knottenbelt" ) );
	show_plist( stdout, l );

	return 0;
}
