#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/cpumask.h>
#include <linux/kernel_stat.h>
#include <linux/delay.h>
#include <asm/cputime.h>
#include <asm/delay.h>
#include <asm/div64.h>
#include <asm/time.h>
#include <asm/uaccess.h> 



#ifndef arch_idle_time
#define arch_idle_time(cpu) 0
#endif

void cpu_use_and_total_time(cputime64_t *use, cputime64_t *total){
	int i ;
	*use = *total = cputime64_zero;
	for_each_possible_cpu(i) {
		*use += cputime64_add(*use, kstat_cpu(i).cpustat.user);
		*use += cputime64_add(*use, kstat_cpu(i).cpustat.nice);
		*use += cputime64_add(*use, kstat_cpu(i).cpustat.system);

		*total += *use;
		*total += cputime64_add(*total, kstat_cpu(i).cpustat.idle);
		*total += cputime64_add(*total, arch_idle_time(i));
		*total += cputime64_add(*total, kstat_cpu(i).cpustat.iowait);
		*total += cputime64_add(*total, kstat_cpu(i).cpustat.irq);
		*total += cputime64_add(*total, kstat_cpu(i).cpustat.softirq);
		*total += cputime64_add(*total, kstat_cpu(i).cpustat.steal);
	}
}



asmlinkage unsigned long long sys_CPU_Utilization(void){
	unsigned long long cpu_utilization, use_diff, total_diff;
	cputime64_t use_1, total_1, use_2, total_2;

	cpu_use_and_total_time(&use_1, &total_1);
	msleep(5000);
	cpu_use_and_total_time(&use_2, &total_2);

	use_diff = use_2-use_1;
	total_diff = total_2 -total_1;
	cpu_utilization = use_diff*100;

	do_div(cpu_utilization, total_diff);
	return cpu_utilization;
}