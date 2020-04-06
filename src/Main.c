#include <stdio.h>
#include <stdlib.h>
#include<string.h>

char* login(int id, char pwd[25])
{
	return "admin";
}

int main(int argc, char *argv[]) {
	int i,id;
	char ch;
	char pwd[25];
	char user_type[25];
	system("clear");
     	printf("\n**********\n");
		printf("                                      Login                           \n");
		printf("\n**********\n");
		

		printf("                Press 1 LOGIN\n");
		printf("                Press 2 EXIT\n");
		scanf("%d",&i);
	
		switch(i){
		    case 1:{
				    printf("\nEnter your employee id:");
        		    scanf("%d",&id);
	        		
	        		printf("\nEnter your password:");
        			scanf("%s",pwd);
					int p=0;
					
					strcpy(user_type,login(id,pwd));
					printf("\n%s\n",user_type);
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
		
        if(strcmp("admin",user_type)==0){
        	
            printf("                Press 1 Employee management\n");
		    printf("                Press 2 Leave management\n");
		    printf("                Press 3 Attendance management\n");
		    printf("                Press 4 Salary management\n");
        	printf("                Press 5 Department management\n");
		    printf("                Press 6 Increment management\n");
		    printf("                Press 7 Grievances redressal\n");
			scanf("%d",&i);
		    
		    switch(i){
			    case 1:{   
			            printf("                Press 1 Add Employee\n");
		                printf("                Press 2 Modify Employee\n");
		                printf("                Press 3 Deactivate Employee\n");
		                printf("                Press 4 Display Employee\n");
		                break;
				    }
			
			    case 2:{   
			            printf("                Press 1 View pending requests\n");
		                printf("                Press 2 Display leaves\n");
		                break;
				    }
				
			    case 3:{   
			            printf("                Press 1 Display attendance\n");
		                printf("                Press 2 Update attendance\n");
		                break;
				    }
				
			    case 4:{   
			            printf("                Press 1 Display salary\n");
		                printf("                Press 2 Update salary\n");
		                break;
				    }
				
			    case 5:{   
			            printf("                Press 1 Add Employee\n");
			            break;
				    }
			    case 6:{    
			            printf("                Press 1 Increment Salary\n");
			            break;
				    }
			    case 7:{   
			            printf("                Press 1 Grievance redressal\n");
			            break;
				    }
								
			    default:{
					    printf("Wrong Input");
					    break;
				    }
		}			    
	}
		
		else if(strcmp("employee",user_type)==0){
			
			int i;
			printf("                Press 1 Personal details management\n");
		    printf("                Press 2 Attendance management\n");
		    printf("                Press 3 Leave management\n");
		    printf("                Press 4 Salary management\n");
        	printf("                Press 5 Grievances redressal\n");
        	scanf("%d",&i);
        	
			switch(i){
				case 1:{   
			            printf("                Press 1 Display employee details \n");
		                printf("                Press 2 Update employee details\n");
		                printf("                Press 3 View employee feedback\n");
		                printf("                Press 4 Change password\n");
		                break;
				    }
				    
				case 2:{   
			            printf("                Press 1 Display attendance\n");
		                printf("                Press 2 Request attendance change\n");
		                break;
				    }
				    
				case 3:{   
			            printf("                Press 1 Request leave\n");
		                printf("                Press 2 Display leaves\n");
		                break;
				    }
				
			    				
			    case 4:{   
			            printf("                Press 1 Display salary (Hourly)\n");
		                printf("                Press 2 Display salary (Regular)\n");
		                break;
				    }

			    case 5:{   
			            printf("                Press 1 Raise Grievance\n");
			            break;
				    }
								
			    default:{
					    printf("Wrong Input");
					    break;
				    }
		    }		
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
			    case 1:{   
			            printf("                Press 1 Display employee details \n");
		                printf("                Press 2 Update employee details\n");
		                printf("                Press 3 Change password\n");
		                break;
				    }
				    
				case 2:{   
			            printf("                Press 1 Display attendance\n");
		                printf("                Press 2 Request attendance change\n");
		                break;
				    }
				    
				case 3:{   
			            printf("                Press 1 Request leave\n");
		                printf("                Press 2 Display leaves\n");
		                break;
				    }
							
			    case 4:{   
			            printf("                Press 1 Display salary (Hourly)\n");
		                printf("                Press 2 Display salary (Regular)\n");
		                break;
				    }

			    case 5:{   
			            printf("                Press 1 Raise Grievance\n");
			            break;
				    }
				    
				case 6:{ 
						printf("                Press 1 Request Employee\n");
			            printf("                Press 2 Rate employee\n");
			            printf("                Press 3 Display employee rating \n");
						break;
				    }
			    default:{
					    printf("Wrong Input");
					    break;
				    }
		    }
		}
		
		else{
			printf("Have a Good Day!");
		}
	
return 0;
}

