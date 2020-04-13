#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<mysql.h>
#include<string.h>
#include <termios.h>
#include <unistd.h>
#define MAX_YEAR 2020
#define MIN_YEAR 2010
#define MAX_MONTH 12
#define MIN_MONTH 1
#include "..\include\employee_personal_dtl_management.h"
//#include "..\include\employee.h"
#include "..\include\admin_attendance.h"


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

//start of display_salary
int display_salary(int emp_id)
{
MYSQL *conn2;
	
	conn2=mysql_init(NULL);
    int id;
    mysql_real_connect(conn2, "localhost", "root", "1234","payroll", 3306, NULL, 0);
	MYSQL_RES *read=NULL;
    MYSQL_RES *res=NULL;
    MYSQL_ROW row=NULL;
    MYSQL_FIELD *field;
    int num;
    char stmt[1500];
    int option;
    printf("                Press 1 if you want to see all pay slips\n");
	printf("                Press 2 if you want to see pay slips for particular pay period\n");
	scanf("%d",&option);
	char qry[300];
	if(option==1)
	{
	    strcpy(qry,"select * from salary_cal where emp_id='%d'  order by year desc,month desc , week desc");	
	}
	else if(option==2)
	{
	    strcpy(qry,"select * from salary_cal where emp_id='%d' and year='%d'and month='%d'and week ='%d'");
	}
    if(conn2)
    {
    	int n;
    	if(option==1)
    	{
    	    n = sprintf(stmt,qry,emp_id);	
		}
		else if(option==2)
		{
			int year,month,week;
			int x=0;
			do{
			printf("Enter the  year you wish to see: \n");
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
	        printf("Enter the month you wish to see: \n");
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
            printf("Enter the pay week you wish to see :\n Select 1 for first half of month \n Select 2 for second half of month\n");
            scanf("%d",&week);
            if(week==1 || week==2)
            {
            	x=1;
			}
			else{
				printf("INVALID week, enter again\n");
			}
            }while(x==0);

            n = sprintf(stmt,qry,emp_id,year,month,week);	
		}
        
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
              printf("No details found");
            }
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
    }

    return 1;
}

//end of display_salary

char* change_pass(int emp_id,char new_pass[45], char confirm_pass[45],char old_pass[45])
{
    MYSQL *oo,*conn,*conn4;
MYSQL_RES *read1=NULL;
MYSQL_RES *res=NULL;
MYSQL_ROW row=NULL;

	oo=mysql_init(NULL);
	mysql_real_connect(oo, "localhost", "root", "1234","payroll", 3306, NULL, 0);
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
       if((old_pass[p]=='\b' ||old_pass[p]==127)&& p>0)
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
       	 if((new_pass[p]=='\b'||new_pass[p]==127)&& p>0)
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
        if((confirm_pass[p]=='\b'||confirm_pass[p]==127)&& p>0)
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

void employee(int emp_id)
{
    int i;
    printf("                Press 1 Personal details management\n");
    printf("                Press 2 Attendance management\n");
    printf("                Press 3 Leave management\n");
    printf("                Press 4 Salary management\n");
    printf("                Press 5 Grievances redressal\n");
    scanf("%d",&i);
    switch(i)
    {
	case 1:
	{
	    emp_detail_mgmt(emp_id);
            break;
	}
	case 2:
	{
	    emp_attendance_mgmt(emp_id);
	    break;
        }

	case 3:
	{
	    printf("                Press 1 Request leave\n");
            printf("                Press 2 Display leaves\n");
	    break;
	}
	case 4:
	{
            int k=display_salary(emp_id);
            break;
	}
        case 5:
	{
	     printf("                Press 1 Raise Grievance\n");
	     printf("%s",raise_grievances(emp_id));
	     break;
	}

	default:
        {
            printf("wrong input");
	    break;
	}

    }
}
