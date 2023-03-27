#include <stdlib.h>
#include <string.h>  //libreria read y write
#include <stdio.h>
#include <unistd.h>


#define MAXIMA_LONGITUD_CADENA 50

void main (){

	char cad[50], cad2 [50];
	int pipep[2], pipeh[2];
	
	int cadena;
	
	pipe (pipep); ///padre
	pipe (pipeh); ///hijo
	int id = fork();

	do{
	  switch(id){

	    case -1: // Error
                printf("Ha habido un error \n");
                exit(-1);
                break;
            case 0: // Hijo
                scanf("%s",&cad);
                write(pipep[1],cad,sizeof(cad));
                fgets(cad, 50, stdin);
                printf("Escribe el hijo... %s\n",cad2);
                read(pipeh[0],cad2,sizeof(cad2));
                memset(cad2,0,50);
                if(strcmp(cad,"ok")==0){
                   exit(0);
                  }
                
                break;
            default: // Padre
            	fgets(cad2, 50, stdin);
            	printf("Escribe el padre... %s\n",cad);
                read(pipep[0],cad,sizeof(cad));
                memset(cad,0,50);
                scanf("%s",&cad2);
                write(pipeh[1],cad2,sizeof(cad2));
                if(strcmp(cad,"ok")==0){
                   exit(0);
                  }
                break;
	    
	   }
	 
	 }while(strcmp (cad2, "ok") !=0);
	 close(pipep[1]);
	 close(pipeh[0]);
	 

    return 0;
}
