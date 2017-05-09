#include <mpi.h>
#include <stdio.h>


/********************************************************************
*Envio de un arreglo usando comunicacion pto a pto
*@author   :   Mario Bocanegra Deza
*@email    :   datascientistperu@gmail.com
*@version  :   09/05/2017 v1.0 
********************************************************************/

//************* definición de constantes ********************//
#define TAG 111
#define N 10 

main(int argc,char* argv[])
{
	
	int myrank,nprocs,ndat,i;
	
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);


	if(myrank==0){
		double X[10]={0,1,2,3,4,5,6,7,8,9};
		MPI_Send(&X[0],10, MPI_DOUBLE,1, TAG, MPI_COMM_WORLD);
			
	}else if(myrank==1){

		double Y[10]={0};
		MPI_Status status;

		printf("\nvalor de Y[] en Pr %d antes de recibir datos\n\n",myrank);
			for (i=0; i<N; i++) printf("%1.2lf", Y[i]);
		printf("\n\n");
		
		MPI_Recv(&Y[0],10, MPI_DOUBLE,0, TAG, MPI_COMM_WORLD,&status);	
		//MPI_Recv(Y,10, MPI_DOUBLE,MPI_ANY_SOURCE, MPI_ANY_TAG,MPI_COMM_WORLD,&status);

		printf("Pr %d recibe Y[] de Pr %d: TAG, %d, N %d \n\n",myrank,status.MPI_SOURCE, status.MPI_TAG, N);
		for (i=0; i<N; i++) printf("\n %1.2lf \n", Y[i]);
		

	}

    

	MPI_Finalize();	
	return 0;
}