#include<windows.h>
#include<mysql.h>
MYSQL *conn2;
char query[1500];
//start of  adding a new employee
char* add_employee()
{
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
 		
 		   return "\n\n\nuser added successfully\n\n\n\n\n";
 	
	    }
    }
   
    else
    {
    	printf("not connected");
        printf("%s\n", mysql_error(conn2));
    	
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
									printf("Pleae specify the employee id: ");
		                			scanf("%d",&id);
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
								
									printf("\n                Press 1 Display with Employee ID.");
                                    printf("\n                Press 2 Display with Departments");
                                    printf("\n                Press 3 Display with Designations");
                                    printf("\n                Press 4 Display all Employees.\n");
                                   
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
