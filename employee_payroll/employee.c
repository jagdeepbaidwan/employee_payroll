#include<stdio.h>
void employee(int emp_id)
{
			int i;
			printf("                Press 1 Personal details management\n");
		    printf("                Press 2 Attendance management\n");
		    printf("                Press 3 Leave management\n");
		    printf("                Press 4 Salary management\n");
        	printf("                Press 5 Grievances redressal\n");
        	
        	scanf("%d",&i);
		    
		    switch(i)
		    {
			    case 1:
			        {   
			            emp_detail_mgmt(emp_id);
						
		                break;
				    }
				    
				case 2:
			        {   
			            
		                break;
				    }
				    
				case 3:
			        {   
			            printf("                Press 1 Request leave\n");
		                printf("                Press 2 Display leaves\n");
		                break;
				    }
				
			    				
			    case 4:
			        {   
			            printf("                Press 1 Display salary (Hourly)\n");
		                printf("                Press 2 Display salary (Regular)\n");
		                break;
				    }

			    case 5:
			        {   
			            printf("                Press 1 Raise Grievance\n");
			            break;
				    }
								
			    default:
				    {
					    printf("wrong input");
					    break;
				    }
				    
		    }
}
