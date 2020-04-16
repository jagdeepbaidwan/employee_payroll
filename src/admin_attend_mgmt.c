#include<windows.h>
#include<mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "..\include\Validation.h"
#include "..\include\attendance_display.h"
MYSQL *conn4;
char query[1500];

// Check record availability in attendance
int port1=3305;
int attendance_month_availability(int mm, int yy)
{
	MYSQL_RES *read=NULL;
	MYSQL_RES *res2=NULL;
	MYSQL_ROW row=NULL;
	char qry_id[]={"select * from daily_attendance where attend_month='%d' and attend_year='%d'"};
	sprintf(query,qry_id,mm,yy);
	if (mysql_query(conn4,query))
    {

        printf(" Error: %s\n", mysql_error(conn4));
        printf("Failed to execute query.");
    }
    else
    {
    	res2=mysql_store_result(conn4);
        row = mysql_fetch_row(res2);
        int count_row = mysql_num_rows(res2);

        if(count_row>1)
        {
        	return 1;
		}
		else
		{
			printf("Month is not present in the database");

			return 0;
		}
	}
}
//Attendance Update Function

void update_attendance()
{
	MYSQL_RES *read=NULL;
	MYSQL_RES *res=NULL;
	MYSQL_ROW row=NULL;
	int emp_id;
	int x=0;
	int dd,mm,yy;
	int r;
	int t;
	char stmt[1500];
	do
	{
		t=0;
		printf("\nEnter the employee Id to update the attendance\n");
		scanf("%d",&emp_id);
		char qry_id1[]={"select * from emp_details where emp_id=%d"};
		sprintf(stmt,qry_id1,emp_id);
		if (mysql_query(conn4,stmt))
    	{
	        printf(" Error: %s\n", mysql_error(conn4));
	        printf("Failed to execute query.");
	    }
	    else
	    {
	    	read = mysql_store_result(conn4);
    		row = mysql_fetch_row(read);
    		if(row==NULL)
    		{
    			printf("No Such Employee ID found\n");
    			t=0;
    		}
    		else
    		{
    			t=1;
			}
	    }


	}while(t!=1);
	do
	{
		printf("\nEnter the attendance date:Format(dd/mm/yyyy)");
		scanf("%d/%d/%d",&dd,&mm,&yy);
		r=validate_date(dd,mm,yy);
	}while(r!=1);
	char new_att[4];
	r=0;
	do
	{
		printf("\nEnter the employee attendance (read mannual regarding format) (Format: P/A/SL/PL/PHL)\n");
		scanf("%s",new_att);
		r=validate_attendance(new_att,yy,emp_id);
	}while(r!=1);

	char qry_id[]={"update daily_attendance set A%d='%s' where attend_month='%d' and attend_year='%d' and emp_id=%d"};
	sprintf(query,qry_id,dd,new_att,mm,yy,emp_id);
	//printf("\n%s",query);
	if (mysql_query(conn4,query))
    {
       	printf(" Error: %s\n", mysql_error(conn4));
       	printf("Failed to execute query.");
    }
    else
    {
    	printf("\nUpdated attendance of employee:%d",emp_id);
	}
}
//End of update attendance Function

void add_attendance()
{
	int emp[1000],lp=0,ff;
	struct attendance
	{
		int emp_att_id;
		char *emp_dept;
		char *emp_desig;
		char att[5];
	};
	struct attendance attnd[150];
	char buffer[1024] ;
    char *record,*line;
    int i=0,j=0,x=0;
    int mat[100][100];
    FILE *fstream = fopen("myFile.csv","r");
    if(fstream == NULL)   {
       printf("\n file opening failed ");
       //return -1 ;
    }
    while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL)
    {
		record = strtok(line,";");
		while(record != NULL)
			{
				char *ptr=strtok(record,",");
				attnd[x].emp_att_id=atoi(ptr);
				ptr = strtok(NULL, ",");
				attnd[x].emp_dept=ptr;
				ptr = strtok(NULL, ",");
				attnd[x].emp_desig=ptr;
				ptr = strtok(NULL, ",");
				strcpy(attnd[x].att,ptr);
				x++;
				mat[i][j++] = atoi(record) ;
			 	record = strtok(NULL,";");
			}
		++i ;
	}
	int tmp=0;
	int dd,mm,yy;
	int r;
	do
	{
		printf("\nEnter the attendance date of file:");
		scanf("%d/%d/%d",&dd,&mm,&yy);
		r=validate_date(dd,mm,yy);
		int rr;
		rr=attendance_month_availability(mm,yy);

		if(rr==0)
		{
			//printf("Hello");
			r=0;
		}
	}while(r!=1);
	int err=0;
	while(tmp<x)
	{
		char qry_id[]={"update daily_attendance set A%d='%s' where attend_month='%d' and attend_year='%d' and emp_id=%d"};
		int v=validate_attendance(attnd[tmp].att,yy,attnd[tmp].emp_att_id);
		if(v==1)
		{
			err=0;
			sprintf(query,qry_id,dd,attnd[tmp].att,mm,yy,attnd[tmp].emp_att_id);
			if (mysql_query(conn4,query))
	    	{
	        	printf(" Error: %s\n", mysql_error(conn4));
	        	printf("Failed to execute query.");
	    	}
	    	else
	    	{
	    		printf("\nUpdated attendance of employee:%d",attnd[tmp].emp_att_id);
			}
		}
		else if(v==2)
		{

			emp[lp] = attnd[tmp].emp_att_id;
			lp=lp+1;
		}
		else
		{
			err=1;
			break;
		}
		tmp++;
	}
	if(err==1)
		{
			printf("%s",attnd[tmp].att);
			printf("Attendance problem. Please check all attendance MARKERS");
		}
	for(ff=0;ff<lp;ff++)
	{
		printf("\nAttendance of following employees were not added\n");
		printf("%d\n",emp[ff]);
	}
}

//hourly_attendance function
void hourly_attendance()
{
    char response[55];
	MYSQL_RES *read=NULL, *res2;
	MYSQL_RES *res=NULL;
	MYSQL_ROW row=NULL, *row1=NULL, *row2=NULL;
	int num,u;
	int emp[1000],lp=0,ff;
	struct attendance
	{
		int emp_att_id;
		char in_time[12];
		char out_time[12];
		char t_hours[5];
	};
	struct attendance attnd[150];
	char buffer[1024] ;
    char *record,*line;
    int i=0,j=0,x=0;
    int mat[100][100];
    FILE *fstream = fopen("Attend.csv","r");
    if(fstream == NULL)   {
       printf("\n file opening failed ");
       //return -1 ;
    }
    while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL)
    {
		record = strtok(line,";");
		while(record != NULL)
			{

				char *ptr=strtok(record,",");
				attnd[x].emp_att_id=atoi(ptr);
				ptr = strtok(NULL, ",");
				strcpy(attnd[x].in_time,ptr);
				ptr = strtok(NULL, ",");
				strcpy(attnd[x].out_time,ptr);
				ptr = strtok(NULL, ",");
				strcpy(attnd[x].t_hours,ptr);
				x++;
				mat[i][j++] = atoi(record) ;
			 	record = strtok(NULL,";");
			}
		++i ;
	}
	int tmp=0;
	int dd,mm,yy;
	int r;
	do
	{
		printf("\nEnter the attendance date of file:");
		scanf("%d/%d/%d",&dd,&mm,&yy);
		r=validate_date(dd,mm,yy);
	}while(r!=1);
	while(tmp<x)
	{
		char qry_id1[]={"select *from hourly_attendance where emp_id='%d' and att_day='%d' and att_month='%d' and att_year='%d'"};
		sprintf(query,qry_id1,attnd[tmp].emp_att_id,dd,mm,yy);

		if (mysql_query(conn4,query))
	    {
	       	printf(" Error: %s\n", mysql_error(conn4));
	       	printf("Failed to execute query.");
	    }
	    else
	    {
	    	res2=mysql_store_result(conn4);
        	row = mysql_fetch_row(res2);
        	int count_row = mysql_num_rows(res2);
	        if(count_row>=1)
	        {
	        	strcpy(response,"Attendance is already in the database\n");
			}
			else
			{
				char qry_id[]={"insert into hourly_attendance (emp_id,att_day,att_month,att_year,in_time,out_time,days) values ('%d','%d','%d','%d','%s','%s','%s')"};
				sprintf(query,qry_id,attnd[tmp].emp_att_id,dd,mm,yy,attnd[tmp].in_time,attnd[tmp].out_time,attnd[tmp].t_hours);
				if (mysql_query(conn4,query))
	    		{
		        	printf(" Error: %s\n", mysql_error(conn4));
		        	printf("Failed to execute query.");
		    	}
		    	else
		    	{
		    	    strcpy(response,"");
		    		printf("\nAdded attendance of employee:%d",attnd[tmp].emp_att_id);
				}
			}
	    }
		tmp=tmp+1;
	}
	printf("%s",response);
}
//End Hourly attendance function



void new_month()
{

	MYSQL_RES *read=NULL, *res2;
	MYSQL_RES *res=NULL;
	MYSQL_ROW row=NULL, *row1=NULL, *row2=NULL;
	int num,u;
	int att_mnth,att_year;
	int r=0;
	do
    {
        printf("Enter the attendance year\n");
        scanf("%d",&att_year);
        r=validate_date(01,01,att_year);
    }while(r!=1);
    r=0;
    do
    {
        printf("Enter the month\n");
        scanf("%d",&att_mnth);
        r=validate_date(01,att_mnth,2020);
    }while(r!=1);

	char qry_id[]={"select * from daily_attendance where attend_month='%d' and attend_year='%d'"};
	sprintf(query,qry_id,att_mnth,att_year);

	if (mysql_query(conn4,query))
    {

        printf(" Error: %s\n", mysql_error(conn4));
        printf("Failed to execute query.");
    }
    else
    {
    	res2=mysql_store_result(conn4);
        row = mysql_fetch_row(res2);
        int count_row = mysql_num_rows(res2);

        if(count_row>=1)
        {
        	printf("This Month is already in the database");
		}
		else
		{
			char emp_qry[]={"select *from emp_details inner join login_details on emp_details.emp_id=login_details.emp_id where login_details.status='A'"};
        	if (mysql_query(conn4,emp_qry))
        	{
        		printf(" Error: %s\n", mysql_error(conn4));
        		printf("Failed to execute query.");
			}
			else
			{

				res=mysql_store_result(conn4);
				int i=0;
            	while((row1 = mysql_fetch_row(res)))
            	{
            			num = mysql_num_fields(res);
                    	char att_qry[]={"insert into daily_attendance (emp_id,department,designation,attend_month,attend_year) values('%d','%s','%s','%d','%d')"};
                    	sprintf(query,att_qry,(int)row1[0],row1[3],row1[4],att_mnth,att_year);
                        if(mysql_query(conn4,query))
                        {
                        	printf(" Error: %s\n", mysql_error(conn4));
        					printf("Failed to execute query.");
						}
				}
				printf("\n\n\n Attendance month created in the data base\n\n");
			}
		}
    }
}
void attend_mgmt(int ch)
{
	conn4=mysql_init(NULL);
	int id;
	mysql_real_connect(conn4, "localhost", "root", "1234","payroll", port1, NULL, 0);
	if(!conn4)
	{
		printf("Connection error");
	}
	else
	{
		switch(ch)
		                {
		                	case 1:
		                		{
		                			new_month();
		                			break;
								}
		                	case 2:
		                		{
		                			printf("		Enter 1 to enter hourly employee attendance\n");
		                			printf("		Enter 2 to enter salaried employee attendance\n");
		                			int choi;
		                			scanf("%d",&choi);
		                			if(choi==1)
		                			{
		                				hourly_attendance();
									}
									else if(choi==2)
									{
										add_attendance();
									}
									else
									{
										printf("Wrong choice");
									}
		                			break;
								}
		                	case 3:
		                		{
		                			printf("Please specify the employee_id for the attendance display: ");
		                			scanf("%d",&id);
		                			view_attendance(id);
		                			break;
								}
							case 4:
								{
                                    update_attendance();
									break;
								}
		                	default:
		                		{
		                			printf("Wrong input");
		                			break;
		                		}
						}

	}
}
