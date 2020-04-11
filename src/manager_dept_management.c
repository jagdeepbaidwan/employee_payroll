#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<mysql.h>
#include<stdlib.h>
MYSQL *conn4;

char* employee_request(int emp_id,char dept[]){
	char stmt[1500];
	char status[15];
	char designation[15];
	char qry_request[]={"insert into employee_request (emp_id,department,designation,request_status) values ('%d','%s','%s','%s')"};
	strcpy(status,"Pending");
	printf("At which position/designation is the employee required: \n");
	scanf("%s",designation);
	
	if(conn4){
	    int n=sprintf(stmt,qry_request,emp_id,dept,designation,status);
		if (mysql_query(conn4,stmt)){
   		    printf(" Error: %s\n", mysql_error(conn4));
   		    return "Failed to execute query.";
 	    }
 	    else{
 	    	return "Request raised successfully";
		}
    }
}

