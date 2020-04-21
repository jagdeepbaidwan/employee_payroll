/**
 * @file manager_dept_management.c
 *
 * Perform the Employee request functionality for managing employees between department.
 *
 */

/* Including basic libraries */
#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<mysql.h>
#include<stdlib.h>

/* Declaration of connection to MYSQL Database pointers */
MYSQL *connect4,*connect5;
int port=3306;

/**
 * \brief Employee request for the department from other department using
 *  'employee_request' table by taking the inputs given by the Manager
 *
 * Manager will request for the employee from other department for their purpose
 * The statys will be approved when admin gives the approval permission
 * Employee can also be promote to higher designation for the projects
 *
 * @param[in] int e_id Employee ID of the user
 * @param[in]	char dept[] Department of the user
 *
 * \return User_Type: Request raised successfully: For positive case
 *		   Failed to execute the query: Connection problem for execution of the query
 *
 */

char* employee_request(int emp_id,char dept[],char designation[]){
	MYSQL_RES *read=NULL;
    MYSQL_RES *res=NULL;
    MYSQL_ROW row=NULL;

    if(strlen(dept)>10)
    {
    	printf("\nDepartment string length invalid\n");
    	return "Department string length invalid";
	}
	else if(strlen(designation)>15)
	{
		printf("\nDesignation string length invalid\n");
    	return "Designation string length invalid";
	}

	char stmt[1500];
	char status[15];
	char dep[20];
	connect5=mysql_init(NULL);
	mysql_real_connect(connect5, "localhost", "root", "1234","payroll",port, NULL, 0);
	char qry_manager_id[]={"select * from emp_details where emp_id='%d'"};

	if(connect5){
        int n=sprintf(stmt,qry_manager_id,emp_id);
        mysql_query(connect5,stmt);
		read = mysql_store_result(connect5);
		row = mysql_fetch_row(read);
		if (row == NULL){
            printf("\nUser does not exist\n");
            return "User does not exist";
        }
        else
        {
        	strcpy(dep,row[3]);
        	if(strcmp(dep,dept)==0)
        	{
        		connect4=mysql_init(NULL);
				mysql_real_connect(connect4, "localhost", "root", "1234","payroll",3306, NULL, 0);
        		char qry_request[]={"insert into employee_request (emp_id,department,designation,request_status) values ('%d','%s','%s','%s')"};
				strcpy(status,"Pending");

				if(connect4){
				    int n=sprintf(stmt,qry_request,emp_id,dept,designation,status);
					if (mysql_query(connect4,stmt)){
			   		    printf(" Error: %s\n", mysql_error(connect4));
			   		    return "Failed to execute query.";
			 	    }
			 	    else{
			 	    	printf("\nRequest raised successfully\n");
			 	    	return "Request raised successfully";
					}
			    }
			}
			else
			{
				printf("\nData Mismatch\n");
				return "Data Mismatch";
			}
		}
    }
}
