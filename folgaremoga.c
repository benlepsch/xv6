#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char **argv)
{
	
	printf(1, "%d\n", writecount());
	setwritecount(0);
	printf(1, "%d\n", writecount());
	exit();
}
