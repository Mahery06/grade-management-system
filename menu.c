#include<stdio.h>
#include"head file/student.h"
#include"head file/read_write.h"

int main(){

    int total=0;
    int req = 0;
    

    while(1){

    printf("What's your request?\n1. Search Data. \n 2. Insert Data.\n3. Delete Data.\n4. Save Data.\n5. Print Data.\n6. Sort Data.\n7. Aggregate Data.\n");
    scanf("%d",&req);

    Student *student;
    _abstract(&total, student);
    Student *result;

    // Search Module
    if(req == 1){
        int ans;

        int n=0;
        printf("What's your specific request?\n 1. Search by ID.\n2. Search by Name.\n3. Search by Score.");
        scanf("%d", &req);
        if(req == 1) ans=searchById(student, total, &n, result) ;
        else if(req == 2) ans=searchByName(student, total,&n, result) ;
        else    ans=searchByScore(student, total,&n, result);

        if(ans == -1) printf("Operation Unsuccessful!😭\n"); 
        else    
        {
            printf("Operation Successful!😄\n");
            printf("The searched content shows below:\n");
            for(int i=0;i<n;i++)
                printf("(ID:%s Name:%s Score:%d)\n", result[i].id, result[i].name,result[i].score);
        }
        
    }
    // Insert Module
    else if(req == 2) {
        Student item;

        printf("Please type in the ID,name,score of the new student.\n");
  
        scanf("%s%s%d", item.id, item.name, &item.score);

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
        if (req == 1) sortByScore(student, total, result);

    }

    // Aggregate Model
    else if(req==7){}


    printf("Do you want to continue?(Y/N)");
    req=scanf("%c");
    if(req == 'N') break;
    }
    printf("Goodbye!✋️");
    return 0;

}




