#include<windows.h>
#include<mysql.h>
MYSQL *conn3;
char query[1500];



void change_password(int id)
{
	char old_pass[40],new_pass[40],confirm_pass[40];
		    printf("\nEnter old password\n");
		    int p=0; 
    		do{ 
       			old_pass[p]=getch(); 
                if(old_pass[p]!='\r')
				{ 
                    printf("*"); 
                } 
                p++; 
            }while(old_pass[p-1]!='\r'); 
            old_pass[p-1]='\0'; 
		    //scanf("%s",old_pass);
		    printf("\nEnter new password\n");
			p=0; 
    		do{ 
       			new_pass[p]=getch(); 
                if(new_pass[p]!='\r')
				{ 
                    printf("*"); 
                } 
                p++; 
            }while(new_pass[p-1]!='\r'); 
            new_pass[p-1]='\0'; 
		    //scanf("%s",new_pass);
		    //gets(new_pass);
		    printf("\nConfirm new password\n");
		    p=0; 
    		do{ 
       			confirm_pass[p]=getch(); 
                if(confirm_pass[p]!='\r')
				{ 
                    printf("*"); 
                } 
                p++; 
            }while(confirm_pass[p-1]!='\r'); 
            confirm_pass[p-1]='\0';
		    //scanf("%s",confirm_pass);
			//gets(confirm_pass);
			printf("%s\n",change_pass(id,new_pass,confirm_pass,old_pass));
}

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
