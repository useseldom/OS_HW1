#include<linux/kernel.h>
#include<linux/linkage.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
asmlinkage int sys_cpu_uti(void)
{
	long long ary[9];
	long long cpu_1 = 0, cpu_2 = 0, idle_1;
	FILE *fp;
	fp = open("/proc/stat", O_RDONLY);
	
	char buf;
	int count = 0;
	long long tmp = -1,num = 0; 
	while(count < 9){
		read(fp,buf,1);
		if(buf == '\0'){
			ary[count] = num;
			tmp = -1
			num = 0;
			break;
		}
		else if(buf == ' ' || buf == 'c' || buf == 'p' || buf == 'u'){
			if(tmp != -1){
				ary[count] = num;
				tmp = -1;
				num = 0;
				count ++;
			}
			continue;
		}
		else{
			tmp = 1;
			num * 10;
			num += buf - 48
		}
	}
	close(fp);
	count = 0;	
	for(int i=0;i<9;i++){
		cpu_1 += ary[i];
	}
	idle_1 = ary[3];

	fp = open("/proc/stat", O_RDONLY);
	while(count < 9){
		read(fp,buf,1);
		if(buf == '\0'){
			ary[count] = num;
			break;
		}
		else if(buf == ' ' || buf == 'c' || buf == 'p' || buf == 'u'){
			if(tmp != -1){
				ary[count] = num;
				tmp = -1;
				num = 0;
				count ++;
			}
			continue;
		}
		else{
			tmp = 1;
			num * 10;
			num += buf - 48
		}
	}
	close(fp);	
	for(int i=0;i<9;i++){
		cpu_2 += ary[i];
	}
	
	
	return (ary[3]-idle_1)*100/(cpu_2-cpu_1);
}
