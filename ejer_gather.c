#include <stdio.h>
#include <mpi.h>

/***************************************************************
@author   :   Mario Bocanegra Deza
@email    :   datascientistperu@gmail.com
@version  :   09/05/2017 v1.0 
***************************************************************/

//************* definición de constantes ********************//
#define ASIZE 20

//************* declaración de funciones **********************//
void imprimirA(int X[], int tam);


void main(int argc, char* argv[])
{   

      int i, j, pSize;
      int arreglo[ASIZE];
      int idProc, nroProcs;

    
      MPI_Init(&argc,&argv);
      MPI_Comm_size(MPI_COMM_WORLD, &nroProcs);
      MPI_Comm_rank(MPI_COMM_WORLD, &idProc);
      
    

       printf("\nSoy el nodo %d de %d procesos", idProc, nroProcs); 

       pSize=(ASIZE/nroProcs);
       int arregloloc[pSize];

       for (j=0; j<ASIZE; j++) arreglo[j]=0; // llena el arreglo con 0

       for(j=0; j<pSize; j++) arregloloc[j]=(idProc*nroProcs) + j;  //llenar el arrgelo con data generada

       printf("\n");
       imprimirA(arregloloc,pSize);

       MPI_Gather(arregloloc,pSize,MPI_INT,arreglo,pSize,MPI_INT,0,MPI_COMM_WORLD);

      
      
       if (idProc==0){ 
           printf("\n***** Arreglo Final *********\n");  
           imprimirA(arreglo,ASIZE);  
       }
      
       MPI_FINALIZE();

}


//********** Definción de Funciones *******************//

void imprimirA(int X[], int tam)
{
    int i;
    for(i=0;i<tam;i++) printf("[%d] => %d; ",i,X[i]); 
}


