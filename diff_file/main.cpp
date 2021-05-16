#include "main.h"


int main(int lenArg, char *arguments[]){
	clock_t start, stop;
	bool res;
	start = clock();
	if(lenArg == 3){
		res = src_cmp(arguments[1], arguments[2]);
		if(res){
			printf("identical contents of folders\n");
		}else{
			printf("folder contents are not identical\n");
		}
	}else{
		printf("try again %s fileA fileB\n", arguments[0]);
	}
	stop = clock();
	printf("%.2f ms\n", (float)((stop-start)*1000) / CLK_TCK);
	return 0;
}
