#include<windows.h>
#include<mysql.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

MYSQL *conn7, *conn8, *conn9;
int port11 =3306;

char* add_salary(int e_id)
{
	MYSQL_RES *read=NULL;
	MYSQL_RES *res=NULL;
	MYSQL_ROW row=NULL;
	MYSQL_FIELD *field;
	int num;
	float salary;
	char sal_type;
	int x=0;
	char stmt[1500];
	int sal_year;
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    sal_year = local->tm_year + 1900;
	char sal_qry[]={"select emp_id,designation from emp_details where emp_id = %d"};	
	char add_sal_qry[] ={"insert into salary values('%d','%s','%f','%d')"};
	struct add_sal
	{
		float salary;
		char sal_type[20];
	};
	struct add_sal sal;
	
	conn7=mysql_init(NULL);
	mysql_real_connect(conn7, "localhost", "root", "1234","payroll", port11, NULL, 0);

	if(conn7)
    {
        printf("Enter the Salary type  hourly or salaried:\n");
		scanf("%s",sal.sal_type);
    	printf("\nEnter the Salary: \n");
    	scanf("%f",&sal.salary);
		getchar(); 
		
    	printf("Salary type is %s",sal.sal_type);
    	if (strcasecmp(sal.sal_type,"hourly")==0 || strcasecmp(sal.sal_type,"Salaried")==0)
    	{	
    	   
        
  				
						int n = sprintf(stmt,add_sal_qry,e_id,sal.sal_type,sal.salary,sal_year);
					
						if (mysql_query(conn7,stmt))
    					{
   							printf(" Error: %s\n", mysql_error(conn7));
   							return "Failed to execute query.";
   						}
    
						else
 						{
 						
							return ("\n\n\t\t		Salary added successfully \n\n");
						}
				
		 	
        	}
        	
			else
			{
			
				printf("\t\t Wrong salary_type for emp_id: %d\n",e_id);
				return ("try again\n");
			}		
    
    }

    else
    {
    	
        printf ("%s\n", mysql_error(conn7));
        return("not connected");
	}
}



char* count_attendances_and_compute_salary(char stmt[1500])
{
	MYSQL_RES *read = NULL;
	MYSQL_RES *read1 = NULL;
	MYSQL_ROW rows=NULL;
	MYSQL_ROW res=NULL;
	MYSQL_FIELD *fields;
	time_t s;
	struct tm* current_time;
	s = time(NULL);
	current_time=localtime(&s);
    
	if (conn7)
	{    
		mysql_query(conn7,stmt);
		read = mysql_store_result(conn7);  
		if (mysql_query(conn7,stmt))
        	{
        		printf("Error: %s\n", mysql_error(conn7));
	        	return ("Failed to execute query.");
        	}

        	else
        	{
  			int num_fields = mysql_num_rows(read);
  			int deduct=0,present=0, absent=0, medical_leave=0, paid_leave=0,emp_id=0;
  			
			if (num_fields<=0)
            		{
		            	return ("\t\t No Record found.\n");
			}
			
			else
			{
				int temp=0;
				while(rows = mysql_fetch_row(read))
				{
					emp_id = atoi(rows[0]);
  					float wage = atof(rows[2]);
  					float hours=0;
					float net_pay=0,deductions=0,total=0;
				  	printf("\t\tEmployee ID:%d with wage:%.2lf\n",emp_id,wage);
				  	
				  	if (0 == strcasecmp(rows[1],"H"))
				  	{
				  		conn8 = mysql_init(NULL);
						mysql_real_connect(conn8, "localhost", "root", "1234","payroll", port11, NULL, 0);
				   		char qry[] ={"select * from hourly_attendance where att_month ='%d' and att_year ='%d' and emp_id ='%d'"};
				  		sprintf(stmt,qry,current_time->tm_mon+1,current_time->tm_year+1900,emp_id);
		
						if (mysql_query(conn8,stmt))
    					    	{
			        			printf("Error: %s\n", mysql_error(conn8));
        						return ("Failed to execute query.");
        					}
        				
						else
	        				{ 
        						read1 = mysql_store_result(conn8);
							int num_fields1 = mysql_num_rows(read1);
							
							if (num_fields <=0)
            						{
            							return ("\t\t No Record found.\n");
							}
							else
							{
								
								while (res = mysql_fetch_row(read1)) 
  								{
	  								hours+=atoi(res[7]);
  								}
  								
								if (hours>40)
								{
									float over_hr = hours-40;
									printf("\t\tHours are: %.2f. but overtime hours:%.2f\n",hours,over_hr);
	  								total = 40*wage + over_hr*(wage*1.5);
	  								deductions = total*0.13;
	  								net_pay = total-deductions;
	  								printf("\tSalary is computed for Employee ID:%d and net_pay is %.2f, deductions: %.2f and total:%.2f \n",emp_id,net_pay,deductions,total);
								}
								
  								else
  								{
	  								printf("\tHours are: %.2f.\n",hours);
	  								total = hours*wage;
	  								deductions = total*0.13;
	  								net_pay = total-deductions;
	  								printf("\tSalary is computed for Employee ID:%d and net_pay is %.2f, deductions: %.2f and total:%.2f \n",emp_id,net_pay,deductions,total);			
	  							}
							}
						}
						
						conn9 = mysql_init(NULL);
						mysql_real_connect(conn9, "localhost", "root", "1234","payroll",port11, NULL, 0);
				   		
						char qry1[] ={"insert into salary_cal (emp_id,salary_type,month,year,calculated_salary,deductions,net_pay) VALUES ('%d','%s','%d','%d','%.2f','%.2f','%.2f')"};
				  		sprintf(stmt,qry1,emp_id,"employee",current_time->tm_mon+1,current_time->tm_year+1900,total,deductions,net_pay);
						
						if (mysql_query(conn9,stmt))
		    			    	{
				        		printf("Error: %s\n", mysql_error(conn9));
        						return ("Failed to execute query.");
        					}
        				
						else
        					{
        						return("\n\n Salary is computed.\n\n");
	        				}
					}
					
					
					else
					{
						char qry[] ={"select * from daily_attendance where attend_month ='%d' and attend_year ='%d' and emp_id ='%d'"};
				  		sprintf(stmt,qry,current_time->tm_mon+1,current_time->tm_year+1900,emp_id);
				  		printf("%s",stmt);
					  	
						if (mysql_query(conn8,stmt))
    			    			{
			        			printf("Error: %s\n", mysql_error(conn8));
        						return ("Failed to execute query.");
	        				}
        				
						else
        					{ 
        						read1 = mysql_store_result(conn8);
							int num_fields1 = mysql_num_rows(read1);
							printf("%d",num_fields1);
							if (num_fields <=0)
            						{
            							return ("\t\t No Record found.\n");
							}
							else
							{
								float hours=0;
								while (res = mysql_fetch_row(read1)) 
  								{
									int i=0;
      									for(i = 6; i < num_fields-1; i++) 
      									{
				          					printf("%s ", rows[i] ? rows[i] : "NULL");
	          								if (0 == strcasecmp(rows[i],"P"))
        	  								{
				          						present+=1;
										}
										else if (0 == strcasecmp(rows[i],"A"))
										{
											absent+=1;
										}
										else if (0 == strcasecmp(rows[i],"ML"))
										{
											medical_leave+=1;
										}
										else if (0 == strcasecmp(rows[i],"PL"))
										{	
											paid_leave+=1;
										}
      									} 
      								
      									if (absent)
									{
										deduct = present - absent;
	  									total = deduct + medical_leave + paid_leave;
	  									deductions = total*0.13;
	  									net_pay = total-deductions;
	  									printf("\tSalary is computed for Employee ID:%d and net_pay is %.2f, deductions: %.2f and total:%.2f \n",emp_id,net_pay,deductions,total);
									}
								
  									else
  									{
		  								total = wage;
		  								deductions = total*0.13;
	  									net_pay = total-deductions;
	  									printf("\tSalary is computed for Employee ID:%d and net_pay is %.2f, deductions: %.2f and total:%.2f \n",emp_id,net_pay,deductions,total);			
	  								}
 								}
 							}			
						}
					
						conn9 = mysql_init(NULL);
						mysql_real_connect(conn9, "localhost", "root", "1234","payroll",port11, NULL, 0);
				   		
						char qry1[] ={"insert into salary_cal (emp_id,salary_type,month,year,calculated_salary,deductions,net_pay) VALUES ('%d','%s','%d','%d','%.2f','%.2f','%.2f')"};
				  		sprintf(stmt,qry1,emp_id,"admin",current_time->tm_mon+1,current_time->tm_year+1900,total,deductions,net_pay);
				  		
						if (mysql_query(conn9,stmt))
		    			    	{
				        		printf("Error: %s\n", mysql_error(conn9));
        						return ("Failed to execute query.");
        					}
        				
						else
        					{
        						return("\n\n Salary is computed.\n\n");
        					}	
					}
				}
			}
		}
	}
	
	else
	{
        printf("%s\n", mysql_error(conn7));	
    	return ("not connected");
        	
	}
}


int emp_sal_mgmt()
{
	conn7 = mysql_init(NULL);
	mysql_real_connect(conn7, "localhost", "root", "1234","payroll",port11, NULL, 0);
	
	if(!conn7)
	{
		printf("Connection error");
		return 0;
	}
	
	else
	{
		int compute_opt;
		
		char stmt [1500];

		time_t s;
		struct tm* current_time;
		s = time(NULL);
		current_time=localtime(&s);
		
		printf("		Press 1 Compute Salary for hourly employees\n");
		printf("		Press 2 Compute Salary for salaried employees\n");
		scanf("%d",&compute_opt);
		if (compute_opt == 1)
		{
			char qry[] = {"select * from salary where salary_type='hourly'"};
          		int n = sprintf(stmt,qry);
            
		            printf("%s",count_attendances_and_compute_salary(stmt));	
		}

		else if(compute_opt == 2)
		{
			char qry[] = {"select * from salary where salary_type='salaried'"};
		        int n = sprintf(stmt,qry);
            
			printf("%s",count_attendances_and_compute_salary(stmt));
		}

	    	else
		{
			printf("Wrong Choice.");
		}     	
	}
	return 1;
}

