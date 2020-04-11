Main: Main.c
	gcc -g -O -c Main.c -fPIC -DPIC -o ../build/Main.o

	gcc -g -O -c Validation.c -fPIC -DPIC -o ../build/Validation.o
	
	gcc -g -O -c employee_management.c -fPIC -DPIC -o ../build/employee_management.o
	
	gcc -g -O -c employee.c -fPIC -DPIC -o ../build/employee.o
	
	gcc -g -O -c employee_personal_dtl_management.c -fPIC -DPIC -o ../build/employee_personal_dtl_management.o
	
	gcc -g -O -c employee_attdnce_management.c -fPIC -DPIC -o ../build/employee_attdnce_management.o

	gcc -g -O -c admin_attend_mgmt.c -fPIC -DPIC -o ../build/admin_attend_mgmt.o	
	
	gcc -o ../bin/Payroll ../build/Main.o ../build/employee_management.o ../build/Validation.o ../build/employee.o ../build/employee_personal_dtl_management.o ../build/employee_attdnce_management.o ../build/admin_attend_mgmt.o libmysql.dll

	./../bin/Payroll    