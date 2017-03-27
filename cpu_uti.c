#include<linux/kernel.h>
#include<linux/linkage.h>
#include<linux/fs.h>
#include<asm/uaccess.h>
asmlinkage int sys_cpu_uti(void)
{
	long long cpu_1 = 0, cpu_2 = 0, idle_1, idle_2;
	struct file *fp;

	mm_segment_t old_fs;
	old_fs = get_fs();
	set_fs(KERNEL_DS);
	
	fp = filp_open("/proc/stat", O_RDONLY,0);
	if(!fp){
		printk("open error");
	}

	char buf;
	int count = 0;
	long long tmp = -1,num = 0; 
	while(count < 9){
		fp->f_op->read(fp,buf,1,&fp->f_pos);
		if(buf == '\0'){
			cpu_1 += num;
			tmp = -1;
			num = 0;
			break;
		}
		else if(buf == ' ' || buf == 'c' || buf == 'p' || buf == 'u'){
			if(tmp != -1){
				if(count == 3){
					idle_1 = num;
				}
				cpu_1 += num;
				tmp = -1;
				num = 0;
				count ++;
			}
			continue;
		}
		else{
			tmp = 1;
			num * 10;
			num += buf - 48;
		}
	}
	filp_close(fp,0);

	count = 0;	

	fp = filp_open("/proc/stat", O_RDONLY , 0);
	if(!fp){
		printk("open error");
	}

	while(count < 9){
		fp->f_op->read(fp,buf,1,&fp->f_pos);
		if(buf == '\0'){
			cpu_2 += num;
			break;
		}
		else if(buf == ' ' || buf == 'c' || buf == 'p' || buf == 'u'){
			if(tmp != -1){
				if(count == 3){
					idle_2 = num;
				}
				cpu_2 += num;
				tmp = -1;
				num = 0;
				count ++;
			}
			continue;
		}
		else{
			tmp = 1;
			num * 10;
			num += buf - 48;
		}
	}
	filp_close(fp,0);

	set_fs(old_fs);
	
	return ((cpu_2-cpu_1)-(idle_2-idle_1))*100/(cpu_2-cpu_1);
}
