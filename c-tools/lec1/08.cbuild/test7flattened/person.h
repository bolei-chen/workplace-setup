// person.h requires name.h

struct person
{
	int age;
	name forenames;
	name surname;
};
typedef struct person *person;

extern person new_person( int age, char * f, char * s );
extern void show_person( FILE * out, person p );
