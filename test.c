#include <unistd.h>
#include <stdio.h>


int main()
{
	char s[100];
  
    // printing current working directory
    printf("%s\n", getcwd(s, 100));
  
    // using the command
    chdir("/");
  
    // printing current working directory
    printf("%s\n", getcwd(s, 100));
  
    // after chdir is executed
    return 0;
}