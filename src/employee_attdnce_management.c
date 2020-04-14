#include<stdio.h>
#include<windows.h>
#include<mysql.h>
#include "..\include\Validation.h"
#include "..\include\attendance_display.h"
MYSQL *conn3;

// Attendance request change...
int port5=3305;
char* attendance_change(int emp_id)
{
	char stmt[1500];
	//struct request
	//{
		int id;
       	char date[15];
       	char description[150];
	//};
	//struct request req;
	printf("Enter the date on which you have problem (mm/dd/yyyy)\n");
    scanf("%s",date);
    int x;
    do{
    printf("Explain your problem in 150 characters\n");
    gets(description);
    x=notempty(description);
    }while(x==0);

    char qry[]={"insert into request_form (emp_id,date,descript,req_status) VALUES('%d','%s','%s','0')"};
	sprintf(stmt,qry,emp_id,date,description);
    if (mysql_query(conn3,stmt))
    {
   		printf(" Error: %s\n", mysql_error(conn3));
   		return "Failed to execute query.";
   	}
    else
 	{
 	   return "\n\n\n Record entered in database\n\n\n\n";
 	}
}
//Function attendance request change

void reuest_status(int emp_id)
{

	MYSQL_RES *read=NULL;
	MYSQL_RES *res=NULL;
	MYSQL_ROW row=NULL;
	int num,u;
	char stmt[1500];
    char qry_id[]={"select * from request_form where emp_id='%d'"};
    sprintf(stmt,qry_id,emp_id);
    if (mysql_query(conn3,stmt))
    {
        printf(" Error: %s\n", mysql_error(conn3));
        printf("Failed to execute query.");
    }
    else
    {
    	int i=0;
    	read = mysql_store_result(conn3);

        printf("\n--------------------------------------------------------------------------------\n");
        while(row = mysql_fetch_row(read))
        {
		num = mysql_num_fields(read);

        printf("|");
		for(i = 0; i < num; i++)
        {
        	if(i==4)
        	{
        		if(atoi(row[i])==0)
        		{
        			printf("-Request Pending-");
				}
				else if(atoi(row[i])==1)
				{
					printf("-Rejected-");
				}
				else if(atoi(row[i])==2)
				{
					printf("-Accepted-");
				}

			}
			else
			{
            	printf("%s|", row[i]);
            }
        }
        printf("\n--------------------------------------------------------------------------------\n");
    	}
        printf("\n");
    }
}



// Attendance request change...
void emp_attendance_mgmt(int emp_id)
{
	conn3=mysql_init(NULL);
	mysql_real_connect(conn3, "localhost", "root", "1234","payroll", port5, NULL, 0);
	if(!conn3)
	{
		printf("Connection error");

	}
	else
	{
		printf("                Press 1 Display attendance \n");
		printf("                Press 2 Display attendance change request\n");
		printf("                Press 3 Request attendance change\n");
		int ch;
		scanf("%d",&ch);
		if(ch==1)
		{
            view_attendance(emp_id);
		}
		else if(ch==2)
		{
			reuest_status(emp_id);
		}
		else if(ch==3)
		{
            printf("%s",attendance_change(emp_id));
		}
		else
		{
			printf("wrong choice");
		}
	}
}
