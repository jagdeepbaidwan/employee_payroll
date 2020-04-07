#include<stdio.h>
#include<windows.h>
#include<mysql.h>
#include "..\include\employee_personal_dtl_management.h"
MYSQL *conn3;
char query[1500];


void emp_detail_mgmt(int emp_id)
{
	conn3=mysql_init(NULL);
	int id;
	mysql_real_connect(conn3, "localhost", "root", "1234","payroll", 3306, NULL, 0);
	int i;
	printf("                Press 1 Display employee details \n");
	printf("                Press 2 Update employee details\n");
	printf("                Press 3 View employee feedback\n");
	printf("                Press 4 Change password\n");
	scanf("%d",&i);
	switch (i)
	{
		case 1:
	    	break;
		case 2:
			break;
		case 3:
			break;
		case 4:
		{
		    change_password(emp_id);
		    break;
		}
		default:
		    break;
	}
}
