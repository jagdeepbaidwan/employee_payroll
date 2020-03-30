#include<windows.h>
#include<mysql.h>
MYSQL *conn5;
void emp_display_leaves(int emp_id)
{
    MYSQL_RES *read=NULL;
	MYSQL_RES *res=NULL;
	MYSQL_ROW row=NULL;
	MYSQL_FIELD *field;
	int num;
	char stmt[1500];
	conn5=mysql_init(NULL);
	mysql_real_connect(conn5, "localhost", "root", "1234","payroll", 3306, NULL, 0);
	char qry[]={"select * from leave_details where emp_id='%d'"};
	if(conn5)
    	{
    		int n = sprintf(stmt,qry,emp_id);
        	mysql_query(conn5,stmt);
		    read = mysql_store_result(conn5);
        	if (mysql_query(conn5,stmt))
        	{
            		printf(" Error: %s\n", mysql_error(conn5));
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
	
	
}
