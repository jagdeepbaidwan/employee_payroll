#include<stdio.h>
#include<string.h>

int valid_phone(char phone[])
{
	if(strlen(phone)!=10)
	{
		printf("Invalid phone number\n");
		return 0;
	}
	else{
		int i;
		for(i=0; i<strlen(phone);i++)
		{
			if(isalpha(phone[i]) != 0)
			{
				printf("Invalid phone number\n");
				return 0;
				
			}
		}
		return 1;
	}
}

int notempty(char num[] )
{
	
	if(strlen(num)<=1)
	{
		//printf("hello");
		printf("Invalid value\n");
		return 0;
	}
	return 1;
	
}
int valid_email(char test[])
{
    int     i;
    char    *pos1, *pos2;
    char    *ch;
	while (1) 
	{
        for (i = 0, ch = test; *ch; *ch++) {
                if (*ch == '@') {
                    pos1 = ch;  // <-stores last @ address
                    i++;
                }
            }
            pos2 = ch;          // <-stores end address ("\0") of test

        /* If there is only one "@" */
        if (i == 1) {

            /* Pos1 - test <-a character must be before "@". Ch - pos1 <-Counts
             * backwards from the end of the string towards "@". A character
             * must be between "@" and "." */
            while (pos1 - test && ch - pos1 > 1) {

                /* From the end of string to "." has to be atleast 2 chars */
                if ((pos2 - ch) > 2 && *ch == '.') {
                    //printf("pos2 - ch is %d and *ch is %c",pos2 - ch, *ch);
                    return 1;
                }
                ch--;
            }
        }
        printf("Email wrong!\n");
        return 0;
        
    } /* End while */

    return 1;
}

int isleap(int y) {
   if((y % 4 == 0) && (y % 100 != 0) && (y % 400 == 0))
      return 1;
   else
      return 0;
}

int datevalid(int d, int m, int y) {
   if(y < 1800 || y > 9999)
      return 0;
   if(m < 1 || m > 12){
   	printf("Invalid month\n");
   	return 0;
   }
     
   if(d < 1 || d > 31){
   	printf("Invalid day\n");
      return 0;
  }
      
 if( m == 2 ) {
      if(isleap(y)) {
         if(d <= 29)
            return 1;
         else
         {
         	
   	     printf("Invalid day\n");
   	     return 0;
		 }
            
         }
      }
        
    
      if ( m == 4 || m == 6 || m == 9 || m == 11 )
         if(d <= 30)
            return 1;
         else
         {
         	printf("Invalid day\n");
		    return 0;
		  }
            return 1;
   }


