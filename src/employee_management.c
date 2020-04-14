#include<stdio.h>
#include<windows.h>
#include<mysql.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "..\include\Validation.h"
#include "..\include\employee_management.h"
#include "..\include\admin_attendance.h"
#include "..\include\employee.h"
#define MAX_YEAR 2020
#define MIN_YEAR 2010
#define MAX_MONTH 12
#define MIN_MONTH 1
MYSQL *conn2, *oo1,*oo3,*conn8;
char query[1500];

//start of update salary

char* update_salary(int emp_id)
{
    MYSQL_RES *read=NULL;
    MYSQL_ROW row=NULL;
    conn2 = mysql_init(NULL);
    char stmt[300];
    int sal_year;
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    sal_year = local->tm_year + 1900;
    mysql_real_connect(conn2, "localhost", "root", "1234","payroll", 3306, NULL, 0);
    if(!conn2)
    {
        return "Connection error";
    }
    else
        
    {
        int option;
        int salary;
        printf("To increment the salary of employee press 1. \nTo make changes to calculated salary press 2\n");
        scanf("%d",&option);
        if(option==1)
        {
            char qry1[]={"select salary_type from salary where emp_id=%d and sal_year='%d'"};
            sprintf(stmt,qry1,emp_id,sal_year);
            if (mysql_query(conn2,stmt))
            {
                printf("		Error: %s\n", mysql_error(conn2));
                return ("		Failed to execute query.");
            }
            else
            {
                read = mysql_store_result(conn2);
                row = mysql_fetch_row(read);
                if(row==NULL)
                {
                    return("		No data found for this id\n");
                    
                }
                if(strcasecmp(row[0],"salaried")==0)
                {
                    printf("%d is a salaried employee, enter salary per cheque i.e. half month salary\n ",emp_id);
                }
                else if(strcasecmp(row[0],"hourly")==0)
                {
                    printf("%d is a hourly employee, enter  per hour salary\n ",emp_id);
                }
                scanf("%d",&salary);
                char qry2[]={"update salary set salary='%d' where emp_id='%d' and sal_year='%d'"};
                sprintf(stmt,qry2,salary,emp_id,sal_year);
                
                if (mysql_query(conn2,stmt))
                {
                    printf("		Error: %s\n", mysql_error(conn8));
                    return ("		Failed to execute query.");
                }
                
                else
                {
                    return ("\n\n Salary updated. \n");
                }
                
            }
            
            
        }
        else if(option==2)
        {
            int year,month,week;
            int x=0;
            do{
                printf("Enter the  year you wish to update: \n");
                scanf("%d",&year);
                if(year<=MAX_YEAR && year>=MIN_YEAR)
                {
                    x=1;
                }
                else{
                    printf("INVALID year, enter again\n");
                }
            }while(x==0);
            x=0;
            do{
                printf("Enter the month you wish to update: \n");
                scanf("%d",&month);
                if(month<=MAX_MONTH && month>=MIN_MONTH)
                {
                    x=1;
                }
                else{
                    printf("INVALID month, enter again\n");
                }
            }while(x==0);
            x=0;
            do{
                printf("Enter the pay week you wish to update :\n Select 1 for first half of month \n Select 2 for second half of month\n");
                scanf("%d",&week);
                if(week==1 || week==2)
                {
                    x=1;
                }
                else{
                    printf("INVALID week, enter again\n");
                }
            }while(x==0);
            
            printf("Enter salary you wish to update\n");
            scanf("%d",&salary);
            char qry[200];
            char qry2[]={"select salary_type from salary_cal where emp_id='%d' and year='%d'and month='%d'and week ='%d'"};
            sprintf(stmt,qry2,emp_id,year,month,week);
            if (mysql_query(conn2,stmt))
            {
                printf("		Error: %s\n", mysql_error(conn2));
                return ("		Failed to execute query.");
            }
            else
            {
                read = mysql_store_result(conn2);
                row = mysql_fetch_row(read);
                if(row==NULL)
                {
                    return("	No data found to update\n");
                    
                }
                
                strcpy(qry,"update salary_cal set calculated_salary='%d' where emp_id='%d' and year='%d'and month='%d'and week ='%d'");
                int n = sprintf(stmt,qry,salary,emp_id,year,month,week);
                if (mysql_query(conn2,stmt))
                {
                    printf("		Error: %s\n", mysql_error(conn2));
                    return ("		Failed to execute query.");
                }
                
                else
                {
                    return ("\n\n Salary updated. \n");
                }
            }
            
        }
        
        
        
    }
}
//End of update salary


void new_leave_detail()
{
    int t=0;
    MYSQL_RES *read=NULL;
    MYSQL_RES *res=NULL;
    MYSQL_ROW row=NULL;
    int paid_leave,med_leave;
    int emp_id,yr;
    char stmt[1500];
    do
    {
        t=0;
        printf("Enter the employee Id:\n");
        scanf("%d",&emp_id);
        char qry_id1[]={"select * from emp_details where emp_id=%d"};
        sprintf(stmt,qry_id1,emp_id);
        if (mysql_query(conn2,stmt))
        {
            printf(" Error: %s\n", mysql_error(conn2));
            printf("Failed to execute query.");
        }
        else
        {
            read = mysql_store_result(conn2);
            row = mysql_fetch_row(read);
            if(row==NULL)
            {
                printf("No Such Employee ID found\n");
                t=0;
            }
            else
            {
                t=1;
            }
        }
        
        
    }while(t!=1);
    
    do
    {
        t=0;
        printf("Enter the year for leaves\n");
        scanf("%d",&yr);
        if(yr>2000 &&yr<9999)
        {
            t=1;
        }
        else
        {
            t=0;
            printf("Wrong year\n");
        }
    }while(t!=1);
    char qry_id[]={"select * from leave_details where leave_year='%d' and emp_id=%d"};
    sprintf(stmt,qry_id,yr,emp_id);
    if (mysql_query(conn2,stmt))
    {
        printf(" Error: %s\n", mysql_error(conn2));
        printf("Failed to execute query.");
    }
    else
    {
        read = mysql_store_result(conn2);
        row = mysql_fetch_row(read);
        if(row==NULL)
        {
            printf("Enter the paid leaves\n");
            scanf("%d",&paid_leave);
            printf("Enter the medical leaves\n");
            scanf("%d",&med_leave);
            char leave_qry[]={"insert into leave_details (emp_id,medical_leave,paid_leave,leave_year,balance_ML,balance_PL) values('%d','%d','%d','%d','0','0')"};
            sprintf(stmt,leave_qry,emp_id,med_leave,paid_leave,yr);
            if (mysql_query(conn2,stmt))
            {
                printf(" Error: %s\n", mysql_error(conn2));
                printf("Failed to execute query.");
            }
            else
            {
                printf("Record entered successfully");
            }
            
        }
        else
        {
            printf("Leaves already have in the databas... do you want to update with new leaves");
        }
    }
    
    
    
}
//End add new leave  function


//view attendance requests
void employee_reuests()
{
    
    MYSQL_RES *read=NULL;
    MYSQL_RES *res=NULL;
    MYSQL_ROW row=NULL;
    int num,u;
    char stmt[1500];
    char qry_id[]={"select * from request_form where req_status='0'"};
    if (mysql_query(conn2,qry_id))
    {
        printf(" Error: %s\n", mysql_error(conn2));
        printf("Failed to execute query.");
    }
    else
    {
        int i=0;
        read = mysql_store_result(conn2);
        
        printf("\n--------------------------------------------------------------------------------\n");
        while(row = mysql_fetch_row(read))
        {
            num = mysql_num_fields(read);
            
            printf("|");
            for(i = 0; i < num; i++)
            {
                if(i==4)
                {
                    if(atoi(row[i])==0)
                    {
                        printf("-Request Pending-");
                    }
                    else if(atoi(row[i])==1)
                    {
                        printf("-Rejected-");
                    }
                    else if(atoi(row[i])==2)
                    {
                        printf("-Accepted-");
                    }
                    
                }
                else
                {
                    printf("%s|", row[i]);
                }
            }
            printf("\n--------------------------------------------------------------------------------\n");
        }
        printf("\n");
        int st,ch,st1;
        printf("Press 1 to update the status of an employee\n");
        printf("Press 2 to exit\n");
        scanf("%d",&st);
        if(st==1)
        {
            do
            {
                int req_id;
                printf("Enter the request id to process\n");
                scanf("%d",&req_id);
                printf("Press 1 to Reject\n");
                printf("Press 2 to Accept\n");
                scanf("%d",&st1);
                
                if(st1==1)
                {
                    
                    char qry[]={"update request_form set req_status='%d' where req_id='%d'"};
                    sprintf(stmt,qry,st1,req_id);
                    //printf("%s",stmt);
                    if(mysql_query(conn2,stmt))
                    {
                        printf("\n Database error please cotact to administrator");
                    }
                    else
                    {
                        printf("\n Request has processed");
                    }
                    
                }
                else if(st1==2)
                {
                    char qry[]={"update request_form set req_status='%d' where req_id='%d';"};
                    sprintf(stmt,qry,2,req_id);
                    if(mysql_query(conn2,stmt))
                    {
                        printf("\n Database error please contact to administrator");
                    }
                    else
                    {
                        printf("\n Request has processed");
                    }
                }
                else
                {
                    printf("You cannot update the status of request with this value");
                }
                printf("\nDo you want to continue? Press 1 to continue else press any key");
                
                scanf("%d",&u);
            }while(u==1);
        }
        else if(st==2)
        {
            printf("thanx");
        }
        else
        {
            printf("wrong choice");
        }
    }
}



//start of  adding a new employee
char* add_employee(char dept[],char desig[],int check, int request_id)
{
    MYSQL_RES *read=NULL;
    MYSQL_RES *res=NULL;
    MYSQL_ROW row=NULL;
    struct employee
    {
        int id;
        char f_name[50];
        char l_name[50];
        char dep[50];
        char des[50];
        int age;
        char address1[45];
        char address2[45];
        char phonenumber[20];
        char gender[10];
        char email[100];
        char status[100];
        int day;
        int month;
        int year;
    };
    struct employee emp;
    int x=0;
    char ch;
    int num;
    getchar();
    do{
        printf("Enter the first name of employee\n");
        gets(emp.f_name);
        x=notempty(emp.f_name);
    }while(x==0);
    x=0;
    do{
        printf("Enter the Last name of employee\n");
        gets(emp.l_name);
        x=notempty(emp.l_name);
    }while(x==0);
    x=0;
    
    if(check==1){
        strcpy(emp.dep,dept);
        strcpy(emp.des,desig);
    }
    else{
        do{
            printf("Enter the department of employee\n");
            gets(emp.dep);
            x=notempty(emp.dep);
        }while(x==0);
        x=0;
        
        do{
            printf("Enter the designation of employee\n");
            gets(emp.des);
            x=notempty(emp.des);
        }while(x==0);
        x=0;
    }
    
    printf("Enter the age of employee\n");
    scanf("%d",&emp.age);
    getchar();
    do{
        printf("Enter house/apartment number and street\n");
        gets(emp.address1);
        x=notempty(emp.address1);
    }while(x==0);
    x=0;
    
    do{
        printf("\nEnter city and country\n");
        gets(emp.address2);
        x=notempty(emp.address2);
    }while(x==0);
    x=0;
    do{
        printf("\nEnter gender Male , Female or Others\n");
        scanf("%s",emp.gender);
        if (strcasecmp(emp.gender,"Male")==0 || strcasecmp(emp.gender,"Female")==0 || strcasecmp(emp.gender,"Female")==0)
        {
            x=1;
            break;
        }
    } while(x==0);
    x=0;
    do
    {
        printf("Enter email\n");
        scanf("%s",emp.email);
        x=valid_email(emp.email);
    }while(x==0);
    x=0;
    do{
        printf("Enter employement status(A for active or I for inactive)\n");
        scanf("%s",emp.status);
        if (strcasecmp(emp.status,"A")==0 || strcasecmp(emp.status,"I")==0)
        {
            x=1;
            break;
        }
    } while(x==0);
    x=0;
    do{
        printf("Enter Phone number\n");
        scanf("%s",emp.phonenumber);
        x=valid_phone(emp.phonenumber);
    } while(x==0);
    x=0;
    do{
        printf("Enter the date of joining\n");
        printf("   Enter day of joining\n");
        scanf("%d",&emp.day);
        printf("   Enter month of joining\n");
        scanf("%d",&emp.month);
        printf("   Enter year of joining\n");
        scanf("%d",&emp.year);
        x=datevalid(emp.day,emp.month,emp.year);
    } while(x==0);
    char stmt[1500];
    conn8=mysql_init(NULL);
    mysql_real_connect(conn8, "localhost", "root", "1234","payroll", 3305, NULL, 0);
    char qry[]={"insert into emp_details (name1,name2,department,designation,age,address_l1,address_l2,phonen,gender,email,day,month,year,emp_type) VALUES('%s','%s','%s','%s','%d','%s','%s','%s','%s','%s','%d','%d','%d','%s')"};
    if(conn8)
    {
        sprintf(stmt,qry,emp.f_name,emp.l_name,emp.dep,emp.des,emp.age,emp.address1,emp.address2,emp.phonenumber,emp.gender,emp.email,emp.day,emp.month,emp.year,emp.status);
        if (mysql_query(conn8,stmt))
        {
            printf(" Error: %s\n", mysql_error(conn8));
            return "Failed to execute query.";
        }
        else
        {
            printf( "\n\n\nuser details added successfully\n\n\n\n\n");
            
        }
    }
    
    else
    {
        printf("not connected");
        printf("%s\n", mysql_error(conn8));
        
    }
    int emp_id;
    char qry2[]={"select max(emp_id) as id from emp_details"};
    if(conn8)
    {
        
        int n=sprintf(stmt,qry2);
        mysql_query(conn8,stmt);
        read = mysql_store_result(conn8);
        if (mysql_query(conn8,stmt))
        {
            printf(" Error: %s\n", mysql_error(conn8));
            printf("Failed to execute query.");
        }
        
        else
        {
            int i=0;
            row = mysql_fetch_row(read);
            emp_id=atoi(row[0]);
            printf("%d\n",emp_id);
            mysql_free_result(read);
            
        }
        
        
    }
    else
    {
        printf("not connected");
        printf("%s\n", mysql_error(conn8));
        
    }
    
    oo1=mysql_init(NULL);
    mysql_real_connect(oo1, "localhost", "root", "1234","payroll", 3305, NULL, 0);
    char password []="1234";
    char employee_type[30];
    printf("Enter the employee type -Admin,Employee or Manager\n");
    scanf("%s",employee_type);
    char qry3[]={"insert into login_details (emp_id,password,emp_type,status) VALUES('%d','%s','%s','%s')"};
    if(oo1)
    {
        
        sprintf(stmt,qry3,emp_id,password,employee_type,emp.status);
        if (mysql_query(oo1,stmt))
        {
            printf(" Error: %s\n", mysql_error(oo1));
            return "Failed to execute query.";
            
        }
        else
        {
            
            if(check=1)
            {
                
                oo3=mysql_init(NULL);
                mysql_real_connect(oo3, "localhost", "root", "1234","payroll", 3305, NULL, 0);
                char request_status[]="Completed";
                char qry_update_request_status[]={"update employee_request set request_status='%s' where request_id='%d'"};
                if(oo3){
                    sprintf(stmt,qry_update_request_status,request_status,request_id);
                    if (mysql_query(oo3,stmt)){
                        printf(" Error: %s\n", mysql_error(oo3));
                        return "Failed to execute query.";
                    }
                    else{
                        printf("Status updated successfully");
                    }
                }
                else{
                    printf("not connected");
                    printf("%s\n", mysql_error(oo3));
                }
            }
            return "\n\n\nUser added successfully\n\n\n\n\n";
        }
    }
    
    else
    {
        printf("not connected");
        printf("%s\n", mysql_error(oo1));
    }
}

/* De-activating employee*/
void deactivate (int emp_id, int login_id){
    MYSQL_RES *read=NULL;
    MYSQL_RES *res=NULL;
    MYSQL_ROW row=NULL;
    char status[20]="0" ;
    snprintf(query,1500,"select emp_id,status FROM login_details where emp_id = '%d'",emp_id) ;
    /* send SQL query */
    if (mysql_query(conn2, query)){
        printf("Failed to execute query. Error: %s\n", mysql_error(conn2));
    }
    else{
        res = mysql_store_result(conn2);
        row = mysql_fetch_row(res);
        if (row == NULL){
            printf("Username Not Found");
        }
        else{
            //strcpy(status,row[0]);
            
            if(strcmp("A",row[1])){
                printf("Already deactivated");
            }
            else{
                if(atoi(row[0])!=login_id){
                    int dd,mm,yy;
                    int r;
                    do
                    {
                        printf("\nEnter the date of leave of an employee:Format(dd/mm/yyyy)");
                        scanf("%d/%d/%d",&dd,&mm,&yy);
                        r=validate_date(dd,mm,yy);
                    }while(r!=1);
                    char date[15];
                    sprintf(date,"%d/%d/%d", dd,mm,yy);
                    char qry[]="update  login_details set status='I', DOL='%s' where emp_id='%d'";
                    sprintf(query,qry,date,emp_id);
                    if (mysql_query(conn2, query)){
                        printf("Failed to execute query. Error: %s\n", mysql_error(conn2));
                    }
                    else{
                        printf("User Successfully deactivated");
                    }
                }
                else{
                    printf("Sorry! You can not deactivate the logged in account");
                }
            }
        }
    }
}
/*End de-activating employee function*/




//Start of displaying employee detail
void emp_display_details(char stmt[]){
    MYSQL_RES *read=NULL;
    MYSQL_RES *res=NULL;
    MYSQL_ROW row=NULL;
    MYSQL_FIELD *field;
    int num;
    
    if(conn2)
    {
        mysql_query(conn2,stmt);
        read = mysql_store_result(conn2);
        if (mysql_query(conn2,stmt))
        {
            printf(" Error: %s\n", mysql_error(conn2));
            printf("Failed to execute query.");
        }
        
        else
        {
            while ((row = mysql_fetch_row(read)))
            {
                int num_fields;
                num_fields = mysql_num_fields(read);
                int i;
                for(i = 0; i < num_fields; i++)
                {
                    printf(" |");
                    if (i == 0)
                    {
                        while(field = mysql_fetch_field(read))
                        {
                            printf("%s |", field->name);
                        }
                        
                        printf("\n");
                    }
                    
                    printf("%s  ", row[i] ? row[i] : "NULL");
                }
            }
            
            printf("\n");
        }
    }
    
    /*mysql_free_result(read);*/
    else
    {
        printf("not connected");
        printf("%s\n", mysql_error(conn2));
    }
    
    return;
}
//end of displaying employee details.


/*Start of Function: Modify Employee*/

char* modify_employee(int emp_id)
{
    struct employee{
        int id;
        char f_name[50];
        char l_name[50];
        int age;
        char address1[45];
        char address2[45];
        char phonenumber[20];
        char gender[10];
        char email[100];
        char status[100];
        int day;
        int month;
        int year;
    };
    
    struct employee emp;
    int i=0;
    int x=0;
    char stmt[1500];
    getchar();
    printf("                Press 1 First Name\n");
    printf("                Press 2 Last Name\n");
    printf("                Press 3 Age\n");
    printf("                Press 4 Address Line 1\n");
    printf("                Press 5 Address Line 2\n");
    printf("                Press 6 Phone Number\n");
    printf("                Press 7 Gender\n");
    printf("                Press 8 Email\n");
    printf("                Press 9 Day of joining\n");
    printf("                Press 10 Month of joining\n");
    printf("                Press 11 Year of joining\n");
    printf("                Press 12 Status\n");
    printf("                Press 13 Exit\n");
    scanf("%d",&i);
    switch(i){
        case 1:{
            
            getchar();
            do{
                printf("Please provide the first name: \n");
                gets(emp.f_name);
                x=notempty(emp.f_name);
            }while(x==0);
            x=0;
            char qry[]={"update emp_details set name1='%s' where emp_id='%d'"};
            
            if(conn2){
                sprintf(stmt,qry,emp.f_name,emp_id);
                
                if(mysql_query(conn2,stmt)){
                    printf(" Error: %s\n", mysql_error(conn2));
                    return "Failed to execute query.";
                }
                else{
                    return "\n\n\n\nUser modified successfully\n\n\n\n";
                }
            }
            else{
                printf("not connected");
                printf("%s\n", mysql_error(conn2));
            }
            break;
        }
        
        case 2:{
            getchar();
            do{
                printf("Please provide the last name: \n");
                gets(emp.l_name);
                x=notempty(emp.l_name);
            }while(x==0);
            x=0;
            
            char qry[]={"update emp_details set name2='%s' where emp_id='%d'"};
            if(conn2){
                sprintf(stmt,qry,emp.l_name,emp_id);
                if(mysql_query(conn2,stmt)){
                    printf(" Error: %s\n", mysql_error(conn2));
                    return "Failed to execute query.";
                }
                
                else{
                    return "\n\n\n\nUser modified successfully\n\n\n\n";
                }
            }
            
            else{
                printf("not connected");
                printf("%s\n", mysql_error(conn2));
            }
            
            break;
        }
        
        case 3:{
            printf("Please provide the age: \n");
            scanf("%d",&emp.age);
            getchar();
            char qry[]={"update emp_details set age='%d' where emp_id='%d'"};
            if(conn2){
                sprintf(stmt,qry,emp.age,emp_id);
                if(mysql_query(conn2,stmt)){
                    printf(" Error: %s\n", mysql_error(conn2));
                    return "Failed to execute query.";
                }
                else{
                    return "\n\n\n\nUser modified successfully\n\n\n\n";
                }
            }
            
            else{
                printf("not connected");
                printf("%s\n", mysql_error(conn2));
            }
            break;
        }
        
        case 4:{
            int x=0;
            getchar();
            do{
                printf("Enter address line 1\n");
                gets(emp.address1);
                x=notempty(emp.address1);
            }while(x==0);
            
            char qry[]={"update emp_details set address_l1='%s' where emp_id='%d'"};
            if(conn2){
                sprintf(stmt,qry,emp.address1,emp_id);
                if(mysql_query(conn2,stmt)){
                    printf(" Error: %s\n", mysql_error(conn2));
                    return "Failed to execute query.";
                }
                
                else{
                    return "\n\n\n\nUser modified successfully\n\n\n\n";
                }
            }
            
            else{
                printf("not connected");
                printf("%s\n", mysql_error(conn2));
            }
            break;
        }
        
        case 5:{
            int x=0;
            getchar();
            do{
                printf("Enter address line 2\n");
                gets(emp.address2);
                x=notempty(emp.address2);
            }while(x==0);
            
            char qry[]={"update emp_details set address_l2='%s' where emp_id='%d'"};
            if(conn2){
                sprintf(stmt,qry,emp.address2,emp_id);
                if(mysql_query(conn2,stmt)){
                    printf(" Error: %s\n", mysql_error(conn2));
                    return "Failed to execute query.";
                }
                else{
                    return "\n\n\n\nUser modified successfully\n\n\n\n";
                }
            }
            
            else{
                printf("not connected");
                printf("%s\n", mysql_error(conn2));
            }
            break;
        }
        
        case 6:{
            int x=0;
            do{
                printf("Please provide the phone number: \n");
                scanf("%s",emp.phonenumber);
                getchar();
                x=valid_phone(emp.phonenumber);
            }while(x==0);
            
            
            char qry[]={"update emp_details set phonen='%s' where emp_id='%d'"};
            
            if(conn2){
                sprintf(stmt,qry,emp.phonenumber,emp_id);
                if(mysql_query(conn2,stmt)){
                    printf(" Error: %s\n", mysql_error(conn2));
                    return "Failed to execute query.";
                }
                
                else{
                    return "\n\n\n\nUser modified successfully\n\n\n\n";
                }
            }
            
            else{
                printf("not connected");
                printf("%s\n", mysql_error(conn2));
            }
            
            break;
        }
        
        case 7:{
            do{
                printf("\nEnter gender Male , Female or Others\n");
                scanf("%s",emp.gender);
                if (strcasecmp(emp.gender,"Male")==0 || strcasecmp(emp.gender,"Female")==0 || strcasecmp(emp.gender,"Female")==0){
                    x=1;
                    break;
                }
            } while(x==0);
            x=0;
            
            char qry[]={"update emp_details set gender='%s' where emp_id='%d'"};
            if(conn2){
                sprintf(stmt,qry,emp.gender,emp_id);
                if(mysql_query(conn2,stmt)){
                    printf(" Error: %s\n", mysql_error(conn2));
                    return "Failed to execute query.";
                }
                
                else{
                    return "\n\n\n\nUser modified successfully\n\n\n\n";
                }
            }
            
            else{
                printf("not connected");
                printf("%s\n", mysql_error(conn2));
            }
            break;
        }
        
        case 8:{
            int x=0;
            do{
                printf("Please provide the email: \n");
                scanf("%s",emp.email);
                getchar();
                x=valid_email(emp.email);
            }while(x==0);
            
            char qry[]={"update emp_details set email='%s' where emp_id='%d'"};
            if(conn2){
                sprintf(stmt,qry,emp.email,emp_id);
                if(mysql_query(conn2,stmt)){
                    printf(" Error: %s\n", mysql_error(conn2));
                    return "Failed to execute query.";
                }
                else{
                    return "\n\n\n\nUser modified successfully\n\n\n\n";
                }
            }
            
            else{
                printf("not connected");
                printf("%s\n", mysql_error(conn2));
            }
            
            break;
        }
        
        case 9:{
            printf("Please provide the day of joining: \n");
            scanf("%d",&emp.day);
            getchar();
            char qry[]={"update emp_details set day='%d' where emp_id='%d'"};
            if(conn2){
                sprintf(stmt,qry,emp.day,emp_id);
                if(mysql_query(conn2,stmt)){
                    printf(" Error: %s\n", mysql_error(conn2));
                    return "Failed to execute query.";
                }
                
                else{
                    return "\n\n\n\nUser modified successfully\n\n\n\n";
                }
            }
            
            else{
                printf("not connected");
                printf("%s\n", mysql_error(conn2));
            }
            
            break;
        }
        
        case 10:{
            printf("Please provide the month of joining: \n");
            scanf("%d",&emp.month);
            getchar();
            char qry[]={"update emp_details set month='%d' where emp_id='%d'"};
            if(conn2){
                sprintf(stmt,qry,emp.month,emp_id);
                if(mysql_query(conn2,stmt)){
                    printf(" Error: %s\n", mysql_error(conn2));
                    return "Failed to execute query.";
                }
                
                else{
                    return "\n\n\n\nUser modified successfully\n\n\n\n";
                }
            }
            
            else{
                printf("not connected");
                printf("%s\n", mysql_error(conn2));
            }
            
            break;
        }
        
        case 11:{
            printf("Please provide the year: \n");
            scanf("%d",&emp.year);
            getchar();
            char qry[]={"update emp_details set year='%d' where emp_id='%d'"};
            if(conn2){
                sprintf(stmt,qry,emp.year,emp_id);
                if(mysql_query(conn2,stmt)){
                    printf(" Error: %s\n", mysql_error(conn2));
                    return "Failed to execute query.";
                }
                else{
                    return "\n\n\n\nUser modified successfully\n\n\n\n";
                }
            }
            
            else{
                printf("not connected");
                printf("%s\n", mysql_error(conn2));
            }
            break;
        }
        
        case 12:{
            int x=0;
            do{
                printf("Enter the employee status (A for Active or I for Inactive)\n");
                scanf("%s",emp.status);
                if(strcmp(emp.status,"A")==0 || strcmp(emp.status,"I")==0){
                    x=1;
                }
            }while(x==0);
            
            char qry[]={"update emp_details set emp_type='%s' where emp_id='%d'"};
            if(conn2){
                sprintf(stmt,qry,emp.status,emp_id);
                if(mysql_query(conn2,stmt)){
                    printf(" Error: %s\n", mysql_error(conn2));
                    return "Failed to execute query.";
                }
                else{
                    return "\n\n\n\nUser modified successfully\n\n\n\n";
                }
            }
            
            else{
                printf("not connected");
                printf("%s\n", mysql_error(conn2));
            }
            
            break;
        }
    }
    return NULL;
}

//Start of Leaves display function
int display_leaves(int emp_id)
{
    MYSQL_RES *read=NULL;
    MYSQL_RES *res=NULL;
    MYSQL_ROW row=NULL;
    MYSQL_FIELD *field;
    int num,year;
    char stmt[1500];
    printf("Enter the leave year you wish to see: \n");
    scanf("%d",&year);
    char qry[]={"select * from leave_details where emp_id='%d' and Leave_year='%d'"};
    if(conn2)
    {
        int n = sprintf(stmt,qry,emp_id,year);
        mysql_query(conn2,stmt);
        read = mysql_store_result(conn2);
        if (mysql_query(conn2,stmt))
        {
            printf(" Error: %s\n", mysql_error(conn2));
            printf("Failed to execute query.");
            return 0;
        }
        
        else
        {
            row = mysql_fetch_row(read);
            if(row==NULL)
            {
                printf("No data found for employee id %d ",emp_id);
                return 0;
            }
            else{
                
                while (row)
                {
                    int num_fields;
                    num_fields = mysql_num_fields(read);
                    int i;
                    for(i = 0; i < num_fields; i++)
                    {
                        printf(" |");
                        if (i == 0)
                        {
                            while(field = mysql_fetch_field(read))
                            {
                                printf("%s |", field->name);
                            }
                            
                            printf("\n");
                        }
                        
                        printf("    %s    ", row[i] ? row[i] : "NULL");
                    }
                    row = mysql_fetch_row(read);
                    
                }
            }
            
            
            printf("\n");
        }
    }
    
    return 1;
}
//End of leaves display


int emp_management(int i,int emp_id)
{
    conn2=mysql_init(NULL);
    int id;
    mysql_real_connect(conn2, "localhost", "root", "1234","payroll", 3305, NULL, 0);
    if(!conn2)
    {
        printf("Connection error");
        return 0;
    }
    else
    {
        switch(i)
        {
            case 1:
            {
                printf("                Press 1 Add Employee\n");
                printf("                Press 2 Modify Employee\n");
                printf("                Press 3 Deactivate Employee\n");
                printf("                Press 4 Display Employee\n");
                int k;
                scanf("%d",&k);
                switch(k)
                {
                    case 1:
                    {
                        printf("%s",add_employee("empty","empty",0,0));
                        break;
                    }
                    case 2:
                    {
                        printf("Please specify the employee id: ");
                        scanf("%d",&id);
                        printf("%s",modify_employee(id));
                        break;
                    }
                    case 3:
                    {
                        printf("Pleae specify the employee id: ");
                        scanf("%d",&id);
                        deactivate(id,emp_id);
                        break;
                    }
                    case 4:
                    {
                        int j;
                        int emp_id;
                        char emp_depart_display[50];
                        char emp_desig_display[50];
                        printf("\n                Press 1 Display with Employee ID.");
                        printf("\n                Press 2 Display with Departments");
                        printf("\n                Press 3 Display with Designations");
                        printf("\n                Press 4 Display all Employees.\n");
                        scanf("%d",&j);
                        if (j == 1)
                        {
                            char stmt[1500];
                            printf("Enter the Employee ID: ");
                            scanf("%d",&emp_id);
                            char qry[] = {"select * from emp_details where emp_id = %d"};
                            int n = sprintf(stmt,qry,emp_id);
                            emp_display_details(stmt);
                        }
                        
                        else if (j == 2)
                        {
                            char stmt[1500];
                            printf("\nEnter the department: ");
                            scanf("%s",emp_depart_display);
                            char qry[] = {"select * from emp_details where department= '%s'"};
                            int n = sprintf(stmt,qry,emp_depart_display);
                            emp_display_details(stmt);
                        }
                        
                        else if (j == 3)
                        {
                            char stmt[1500];
                            printf("\nEnter the designation: ");
                            scanf("%s",emp_desig_display);
                            char qry[] = {"select * from emp_details where designation = '%s'"};
                            int n = sprintf(stmt,qry,emp_desig_display);
                            emp_display_details(stmt);
                        }
                        
                        else if (j == 4)
                        {
                            char stmt[1500];
                            printf("\nDisplaying all employees \n");
                            char qry[] = {"select * from emp_details"};
                            int n = sprintf(stmt,qry);
                            emp_display_details(stmt);
                        }
                        
                        else
                        {
                            printf("Entered Incorrect number");
                            break;
                        }
                    }
                }
                break;
            }
            
            case 2:
            {
                printf("                Press 1 Add new leave details\n");
                printf("                Press 2 View pending requests\n");
                printf("                Press 3 Display leaves\n");
                int ch;
                scanf("%d",&ch);
                if(ch==1)
                {
                    new_leave_detail();
                }
                else if(ch==2)
                {
                    employee_reuests();
                }
                else if(ch==3)
                {
                    
                }
                else
                {
                    printf("Wrong choice");
                }
                break;
            }
            
            case 3:
            {
                printf("                Press 1 create attendance month\n");
                printf("                Press 2 to add daily attendance attendance\n");
                printf("                Press 3 Display attendance\n");
                printf("                Press 4 Update attendance\n");
                int ch;
                scanf("%d",&ch);
                attend_mgmt(ch);
                break;
            }
            
            case 4:
            {
                printf("                Press 1 Display salary\n");
                printf("                Press 2 Update salary\n");
                int i;
                scanf("%d",&i);
                switch(i)
                {
                    case 1:
                    break;
                    case 2:
                    printf("Enter employee id of employee, you wish to change salary for: \n");
                    int i;
                    scanf("%d",&i);
                    printf("%s",update_salary(i));
                    break;
                    default:
                    printf("Wrong option\n");
                    break;
                }
                break;
            }
            
            case 5:{
                int i=0;
                printf("                Press 1 View pending requests to add employee\n");
                printf("                Press 2 Add employee to the department\n");
                scanf("%d",&i);
                switch(i){
                    case 1:{
                        char status[10];
                        strcpy(status,"Pending");
                        printf("%s",view_pending_requests(status));
                        break;
                    }
                    case 2:{
                        int req_id;
                        printf("Please provide the request id to be addressed: ");
                        scanf("%d",&req_id);
                        printf("%s",add_employee_department(req_id));
                        break;
                    }
                    break;
                }
                
                break;
            }
            case 6:
            {
                printf("                Press 1 Increment Salary\n");
                break;
            }
            case 7:
            {
                int gri_choice;
                printf("                Press 1 Grievances Redressal\n");
                scanf("%d",&gri_choice);
                if (1 == gri_choice)
                {
                    int choice;
                    printf("		Press 1 Raise Grievance\n");
                    printf("		Press 2 View Grievances\n");
                    scanf("%d",&choice);
                    
                    if (1 == choice)
                    {
                        printf("%s",raise_grievances(emp_id));
                    }
                    
                    else if(2 == choice)
                    {
                        //view_raised_grievances();
                    }
                    
                    else
                    {
                        printf("\t\t Wrong Choice Entered.\n");
                    }
                }
                
                else
                {
                    printf("\t\t Wrong Choice entered.\n");
                }
                break;
            }
            
            case 8:
            {
                change_password(emp_id);
                break;
            }
            
            default:
            {
                printf("wrong input");
                break;
            }
        }
        return 1;
    }
    
}
