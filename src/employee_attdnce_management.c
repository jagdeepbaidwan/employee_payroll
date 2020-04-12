#include<stdio.h>
#include<windows.h>
#include<mysql.h>
#include "..\include\Validation.h"
MYSQL *conn3;



//Attendance View function

void view_attendance(int emp_id)
{
	int dd,mm,yy,r,num;
	MYSQL_RES *read=NULL;
	MYSQL_RES *res=NULL;
	MYSQL_ROW row=NULL;
	char stmt[2500];
	char qry_id[2000];
	int days;
    do
	{
		printf("\nEnter the attendance month and year:Format(mm/yyyy)\n");
		scanf("%d/%d",&mm,&yy);
		r=validate_date(01,mm,yy);
	}while(r!=1);
	if(mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12)
	{
		strcpy(qry_id,"select emp_details.name1,emp_details.name2, daily_attendance.designation,daily_attendance.A1,daily_attendance.A2,daily_attendance.A3,daily_attendance.A4,daily_attendance.A5,daily_attendance.A6,daily_attendance.A7,daily_attendance.A8,daily_attendance.A9,daily_attendance.A10,daily_attendance.A11,daily_attendance.A12,daily_attendance.A13,daily_attendance.A14,daily_attendance.A15,daily_attendance.A16,daily_attendance.A17,daily_attendance.A18,daily_attendance.A19,daily_attendance.A20,daily_attendance.A21,daily_attendance.A22,daily_attendance.A23,daily_attendance.A24,daily_attendance.A25,daily_attendance.A26,daily_attendance.A27,daily_attendance.A28,daily_attendance.A29,daily_attendance.A30,daily_attendance.A31 from daily_attendance join emp_details on emp_details.emp_id=daily_attendance.emp_id where emp_details.emp_id='%d' and daily_attendance.attend_month='%d'and attend_year='%d'");
	}
	else if(mm==4 || mm==6 || mm==9 || mm==11)
	{
		days=30;
		strcpy(qry_id,"select emp_details.name1,emp_details.name2, daily_attendance.designation,daily_attendance.A1,daily_attendance.A2,daily_attendance.A3,daily_attendance.A4,daily_attendance.A5,daily_attendance.A6,daily_attendance.A7,daily_attendance.A8,daily_attendance.A9,daily_attendance.A10,daily_attendance.A11,daily_attendance.A12,daily_attendance.A13,daily_attendance.A14,daily_attendance.A15,daily_attendance.A16,daily_attendance.A17,daily_attendance.A18,daily_attendance.A19,daily_attendance.A20,daily_attendance.A21,daily_attendance.A22,daily_attendance.A23,daily_attendance.A24,daily_attendance.A25,daily_attendance.A26,daily_attendance.A27,daily_attendance.A28,daily_attendance.A29,daily_attendance.A30 from daily_attendance join emp_details on emp_details.emp_id=daily_attendance.emp_id where emp_details.emp_id='%d' and daily_attendance.attend_month='%d'and attend_year='%d'");
	}
	else if(mm==2)
	{
		if(yy%400==0 ||(yy%4==0 && yy%100!=0))
		{
			strcpy(qry_id,"select emp_details.name1,emp_details.name2, daily_attendance.designation,daily_attendance.A1,daily_attendance.A2,daily_attendance.A3,daily_attendance.A4,daily_attendance.A5,daily_attendance.A6,daily_attendance.A7,daily_attendance.A8,daily_attendance.A9,daily_attendance.A10,daily_attendance.A11,daily_attendance.A12,daily_attendance.A13,daily_attendance.A14,daily_attendance.A15,daily_attendance.A16,daily_attendance.A17,daily_attendance.A18,daily_attendance.A19,daily_attendance.A20,daily_attendance.A21,daily_attendance.A22,daily_attendance.A23,daily_attendance.A24,daily_attendance.A25,daily_attendance.A26,daily_attendance.A27,daily_attendance.A28,daily_attendance.A29 from daily_attendance join emp_details on emp_details.emp_id=daily_attendance.emp_id where emp_details.emp_id='%d' and daily_attendance.attend_month='%d'and attend_year='%d'");
			days=29;
		}
		else
		{
			strcpy(qry_id,"select emp_details.name1,emp_details.name2, daily_attendance.designation,daily_attendance.A1,daily_attendance.A2,daily_attendance.A3,daily_attendance.A4,daily_attendance.A5,daily_attendance.A6,daily_attendance.A7,daily_attendance.A8,daily_attendance.A9,daily_attendance.A10,daily_attendance.A11,daily_attendance.A12,daily_attendance.A13,daily_attendance.A14,daily_attendance.A15,daily_attendance.A16,daily_attendance.A17,daily_attendance.A18,daily_attendance.A19,daily_attendance.A20,daily_attendance.A21,daily_attendance.A22,daily_attendance.A23,daily_attendance.A24,daily_attendance.A25,daily_attendance.A26,daily_attendance.A27,daily_attendance.A28 from daily_attendance join emp_details on emp_details.emp_id=daily_attendance.emp_id where emp_details.emp_id='%d' and daily_attendance.attend_month='%d'and attend_year='%d'");
			days=28;
		}
	}

	//char qry_id[]={"select emp_details.name1,emp_details.name2, daily_attendance.designation,daily_attendance.A%d from daily_attendance join emp_details on emp_details.emp_id=daily_attendance.emp_id where emp_details.emp_id='%d' and daily_attendance.attend_month='%d'and attend_year='%d'"};
    sprintf(stmt,qry_id,emp_id,mm,yy);

	if (mysql_query(conn3,stmt))
    {
        printf(" Error: %s\n", mysql_error(conn3));
        printf("Failed to execute query.");
    }
    else
    {
    	int i=0;
    	read = mysql_store_result(conn3);

        //printf("\nName |LName|Designation\n");
        row = mysql_fetch_row(read);
		num = mysql_num_fields(read);
		printf("|");
		printf("Name=%s\n",row[0]);
		printf("Last Name=%s\n",row[1]);
		printf("Designation=%s\n",row[2]);
		for(i = 3; i < num; i++)
        {
			printf("Date %d=%s\n",(i-2),row[i]);
	    }
	    printf("\n--------------------------------------------------------------------------------\n");
	}
}
//end of Attendance View function

// Attendance request change...


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
	mysql_real_connect(conn3, "localhost", "root", "1234","payroll", 3305, NULL, 0);
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
