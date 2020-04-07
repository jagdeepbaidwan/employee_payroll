#include<stdio.h>
#include<windows.h>
#include<mysql.h>
#include<string.h>
#include<stdlib.h>
#include "..\include\Validation.h"
#include "..\include\employee_management.h"
MYSQL *conn2, *oo1;
char query[1500];


//start of  adding a new employee
char* add_employee()
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
    char qry[]={"insert into emp_details (name1,name2,department,designation,age,address_l1,address_l2,phonen,gender,email,day,month,year,emp_type) VALUES('%s','%s','%s','%s','%d','%s','%s','%s','%s','%s','%d','%d','%d','%s')"};
    if(conn2)
    {
        sprintf(stmt,qry,emp.f_name,emp.l_name,emp.dep,emp.des,emp.age,emp.address1,emp.address2,emp.phonenumber,emp.gender,emp.email,emp.day,emp.month,emp.year,emp.status);
        if (mysql_query(conn2,stmt))
      	{
   		    printf(" Error: %s\n", mysql_error(conn2));
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
        printf("%s\n", mysql_error(conn2));
    	
    }
	int emp_id;
	char qry2[]={"select max(emp_id) as id from emp_details"};
    if(conn2)
    {
    	
    	int n=sprintf(stmt,qry2);
        mysql_query(conn2,stmt);
		read = mysql_store_result(conn2);
        if (mysql_query(conn2,stmt))
        {
            printf(" Error: %s\n", mysql_error(conn2));
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
        printf("%s\n", mysql_error(conn2));
    	
    }
	
	oo1=mysql_init(NULL);
	mysql_real_connect(oo1, "localhost", "root", "1234","payroll", 3306, NULL, 0);
	char password []="1234";
	char employee_type[30];
	printf("Enter the employee type -Admin,Employee or Manager\n");
	scanf("%s",employee_type);
	char qry3[]={"insert into login_details (emp_id,password,emp_type,status) VALUES('%d','%s','%s','%s')"};
	if(oo1)
    {
    	
    	sprintf(stmt,qry3,emp_id,password,employee_type,emp.status);
        printf("%s",stmt);
        if (mysql_query(oo1,stmt))
      	{
   		    printf(" Error: %s\n", mysql_error(oo1));
   		    return "Failed to execute query.";
   		
 	    }
       	else
 	    {
 		
 		   return "\n\n\nuser added successfully\n\n\n\n\n";
 	
	    }
    }
   
    else
    {
    	printf("not connected");
        printf("%s\n", mysql_error(oo1));
    	
	}

	
	
	
}


int emp_management(int i,int emp_id)
{
	conn2=mysql_init(NULL);
	int id;
	mysql_real_connect(conn2, "localhost", "root", "1234","payroll", 3306, NULL, 0);
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
		                			
		            
		                			printf("%s",add_employee());
		                			break;
								}
							case 2:
								{
									printf("Pleae specify the employee id: ");
		                			                scanf("%d",&id);
		                			                break;
								}
							case 3:
								{
									printf("Pleae specify the employee id: ");
		                			                scanf("%d",&id);
									break;
								}
							case 4:
								{
									int j;
									printf("\n                Press 1 Display with Employee ID.");
                                    printf("\n                Press 2 Display with Departments");
                                    printf("\n                Press 3 Display with Designations");
                                    printf("\n                Press 4 Display all Employees.\n");
                                    scanf("%d",&j);
                                    					
								}
						}
		                			break;
				    }
			
			    case 2:
			        {   
			            printf("                Press 1 View pending requests\n");
		                printf("                Press 2 Display leaves\n");
		                int ch;
		                scanf("%d",&ch);
		                if(ch==1)
		                {
		                	
						}
						else if(ch==2)
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
			            printf("                Press 1 Display attendance\n");
		                printf("                Press 2 Update attendance\n");
		                break;
				    }
				
			    case 4:
			        {   
			            printf("                Press 1 Display salary\n");
		                printf("                Press 2 Update salary\n");
		                break;
				    }
				
			    case 5:
			        {   
			            printf("                Press 1 Add Employee\n");
			            break;
				    }
			    case 6:
			        {    
			            printf("                Press 1 Increment Salary\n");
			            break;
				    }
			    case 7:
			        {   
			            printf("                Press 1 Grievance redressal\n");
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
