/**
 * @file test.c
 *
 * @brief Implementation of unit test cases.
 *
 * @author Arshpreet Singh -
 * @author Jagdeep Singh -
 * @author Puneet Singh -
 * @author Varinder Singh Dhanda -
 */
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<mysql.h>
#include<string.h>
#include "..\include\employee_management.h"
#include "..\include\employee.h"
#include "..\include\manager_dept_management.h"

MYSQL *conn;
MYSQL_RES *read1=NULL;
MYSQL_RES *res=NULL;
MYSQL_ROW row=NULL;
 #define ASSERT_TEST(x)                        \
    {                                         \
        if (x)                                \
        {                                     \
            printf("\n\nPASSED\n\n\n");               \
        }                                     \
        else                                  \
        {                                     \
            printf("\n\nFAILED\n\n\n"); \
        }                                     \
    }


char* login(int id, char pwd[25])
{
	char stmt[1500];
	char qry[]={"select * from login_details where emp_id='%d'and password='%s'"};
	conn=mysql_init(NULL);
	mysql_real_connect(conn, "localhost", "root", "1234","payroll", 3306, NULL, 0);
	if(conn)
    {

            int n=sprintf(stmt,qry,id,pwd);
            mysql_query(conn,stmt);
            read1=mysql_store_result(conn);
            row = mysql_fetch_row(read1);
            if(row==NULL)
            {
                return "\nWrong username or password\n\n\n\n\n";

	        }
	    else
	    {
	        if(strcmp("I",row[3])==0)
	        {

	         return "\nUser is deactivated\n\n\n\n\n\n";
	        }
	        else
	        {
	            printf("\nSuccessfully logged in \n");
	            return row[2];

		    }
	    }
	}
    else
    {
        printf("not connected");
        printf("%s\n", mysql_error(conn));
    }
}

int main(int argc, char *argv[])
{
    int ch;
    printf("\n     Press 1 to test login\n");
    printf("\n     Press 2 to raise attendance change request\n");
    printf("Enter test case number");

    scanf("%d",&ch);
    switch(ch)
    {
    case 1:
        {
            printf("*********************************TEST 1 for Login**********************************************\n");
            printf("***********************************TEST 1A*****************************************************\n");
            printf("We are first going to login using correct credentials for Admin i.e. Userid=1 and password=1234\n");
            printf("Expected result is it should return string admin\n ");
            ASSERT_TEST(strcmp(login(1,"1234"),"admin")==0);
            printf("***********************************TEST 1B****************************************************\n");
            printf("We are going to login using incorrect password Userid=1 and password=1233\n");
            printf("Expected result is it should return string Wrong username or password\n ");
            ASSERT_TEST(strcmp(login(1,"1233"),"\nWrong username or password\n\n\n\n\n")==0);
            printf("***********************************TEST 1C****************************************************\n");
            printf("We are going to login using incorrect username Userid=999 and password=1233\n");
            printf("Expected result is it should return string Wrong username or password\n ");
            ASSERT_TEST(strcmp(login(999,"1233"),"\nWrong username or password\n\n\n\n\n")==0);
            printf("***********************************TEST 1D****************************************************\n");
            printf("We are going to login using Inactive user credentials i.e UserId=3 and Password=1234\n");
            printf("Expected result is it should return string User is deactivated\n ");
            ASSERT_TEST(strcmp(login(3,"1234"),"\nUser is deactivated\n\n\n\n\n\n")==0);

            break;
            
        }
    case 2:
    	{
    		
    		printf("*******************************TEST 2 for change_password*****************************************\n");
            printf("***********************************TEST 2A*****************************************************\n");
            printf("Change_password accepts 4 parameters i.e. userid,old password , new password , confirm new password\n");
            printf("In first case we are going to input correct credentials, it should return string Password updated\n");
            ASSERT_TEST(strcmp(change_pass(1,"1233","1233","1234"),"Password updated\n")==0);
            change_pass(1,"1234","1234","1233");
            printf("***********************************TEST 2B*****************************************************\n");
            printf("In second case we are going to input incorrect old password, it should return string Old password wrong\n");
            ASSERT_TEST(strcmp(change_pass(1,"1222","1222","12"),"\nOld password wrong\n\n\n")==0);
            printf("***********************************TEST 2C*****************************************************\n");
            printf("In second case we are going to input incorrect new password, it should return string re-enter new password\n");
            ASSERT_TEST(strcmp(change_pass(1,"1232","1224","1234"),"re-enter new password \n")==0);
    		break;
    		
		}
    case 3:
        {
            printf("\n\n\n\n*********************************TEST 3 for attendance change request**********************************************\n");
            printf("***********************************TEST 3A*****************************************************\n");
            printf("We are first going to raise a request with wrong date 123/123/1243 and a random description\n");
            printf("Expected result is it should return Invalid date format\n ");
            ASSERT_TEST(strcmp("Invalid Date",attendance_change(2,123,123,1243,"abcd"))==0);
            printf("\n\n***********************************TEST 3B*****************************************************\n");
            printf("Function call with a description with more than 150 character\n");
            printf("Expected result is it should return Description must not be greater than 150 characters 'C is a procedural programming language. It was initially developed by Dennis Ritchie in the year 1972. It was mainly developed as a system programming language to write an operating system' \n ");
            ASSERT_TEST(strcmp("Invalid description",attendance_change(2,01,04,2020,"C is a procedural programming language. It was initially developed by Dennis Ritchie in the year 1972. It was mainly developed as a system programming language to write an operating system"))==0);
            printf("\n\n***********************************TEST 3C*****************************************************\n");
            printf("Function call without employee id \n");
            printf("Expected result is it should return Employee not exists\n ");
            ASSERT_TEST(strcmp("User not found",attendance_change(0,01,04,2020,"abcd"))==0);
            printf("\n\n***********************************TEST 3D*****************************************************\n");
            printf("Function call with a correct parameters empID=2, date= 17/04/2020 and description='change Absent with ML'\n");
            printf("Expected result is it should return Request submitted\n ");
            ASSERT_TEST(strcmp("Request submitted",attendance_change(2,17,04,2020,"change Absent with ML"))==0);
             break;
        }
    case 4:
        {
            printf("\n\n\n\n*********************************TEST 4 for employee deactivation**********************************************\n");
            printf("***********************************TEST 4A*****************************************************\n");
            printf("We are first going to raise a request with a wrong emp_id to deactivate\n");
            printf("Expected result is it should return Employee does not exists\n ");
            ASSERT_TEST(strcmp("No employee exists",deactivate(92344,1))==0);
            printf("***********************************TEST 4B*****************************************************\n");
            printf("Now we raise a request to deactivate the same logged in user id\n");
            printf("Expected result is it should return: Same logged in user can not deactivate himself\n ");
            ASSERT_TEST(strcmp("Same logged in user",deactivate(1,1))==0);
            printf("***********************************TEST 4C*****************************************************\n");
            printf("Now we raise a request to deactivate the already deactivated account\n");
            printf("Expected result is it should return: User already deactivated\n ");
            ASSERT_TEST(strcmp("Already de-activated",deactivate(8,1))==0);
            printf("***********************************TEST 4D*****************************************************\n");
            printf("Now we raise a request to deactivate right employee\n");
            printf("Expected result is it should return: Employee deactivated\n ");
            ASSERT_TEST(strcmp("Employee deactivated",deactivate(2,1))==0);
             break;
        }
    case 5:
        {
            printf("\n\n\n\n*********************************TEST 5 for employee display leaves**********************************************\n");
            printf("***********************************TEST 5A*****************************************************\n");
            printf("We are first going to raise a display leave request with a wrong year\n");
            printf("Expected result is it should return Wrong year chosen\n ");
            ASSERT_TEST(display_leaves(2,22)==2);
            printf("***********************************TEST 5B*****************************************************\n");
            printf("Now if the data is not available in the data base \n");
            printf("Expected result is it should return: No data found \n ");
            ASSERT_TEST(display_leaves(555,2020)==3);
            printf("***********************************TEST 5C*****************************************************\n");
            printf("Now we show the data available in the database...\n");
            printf("Expected result is it should return: table show the data of leave\n ");
            ASSERT_TEST(display_leaves(2,2020)==1);
            printf("***********************************TEST 5D*****************************************************\n");
            printf("Now if the the employee does not exist \n");
            printf("Expected result is it should return: No data found \n ");
            ASSERT_TEST(display_leaves(1234,2020)==3);
             break;
        }
        case 6:
        	{
        	printf("\n\n\n\n*********************************TEST 6 for admin display leaves**********************************************\n");
            printf("***********************************TEST 6A*****************************************************\n");
            printf("We are first going to raise a display leave request with a wrong year\n");
            printf("Expected result is it should return Wrong year chosen\n ");
            ASSERT_TEST(display_leaves(2,2)==2);
            printf("***********************************TEST 6B*****************************************************\n");
            printf("Now if the data is not available in the data base \n");
            printf("Expected result is it should return: No data found \n ");
            ASSERT_TEST(display_leaves(100,2025)==3);
            printf("***********************************TEST 6C*****************************************************\n");
            printf("Now we show the data available in the database...\n");
            printf("Expected result is it should return: table show the data of leave\n ");
            ASSERT_TEST(display_leaves(2,2020)==1);
            printf("***********************************TEST 6D*****************************************************\n");
            printf("Now if the the employee does not exist \n");
            printf("Expected result is it should return: No data found \n ");
            ASSERT_TEST(display_leaves(9999,2020)==3);
            break;
			}
		case 7:
			{
				
			printf("\n\n\n*****  TEST 7 Function: char* leave_request(int emp_id,int dd,int mm,int yy,int no_of_days,char leave_type[]) ****\n");
            printf("*********************  TEST 7A  **************************************************\n");
            printf("A leave request will be raised with all valid input parameters except the date which is invalid: 123/123/124\n");
            printf("Expected result is that it should return an Invalid date message \n ");
            ASSERT_TEST(strcmp("Invalid Date",leave_request(12,123,123,124,4,"SL"))==0);
            
            printf("\n\n*****************  TEST 7B  **************************************************\n");
            printf("A leave request will be raised with all valid input parameters except the leave type which is invalid: ABCD \n");
            printf("Expected result is it should return Invalid Leave Type \n ");
            ASSERT_TEST(strcmp("Invalid Leave Type",leave_request(12,11,12,2006,4,"ABCD"))==0);
            
            printf("\n\n*****************  TEST 7C  ***************************************************\n");
            printf("A leave request will be raised with employee id that does not exist in the database\n");
            printf("Expected result is it should return User does not exist \n ");
            ASSERT_TEST(strcmp("User does not exist",leave_request(26,11,12,2006,4,"SL"))==0);
            
            printf("\n\n*****************  TEST 7D  **************************************************\n");
            printf("A leave request will be raised with leave_type length greater than 10\n");
            printf("Expected result is that it should return Invalid string length for leave_type message\n ");
            ASSERT_TEST(strcmp("Invalid string length for leave_type",leave_request(12,11,12,2006,4,"ABCDEFGHIJKL"))==0);
            
            printf("\n\n*****************  TEST 7E  **************************************************\n");
            printf("\n A leave request will be raised with all the right parameters and therefore will be raised successfully\n");
            printf("Expected result is it should return a string message Request raised successfully \n ");
            ASSERT_TEST(strcmp("Request raised successfully",leave_request(12,11,12,2009,4,"SL"))==0);
			break;	
			}
		case 8:
		{
			printf("\n\n\n*****  TEST 8 Function: char* employee_request(int emp_id,char dept[]) ****\n");
            printf("*********************  TEST 8A  **************************************************\n");
            printf("The employee request function is called to raise employee request but emp_id of the manager who raises request doesn't exist in the database\n");
            printf("Expected result is that it should return User does not exist message \n ");
            ASSERT_TEST(strcmp("User does not exist",employee_request(24,"Elec","Technician"))==0);
            
            printf("\n\n*****************  TEST 8B  **************************************************\n");
            printf("The employee request function is called to raise emp request but the department input to function is not the one assigned to the manager \n");
            printf("Expected result is it should return Data Mismatch message as the department does not match the department assigned to the manager\n ");
            ASSERT_TEST(strcmp("Data Mismatch",employee_request(5,"Physics","Technician"))==0);
            
            printf("\n\n*****************  TEST 8C  ***************************************************\n");
            printf("The employee request function is called to raise emp request but the department length is greater than 10\n");
            printf("Expected result is it should return Department string length invalid \n ");
            ASSERT_TEST(strcmp("Department string length invalid",employee_request(5,"Mechanical Engineer","Technician"))==0);
            
            printf("\n\n*****************  TEST 8D  ***************************************************\n");
            printf("The employee request function is called to raise emp request but the designation length is greater than 15\n");
            printf("Expected result is it should return Designation string length invalid \n ");
            ASSERT_TEST(strcmp("Designation string length invalid",employee_request(5,"Elec","abcdefghijklmnopqrst"))==0);
            
			printf("\n\n*****************  TEST 8E  **************************************************\n");
            printf("The employee request function is called to raise emp request with right parameters\n");
            printf("Expected result is that it should return Request raised successfully\n ");
            ASSERT_TEST(strcmp("Request raised successfully",employee_request(5,"Elec","Technician"))==0);
			break;
		}
		case 9:
		{
			printf("\n\n\n*****  TEST 9 Function: char* decision_leave_request(int req_id,int k) ****\n");
            printf("*********************  TEST 9A  **************************************************\n");
            printf("The decision leave request function is called but no leave request exists with the input request id\n");
            printf("Expected result is that it should return No such pending leave request exists message \n ");
            ASSERT_TEST(strcmp("No such pending leave request exists",decision_leave_request(75,1))==0);
            
            printf("*********************  TEST 9B  **************************************************\n");
            printf("The decision leave request function is called but decision input: k is invalid as k can be only 1 or 2\n");
            printf("Expected result is that it should return Invalid input for k message \n ");
            ASSERT_TEST(strcmp("Invalid input for k",decision_leave_request(4,4))==0);
            
            printf("*********************  TEST 9C  **************************************************\n");
            printf("The decision leave request function is called with right parameters to approve a leave request id\n");
            printf("Expected result is that it should return Leave request and Leave balance status updated successfully message \n ");
            ASSERT_TEST(strcmp("Leave request and Leave balance status updated successfully",decision_leave_request(4,1))==0);
            
            printf("*********************  TEST 9D  **************************************************\n");
            printf("The decision leave request function is called to approve req id which is already approved\n");
            printf("Expected result is that it should return Request is already approved message \n ");
            ASSERT_TEST(strcmp("Request is already approved",decision_leave_request(4,1))==0);
            
            printf("*********************  TEST 9E  **************************************************\n");
            printf("The decision leave request function is called with right parameters to reject a leave request id\n");
            printf("Expected result is that it should return Request Status Updated successfully message \n ");
            ASSERT_TEST(strcmp("Request Status Updated successfully",decision_leave_request(4,2))==0);
            
		break;
	}		
    }
}
