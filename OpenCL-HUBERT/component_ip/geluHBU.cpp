#include "geluHBU.h"
#include "HLS/math.h"

int geluHBU(int input, int b, int c, int shift){ //b and c are undone scaling factors
    int sigmoid = int_erf(input, b, c);
	sigmoid = sigmoid + shift;
	return input * sigmoid;
}

int int_erf(int input, int b, int c) {
	//x_int is normally 22x1x3072, while our scaling factor constants are 1x3072
	int sign;
	if (input >= 0) sign = 1;
	else sign = -1;
	int abs_int = abs(input);
	abs_int = (abs_int < -b) ? abs_int : -b; //min (abs_int, -b)
	int y = pow(abs_int + b, 2) + c;
	y = sign * y;
	y = y / (1 << 14);
	return y;
}