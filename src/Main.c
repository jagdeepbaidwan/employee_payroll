#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<mysql.h>
#include<string.h>
#include <termios.h>
#include <unistd.h>
#include "..\include\employee_management.h"
#include "..\include\employee.h"
MYSQL *oo,*conn;
MYSQL_RES *read1=NULL;
MYSQL_RES *res=NULL;
MYSQL_ROW row=NULL;


int getch(void)
{
    struct termios oldt,newt;
    int   ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
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

void change_password(int id)
{
    char old_pass[40],new_pass[40],confirm_pass[40];
    getch();
    printf("\nEnter old password\n");
    int p=0;
    do
    {
       old_pass[p]=getch();
       if(old_pass[p]=='\b'&& p>0)
       {
           p--;
       	   printf("\b \b");
       	   continue;
       }
       if(old_pass[p]!='\r')
       {
           printf("*");
       }
       if(old_pass[p]=='\n'||old_pass[p]==13)
       {
           p++;
	   break;
       }
       p++;
     }while(old_pass[p-1]!='\r'||old_pass[p-1]!=13);
     old_pass[p-1]='\0';
     printf("\nEnter new password\n");
     p=0;
     do
     {
         new_pass[p]=getch();
       	 if(new_pass[p]=='\b'&& p>0)
       	 {
       	     p--;
       	     printf("\b \b");
             continue;
       	 }
	 if(new_pass[p]!='\r')
	 {
              printf("*");
         }
	 if(new_pass[p]=='\n'||new_pass[p]==13)
         {
             p++;
	     break;
	 }
         p++;
        }while(new_pass[p-1]!='\r'||new_pass[p-1]!=13);
        new_pass[p-1]='\0';
        printf("\nConfirm new password\n");
        p=0;
    do
    {
        confirm_pass[p]=getch();
        if(confirm_pass[p]=='\b'&& p>0)
        {
       	    p--;
       	    printf("\b \b");
       	    continue;
        }
        if(confirm_pass[p]!='\r')
	{
            printf("*");
        }
	if(confirm_pass[p]=='\n'||confirm_pass[p]==13)
        {
	    p++;
	    break;
	}
        p++;
    }while(confirm_pass[p-1]!='\r'||confirm_pass[p-1]!=13);
    confirm_pass[p-1]='\0';
    printf("%s\n",change_pass(id,new_pass,confirm_pass,old_pass));
}

char* login(int id, char pwd[25])
{
	char stmt[1500];
	char qry[]={"select * from login_details where emp_id='%d'and password='%s'"};
	oo=mysql_init(NULL);
	mysql_real_connect(oo, "localhost", "root", "1234","payroll", 3305, NULL, 0);
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
	            printf("\nSuccessfully logged in \n\n\n\n\n\n\n\n\n");
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
int main(int argc, char *argv[])
{
	int i,id;
	char ch;
	char pwd[25];
	char user_type[25];
	system("clear");
     	printf("\n*********************************************************************\n");
	printf("                               Login                                   \n");
	printf("\n*********************************************************************\n");

	printf("                Press 1 LOGIN\n");
	printf("                Press 2 EXIT\n");
	scanf("%d",&i);
	switch(i)
	{
		case 1:{
			   printf("\nEnter your employee id:");
        	           scanf("%d",&id);
        	           getchar();
	                   printf("\nEnter your Password:");
        	           int p=0;
    		           do
			   {
       		           pwd[p]=getch();
       			   if(pwd[p]=='\b'&& p>0)
       		 	   {
       			       p--;
       			       printf("\b \b");
       			       continue;
       			    }
			    if(pwd[p]!='\r')
			    {
                                printf("*");
                            }
			    if(pwd[p]=='\n'||pwd[p]==13)
			    {
				p++;
				break;
			    }
                           p++;
                           }while(pwd[p-1]!='\r'||pwd[p-1]!=13);
                           pwd[p-1]='\0';
        	           strcpy(user_type,login(id,pwd));
			   printf("%s\n",user_type);
			   break;
		       }

		case 2:{
			printf("EXIT\n");
			break;
			}

		default:
			{
				printf("Wrong Input");
				break;
			}
	    }

	if(strcmp("admin",user_type)==0)
	{
                printf("                Press 1 Employee management\n");
		printf("                Press 2 Leave management\n");
		printf("                Press 3 Attendance management\n");
		printf("                Press 4 Salary management\n");
                printf("                Press 5 Department management\n");
		printf("                Press 6 Increment management\n");
		printf("                Press 7 Grievances redressal\n");
		printf("                Press 8 To change password\n");
		scanf("%d",&i);
		int st=emp_management(i,id);

	}

	else if(strcmp("employee",user_type)==0)
	{
	    employee(id);
	}

		else if(strcmp("manager",user_type)==0){
			printf("                Press 1 Personal details management\n");
		    printf("                Press 2 Attendance management\n");
		    printf("                Press 3 Leave management\n");
		    printf("                Press 4 Salary management\n");
        	printf("                Press 5 Grievances redressal\n");
			printf("                Press 6 Department management\n");

			scanf("%d",&i);

		    switch(i){
			    case 1:
			    {
                    printf("                Press 1 Display employee details \n");
                    printf("                Press 2 Update employee details\n");
                    printf("                Press 3 Change password\n");
                    scanf("%d",&i);
				    switch (i)
				    {
					case 1:
	    				    break;
					case 2:
					    break;
					case 3:
					{
					    change_password(id);
		    			    break;
					}
					default:
		    			    break;
				    }
		                    break;
		              }

				case 2:{
			            printf("                Press 1 Display attendance\n");
		                printf("                Press 2 Request attendance change\n");
		                break;
				    }

				case 3:{
			            printf("                Press 1 Request leave\n");
		                printf("                Press 2 Display leaves\n");
		                break;
				    }

			    case 4:{
			            printf("                Press 1 Display salary (Hourly)\n");
		                printf("                Press 2 Display salary (Regular)\n");
		                break;
				    }

			    case 5:{
			            printf("                Press 1 Raise Grievance\n");
			            break;
				    }

				case 6:{
						printf("                Press 1 Request Employee\n");
			            printf("                Press 2 Rate employee\n");
			            printf("                Press 3 Display employee rating \n");
						break;
				    }
			    default:{
					    printf("Wrong Input");
					    break;
				    }
		    }
		}

		else{
			printf("Have a Good Day!");
		}

return 0;
}


