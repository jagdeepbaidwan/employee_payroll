#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<mysql.h>
#include<stdlib.h>

MYSQL *connect7,*connect8;
char* leave_request(int emp_id,int dd,int mm,int yy,int no_of_days,char leave_type[]){
	MYSQL_RES *read=NULL;
    MYSQL_RES *res=NULL;
    MYSQL_ROW row=NULL;
    char stmt[1500];
    connect7=mysql_init(NULL);
	mysql_real_connect(connect7,"localhost", "root", "1234","payroll", 3306, NULL, 0);
	char status[15];
	
	char qry_leave_request[]={"insert into leave_request (emp_id,start_day,leave_month,leave_year,no_of_days,leave_type,status) values ('%d','%d','%d','%d','%d','%s','%s')"};
	strcpy(status,"Pending");

	if(connect7){
	    int n=sprintf(stmt,qry_leave_request,emp_id,dd,mm,yy,no_of_days,leave_type,status);
		if (mysql_query(connect7,stmt)){
   		    printf(" Error: %s\n", mysql_error(connect7));
   		    return "Failed to execute query.";
 	    }
 	    else{
 	    	return "Request raised successfully";
		}
    }
    return "Success";
}

char* view_pending_leave_requests(char status[]){
	MYSQL_RES *read=NULL;
	MYSQL_RES *res=NULL;
	MYSQL_ROW row=NULL;

	char stmt[1500];
	char qry_view_leave_req[]={"select * from leave_request where status='%s'"};
	connect8=mysql_init(NULL);
	mysql_real_connect(connect8, "localhost", "root", "1234","payroll", 3306, NULL, 0);

	if(connect8){
        int n=sprintf(stmt,qry_view_leave_req,status);
        mysql_query(connect8,stmt);
		read = mysql_store_result(connect8);
        if (mysql_query(connect8,stmt)){
            printf(" Error: %s\n", mysql_error(connect8));
            printf("Failed to execute query.");
        }
		else{
            int i=0;
            int num=0;
            printf("\n");
            printf("REQ_ID  |	EMP_ID	|   START_DAY   |   LEAVE_MONTH |  LEAVE_YEAR   |   NO_OF_DAYS  |  Leave_Type  |	STATUS");
            printf("\n");
			printf("\n");
			while((row = mysql_fetch_row(read))){
            	num = mysql_num_fields(read);
            	for(i = 0; i < num; i++){
                    printf("%s ", row[i]);
                    printf("	|	");
                }
                printf("\n");
			}
        }
    }
    else{
    	printf("not connected");
        printf("%s\n", mysql_error(connect8));
	}
return "\n\n\nRequests displayed successfully";
}
