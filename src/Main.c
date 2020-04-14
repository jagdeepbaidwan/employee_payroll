#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<mysql.h>
#include<string.h>
#include <termios.h>
#include <unistd.h>
#include "..\include\employee_management.h"
#include "..\include\employee.h"
#include "..\include\manager_dept_management.h"
#include "..\include\employee_personal_dtl_management.h"
#include "..\include\employee.h"

MYSQL *oo,*conn,*conn4;
MYSQL_RES *read1=NULL;
MYSQL_RES *res=NULL;
MYSQL_ROW row=NULL;
int port8=3306;
/*
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
}*/


char* login(int id, char pwd[25])
{
	char stmt[1500];
	char qry[]={"select * from login_details where emp_id='%d'and password='%s'"};
	oo=mysql_init(NULL);
	mysql_real_connect(oo, "localhost", "root", "1234","payroll", port8, NULL, 0);
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
                if((pwd[p]=='\b' ||pwd[p]==127)&& p>0)
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

    else if(strcmp("employee",user_type)==0){
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
                printf("                Press 1 Display personal details \n");
                printf("                Press 2 Update details\n");
                printf("                Press 3 Change password\n");
                scanf("%d",&i);
                switch (i)
                {
                    case 1:
                    break;
                    case 2:
		    {
			 printf("%s",update_employee(id));
                         break;
		    }
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
            	int i;
                printf("                Press 1 Request leave\n");
                printf("                Press 2 Display leaves\n");
                
				scanf("%d",&i);
				switch(i){	
				case 1:{
	    			break;
				}
				case 2:{
					display_leaves(id);
					break;
				}
				break;
				}
                break;
            }

            case 4:{
                int i=display_salary(id);
                break;
            }

            case 5:{
                printf("                Press 1 Raise Grievance\n");
                printf("%s",raise_grievances(id));
                break;
            }

            case 6:{
                int j=0;
                printf("                Press 1 Request Employee\n");
                printf("                Press 2 Rate employee\n");
                printf("                Press 3 Display employee rating \n");
                scanf("%d",&j);

                switch(j){
                    case 1:{
                        char stmt[1500];
                        char dept[10];
                        conn4=mysql_init(NULL);
                        mysql_real_connect(conn4, "localhost", "root", "1234","payroll", port8, NULL, 0);
                        char qry_dep[]={"select department from emp_details where emp_id='%d'"};
                        if(conn4){
                            int n=sprintf(stmt,qry_dep,id);
                            mysql_query(conn4,stmt);
                            read1=mysql_store_result(conn4);
                            row=mysql_fetch_row(read1);
                            strcpy(dept,row[0]);
                            printf("%s",employee_request(id,dept));
                        }else{
                            printf("not connected");
                            printf("%s\n", mysql_error(oo));
                        }

                        break;
                    }

					case 2:
		            {
		               	printf("%s",employee_rating());
		               	break;
					}

                    case 3:
                    {
	    	        	char stmt[1500];
    	    		    char qry[] = {"select * from emp_perfor where emp_id = %d"};
			            int n = sprintf(stmt,qry,id);
            			emp_display(stmt);
            			break;
					}

            		default:{
                		printf("Wrong Input");
                		break;
            		}
                	break;
            	}
            }
        }
    }

    else{
        printf("Have a Good Day!");
    }

    return 0;
}


