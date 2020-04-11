#include<stdio.h>
#include<windows.h>
#include<mysql.h>
#include "..\include\employee_personal_dtl_management.h"
MYSQL *conn3;


//Start of displaying a employee detail
void emp_display(char stmt[]){
	MYSQL_RES *read=NULL;
	MYSQL_RES *res=NULL;
	MYSQL_ROW row=NULL;
	MYSQL_FIELD *field;
	int num;

    if(conn3)
    {
        mysql_query(conn3,stmt);
		read = mysql_store_result(conn3);
        if (mysql_query(conn3,stmt))
        {
            printf(" Error: %s\n", mysql_error(conn3));
            printf("Failed to execute query.");
        }

        else
        {
        	while (row = mysql_fetch_row(read))
  			{
  				int num_fields;
				num_fields = mysql_num_fields(read);
	  			int i;
    			for(i = 0; i < num_fields; i++)
    			{
    			printf("|");
       		   	if (i == 0)
          		{
            		while(field = mysql_fetch_field(read))
  		          	{
        	    	printf("%s|", field->name);
            		}
	            	printf("\n");
          		}
				printf(" %s", row[i] ? row[i] : "NULL");
      			}
  			}

		printf("\n");
		}
    }

    else
    {
        printf("not connected");
        printf("%s\n", mysql_error(conn3));
    }

return;
}
//end of displaying a employee detail.


void emp_detail_mgmt(int emp_id)
{
	conn3=mysql_init(NULL);
	int id;
	mysql_real_connect(conn3, "localhost", "root", "1234","payroll", 3305, NULL, 0);
	int i;
	printf("                Press 1 Display employee details \n");
	printf("                Press 2 Update employee details\n");
	printf("                Press 3 View employee feedback\n");
	printf("                Press 4 Change password\n");
	scanf("%d",&i);
	switch (i)
	{
		case 1:
			{
				char stmt[1500];
            	char qry[] = {"select * from emp_details where emp_id = %d"};
            	int n = sprintf(stmt,qry,emp_id);
            	emp_display(stmt);
				break;
			}
		case 2:
			break;
		case 3:
			{
				char stmt[1500];
	           	char qry[] = {"select * from emp_perfor where emp_id = %d"};
    	        int n = sprintf(stmt,qry,emp_id);
        	    emp_display(stmt);
				break;
			}
		case 4:
		{
		    change_password(emp_id);
		    break;
		}
		default:
		    break;
	}
}
