#include<stdio.h>
#include"student.h"
#include"read_write.h"

int main(){

    int total=0;
    int req = 0;
    

    while(1){

    printf("What's your request?\n1. Search Data. \n 2. Insert Data.\n3. Delete Data.\n4. Save Data.\n5. Print Data.\n6. Sort Data.\n7. Aggregate Data.\n");
    scanf("%d",&req);

    Student *student=abstract(&total);
    Student *result=NULL;

    int ans=2;

    // Search Module
    if(req == 1){
        printf("What's your specific request?\n 1. Search by ID.\n2. Search by Name.\n3. Search by Score.");
        scanf("%d", &req);
        if(req == 1) ans=searchById(student, total, result) ;
        else if(req == 2) ans=searchByName(student, total, result) ;
        else    ans=earchByScore(student, total, result);
    }
    // Insert Module
    else if(req == 2) {
        Student item;

        printf("Please type in the ID,name,score of the new student.\n");
        char *p, *n;
        int s;
        scanf("The ID: %s\n", p);
        scanf("The name: %s\n", n);
        scanf("The score: %d\n", &s);

        insertStudent(student, &total, item);
    
    }

    // Delete Module
    else if(req == 3){}

    // Save Module
    else if(req==4){}


    // Print Model
    else if(req==5){}

    // Sort Model
    else if(req==6){
        printf("What's your specific request? \n1. Sort by score.\n2. Sort by ID.");
        scanf("%d",&req);
        if (req == 1) sortByScore(student,total,result);

    }

    // Aggregate Model
    else if(req==7){}

    if(ans == 0) printf("Operation Unsuccessful!😭\n"); 
    else if(ans == 1 || ans ==2) printf("Operation Successful!😄\n");
    else if (ans == -1) printf("Storage Maximal!\nPlease verify the server.⬆️\n");

    if(result) _writeIn(total, result);


    
    }

}




