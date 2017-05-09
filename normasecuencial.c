#include <math.h>
#include <stdio.h>


/********************************************************************
*Calculo de la norma euclidiana  de forma secuencial
*@author   :   Mario Bocanegra Deza
*@email    :   datascientistperu@gmail.com
*@version  :   09/05/2017 v1.0 
********************************************************************/


//************* definición de constantes ********************//
#define SIZE 100000

int main()
{
	double X[SIZE];
	int i;

	for(i=0;i<SIZE;i++) X[i]=rand() % 20; // El vector se llena con nro entero entre 0 y 19 
	


	double sumparcial=0;

    for(i=0;i<SIZE;i++) sumparcial+=X[i]*X[i];

    double y=sqrt(sumparcial);	

    printf("sqrt(%lf) = %lf\n", sumparcial,y);
    return 0;
}