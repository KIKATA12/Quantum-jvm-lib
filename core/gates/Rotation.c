#include <complex.h>
#include <math.h>

typedef struct 
{
    double complex alpha;
    double complex beta;
}QubitC;

//rotation around the X-axis by angle theta
void rotationX(QubitC* qubit, double theta){
    double c = cos(theta/2);
    double s = sin(theta/2);
    double complex temp0 = c*qubit->alpha - I*s*qubit->beta;
    double complex temp1 = -I*s*qubit->alpha + c*qubit->beta;
    qubit->alpha = temp0;
    qubit->beta = temp1;            
}  

//rotation around the Y-axis by angle theta
void rotationY(QubitC* qubit, double theta){
    double c = cos(theta/2);
    double s = sin(theta/2);
    double complex temp0 = c*qubit->alpha - s*qubit->beta;
    double complex temp1 = s*qubit->alpha + c*qubit->beta;
    qubit->alpha = temp0;
    qubit->beta = temp1;
}

//rotation around the Z-axis by angle theta
void rotationZ(QubitC* qubit, double theta){
    double complex temp0 = cexp(-I*theta/2)*qubit->alpha;
    double complex temp1 = cexp(I*theta/2)*qubit->beta;
    qubit->alpha = temp0;
    qubit->beta = temp1;
}