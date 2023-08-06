// plist.h requires name.h
// plist.h requires person.h

#define MAXPEOPLE	32
struct plist
{
	person arr[MAXPEOPLE];
	int np;
};
typedef struct plist *plist;

extern plist empty_plist( void );
extern void add_person( plist p, person one );
extern void show_plist( FILE * out, plist p );
