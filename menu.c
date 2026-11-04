#include<stdio.h>
#include"head file/student.h"
#include"head file/read_write.h"
#include"head file/login.h"

int main(){

    int total=0;
    int req = 0;
    

    while(1){
    printf("========== Welcome to grade management system!! ==========\n ");
    printf("What's your request?\n1. Search Data. \n2. Insert Data.\n3. Delete Data.\n4. Print Data.\n5. Sort Data.\n6. Aggregate Data.\n7. Modify Data.\n");
    printf("Input:");
    scanf("%d",&req);

    Student student[MAX_STUDENTS];
    _abstract(&total, student);
    Student result[MAX_STUDENTS];

    if((req == 2 || req == 3 || req == 5 || req == 6) && !canModify()){
        printf("Insufficient permissions: regular users can only query; add and delete operations are available only to administrators.\n");
    }
    // Search Module
    else if(req == 1){
        int ans;

        int n=0;
        printf("What's your specific request?\n1. Search by ID.\n2. Search by Name.\n3. Search by Score.\n");
        scanf("%d", &req);
        if(req == 1) ans=searchById(student, total, &n, result) ;
        else if(req == 2) ans=searchByName(student, total,&n, result) ;
        else ans=searchByScore(student, total,&n, result);

        if(ans == -1) printf("Operation Unsuccessful!😭\n"); 
        else    
        {
            printf("Operation Successful!😄\n\n");
            printf("The searched content shows below:\n");
            for(int i=0;i<n;i++)
                printf("(ID:%s Name:%s Score:%.2f)\n", result[i].id, result[i].name, result[i].score);

            printf("Do you need pieces of AI tailored report?(Y/N):");
            char wantReport;
            scanf(" %c", &wantReport);
            if(wantReport == 'Y' || wantReport == 'y') tailored_report(result, n);
        }
        
    }
    // Insert Module
    else if(req == 2) {
        Student item;

        printf("Please type in the ID,name,score of the new student.(seperate with space)\n");
        printf("Input:");
        scanf("%s%s%lf", item.id, item.name, &item.score);

        insertStudent(student, &total, item);
    
    }

    // Delete Module
    else if(req == 3){ int ans = deleteStudent(student, &total);
            if (ans == 1)
            {
                printf("Operation Successful!😄\n");
                _writeIn(total, student);
            }
            else
                printf("Operation Unsuccessful!😭\n");}


    // Print Module
    else if(req==4)out(total,student);

    // Sort Module
    else if(req==5){
        printf("What's your specific request? \n1. Sort by score.\n2. Sort by ID.\n");
        printf("Input:");
        scanf("%d",&req);
        if (req == 1) sortByScore(student, total, result);
        else if (req == 2)
                sortById(student, total, result);
        else
            {
                printf("Invalid option.\n");
                continue;
            }
            out(total, result);
        }

    // Aggregate Module
    else if (req == 6) aggregate(total, student);
    
    else if (req == 7) {
        
        int ans = modify(total, student);
        if (ans) printf("修改成功！\n");
        else printf("修改失败~\n");
    }
    printf("您需要继续操作吗？(Y/N):");
    char cont;
    scanf(" %c", &cont);
    if(cont == 'N' || cont == 'n') break;
    }

    printf("Goodbye!✋️");
    return 0;

}
