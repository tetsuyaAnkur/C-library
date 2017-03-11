//Demo program for the "intal" library of integers of arbitrary length.
//intal stands for "int"eger of "a"rbitrary "l"ength.

#include <stdio.h>
#include "just.h"

int main() {
	intal* i1 = create_intal();
	intal* i2 = create_intal();
	intal* i3 = create_intal();
	intal* i4 = create_intal();
	intal* i5 = NULL;

	read_intal(i1, "-999909099090900909");
	read_intal(i2, "-4");
	read_intal(i3, "99990909900989090");
	read_intal(i4, "32");

	printf("i1 = ");
	print_intal(i1);
	printf("\n");

	printf("i2 = ");
	print_intal(i2);
	printf("\n");
	
	printf("i3 = ");
	print_intal(i3);
	printf("\n");
	
	printf("i4 = ");
	print_intal(i4);
	printf("\n");

	intal* new1=add_intal(i1,i3);
	printf("add_intal(i1,i3) = %s\n\n",new1->s);

	intal* new2=subtract_intal(i1,i3);
	printf("subtract_intal(i1,i3) = %s\n\n",new2->s);

	intal* new3=multiply_intal(i1,i3);
	printf("multiply_intal(i1,i3) = %s\n\n",new3->s);

	int new4=divide_intal(i1,i3);
	printf("divide_intal(i1,i3) = %d\n\n",new4);

	intal* new5=pow_intal(i2,i4);
	printf("pow_intal(i2,i4) = %s\n\n",new5->s);
	
	delete_intal(&i1);
	delete_intal(&i2);
	delete_intal(&i3);
	delete_intal(&i4);

	return 0;
}