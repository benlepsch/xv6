#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "kalloc.h"

int sys_getpagetableentry(void) {
  // getpagetable() returns actual contents of pte, walkpgdir() returns location of the content, 
  // don't just return the pointer, you'll get incorrect results that might look right

  int pid;
  int address;

  if ((argint(0, &pid) < 0) || (argint(1, &address) < 0))
    return -1;

  return getpagetableentry(pid, address);
}

int sys_isphysicalpagefree(void) {
  /**
   * Add a new system call int isphysicalpagefree(int ppn) that returns 
   * a true value if physical page number ppn is on the free list managed 
   * by kalloc.c and a false value (0) otherwise.
  */

  int ppn;
  if (argint(0, &ppn) < 0)
    return -1;
  
  return isphysicalpagefree(ppn);
}

int sys_dumppagetable(void) {
  /**
   * There's a lot for this one
   * just go read the assignment
  */

  int pid;
  if (argint(0, &pid) < 0)
    return -1;
  
  dumppagetable(pid);

  return 0;
}

int sys_settickets(void) {
	int tickets;
	if (argint(0, &tickets) < 0)
		return -1;
	myproc()->tickets = tickets;
	return 0;
}

int
sys_getprocessesinfo(void)
{
	struct processes_info *p;
	if (argptr(0, (void*)&p, sizeof(*p)) < 0)
		return -1;
	
	getprocessesinfo(p);
  return 0;
}

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

int
sys_yield(void)
{
  yield();
  return 0;
}

int sys_shutdown(void)
{
  shutdown();
  return 0;
}
