/**
 * @file test.c
 *
 * @brief Implementation of unit test cases.
 *
 * @author Arshdeep Singh - 
 * @author Jagdeep Singh - 
 * @author Puneet Singh -
 * @author Varinder Singh Dhanda - 
 */
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<mysql.h>
#include<string.h>
MYSQL *oo,*conn;
MYSQL_RES *read1=NULL;
MYSQL_RES *res=NULL;
MYSQL_ROW row=NULL;
 #define ASSERT_TEST(x)                        \
    {                                         \
        if (x)                                \
        {                                     \
            printf("PASSED\n");               \
        }                                     \
        else                                  \
        {                                     \
            printf("FAILED\n"); \
        }                                     \
    }

char* login(int id, char pwd[25])
{
	char stmt[1500];
	char qry[]={"select * from login_details where emp_id='%d'and password='%s'"};
	oo=mysql_init(NULL);
	mysql_real_connect(oo, "localhost", "root", "1234","payroll", 3306, NULL, 0);
	if(oo)
    {

            int n=sprintf(stmt,qry,id,pwd);
            mysql_query(oo,stmt);
            read1=mysql_store_result(oo);
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
        printf("%s\n", mysql_error(oo));
    }
}

    
char* change_pass(int emp_id,char new_pass[45], char confirm_pass[45],char old_pass[45])
{
    char stmt[1500];
    char qry[]={"select password from login_details where emp_id='%d'"};
    if(oo)
    {
        sprintf(stmt,qry,emp_id);
        if (mysql_query(oo,stmt))
      	{
            printf(" Error: %s\n", mysql_error(oo));
            return "Failed to execute query.";
        }
       	else
 	{
 	    read1=mysql_store_result(oo);
            row = mysql_fetch_row(read1);
            if(row==NULL)
            {
                 return "\nWrong username or password\n\n\n\n\n";
        	
            }
            else
	    {
                if(strcmp(old_pass,row[0])==0)
		{
	            char qry[]={"update login_details set password='%s' where emp_id='%d'"};
	            printf( "\nOld Password confirmed\n\n\n");
	            if(strcmp(new_pass,confirm_pass)==0)
	            {
	                sprintf(stmt,qry,new_pass,emp_id);
		        if (mysql_query(oo,stmt))
      	                {
   			     printf(" Error: %s\n", mysql_error(oo));
   		             return "Failed to execute query.\n";
   	                }
         	        else
 	                {
 	                    return "Password updated\n";
			}
		    }
                   else
		   {
		       return "re-enter new password \n";
		   }
               }
	       else
	       {
	          return "\nOld password wrong\n\n\n";
			   
               }
	   }
 	
       }
    }
    else
    {
    	printf("not connected");
        printf("%s\n", mysql_error(oo));
        return "Error\n";
    	
    }
	
}

int main(int argc, char *argv[])
{
  	
  printf("*********************************TEST 1 for Login**********************************************\n");
  printf("***********************************TEST 1A*****************************************************\n");
  printf("We are first going to login using correct credentials for Admin i.e. Userid=1 and password=1234\n");
  printf("Expected result is it should return string admin\n ");
  ASSERT_TEST(strcmp(login(1,"1234"),"admin")==0);	
  printf("***********************************TEST 1B****************************************************\n");
  printf("We are going to login using incorrect credentials Userid=1 and password=1233\n");
  printf("Expected result is it should return string Wrong username or password\n ");
  ASSERT_TEST(strcmp(login(1,"1233"),"\nWrong username or password\n\n\n\n\n")==0);
  printf("*******************************TEST 2 for change_password*****************************************\n");
  printf("***********************************TEST 2A*****************************************************\n");
  printf("Change_password accepts 4 parameters i.e. userid,old password , new password , confirm new password\n");  
  printf("In first case we are going to input correct credentials, it should return string Password updated\n");
  ASSERT_TEST(strcmp(change_pass(1,"1222","1222","1234"),"Password updated\n")==0);
  printf("***********************************TEST 2B*****************************************************\n");
  printf("In second case we are going to input incorrect old password, it should return string Old password wrong\n");
  ASSERT_TEST(strcmp(change_pass(1,"1222","1222","12"),"\nOld password wrong\n\n\n")==0);	
 
  printf("***********************************TEST 2C*****************************************************\n");
  printf("In second case we are going to input incorrect new password, it should return string re-enter new password\n");
  ASSERT_TEST(strcmp(change_pass(1,"1232","1224","1222"),"re-enter new password \n")==0);	
		
}

