#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// 프로세스 id 출력
int main(void)
{
	printf("Process ID	= %d\n", getpid());		// 프로세스 id
	printf("Parent process ID  = %d\n", getppid());		// 부모 프로세스 id
	printf("Real user ID	   = %d\n", getuid());		// 사용자 id
	printf("Effective user ID  = %d\n", geteuid());		// 유효 사용자 id
	printf("Real group ID	   = %d\n", getgid());		// 그룹 id
	printf("Effective group ID = %d\n", getegid());		// 유효 그룹 id
	exit(0);
}