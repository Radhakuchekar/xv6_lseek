#include "types.h"
#include "x86.h"
#include "date.h"
#include "mmu.h"
#include "proc.h"
#include "defs.h"
#include "param.h"
#include "fs.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "file.h"
#include "memlayout.h"
#include "syscall.h"
int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
uint lseek(int fd, uint offset, int whence){
	struct file *f;
	int n;
	char *p;
	if(argfd(0, 0, &f) < 0 || argint(2, &n) < 0 || argptr(1, &p, n) < 0)
		return 0;
	if (offset < 0)
        	return 0;
	if (offset > n)
		return 0;
	switch (whence) {
		
	        case SEEK_END:
			ilock(f->ip);
			offset += n;
			f -> off = offset;
			iunlock(f->ip);
			return f->off;
	        case SEEK_CUR:
			ilock(f->ip);
			
			if (offset != f->off) {
				f->off += offset;
			}
                	iunlock(f->ip);
			return f->off;
	        case SEEK_SET:
			ilock(f->ip);
			f -> off = offset;
			iunlock(f->ip);
			return f->off;
	}
	return 0;
		
}

