#include<linux/kernel.h>
#include<linux/linkage.h>
#include<linux/fs.h>
#include<asm/uaccess.h>
asmlinkage int sys_cpu_uti(void)
{
	long long ary[9];
	long long cpu_1 = 0, cpu_2 = 0, idle_1;
	struct fILE *fp;

	mm_segment_t old_fs;
	old_fs = get_fs();
	set_fs(KERNEL_DS);
	
	fp = filp_open("/proc/stat", O_RDONLY);
	
	char buf;
	int count = 0;
	long long tmp = -1,num = 0; 
	while(count < 9){
		fp->f_op->read(fp,buf,1,&fp->f_pos);
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
	filp_close(fp);
	count = 0;	
	for(int i=0;i<9;i++){
		cpu_1 += ary[i];
	}
	idle_1 = ary[3];

	fp = filp_open("/proc/stat", O_RDONLY);
	while(count < 9){
		fp->f_op->read(fp,buf,1,&fp->f_pos);
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
	filp_close(fp);	
	for(int i=0;i<9;i++){
		cpu_2 += ary[i];
	}

	set_fs(old_fs);
	
	return (ary[3]-idle_1)*100/(cpu_2-cpu_1);
}
