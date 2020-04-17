Main: Test.c
	gcc -g -O -c Test.c -fPIC -DPIC -o ../build/Test.o

	gcc -o ../bin/Test ../build/Test.o ../build/employee_management.o ../build/Validation.o ../build/employee.o ../build/employee_personal_dtl_management.o ../build/employee_attdnce_management.o ../build/admin_attend_mgmt.o ../build/manager_dept_management.o ../build/admin_dept_management.o ../build/attendance_display.o ../build/leave_request.o ../build/salary_management.o libmysql.dll

	../bin/Test 