#define MAX_STUDENTS 200
#define ID_LENGTH 20
#define NAME_LENGTH 40

typedef struct
{
    char id[ID_LENGTH];
    char name[NAME_LENGTH];
    double score;
} Student;

Student *_abstract(int *);
void _writeIn(int total, Student *result);
