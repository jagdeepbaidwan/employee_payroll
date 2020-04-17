#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<mysql.h>
#include<stdlib.h>
int port10=3306;
MYSQL *connect7,*connect8,*connect9,*connect10,*connect2,*connect1;
char* leave_request(int emp_id,int dd,int mm,int yy,int no_of_days,char leave_type[]){
	MYSQL_RES *read=NULL;
    MYSQL_RES *res=NULL;
    MYSQL_ROW row=NULL;
    char stmt[1500];
    connect7=mysql_init(NULL);
	mysql_real_connect(connect7,"localhost", "root", "1234","payroll", port10, NULL, 0);
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
	mysql_real_connect(connect8, "localhost", "root", "1234","payroll", port10, NULL, 0);

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

char* decision_leave_request(req_id)
{
	int k;
	printf("\n");
	printf("-------------------------Press 1: To Approve----------------------\n");
	printf("-------------------------Press 2: To Reject----------------------\n");
	scanf("%d",&k);

	switch(k)
	{
		case 1:
		{

			MYSQL_RES *read=NULL;
			MYSQL_RES *res=NULL;
			MYSQL_ROW row=NULL;
			int remaining=0;
			int balance_ML=0;
			int balance_PL=0;
			char stmt[1500];
			char qry_decision[]={"select * from leave_request where request_id='%d'"};
			connect9=mysql_init(NULL);
			mysql_real_connect(connect9, "localhost", "root", "1234","payroll", port10, NULL, 0);

			if(connect9){
		        int n=sprintf(stmt,qry_decision,req_id);
		        mysql_query(connect9,stmt);
				read = mysql_store_result(connect9);
		        if (mysql_query(connect9,stmt)){
		            printf(" Error: %s\n", mysql_error(connect9));
		            printf("Failed to execute query.");
		        }
				else{
					row = mysql_fetch_row(read);
		            int no_of_days=atoi(row[5]);
		            int year=atoi(row[4]);
		            int emp_id=atoi(row[1]);
					char leave_type[20];
					strcpy(leave_type,row[6]);
					printf("\n");

					char qry_retrieve_leaves[]={"select * from leave_details where Emp_id='%d' and Leave_year='%d'"};
					connect10=mysql_init(NULL);
					mysql_real_connect(connect10, "localhost", "root", "1234","payroll", port10, NULL, 0);

					if(connect10){
						int n=sprintf(stmt,qry_retrieve_leaves,emp_id,year);
		        		mysql_query(connect10,stmt);
						read = mysql_store_result(connect10);
		        		if (mysql_query(connect10,stmt)){
		            		printf(" Error: %s\n", mysql_error(connect10));
		            		printf("Failed to execute query.");
						}
						else{
						row = mysql_fetch_row(read);
						balance_ML=atoi(row[5]);
						balance_PL=atoi(row[6]);
						}
					printf("\n");
					}
					else{
		    			printf("not connected");
		        		printf("%s\n", mysql_error(connect8));
		        	}

		        	if(strcmp(leave_type,"ML")==0){
		        		if(balance_ML>no_of_days){
		        			balance_ML=balance_ML-no_of_days;
						}
		        		else{
		        			remaining=no_of_days-balance_ML;
							balance_ML=0;
							if(balance_PL>remaining){
								balance_PL=balance_PL-remaining;
							}
							else{
								balance_PL=0;
							}
						}
					}

					else if(strcmp(leave_type,"PL")==0){
						if(balance_PL>no_of_days){
							balance_PL=balance_PL-no_of_days;
						}
						else{
							balance_PL=0;
						}
					}

					char qry_update_balance[]={"update leave_details set Balance_ML='%d',Balance_PL='%d' where Emp_id='%d'"};
					connect2=mysql_init(NULL);
					mysql_real_connect(connect2, "localhost", "root", "1234","payroll", port10, NULL, 0);
					if(connect2){
	    				int n=sprintf(stmt,qry_update_balance,balance_ML,balance_PL,emp_id);
						if (mysql_query(connect2,stmt)){
   		    				printf(" Error: %s\n", mysql_error(connect2));
   		   					printf("Failed to execute query.");
 	   					}
 	   				else{
 	   					printf("Leave balance updated successfully\n");
						}
    				}

    				char status[20]="Approved";
    				char qry_status_update[]={"update leave_request set status='%s' where emp_id='%d'"};
					connect1=mysql_init(NULL);
					mysql_real_connect(connect1, "localhost", "root", "1234","payroll", port10, NULL, 0);
					if(connect1){
	    				int n=sprintf(stmt,qry_status_update,status,emp_id);
						if (mysql_query(connect1,stmt)){
   		    				printf(" Error: %s\n", mysql_error(connect1));
   		   					printf( "Failed to execute query.");
   		   					break;
 	   					}
 	   				else{
 	   					printf("Leave request status updated successfully\n");
 	   					break;
						}
    				break;
					}
				break;
				}
		    break;
			}

		else{
		    printf("not connected");
		    printf("%s\n", mysql_error(connect8));
		}
		break;
	}
	case 2:{
			MYSQL_RES *read=NULL;
			MYSQL_RES *res=NULL;
			MYSQL_ROW row=NULL;
			char stmt[1500];
			char qry_decision[]={"select * from leave_request where request_id='%d'"};
			connect9=mysql_init(NULL);
			mysql_real_connect(connect9, "localhost", "root", "1234","payroll", port10, NULL, 0);

			if(connect9){
		        int n=sprintf(stmt,qry_decision,req_id);
		        mysql_query(connect9,stmt);
				read = mysql_store_result(connect9);
		        if (mysql_query(connect9,stmt)){
		            printf(" Error: %s\n", mysql_error(connect9));
		            printf("Failed to execute query.");
		        }
				else{
					row = mysql_fetch_row(read);
		            int emp_id=atoi(row[1]);

		            char status[20]="Rejected";
    				char qry_status_update[]={"update leave_request set status='%s' where emp_id='%d'"};
					connect1=mysql_init(NULL);
					mysql_real_connect(connect1, "localhost", "root", "1234","payroll", port10, NULL, 0);
					if(connect1){
	    				int n=sprintf(stmt,qry_status_update,status,emp_id);
						if (mysql_query(connect1,stmt))
						{
   		    				printf(" Error: %s\n", mysql_error(connect1));
   		   					printf("Failed to execute query.");
 	   					}
						else{
 	   					printf("Status Updated successfully");
						}
					}
					else{
		    			printf("not connected");
		    			printf("%s\n", mysql_error(connect8));
					}
				}

			break;
		}
		else{
		    printf("not connected");
		    printf("%s\n", mysql_error(connect9));
		}

}
	return "Success";
}
}
