#include <stdio.h>


int main(){

	int r,g,b;
	r = g = b = 255;
  printf("P3\n %d \t %d\n 255\n", 255, 255);

	for(int i=0; i<255; i++){
		for(int j=0; j<255; j++)
{
	printf("%d \t %d \t %d \n",r-1,g-1,b-1);
	if (r==0) r = g = b = 255;
}
}

	return 0;
}
