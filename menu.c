#include<stdio.h>
#include"head file/student.h"
#include"head file/read_write.h"

int main(){

    int total=0;
    int req = 0;
    

    while(1){

    printf("What's your request?\n1. Search Data. \n2. Insert Data.\n3. Delete Data.\n4. Print Data.\n5. Sort Data.\n");
    scanf("%d",&req);

    Student student[MAX_STUDENTS];
    _abstract(&total, student);
    Student result[MAX_STUDENTS];

    // Search Module
    if(req == 1){
        int ans;

        int n=0;
        printf("What's your specific request?\n1. Search by ID.\n2. Search by Name.\n3. Search by Score.\n");
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
                printf("(ID:%s Name:%s Score:%.2f)\n", result[i].id, result[i].name,result[i].score);
        }
        
    }
    // Insert Module
    else if(req == 2) {
        Student item;

        printf("Please type in the ID,name,score of the new student.\n");
  
        scanf("%s%s%lf", item.id, item.name, &item.score);

        insertStudent(student, &total, item);
    
    }

    // Delete Module
    else if(req == 3){}


    // Print Model
    else if(req==4)out(total,student);

    // Sort Model
    else if(req==5){
        printf("What's your specific request? \n1. Sort by score.\n2. Sort by ID.\n");
        scanf("%d",&req);
        if (req == 1) sortByScore(student, total, result);

    }



    printf("Do you want to continue?(Y/N)");
    char cont;
    scanf(" %c", &cont);
    if(cont == 'N' || cont == 'n') break;
    }
    printf("Goodbye!✋️");
    return 0;

}




