#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/********************************************************************
*Calculo de la norma euclidiana  aplicando comunicación punto a punto
*@author   :   Mario Bocanegra Deza
*@email    :   datascientistperu@gmail.com
*@version  :   09/05/2017 v1.0 
********************************************************************/


//************* definición de constantes ********************//
#define TAG 110
#define TAG1 111
#define TAG2 112
#define SIZE 100000 
#define CDATOS 25000


//************* declaración de funciones **********************//
void imprimirA(double X[], int tam);
double normaEuclidiana(double X[], int nroproc, int factor);



void main(int argc,char* argv[])
{
	
	int nroProceso,idProceso,ndat,i,j,Datos;
	double X[SIZE];
	double Y, Y0,Y1,Y2,Y3;
	MPI_Status status;
		
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nroProceso);
	MPI_Comm_rank(MPI_COMM_WORLD,&idProceso);



	for(i=0;i<SIZE;i++)	X[i]=rand() % 20; // El vector se llena con nro entero entre 0 y 19 
		
	

	Datos=1;

	double  sumtotal,gsub1,sumparcial0,sumparcial1,sumparcial2,sumparcial3=0;

	if(idProceso==3){	
		
				
    	sumparcial3=normaEuclidiana(X,nroProceso,1);


    	printf("Suma Parcial por proceso %d is %f\n", idProceso, sumparcial3); 	
    	
    	
		MPI_Send(&sumparcial3,Datos, MPI_DOUBLE,1, TAG1, MPI_COMM_WORLD);
		
		 
	}else if(idProceso==1){

    		
		MPI_Recv(&Y1,Datos, MPI_DOUBLE,3, TAG1, MPI_COMM_WORLD,&status);

		sumparcial1=normaEuclidiana(X,nroProceso,2);

		gsub1=sumparcial1+Y1;	




		printf("Suma Parcial por proceso %d is %f\n", idProceso, sumparcial1);	
		
		MPI_Send(&gsub1,Datos, MPI_DOUBLE,0, TAG, MPI_COMM_WORLD);


	}else if(idProceso==2){

		

		sumparcial2=normaEuclidiana(X,nroProceso,3);


    	printf("Suma Parcial por proceso %d is %f\n", idProceso, sumparcial2);	

    	MPI_Send(&sumparcial2,Datos, MPI_DOUBLE,0, TAG2, MPI_COMM_WORLD);	

					

	}if(idProceso==0){
			
		MPI_Recv(&Y2,Datos, MPI_DOUBLE,2, TAG2, MPI_COMM_WORLD,&status);	
		MPI_Recv(&Y3,Datos, MPI_DOUBLE,1, TAG, MPI_COMM_WORLD,&status);	

		

		sumparcial0=normaEuclidiana(X,nroProceso,4);
			
		
		//imprimirA(X0,5);

		printf("Suma Parcial por proceso %d is %f\n", idProceso, sumparcial0); 		

		sumtotal=sumparcial0+Y2+Y3;	
			

		printf("\nEl Resultado de la Norma Euclidiana es sqrt(%1.2lf)=%1.2lf \n", sumtotal,sqrt(sumtotal));
			
	}


	MPI_Finalize();		
}


//********** Definción de Funciones *******************//

void imprimirA(double X[], int tam)
{
	int i=0;
    for(i=0;i<tam;i++)
	  printf("\n [%d] ,'',%1.2lf:",i,X[i]);	
}



double normaEuclidiana(double X[], int nroproc, int factor) 
{

    int i,inicio=0;
    int n = (SIZE/nroproc)*factor;
    double sumparcial=0;

    inicio=n-CDATOS;

        for(i=inicio;i<n;i++) 
        	sumparcial+=pow(X[i],2);

   
    return sumparcial;
}
