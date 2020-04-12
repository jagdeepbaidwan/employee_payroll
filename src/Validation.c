#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<mysql.h>
#include <stdlib.h>
#include<time.h>
#include<ctype.h>
#include "..\include\Validation.h"
MYSQL *conn9;
char query[1500];


char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

int validate_attendance(char attnd[4],int yy, int emp_id)
{
	MYSQL_RES *read=NULL;
	MYSQL_RES *res2=NULL;
	MYSQL_ROW row=NULL;
	conn9=mysql_init(NULL);
	//int id;
	mysql_real_connect(conn9, "localhost", "root", "1234","payroll", 3305, NULL, 0);
	if(!conn9)
	{
		printf("Connection error");
		return 0;
	}
	attnd=rtrim(attnd);
	if(strcmp(attnd,"L")==0 || strcmp(attnd,"PHL")==0 || strcmp(attnd,"ML")==0 || strcmp(attnd,"PL")==0 || strcmp(attnd,"LWP")==0 || strcmp(attnd,"WOFF")==0 || strcmp(attnd,"A")==0 || strcmp(attnd,"P")==0)
	{
		if(strcmp(attnd,"ML")==0 )
		{
			char qry_id[]={"select * from leave_details where leave_year='%d' and emp_id=%d"};
			sprintf(query,qry_id,yy,emp_id);
			if (mysql_query(conn9,query))
    		{
		        printf(" Error: %s\n", mysql_error(conn9));
		        printf("Failed to execute query.");
    		}
    		else
    		{
    			res2=mysql_store_result(conn9);
        		row = mysql_fetch_row(res2);
        		int l_balance=atoi(row[5]);
        		if(l_balance==0)
        		{
        			printf("Employee=%d has no medical leave. Please add some leaves\n",emp_id);
        			return 2;
				}
				else
				{
					l_balance=l_balance-1;
					char qry_id[]={"update leave_details set balance_ML='%d' where leave_year='%d' and emp_id=%d"};
					sprintf(query,qry_id,l_balance,yy,emp_id);
					if (mysql_query(conn9,query))
    				{
		        		printf(" Error: %s\n", mysql_error(conn9));
		        		printf("Failed to execute query.");
    				}
				}
    		}
			//printf("%s",attnd);
			return 1;
		}
		if(strcmp(attnd,"PL")==0)
		{
			char qry_id[]={"select * from leave_details where leave_year='%d' and emp_id=%d"};
			sprintf(query,qry_id,yy,emp_id);
			if (mysql_query(conn9,query))
    		{
		        printf(" Error: %s\n", mysql_error(conn9));
		        printf("Failed to execute query.");
    		}
    		else
    		{
    			res2=mysql_store_result(conn9);
        		row = mysql_fetch_row(res2);
        		int l_balance=atoi(row[6]);
        		if(l_balance==0)
        		{
        			printf("Employee=%d has no paid leave. Please add some leaves\n",emp_id);
        			return 2;
				}
				else
				{
					l_balance=l_balance-1;
					char qry_id[]={"update leave_details set balance_PL='%d' where leave_year='%d' and emp_id=%d"};
					sprintf(query,qry_id,l_balance,yy,emp_id);
					if (mysql_query(conn9,query))
    				{
		        		printf(" Error: %s\n", mysql_error(conn9));
		        		printf("Failed to execute query.");
    				}
				}
    		}
			//printf("%s",attnd);
			return 1;
		}
		else
		{
			return 1;
		}

	}
	else
	{
		return 0;
	}
}
int validate_current_month(int dd, int mm, int yy)
{
	int month, year;
	time_t now;
	time(&now);
	//printf("Today is : %s", ctime(&now));
	struct tm *local = localtime(&now);
	month = local->tm_mon + 1;   	// get month of year (0 to 11)
    year = local->tm_year + 1900;	// get year since 1900
    if( (mm== month || mm == month-1) && yy == year)
    {

    	if((dd>=1 && dd<=31) && (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12))
            {
            	return 1;
			}
            else if((dd>=1 && dd<=30) && (mm==4 || mm==6 || mm==9 || mm==11))
            {
            	return 1;
			}
            else if((dd>=1 && dd<=28) && (mm==2))
            {
            	return 1;
			}
            else if(dd==29 && mm==2 && (yy%400==0 ||(yy%4==0 && yy%100!=0)))
            {
            	return 1;
			}
            else
            {
            	printf("Day is invalid.\n");
            	return 0;
			}
	}
	else
	{
		printf("\nPlease choose current month and year\n");
		return 0;
	}
}

int validate_date(int dd,int mm,int yy)
{
	if(yy>=1900 && yy<=9999)
    {
        //check month
        if(mm>=1 && mm<=12)
        {
            //check days
            if((dd>=1 && dd<=31) && (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12))
            {
            	return 1;
			}
            else if((dd>=1 && dd<=30) && (mm==4 || mm==6 || mm==9 || mm==11))
            {
            	return 1;
			}
            else if((dd>=1 && dd<=28) && (mm==2))
            {
            	return 1;
			}
            else if(dd==29 && mm==2 && (yy%400==0 ||(yy%4==0 && yy%100!=0)))
            {
            	return 1;
			}
            else
            {
            	printf("Day is invalid.\n");
            	return 0;
			}

        }
        else
        {
            printf("Month is not valid.\n");
            return 0;
        }
    }
    else
    {
        printf("Year is not valid.\n");
    }
}


int valid_phone(char phone[])
{
	if(strlen(phone)!=10)
	{
		printf("Invalid phone number\n");
		return 0;
	}
	else{
		int i;
		for(i=0; i<strlen(phone);i++)
		{
			if(isalpha(phone[i]) != 0)
			{
				printf("Invalid phone number\n");
				return 0;

			}
		}
		return 1;
	}
}

int notempty(char num[] )
{

	if(strlen(num)<=1)
	{
		//printf("hello");
		printf("Invalid value\n");
		return 0;
	}
	return 1;

}
int valid_email(char test[])
{
    int     i;
    char    *pos1, *pos2;
    char    *ch;
	while (1)
	{
        for (i = 0, ch = test; *ch; *ch++)
		{
            if (*ch == '@')
			{
                pos1 = ch;  // <-stores last @ address
                i++;
            }
        }
            pos2 = ch;          // <-stores end address ("\0") of test

        /* If there is only one "@" */
        if (i == 1)
		{
            while (pos1 - test && ch - pos1 > 1) {

                /* From the end of string to "." has to be atleast 2 chars */
                if ((pos2 - ch) > 2 && *ch == '.') {
                    //printf("pos2 - ch is %d and *ch is %c",pos2 - ch, *ch);
                    return 1;
                }
                ch--;
            }
        }
        printf("Email wrong!\n");
        return 0;

    } /* End while */

    return 1;
}

int isleap(int y) {
   if((y % 4 == 0) && (y % 100 != 0) && (y % 400 == 0))
   {
   	 return 1;
   }

   else
   {
   	return 0;
   }

}

int datevalid(int d, int m, int y) {
   if(y < 1800 || y > 9999)
      return 0;
   if(m < 1 || m > 12){
   	printf("Invalid month\n");
   	return 0;
   }

   if(d < 1 || d > 31){
   	printf("Invalid day\n");
      return 0;
  }

   if( m == 2 )
   {
        if(isleap(y))
	    {
        	if(d <= 29)
        		return 1;
        	else
        	{
        		printf("Invalid day\n");
   	    		return 0;
			}

    	}
	}
  if ( m == 4 || m == 6 || m == 9 || m == 11 )
  {
  		if(d <= 30)
            return 1;
        else
        {
         	printf("Invalid day\n");
		    return 0;
		}
            return 1;
  }

}

