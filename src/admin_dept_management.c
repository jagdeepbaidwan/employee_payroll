#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<mysql.h>
#include<stdlib.h>
#include "..\include\Validation.h"
MYSQL *conn5;
MYSQL *conn6;
MYSQL *conn7;
MYSQL *oo2;
MYSQL *oo3;

char* view_pending_requests(char status[]){
	MYSQL_RES *read=NULL;
	MYSQL_RES *res=NULL;
	MYSQL_ROW row=NULL;
	
	char stmt[1500];
	char qry_req[]={"select * from employee_request where request_status='%s'"};
	conn5=mysql_init(NULL);
	mysql_real_connect(conn5, "localhost", "root", "1234","payroll", 3306, NULL, 0);
	
	if(conn5){
        int n=sprintf(stmt,qry_req,status);
        mysql_query(conn5,stmt);
		read = mysql_store_result(conn5);
        if (mysql_query(conn5,stmt)){
            printf(" Error: %s\n", mysql_error(conn5));
            printf("Failed to execute query.");
        }
		else{
            int i=0;
            int num=0;
            printf("\n");
            printf("REQUEST_ID	  MANAGER_EMP_ID    DEPARTMENT      DESIGNATION	         STATUS");
            printf("\n");
			while((row = mysql_fetch_row(read))){
            	num = mysql_num_fields(read);
            	printf("	");
            	for(i = 0; i < num; i++){
                    printf("%s ", row[i]);
                    printf("	|	");
                }
                printf("\n");
			}
        }
    }
    else{
    	printf("not connected");
        printf("%s\n", mysql_error(conn5));
	}
return "\n\n\nRequests displayed successfully";
}

char* add_employee_department(int request_id){
	MYSQL_RES *read=NULL;
	MYSQL_RES *res=NULL;
	MYSQL_ROW row=NULL;
	struct employee { 
       int id; 
       char first_name[25]; 
       char last_name[25];
       char dep[20];
       char des[20];
       int age;
       char address_line1[40];
       char address_line2[40];
       char phone_number[15];
	   char gender[10];
	   char email[50];
	   char status[5]; 
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
    gets(emp.first_name);
    x=notempty(emp.first_name);
    }while(x==0);
    x=0;
    
    do{
    printf("Enter the Last name of employee\n");
    gets(emp.last_name);
    x=notempty(emp.last_name);
    }while(x==0);
    x=0;
    
    printf("Enter the age of employee\n");
    scanf("%d",&emp.age);
    getchar();
    
    do{
    printf("Enter House No./Apartment No. and Street\n");
    gets(emp.address_line1);
    x=notempty(emp.address_line1);
    }while(x==0);
    x=0;
   
    do{
    printf("\nEnter city and country\n");
    gets(emp.address_line2);
    x=notempty(emp.address_line2);
    }while(x==0);
    x=0;
    
    do{
    printf("\nEnter gender Male,Female or Others\n");
    scanf("%s",emp.gender);
    if (strcasecmp(emp.gender,"Male")==0 || strcasecmp(emp.gender,"Female")==0 || strcasecmp(emp.gender,"Others")==0){
        x=1;
        break;
    }
    } while(x==0);
    x=0;
	
	do{
    printf("Enter email\n");
    scanf("%s",emp.email);
    x=valid_email(emp.email);
	}while(x==0);
	x=0;
	
	do{
    printf("Enter employement status (A: Active or I: Inactive)\n");
    scanf("%s",emp.status);
    if (strcasecmp(emp.status,"A")==0 || strcasecmp(emp.status,"I")==0){
       x=1;
       break;	
	}
    }while(x==0);
    x=0;
    
	do{
    printf("Enter Phone number\n");
    scanf("%s",emp.phone_number);
    x=valid_phone(emp.phone_number);
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
	char qry_retrieve[]={"select department,designation from employee_request where request_id='%d'"};
	conn6=mysql_init(NULL);
	mysql_real_connect(conn6, "localhost", "root", "1234","payroll", 3306, NULL, 0);
	
	if(conn6){
		int n=sprintf(stmt,qry_retrieve,request_id);
		mysql_query(conn6,stmt);
		read = mysql_store_result(conn6);
		if (mysql_query(conn6,stmt)){
            printf(" Error: %s\n", mysql_error(conn6));
            printf("Failed to execute query.");
        }
        else{
			row = mysql_fetch_row(read);
			strcpy(emp.dep,row[0]);
			strcpy(emp.des,row[1]);
        }		
	}
	
	else{
    	printf("not connected");
        printf("%s\n", mysql_error(conn6));
	}
	conn7=mysql_init(NULL);
	mysql_real_connect(conn7, "localhost", "root", "1234","payroll", 3306, NULL, 0);
	char qry_add_emp[]={"insert into emp_details (name1,name2,department,designation,age,address_l1,address_l2,phonen,gender,email,day,month,year,emp_type) VALUES('%s','%s','%s','%s','%d','%s','%s','%s','%s','%s','%d','%d','%d','%s')"};

	if(conn7){
    	int n=sprintf(stmt,qry_add_emp,emp.first_name,emp.last_name,emp.dep,emp.des,emp.age,emp.address_line1,emp.address_line2,emp.phone_number,emp.gender,emp.email,emp.day,emp.month,emp.year,emp.status);
        if (mysql_query(conn7,stmt)){
   		    printf(" Error: %s\n", mysql_error(conn6));
   		    return "Failed to execute query.";	
 	    }
       	else{
 		   printf( "\n\n\nuser details added successfully\n\n\n\n\n");
	    }
    }
    else{
    	printf("not connected");
        printf("%s\n", mysql_error(conn6));	
	}
	int emp_id;
	char qry_get_emp_id[]={"select max(emp_id) as id from emp_details"};
	if(conn7){
    	int n=sprintf(stmt,qry_get_emp_id);
        mysql_query(conn7,stmt);
		read = mysql_store_result(conn7);
        if (mysql_query(conn7,stmt)){
            printf(" Error: %s\n", mysql_error(conn7));
            printf("Failed to execute query.");
        }
        else{
            int i=0;
			row = mysql_fetch_row(read);
            emp_id=atoi(row[0]);
            mysql_free_result(read);        
        }
	}
    else{
    	printf("not connected");
        printf("%s\n", mysql_error(conn7));	
	}
	oo2=mysql_init(NULL);
	mysql_real_connect(oo2, "localhost", "root", "1234","payroll", 3306, NULL, 0);
	char password []="1234";
	char employee_type[30];
	printf("Enter the employee type -Employee or Manager\n");
	scanf("%s",employee_type);
	char qry_add_login[]={"insert into login_details (emp_id,password,emp_type,status) VALUES('%d','%s','%s','%s')"};
	if(oo2){
    	sprintf(stmt,qry_add_login,emp_id,password,employee_type,emp.status);
        if (mysql_query(oo2,stmt)){
   		    printf(" Error: %s\n", mysql_error(oo2));
   		    return "Failed to execute query.";
 	    }
       	else{
			oo3=mysql_init(NULL);
			mysql_real_connect(oo3, "localhost", "root", "1234","payroll", 3306, NULL, 0);
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
			return "\n\n\nUser added successfully\n\n\n\n\n";	
		}
	}
    else{
    	printf("not connected");
        printf("%s\n", mysql_error(oo2));	
	}
	return "Success";
}
