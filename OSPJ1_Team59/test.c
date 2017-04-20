#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	//show 
	syscall(338);
	//multiply
	long a = 5;
	long b = 3;
	long mul = syscall(339, a, b);
	printf("%ld * %ld = %ld\n", a, b, mul);
	//min
	printf("Min of %ld and %ld is %ld\n", a, b, syscall(341, a, b));
	//cpu_utilization
	float cpu_u = syscall(337);
	printf("CPU Utilization: %5.1f%%",cpu_u);

	
	
	return 0;
}
