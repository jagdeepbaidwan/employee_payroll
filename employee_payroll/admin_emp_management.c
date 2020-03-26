#include<windows.h>
#include<mysql.h>
#include<stdlib.h>
MYSQL *conn2, *oo1;
char query[1500];
char* modify_employee(int);

//Start of displaying employee detail
void emp_display_details(int case_type){
	MYSQL_RES *read=NULL;
	MYSQL_RES *res=NULL;
	MYSQL_ROW row=NULL;
	int num;
	
	char stmt[1500];
    char qry_id[]={"select * from emp_details where emp_id='%d'"};
	char qry_dep[] ={"select * from emp_details where department='%s'"};
	char qry_des[] ={"select * from emp_details where designation='%s'"};
	char qry_all[] = {"select * from emp_details"};
    int emp_id;
    char emp_depart_display[50];
    char emp_desig_display[50];
    char data[20];


    switch(case_type)
    {
    case 1:
        {
        printf("Enter the employee id: ");
        scanf("%d",&emp_id);
    	if(conn2)
        {
            int n=sprintf(stmt,qry_id,emp_id);
            mysql_query(conn2,stmt);
			read = mysql_store_result(conn2);
            if (mysql_query(conn2,stmt))
            {
                printf(" Error: %s\n", mysql_error(conn2));
                printf("Failed to execute query.");
            }

            else
            {
            	int i=0;
				row = mysql_fetch_row(read);
                
                num = mysql_num_fields(read);
               	printf("|");
				for(i = 0; i < num; i++)
                    {
                        printf("%s|", row[i]);
                    }
                printf("\n");
            }
        }

        /*mysql_free_result(read);*/
        else
        {
            printf("not connected");
            printf("%s\n", mysql_error(conn2));
        }
        break;
        }

    case 2:
        {
        	
        printf("\nEnter the department: ");
        scanf("%s",emp_depart_display);

    	if(conn2)
        {
            int n=sprintf(stmt,qry_dep,emp_depart_display);
            mysql_query(conn2,stmt);
			read = mysql_store_result(conn2);
            if (mysql_query(conn2,stmt))
            {
                printf(" Error: %s\n", mysql_error(conn2));
                printf("Failed to execute query.");
            }

            else
            {
            	int i=0;
            	while((row = mysql_fetch_row(read)))
            	{
            		num = mysql_num_fields(read);
            		for(i = 0; i < num; i++)
                    {
                        printf("%s ", row[i]);
                    }
                    printf("\n");
				}
            }
        }

        /*mysql_free_result(read);*/
        else
        {
            printf("not connected");
            printf("%s\n", mysql_error(conn2));
        }
        break;
        }

    case 3:
        {
        	
        printf("\nEnter the designation: ");
        scanf("%s",emp_desig_display);

    	if(conn2)
        {
            int n=sprintf(stmt,qry_des,emp_desig_display);
            mysql_query(conn2,stmt);
			read = mysql_store_result(conn2);
            if (mysql_query(conn2,stmt))
            {
                printf(" Error: %s\n", mysql_error(conn2));
                printf("Failed to execute query.");
            }

            else
            {
            	int i=0;
            	while((row = mysql_fetch_row(read)))
            	{
            		num = mysql_num_fields(read);
            		for(i = 0; i < num; i++)
                    {
                        printf(" |%s| ", row[i]);
                    }
                    printf("\n");
				}
            }
        }

        /*mysql_free_result(read);*/
        else
        {
            printf("not connected");
            printf("%s\n", mysql_error(conn2));
        }
        break;
        }

    case 4:
        {
        	
    	if(conn2)
        {
            int n=sprintf(stmt,qry_all);
            mysql_query(conn2,stmt);
			read = mysql_store_result(conn2);
            if (mysql_query(conn2,stmt))
            {
                printf(" Error: %s\n", mysql_error(conn2));
                printf("Failed to execute query.");
            }

            else
            {
            	int i=0;
            	while((row = mysql_fetch_row(read)))
            	{
            		num = mysql_num_fields(read);
            		for(i = 0; i < num; i++)
                    {
                        printf("%s ", row[i]);
                    }
                    printf("\n");
				}
            }
        }

        /*mysql_free_result(read);*/
        else
        {
            printf("not connected");
            printf("%s\n", mysql_error(conn2));
        }
        break;
        }

    default:
    {
        printf("Inavalid Input");
        break;
    }

    }
return;
}


//end of employee displaying function of 

//start of  adding a new employee
char* add_employee()
{
	MYSQL_RES *read=NULL;
	MYSQL_RES *res=NULL;
	MYSQL_ROW row=NULL;
	struct employee 
	{ 
       int id; 
       char f_name[50]; 
       char l_name[50];
       char dep[50];
       char des[50];
       int age;
       char address1[45];
       char address2[45];
       char phonenumber[20];
	   char gender[10];
	   char email[100];
	   char status[100]; 
	   int day;
	   int month;
	   int year; 
        
    };
     
    struct employee emp;
    int x=0;
    char ch;
    int num;
	printf("Enter the first name of employee\n");
    scanf("%s",emp.f_name);
    printf("Enter the Last name of employee\n");
    scanf("%s",emp.l_name);

    do{
    printf("Enter the department of employee\n");
    gets(emp.dep);
    x=notempty(emp.dep);
    }while(x==0);
    x=0;

    do{
    printf("Enter the designation of employee\n");
    gets(emp.des);
    x=notempty(emp.des);
    }while(x==0);
    x=0;

    printf("Enter the age of employee\n");
    scanf("%d",&emp.age);
    
    do{
    printf("Enter house/apartment number and street\n");
    gets(emp.address1);
    x=notempty(emp.address1);
    }while(x==0);
    x=0;
   
    do{
    printf("\nEnter city and country\n");
    gets(emp.address2);
    x=notempty(emp.address2);
    }while(x==0);
    x=0;
    
    do{
    printf("\nEnter gender Male , Female or Others\n");
	scanf("%s",emp.gender);
    if (stricmp(emp.gender,"Male")==0 || stricmp(emp.gender,"Female")==0 || stricmp(emp.gender,"Female")==0)
    {
       x=1;
       break;	
	}
	
	} while(x==0);
	x=0;
	do
	{
    printf("Enter email\n");
    scanf("%s",emp.email);
    x=valid_email(emp.email);
	}while(x==0);
	
	x=0;
	do{
    printf("Enter employement status(A for active or I for inactive)\n");
    scanf("%s",emp.status);
    if (stricmp(emp.status,"A")==0 || stricmp(emp.status,"I")==0)
    {
       x=1;
       break;	
	}
    } while(x==0);
    
    x=0;
    do{
    printf("Enter Phone number\n");
    scanf("%s",emp.phonenumber);
    x=valid_phone(emp.phonenumber);
    } while(x==0);
    x=0;
	do{
    printf("Enter the date of joining\n");
    printf("   Enter day of joining\n");
    scanf("%d",&emp.day);
    printf("   Enter month of joining\n");
    scanf("%d",&emp.month);
    printf("   Enter year of joining\n");
    scanf("%d",&emp.year);
    x=datevalid(emp.day,emp.month,emp.year);
     } while(x==0);
    char stmt[1500];
	char qry[]={"insert into emp_details (name1,name2,department,designation,age,address_l1,address_l2,phonen,gender,email,day,month,year,emp_type) VALUES('%s','%s','%s','%s','%d','%s','%s','%s','%s','%s','%d','%d','%d','%s')"};
	if(conn2)
    {
    	
    	sprintf(stmt,qry,emp.f_name,emp.l_name,emp.dep,emp.des,emp.age,emp.address1,emp.address2,emp.phonenumber,emp.gender,emp.email,emp.day,emp.month,emp.year,emp.status);
        
        if (mysql_query(conn2,stmt))
      	{
   		    printf(" Error: %s\n", mysql_error(conn2));
   		    return "Failed to execute query.";
   		
 	    }
       	else
 	    {
 		
 		   printf( "\n\n\nuser details added successfully\n\n\n\n\n");
 	
	    }
    }
   
    else
    {
    	printf("not connected");
        printf("%s\n", mysql_error(conn2));
    	
	}
	int emp_id;
	char qry2[]={"select max(emp_id) as id from emp_details"};
	if(conn2)
    {
    	
    	int n=sprintf(stmt,qry2);
        mysql_query(conn2,stmt);
		read = mysql_store_result(conn2);
        if (mysql_query(conn2,stmt))
        {
            printf(" Error: %s\n", mysql_error(conn2));
            printf("Failed to execute query.");
        }

        else
        {
            int i=0;
			row = mysql_fetch_row(read);
            emp_id=atoi(row[0]);
            printf("%d\n",emp_id);
            mysql_free_result(read);
             
        }
 		   
 	
	}

   
    else
    {
    	printf("not connected");
        printf("%s\n", mysql_error(conn2));
    	
	}
	
	oo1=mysql_init(NULL);
	mysql_real_connect(oo1, "localhost", "root", "1234","payroll", 3306, NULL, 0);
	char password []="1234";
	char employee_type[30];
	printf("Enter the employee type -Admin,Employee or Manager\n");
	scanf("%s",employee_type);
	char qry3[]={"insert into login_details (emp_id,password,emp_type,status) VALUES('%d','%s','%s','%s')"};
	if(oo1)
    {
    	
    	sprintf(stmt,qry3,emp_id,password,employee_type,emp.status);
        printf("%s",stmt);
        if (mysql_query(oo1,stmt))
      	{
   		    printf(" Error: %s\n", mysql_error(oo1));
   		    return "Failed to execute query.";
   		
 	    }
       	else
 	    {
 		
 		   return "\n\n\nuser added successfully\n\n\n\n\n";
 	
	    }
    }
   
    else
    {
    	printf("not connected");
        printf("%s\n", mysql_error(oo1));
    	
	}

	
	
	
}


int emp_management(int i,int emp_id)
{
	conn2=mysql_init(NULL);
	int id;
	mysql_real_connect(conn2, "localhost", "root", "1234","payroll", 3306, NULL, 0);
	if(!conn2)
	{
		printf("Connection error");
		return 0;
	}
	else
	{
	switch(i)
		    {
			    case 1:
			        {   
			            printf("                Press 1 Add Employee\n");
		                printf("                Press 2 Modify Employee\n");
		                printf("                Press 3 Deactivate Employee\n");
		                printf("                Press 4 Display Employee\n");
		                int k;
		                scanf("%d",&k);
		                switch(k)
		                {
		                	case 1:
		                		{
		                			
		            
		                			printf("%s",add_employee());
		                			break;
								}
							case 2:
								{
									printf("Please specify the employee id: ");
		                			scanf("%d",&id);
		                			printf("%s",modify_employee(id));
		                			break;
								}
							case 3:
								{
									printf("Pleae specify the employee id: ");
		                			scanf("%d",&id);
									break;
								}
							case 4:
								{
									int j;
									printf("\n                Press 1 Display with Employee ID.");
                                    printf("\n                Press 2 Display with Departments");
                                    printf("\n                Press 3 Display with Designations");
                                    printf("\n                Press 4 Display all Employees.\n");
                                    scanf("%d",&j);
                                    emp_display_details(j);
								}
						}
		                break;
				    }
			
			    case 2:
			        {   
			            printf("                Press 1 View pending requests\n");
		                printf("                Press 2 Display leaves\n");
		                int ch;
		                scanf("%d",&ch);
		                if(ch==1)
		                {
		                	
						}
						else if(ch==2)
						{
							
						}
						else
						{
							printf("Wrong choice");
						}
		                break;
				    }
				
			    case 3:
			        {   
			            printf("                Press 1 Display attendance\n");
		                printf("                Press 2 Update attendance\n");
		                break;
				    }
				
			    case 4:
			        {   
			            printf("                Press 1 Display salary\n");
		                printf("                Press 2 Update salary\n");
		                break;
				    }
				
			    case 5:
			        {   
			            printf("                Press 1 Add Employee\n");
			            break;
				    }
			    case 6:
			        {    
			            printf("                Press 1 Increment Salary\n");
			            break;
				    }
			    case 7:
			        {   
			            printf("                Press 1 Grievance redressal\n");
			            break;
				    }
								
			    default:
				    {
					    printf("wrong input");
					    break;
				    }
		    }
		    return 1;
	}
	
}	

char* modify_employee(int emp_id)
{
    struct employee 
	{ 
        int id; 
        char f_name[50]; 
        char l_name[50];
        int age;
        char address1[45];
        char address2[45];
        char phonenumber[20];
	    char gender[10];
	    char email[100];
	    char status[100]; 
	    int day;
	    int month;
        int year;
	};
     
    struct employee emp;
	
	int i=0;
	char stmt[1500];
    printf("                Press 1 First Name\n");
	printf("                Press 2 Last Name\n");
	printf("                Press 3 Age\n");
	printf("                Press 4 Address Line 1\n");
    printf("                Press 5 Address Line 2\n");
    printf("                Press 6 Phone Number\n");
    printf("                Press 7 Gender\n");
    printf("                Press 8 Email\n");
	printf("                Press 9 Day of joining\n");
    printf("                Press 10 Month of joining\n");
    printf("                Press 11 Year of joining\n");
	printf("                Press 12 Status\n");
	printf("                Press 13 Exit\n");
	scanf("%d",&i);
	switch(i)
	    {
	        case 1:
	    		{
					printf("Please provide the first name: \n");
	    			scanf("%s",emp.f_name);
	    			char qry[]={"update emp_details set name1='%s' where emp_id='%d'"};
					if(conn2)
					{
					    sprintf(stmt,qry,emp.f_name,emp_id);
		    			if(mysql_query(conn2,stmt))
		    			{	
		    			    printf(" Error: %s\n", mysql_error(conn2));
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
						printf("%s\n", mysql_error(conn2));
					}
				break;
				}
			case 2:
	    		{
					printf("Please provide the last name: \n");
	    			scanf("%s",emp.l_name);
	    			char qry[]={"update emp_details set name2='%s' where emp_id='%d'"};
					if(conn2)
					{
					    sprintf(stmt,qry,emp.l_name,emp_id);
		    			if(mysql_query(conn2,stmt))
		    			{	
		    			    printf(" Error: %s\n", mysql_error(conn2));
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
						printf("%s\n", mysql_error(conn2));
					}
				break;
				}
			case 3:
	    		{
					printf("Please provide the age: \n");
	    			scanf("%d",&emp.age);
	    			char qry[]={"update emp_details set age='%d' where emp_id='%d'"};
					if(conn2)
					{
					    sprintf(stmt,qry,emp.age,emp_id);
		    			if(mysql_query(conn2,stmt))
		    			{	
		    			    printf(" Error: %s\n", mysql_error(conn2));
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
						printf("%s\n", mysql_error(conn2));
					}
				break;
				}
			case 4:
	    		{   int x=0; 
	    		    do
					{
					    printf("Enter address line 1\n");
	    			    gets(emp.address1);
						x=notempty(emp.address1);
					}while(x==0);
						
	    			char qry[]={"update emp_details set address_l1='%s' where emp_id='%d'"};
					if(conn2)
					{
					    sprintf(stmt,qry,emp.address1,emp_id);
		    			if(mysql_query(conn2,stmt))
		    			{	
		    			    printf(" Error: %s\n", mysql_error(conn2));
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
						printf("%s\n", mysql_error(conn2));
					}
				break;
				}
				
			case 5:
	    		{
					int x=0; 
	    		    do
					{
					    printf("Enter address line 2\n");
	    			    gets(emp.address2);
						x=notempty(emp.address2);
					}while(x==0);
					
					char qry[]={"update emp_details set address_l2='%s' where emp_id='%d'"};
					if(conn2)
					{
					    sprintf(stmt,qry,emp.address2,emp_id);
		    			if(mysql_query(conn2,stmt))
		    			{	
		    			    printf(" Error: %s\n", mysql_error(conn2));
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
						printf("%s\n", mysql_error(conn2));
					}
				break;
				}
				
			case 6:
	    		{
	    			int x=0;
					do
					{
					    printf("Please provide the phone number: \n");
	    			    scanf("%s",emp.phonenumber);
	    			    x=valid_phone(emp.phonenumber);
	    		    }while(x==0);
	    			    
	    			    
	    			char qry[]={"update emp_details set phonen='%s' where emp_id='%d'"};
					
					if(conn2)
					{
					    sprintf(stmt,qry,emp.phonenumber,emp_id);
		    			if(mysql_query(conn2,stmt))
		    			{	
		    			    printf(" Error: %s\n", mysql_error(conn2));
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
						printf("%s\n", mysql_error(conn2));
					}
				break;
				}
				
			case 7:
	    		{
					printf("Enter gender Male,Female or Others\n");
	    			scanf("%s",emp.gender);
	    			char qry[]={"update emp_details set gender='%s' where emp_id='%d'"};
					if(conn2)
					{
					    sprintf(stmt,qry,emp.gender,emp_id);
		    			if(mysql_query(conn2,stmt))
		    			{	
		    			    printf(" Error: %s\n", mysql_error(conn2));
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
						printf("%s\n", mysql_error(conn2));
					}
				break;
				}
			case 8:
	    		{   
	    		    int x=0;
					do{
						printf("Please provide the email: \n");
						scanf("%s",emp.email);
						x=valid_email(emp.email);
					}while(x==0);
	    			
	    			char qry[]={"update emp_details set email='%s' where emp_id='%d'"};
					if(conn2)
					{
					    sprintf(stmt,qry,emp.email,emp_id);
		    			if(mysql_query(conn2,stmt))
		    			{	
		    			    printf(" Error: %s\n", mysql_error(conn2));
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
						printf("%s\n", mysql_error(conn2));
					}
				break;
				}
			case 9:
	    		{
					printf("Please provide the day of joining: \n");
	    			scanf("%d",&emp.day);
	    			char qry[]={"update emp_details set day='%d' where emp_id='%d'"};
					if(conn2)
					{
					    sprintf(stmt,qry,emp.day,emp_id);
		    			if(mysql_query(conn2,stmt))
		    			{	
		    			    printf(" Error: %s\n", mysql_error(conn2));
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
						printf("%s\n", mysql_error(conn2));
					}
				break;
				}
			
			case 10:
	    		{
					printf("Please provide the month of joining: \n");
	    			scanf("%d",&emp.month);
	    			char qry[]={"update emp_details set month='%d' where emp_id='%d'"};
					if(conn2)
					{
					    sprintf(stmt,qry,emp.month,emp_id);
		    			if(mysql_query(conn2,stmt))
		    			{	
		    			    printf(" Error: %s\n", mysql_error(conn2));
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
						printf("%s\n", mysql_error(conn2));
					}
				break;
				}
			case 11:
	    		{
					printf("Please provide the year: \n");
	    			scanf("%d",&emp.year);
	    			char qry[]={"update emp_details set year='%d' where emp_id='%d'"};
					if(conn2)
					{
					    sprintf(stmt,qry,emp.year,emp_id);
		    			if(mysql_query(conn2,stmt))
		    			{	
		    			    printf(" Error: %s\n", mysql_error(conn2));
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
						printf("%s\n", mysql_error(conn2));
					}
				break;
				}
					
			case 12:
	    		{
	    			int x=0;
					do{
					    printf("Enter the employee status (A for Active or I for Inactive)\n");
					    scanf("%s",emp.status);
	    			    
						if(strcmp(emp.status,"A")==0 || strcmp(emp.status,"I")==0)
	    			    {
	    				    x=1;
					    }
	    			}while(x==0);
	    			
	    			char qry[]={"update emp_details set emp_type='%s' where emp_id='%d'"};
					if(conn2)
					{
					    sprintf(stmt,qry,emp.status,emp_id);
		    			if(mysql_query(conn2,stmt))
		    			{	
		    			    printf(" Error: %s\n", mysql_error(conn2));
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
						printf("%s\n", mysql_error(conn2));
					}
				break;
				}	
	    }	
return NULL;
}
