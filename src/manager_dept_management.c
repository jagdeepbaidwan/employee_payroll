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
MYSQL *conn4;

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

char* employee_request(int emp_id,char dept[]){
	char stmt[1500];
	char status[15];
	char designation[15];
	
	/* Insert the employee request details in the employee_request table of the employee*/
	char qry_request[]={"insert into employee_request (emp_id,department,designation,request_status) values ('%d','%s','%s','%s')"};
	
	/* Initially Pending status is inserted for the permission of the employee*/
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

