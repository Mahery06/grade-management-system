
#define ID_LENGTH 20
#define NAME_LENGTH 40
#define MAX_STUDENTS 200

typedef struct
{
    char id[ID_LENGTH];
    char name[NAME_LENGTH];
    double score;
} Student;


// Search Module
int searchById(Student stu[],
    int n,
    Student result[]);

int searchByName(Student stu[],
    int n,
    Student result[]);

int searchByScore(Student stu[],
    int n,
    Student result[]);

// Insert Module
int insertStudent(
    Student students[],
    int *count,
    Student item);


// Delete Module
int deleteStudent(
    Student students[],
    int *count,
    const char *id);


// Save Module



// Print Model


// Sort Model

void sortByScore(
    const Student students[],
    int count,
    Student sorted[]);

// Aggregate Model




