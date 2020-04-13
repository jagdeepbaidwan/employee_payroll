#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<mysql.h>
#include<stdlib.h>
#include "..\include\Validation.h"
#include "..\include\employee_management.h"
MYSQL *conn5;
MYSQL *conn2;
/*MYSQL *conn7;
MYSQL *oo2;
MYSQL *oo3;*/

char* view_pending_requests(char status[]){
	MYSQL_RES *read=NULL;
	MYSQL_RES *res=NULL;
	MYSQL_ROW row=NULL;

	char stmt[1500];
	char qry_req[]={"select * from employee_request where request_status='%s'"};
	conn5=mysql_init(NULL);
	mysql_real_connect(conn5, "localhost", "root", "1234","payroll", 3305, NULL, 0);

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
    char dep[20];
    char des[20];
    int check=1;
	char stmt[1500];
	char qry_retrieve[]={"select department,designation from employee_request where request_id='%d'"};
	mysql_real_connect(conn2, "localhost", "root", "1234","payroll", 3305, NULL, 0);

	if(conn2){
		int n=sprintf(stmt,qry_retrieve,request_id);
		mysql_query(conn2,stmt);
		read = mysql_store_result(conn2);
		if (mysql_query(conn2,stmt)){
            printf(" Error: %s\n", mysql_error(conn2));
            printf("Failed to execute query.");
        }
        else{
			row = mysql_fetch_row(read);
			strcpy(dep,row[0]);
			strcpy(des,row[1]);
        }
	}
	else{
    	printf("not connected");
        printf("%s\n", mysql_error(conn2));
	}
	add_employee(dep,des,check,request_id);
}
