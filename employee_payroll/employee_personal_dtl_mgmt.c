#include<windows.h>
#include<mysql.h>
MYSQL *conn3;
char query[1500];

char* update_employee(int emp_id)
{
	
	struct employee 
	{ 
       char address1[45];
       char address2[45];
       char phonenumber[20];
	   char gender[10];
	   char email[100];
	};
     
    struct employee emp;
	
	int i=0;
	char stmt[1500];
	printf("                Press 1 Address Line 1\n");
    printf("                Press 2 Address Line 2\n");
    printf("                Press 3 Phone Number\n");
    printf("                Press 4 Gender\n");
    printf("                Press 5 Email\n");
	printf("                Press 6 Exit\n");
	
	scanf("%d",&i);
	switch(i)
	    {
			case 1:
	    		{   int x=0; 
	    		    do
					{
					    printf("Enter address line 1\n");
	    			    gets(emp.address1);
						x=notempty(emp.address1);
					}while(x==0);
						
	    			char qry[]={"update emp_details set address_l1='%s' where emp_id='%d'"};
					if(conn3)
					{
					    sprintf(stmt,qry,emp.address1,emp_id);
		    			if(mysql_query(conn3,stmt))
		    			{	
		    			    printf(" Error: %s\n", mysql_error(conn3));
							return "Failed to execute query.";
						}
						else
						{
							return "\n\n\n\nUser modified successfully\n\n\n\n";
						}
					}
					else
					{
						printf("not connected");
						printf("%s\n", mysql_error(conn3));
					}
				break;
				}
				
			case 2:
	    		{
					int x=0; 
	    		    do
					{
					    printf("Enter address line 2\n");
	    			    gets(emp.address2);
						x=notempty(emp.address2);
					}while(x==0);
					
					char qry[]={"update emp_details set address_l2='%s' where emp_id='%d'"};
					if(conn3)
					{
					    sprintf(stmt,qry,emp.address2,emp_id);
		    			if(mysql_query(conn3,stmt))
		    			{	
		    			    printf(" Error: %s\n", mysql_error(conn3));
							return "Failed to execute query.";
						}
						else
						{
							return "\n\n\n\nUser modified successfully\n\n\n\n";
						}
					}
					else
					{
						printf("not connected");
						printf("%s\n", mysql_error(conn3));
					}
				break;
				}
				
			case 3:
	    		{
	    			int x=0;
					do
					{
					    printf("Please provide the phone number: \n");
	    			    scanf("%s",emp.phonenumber);
	    			    x=valid_phone(emp.phonenumber);
	    		    }while(x==0);
	    			    
	    			    
	    			char qry[]={"update emp_details set phonen='%s' where emp_id='%d'"};
					
					if(conn3)
					{
					    sprintf(stmt,qry,emp.phonenumber,emp_id);
		    			if(mysql_query(conn3,stmt))
		    			{	
		    			    printf(" Error: %s\n", mysql_error(conn3));
							return "Failed to execute query.";
						}
						else
						{
							return "\n\n\n\nUser modified successfully\n\n\n\n";
						}
					}
					else
					{
						printf("not connected");
						printf("%s\n", mysql_error(conn3));
					}
				break;
				}
				
			case 4:
	    		{
					printf("Enter gender Male,Female or Others\n");
	    			scanf("%s",emp.gender);
	    			char qry[]={"update emp_details set gender='%s' where emp_id='%d'"};
					if(conn3)
					{
					    sprintf(stmt,qry,emp.gender,emp_id);
		    			if(mysql_query(conn3,stmt))
		    			{	
		    			    printf(" Error: %s\n", mysql_error(conn3));
							return "Failed to execute query.";
						}
						else
						{
							return "\n\n\n\nUser modified successfully\n\n\n\n";
						}
					}
					else
					{
						printf("not connected");
						printf("%s\n", mysql_error(conn3));
					}
				break;
				}
			case 5:
	    		{   
	    		    int x=0;
					do{
						printf("Please provide the email: \n");
						scanf("%s",emp.email);
						x=valid_email(emp.email);
					}while(x==0);
	    			
	    			char qry[]={"update emp_details set email='%s' where emp_id='%d'"};
					if(conn3)
					{
					    sprintf(stmt,qry,emp.email,emp_id);
		    			if(mysql_query(conn3,stmt))
		    			{	
		    			    printf(" Error: %s\n", mysql_error(conn3));
							return "Failed to execute query.";
						}
						else
						{
							return "\n\n\n\nUser modified successfully\n\n\n\n";
						}
					}
					else
					{
						printf("not connected");
						printf("%s\n", mysql_error(conn3));
					}
			
				break;
				}	
	    }	
}
/*End Modifying employee function*/





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
			printf("%s",update_employee(emp_id));
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
