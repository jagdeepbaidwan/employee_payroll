#include<stdio.h>
#include<windows.h>
#include<mysql.h>
#include<string.h>
#include<stdlib.h>
#include "..\include\Validation.h"
#include "..\include\employee_management.h"
MYSQL *conn2, *oo1,*oo3,*conn8;
char query[1500];


//start of  adding a new employee
char* add_employee(char dept[],char desig[],int check, int request_id)
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
	getchar();
    do{
    printf("Enter the first name of employee\n");
    gets(emp.f_name);
    x=notempty(emp.f_name);
    }while(x==0);
    x=0;
    do{
    printf("Enter the Last name of employee\n");
    gets(emp.l_name);
    x=notempty(emp.l_name);
    }while(x==0);
    x=0;
    
    if(check==1){
    	strcpy(emp.dep,dept);
    	strcpy(emp.des,desig);
	}
    else{
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
	}

    printf("Enter the age of employee\n");
    scanf("%d",&emp.age);
    getchar();
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
    if (strcasecmp(emp.gender,"Male")==0 || strcasecmp(emp.gender,"Female")==0 || strcasecmp(emp.gender,"Female")==0)
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
          if (strcasecmp(emp.status,"A")==0 || strcasecmp(emp.status,"I")==0)
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
    conn8=mysql_init(NULL);
	mysql_real_connect(conn8, "localhost", "root", "1234","payroll", 3306, NULL, 0);
    char qry[]={"insert into emp_details (name1,name2,department,designation,age,address_l1,address_l2,phonen,gender,email,day,month,year,emp_type) VALUES('%s','%s','%s','%s','%d','%s','%s','%s','%s','%s','%d','%d','%d','%s')"};
    if(conn8)
    {
        sprintf(stmt,qry,emp.f_name,emp.l_name,emp.dep,emp.des,emp.age,emp.address1,emp.address2,emp.phonenumber,emp.gender,emp.email,emp.day,emp.month,emp.year,emp.status);
        if (mysql_query(conn8,stmt))
      	{
   		    printf(" Error: %s\n", mysql_error(conn8));
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
        printf("%s\n", mysql_error(conn8));

    }
	int emp_id;
	char qry2[]={"select max(emp_id) as id from emp_details"};
    if(conn8)
    {

    	int n=sprintf(stmt,qry2);
        mysql_query(conn8,stmt);
		read = mysql_store_result(conn8);
        if (mysql_query(conn8,stmt))
        {
            printf(" Error: %s\n", mysql_error(conn8));
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
        printf("%s\n", mysql_error(conn8));

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
        if (mysql_query(oo1,stmt))
      	{
   		    printf(" Error: %s\n", mysql_error(oo1));
   		    return "Failed to execute query.";

 	    }
       	else
 	    {
 	    	
			if(check=1)
			{
			
			oo3=mysql_init(NULL);
			mysql_real_connect(oo3, "localhost", "root", "1234","payroll", 3306, NULL, 0);
			char request_status[]="Completed";
			char qry_update_request_status[]={"update employee_request set request_status='%s' where request_id='%d'"};
			if(oo3){
				sprintf(stmt,qry_update_request_status,request_status,request_id);
				if (mysql_query(oo3,stmt)){
				    printf(" Error: %s\n", mysql_error(oo3));
					return "Failed to execute query.";
				}
				else{
					printf("Status updated successfully");
				}
		    }
			else{
			    printf("not connected");
			    printf("%s\n", mysql_error(oo3));
			}
			}
		return "\n\n\nUser added successfully\n\n\n\n\n";
	    }
    }

    else
    {
    	printf("not connected");
        printf("%s\n", mysql_error(oo1));
	}
}

/* De-activating employee*/
void deactivate (int emp_id, int login_id){
	MYSQL_RES *read=NULL;
	MYSQL_RES *res=NULL;
	MYSQL_ROW row=NULL;
	char status[20]="0" ;
 	snprintf(query,1500,"select emp_id,status FROM login_details where emp_id = '%d'",emp_id) ;
 	/* send SQL query */
 	if (mysql_query(conn2, query)){
   	printf("Failed to execute query. Error: %s\n", mysql_error(conn2));
    }
 	else{
	 res = mysql_store_result(conn2);
	 row = mysql_fetch_row(res);
	 if (row == NULL){
	   printf("Username Not Found");
	 }
	 else{
	 	//strcpy(status,row[0]);

	 	if(strcmp("A",row[1])){
		 	printf("Already deactivated");
		 }
		 else{
		 	 if(atoi(row[0])!=login_id){
                int dd,mm,yy;
				int r;
				do
				{
					printf("\nEnter the date of leave of an employee:Format(dd/mm/yyyy)");
					scanf("%d/%d/%d",&dd,&mm,&yy);
					r=validate_date(dd,mm,yy);
				}while(r!=1);
				char date[15];
		 	 	sprintf(date,"%d/%d/%d", dd,mm,yy);
			 	char qry[]="update  login_details set status='I', DOL='%s' where emp_id='%d'";
				sprintf(query,qry,date,emp_id);
				if (mysql_query(conn2, query)){
			   		printf("Failed to execute query. Error: %s\n", mysql_error(conn2));
			   	}
			   	else{
				   printf("User Successfully deactivated");
				}
		 	}
		 	else{
		 		printf("Sorry! You can not deactivate the logged in account");
			}
		 }
      }
	}
}
/*End de-activating employee function*/




//Start of displaying employee detail
void emp_display_details(char stmt[]){
	MYSQL_RES *read=NULL;
	MYSQL_RES *res=NULL;
	MYSQL_ROW row=NULL;
	MYSQL_FIELD *field;
	int num;

    if(conn2)
    {
        mysql_query(conn2,stmt);
		read = mysql_store_result(conn2);
        if (mysql_query(conn2,stmt))
        {
            printf(" Error: %s\n", mysql_error(conn2));
            printf("Failed to execute query.");
        }

        else
        {
        	  while ((row = mysql_fetch_row(read)))
  			{
  				int num_fields;
				num_fields = mysql_num_fields(read);
	  			int i;
    			for(i = 0; i < num_fields; i++)
    			{
    			printf(" |");
       		   	if (i == 0)
          		{
            		while(field = mysql_fetch_field(read))
  		          	{
        	    	printf("%s |", field->name);
            		}

	            	printf("\n");
          		}

				printf("%s  ", row[i] ? row[i] : "NULL");
      			}
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

return;
}
//end of displaying employee details.



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
		                			printf("%s",add_employee("empty","empty",0,0));
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
		                		    deactivate(id,emp_id);
									break;
								}
							case 4:
								{
									int j;
									int emp_id;
                                    char emp_depart_display[50];
                                    char emp_desig_display[50];
									printf("\n                Press 1 Display with Employee ID.");
                                    printf("\n                Press 2 Display with Departments");
                                    printf("\n                Press 3 Display with Designations");
                                    printf("\n                Press 4 Display all Employees.\n");
                                    scanf("%d",&j);
                                    if (j == 1)
                                    {
                                    	char stmt[1500];
                                        printf("Enter the Employee ID: ");
                                        scanf("%d",&emp_id);
                                        char qry[] = {"select * from emp_details where emp_id = %d"};
                                        int n = sprintf(stmt,qry,emp_id);
                                        emp_display_details(stmt);
                                    }

                                    else if (j == 2)
                                    {
                                    	char stmt[1500];
                                        printf("\nEnter the department: ");
                                        scanf("%s",emp_depart_display);
                                        char qry[] = {"select * from emp_details where department= '%s'"};
                                        int n = sprintf(stmt,qry,emp_depart_display);
                                        emp_display_details(stmt);
                                    }

                                    else if (j == 3)
                                    {
                                    	char stmt[1500];
                                        printf("\nEnter the designation: ");
                                        scanf("%s",emp_desig_display);
                                        char qry[] = {"select * from emp_details where designation = '%s'"};
                                        int n = sprintf(stmt,qry,emp_desig_display);
                                        emp_display_details(stmt);
                                    }

                                    else if (j == 4)
                                    {
                                    	char stmt[1500];
                                        printf("\nDisplaying all employees \n");
                                        char qry[] = {"select * from emp_details"};
                                        int n = sprintf(stmt,qry);
                                        emp_display_details(stmt);
                                    }

                                    else
                                    {
                                    printf("Entered Incorrect number");
                                    break;
                                    }
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
			            printf("                Press 1 create attendance month\n");
						printf("                Press 2 to add daily attendance attendance\n");
			            printf("                Press 3 Display attendance\n");
		                printf("                Press 4 Update attendance\n");
		                int ch;
		                scanf("%d",&ch);
		                attend_mgmt(ch);
		                break;
				    }

			    case 4:
			        {
			            printf("                Press 1 Display salary\n");
		                printf("                Press 2 Update salary\n");
		                break;
				    }

				case 5:{
					int i=0;
					printf("                Press 1 View pending requests to add employee\n");
					printf("                Press 2 Add employee to the department\n");
					scanf("%d",&i);
					switch(i){
						case 1:{
							char status[10];
							strcpy(status,"Pending");
							printf("%s",view_pending_requests(status));
							break;
						}
						case 2:{
							int req_id;
							printf("Please provide the request id to be addressed: ");
							scanf("%d",&req_id);
							printf("%s",add_employee_department(req_id));
							break;
						}	
						break;
				    }
						
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
				case 8:
			        {
			            change_password(emp_id);
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


/*Start of Function: Modify Employee*/

char* modify_employee(int emp_id)
{
    struct employee{
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
	int x=0;
	char stmt[1500];
	getchar();
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
	switch(i){
	    case 1:{

	    	getchar();
			do{
			printf("Please provide the first name: \n");
			gets(emp.f_name);
			x=notempty(emp.f_name);
			}while(x==0);
			x=0;
			char qry[]={"update emp_details set name1='%s' where emp_id='%d'"};

			if(conn2){
				sprintf(stmt,qry,emp.f_name,emp_id);

				if(mysql_query(conn2,stmt)){
		    		printf(" Error: %s\n", mysql_error(conn2));
					return "Failed to execute query.";
				}
				else{
					return "\n\n\n\nUser modified successfully\n\n\n\n";
				}
			}
			else{
				printf("not connected");
				printf("%s\n", mysql_error(conn2));
			}
			break;
		}

		case 2:{
	    	getchar();
			do{
			printf("Please provide the last name: \n");
			gets(emp.l_name);
			x=notempty(emp.l_name);
			}while(x==0);
			x=0;

			char qry[]={"update emp_details set name2='%s' where emp_id='%d'"};
			if(conn2){
				sprintf(stmt,qry,emp.l_name,emp_id);
		    	if(mysql_query(conn2,stmt)){
		    		printf(" Error: %s\n", mysql_error(conn2));
					return "Failed to execute query.";
				}

				else{
					return "\n\n\n\nUser modified successfully\n\n\n\n";
				}
			}

			else{
				printf("not connected");
				printf("%s\n", mysql_error(conn2));
			}

				break;
		}

		case 3:{
			printf("Please provide the age: \n");
	    	scanf("%d",&emp.age);
	    	getchar();
			char qry[]={"update emp_details set age='%d' where emp_id='%d'"};
			if(conn2){
				sprintf(stmt,qry,emp.age,emp_id);
		    	if(mysql_query(conn2,stmt)){
		    		printf(" Error: %s\n", mysql_error(conn2));
					return "Failed to execute query.";
				}
				else{
					return "\n\n\n\nUser modified successfully\n\n\n\n";
				}
			}

			else{
				printf("not connected");
				printf("%s\n", mysql_error(conn2));
			}
			break;
		}

		case 4:{
		    int x=0;
	    	getchar();
			do{
			printf("Enter address line 1\n");
	    	gets(emp.address1);
			x=notempty(emp.address1);
			}while(x==0);

	    	char qry[]={"update emp_details set address_l1='%s' where emp_id='%d'"};
			if(conn2){
				sprintf(stmt,qry,emp.address1,emp_id);
		    	if(mysql_query(conn2,stmt)){
		    		printf(" Error: %s\n", mysql_error(conn2));
					return "Failed to execute query.";
				}

				else{
					return "\n\n\n\nUser modified successfully\n\n\n\n";
				}
			}

			else{
				printf("not connected");
				printf("%s\n", mysql_error(conn2));
			}
			break;
		}

		case 5:{
			int x=0;
			getchar();
	    	do{
			printf("Enter address line 2\n");
	    	gets(emp.address2);
			x=notempty(emp.address2);
			}while(x==0);

			char qry[]={"update emp_details set address_l2='%s' where emp_id='%d'"};
			if(conn2){
				sprintf(stmt,qry,emp.address2,emp_id);
		    	if(mysql_query(conn2,stmt)){
		    		printf(" Error: %s\n", mysql_error(conn2));
					return "Failed to execute query.";
				}
				else{
					return "\n\n\n\nUser modified successfully\n\n\n\n";
				}
			}

			else{
				printf("not connected");
				printf("%s\n", mysql_error(conn2));
			}
			break;
		}

		case 6:{
	    	int x=0;
			do{
				printf("Please provide the phone number: \n");
	    		scanf("%s",emp.phonenumber);
	    		getchar();
				x=valid_phone(emp.phonenumber);
	    	}while(x==0);


	    	char qry[]={"update emp_details set phonen='%s' where emp_id='%d'"};

			if(conn2){
				sprintf(stmt,qry,emp.phonenumber,emp_id);
		    	if(mysql_query(conn2,stmt)){
		    		printf(" Error: %s\n", mysql_error(conn2));
					return "Failed to execute query.";
				}

				else{
					return "\n\n\n\nUser modified successfully\n\n\n\n";
				}
			}

			else{
				printf("not connected");
				printf("%s\n", mysql_error(conn2));
			}

			break;
		}

		case 7:{
	    	do{
			printf("\nEnter gender Male , Female or Others\n");
			scanf("%s",emp.gender);
			if (strcasecmp(emp.gender,"Male")==0 || strcasecmp(emp.gender,"Female")==0 || strcasecmp(emp.gender,"Female")==0){
			    x=1;
				break;
			}
			} while(x==0);
			x=0;

			char qry[]={"update emp_details set gender='%s' where emp_id='%d'"};
			if(conn2){
				sprintf(stmt,qry,emp.gender,emp_id);
		    	if(mysql_query(conn2,stmt)){
		    		printf(" Error: %s\n", mysql_error(conn2));
					return "Failed to execute query.";
				}

				else{
					return "\n\n\n\nUser modified successfully\n\n\n\n";
				}
			}

			else{
				printf("not connected");
				printf("%s\n", mysql_error(conn2));
			}
			break;
		}

		case 8:{
	    	int x=0;
			do{
			    printf("Please provide the email: \n");
				scanf("%s",emp.email);
				getchar();
				x=valid_email(emp.email);
			}while(x==0);

	    	char qry[]={"update emp_details set email='%s' where emp_id='%d'"};
			if(conn2){
				sprintf(stmt,qry,emp.email,emp_id);
		    	if(mysql_query(conn2,stmt)){
		    		printf(" Error: %s\n", mysql_error(conn2));
					return "Failed to execute query.";
				}
				else{
					return "\n\n\n\nUser modified successfully\n\n\n\n";
				}
			}

			else{
				printf("not connected");
				printf("%s\n", mysql_error(conn2));
			}

			break;
		}

		case 9:{
			printf("Please provide the day of joining: \n");
	    	scanf("%d",&emp.day);
	    	getchar();
			char qry[]={"update emp_details set day='%d' where emp_id='%d'"};
			if(conn2){
				sprintf(stmt,qry,emp.day,emp_id);
		    	if(mysql_query(conn2,stmt)){
			        printf(" Error: %s\n", mysql_error(conn2));
					return "Failed to execute query.";
				}

				else{
					return "\n\n\n\nUser modified successfully\n\n\n\n";
				}
			}

			else{
				printf("not connected");
				printf("%s\n", mysql_error(conn2));
			}

			break;
		}

		case 10:{
			printf("Please provide the month of joining: \n");
	    	scanf("%d",&emp.month);
	    	getchar();
			char qry[]={"update emp_details set month='%d' where emp_id='%d'"};
			if(conn2){
				sprintf(stmt,qry,emp.month,emp_id);
		    	if(mysql_query(conn2,stmt)){
		    		printf(" Error: %s\n", mysql_error(conn2));
					return "Failed to execute query.";
				}

				else{
					return "\n\n\n\nUser modified successfully\n\n\n\n";
				}
			}

			else{
				printf("not connected");
				printf("%s\n", mysql_error(conn2));
			}

			break;
		}

		case 11:{
			printf("Please provide the year: \n");
	    	scanf("%d",&emp.year);
	    	getchar();
			char qry[]={"update emp_details set year='%d' where emp_id='%d'"};
			if(conn2){
				sprintf(stmt,qry,emp.year,emp_id);
		    	if(mysql_query(conn2,stmt)){
		    		printf(" Error: %s\n", mysql_error(conn2));
					return "Failed to execute query.";
				}
				else{
					return "\n\n\n\nUser modified successfully\n\n\n\n";
				}
			}

			else{
				printf("not connected");
				printf("%s\n", mysql_error(conn2));
			}
			break;
		}

		case 12:{
	    	int x=0;
			do{
				printf("Enter the employee status (A for Active or I for Inactive)\n");
				scanf("%s",emp.status);
	    		if(strcmp(emp.status,"A")==0 || strcmp(emp.status,"I")==0){
	    			x=1;
				}
	    	}while(x==0);

	    	char qry[]={"update emp_details set emp_type='%s' where emp_id='%d'"};
			if(conn2){
				sprintf(stmt,qry,emp.status,emp_id);
		    	if(mysql_query(conn2,stmt)){
		    		printf(" Error: %s\n", mysql_error(conn2));
					return "Failed to execute query.";
				}
				else{
					return "\n\n\n\nUser modified successfully\n\n\n\n";
				}
			}

			else{
				printf("not connected");
				printf("%s\n", mysql_error(conn2));
			}

			break;
		}
	}
return NULL;
}
