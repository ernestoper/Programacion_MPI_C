#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/********************************************************************
*Calculo de la norma euclidiana  aplicando comunicación punto a punto
*@author   :   Mario Bocanegra Deza
*@email    :   datascientistperu@gmail.com
*@version  :   09/05/2017 v1.0.1
********************************************************************/


//************* definición de constantes ********************//
#define TAG 110
#define TAG1 111
#define TAG2 112
#define SIZE  100000
#define CDATOS 25000


//************* declaración de funciones **********************//
void imprimirA(double X[], int tam);
int procesoPar(int idProceso);
double normaEuclidiana(double X[], int nroproc, int factor);


void main(int argc,char* argv[])
{
	
	int nroProceso,idProceso,ndat,i,j,Datos;
	double X[SIZE];
	double Y, Y0,Y1,Y2,Y3=0;
	MPI_Status status;
		
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nroProceso);
	MPI_Comm_rank(MPI_COMM_WORLD,&idProceso);



	for(i=0;i<SIZE;i++)	X[i]=rand() % 20; // El vector se llena con nro entero entre 0 y 19 
			

	Datos=1;

	double  sumtotal,gsub1,sumparcial0,sumparcial1,sumparcial2,sumparcial3=0;

	
	int isPar=0;

	double sumparcial[nroProceso];

	int Proc=0;
	int Peu=nroProceso-1;
	isPar=procesoPar(idProceso+1);
	int TAGL;
		
	if (idProceso!=0){
		
		i=Peu; j=0;
		while(i!=0){	
			if(idProceso==i){	
			
	    		sumparcial[i]=normaEuclidiana(X,nroProceso,j+1);
	    		printf("Suma Parcial por proceso %d is %f\n", idProceso, sumparcial[i]); 
		
				if((idProceso-1)==0){
				  MPI_Recv(&Y1,Datos, MPI_DOUBLE,Peu, TAG1, MPI_COMM_WORLD,&status);

				  gsub1=sumparcial[i]+Y1;	

				  MPI_Send(&gsub1,Datos, MPI_DOUBLE,0, TAG, MPI_COMM_WORLD);

				}else{ 

				   if(isPar){
				   	  Proc=1;
				   	  TAGL=TAG1;
				   }else{ 
				      Proc=0;
				      TAGL=TAG2;
				   }  

				   MPI_Send(&sumparcial[i],Datos, MPI_DOUBLE,Proc, TAGL, MPI_COMM_WORLD);	
				  } 		
			}

			i--;
			j++;
		}
	}

	
	if(idProceso==0){

			MPI_Recv(&Y2,Datos, MPI_DOUBLE,2, TAG2, MPI_COMM_WORLD,&status);	
			MPI_Recv(&Y3,Datos, MPI_DOUBLE,1, TAG, MPI_COMM_WORLD,&status);	

			sumparcial0=normaEuclidiana(X,nroProceso,4);
				

			printf("Suma Parcial por proceso %d is %f\n", idProceso, sumparcial0); 		

			sumtotal=sumparcial0+Y2+Y3;	
				
			printf("\nEl Resultado de la Norma Euclidiana es sqrt(%1.2lf)=%1.2lf \n", sumtotal,sqrt(sumtotal));

	}	
	
	

   	
	MPI_Finalize();		
}


//********** Definición de Funciones *******************//

void imprimirA(double X[], int tam)
{
	int i=0;
    for(i=0;i<tam;i++)
	  printf("\n [%d] ,'',%1.2lf:",i,X[i]);	
}


int procesoPar(int idProceso)
{
  int isTrue=0;
   if(idProceso%2==0){
   		isTrue=1;
   }

   return isTrue;	
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


