#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/********************************************************************
*Calculo de la norma euclidiana  aplicando comunicación colectiva
*@author   :   Mario Bocanegra Deza
*@email    :   datascientistperu@gmail.com
*@version  :   09/05/2017 v1.0 
********************************************************************/
	
//************* definición de constantes ********************//
#define SIZE 100000
#define CDATOS 25000

//************* declaración de funciones **********************//
double NormaEuclidiana(double X[], int SIZE)


main(int argc,char* argv[])
{
	
	int nroProceso,idProceso,ndat,i,Datos=CDATOS;	

	double X[SIZE],y=0,rsecuencial;
	
		
    double tInicio, // Tiempo en el que comienza la ejecucion
            tFin; // Tiempo en el que acaba la ejecucion
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nroProceso);
	MPI_Comm_rank(MPI_COMM_WORLD,&idProceso);

	

	if(idProceso==0){
				
		for(i=0;i<SIZE;i++) X[i]=rand() % 20; // El vector se llena con nro entero entre 0 y 19 
		

		rsecuencial=NormaEuclidiana(X,SIZE);

	}


	double miVector[CDATOS];
	 // Repartimos una fila por cada proceso, es posible hacer la reparticion de esta
    // manera ya que la matriz esta creada como un unico vector.

   
    
    MPI_Scatter(&X, // Matriz que vamos a compartir
            Datos, // Numero de columnas a compartir
            MPI_DOUBLE, // Tipo de dato a enviar
            &miVector, // Vector en el que almacenar los datos
            Datos, // Numero de columnas a compartir
            MPI_DOUBLE, // Tipo de dato a recibir
            0, // Proceso raiz que envia los datos
            MPI_COMM_WORLD); // Comunicador utilizado (En este caso, el global)
	

    // Hacemos una barrera para asegurar que todas los procesos comiencen la ejecucion
    // a la vez, para tener mejor control del tiempo empleado
    MPI_Barrier(MPI_COMM_WORLD);

     // Inicio de medicion de tiempo
    tInicio = MPI_Wtime();

    double sumparcial=0, globalsum=0;
   

    for(i=0;i<CDATOS;i++) sumparcial+=miVector[i]*miVector[i];
	
    MPI_Reduce(&sumparcial,&globalsum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);     

    printf("Suma Parcial por proceso %d is %f\n", idProceso, sumparcial); 


	
	// Otra barrera para asegurar que todas ejecuten el siguiente trozo de codigo lo
    // mas proximamente posible
    MPI_Barrier(MPI_COMM_WORLD);
    // fin de medicion de tiempo
    tFin = MPI_Wtime();



    MPI_Gather(&globalsum, // Dato que envia cada proceso
            1, // Numero de elementos que se envian
            MPI_DOUBLE, // Tipo del dato que se envia
            &y, // Vector en el que se recolectan los datos
            1, // Numero de datos que se esperan recibir por cada proceso
            MPI_DOUBLE, // Tipo del dato que se recibira
            0, // proceso que va a recibir los datos
            MPI_COMM_WORLD); // Canal de comunicacion (Comunicador Global)
 
     printf("Suma Total por proceso %d is %f\n", idProceso, y); 
	
	MPI_Finalize();	
  


	if (idProceso == 0) {

		printf("\nEl Resultado de la Norma Euclidiana Secuencial es sqrt(%1.2lf)=%1.2lf", rsecuencial,sqrt(rsecuencial));

        printf("\nEl Resultado de la Norma Euclidiana es sqrt(%1.2lf)=%1.2lf", y,sqrt(y));
 
        printf("\nEl tiempo tardado ha sido %1.2lf , segundos.\n",tFin - tInicio); 
 
    }

  

	return 0;
}



double NormaEuclidiana(double X[], int SIZE)
{

    int i=0; 
    double sumparcial=0;

        for(i=0;i<SIZE;i++) 
        	sumparcial+=X[i]*X[i];

   
    return sumparcial;
}

