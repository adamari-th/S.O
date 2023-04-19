#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

//gcc -o proyectocli proyecto.c -I /usr/include/postgresql -lpq


struct vehiculo {
	char placa [10];
	float capacidad_vol;
	float capacidad_peso;
}vehiculo;

struct viaje {
	int num_viaje;
	char placa [10];
	//date fecha;
	int cantidad_envios;
}viaje;


void altavehiculo(){
	int fd1, fd2;
	char consulta[300];

	fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
	
	printf("\t\t---- Alta del VEHICULO----\n");
	printf("Ingrese la placa: ");
	scanf(" %s", vehiculo.placa);
	printf("Ingrese la capacidad del volumen que soportara: ");
	scanf(" %f", &vehiculo.capacidad_vol);
	printf("Ingrese la capacidad del peso que soportara: ");
	scanf(" %f", &vehiculo.capacidad_peso);
	
	snprintf(consulta, sizeof(consulta),"INSERT INTO vehiculo(placa, capacidad_vol, capacidad_peso) VALUES ('%s',%f,%f)", vehiculo.placa,vehiculo.capacidad_vol,vehiculo.capacidad_peso);
	write(fd1,consulta, sizeof(consulta));

	close(fd1);
}


int main(){
	
	int Opc, fd1;
	char * consulta[30], opcMenu[2];
	
	do{
		system("clear");
		printf("\t\t ----------------------------------\n");
		printf("\n\t\t |MENU - CAMIONEROS| \n");
		printf("\t\t ----------------------------------\n\n");
        	printf("1. Vehiculo\n");
	        printf("2. Envios\n");
		printf("3. Viaje\n");
		printf("4. Tienda\n"); 
		printf("5. Almacen\n");
		printf("6. Salir\n");
		printf("ELige una opcion: ");
		scanf("%d",&Opc);

		sprintf(opcMenu,"%d",Opc);
		fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
		write(fd1,opcMenu,sizeof(opcMenu));
		close(fd1);
		switch (Opc){
			case 1:
				do
				{
					system("clear");
					memset(opcMenu, '\0', sizeof(opcMenu));

					printf("\n\t\t Control de Vehiculo\n");
					printf("\t\t -------------------------\n");
					printf("1. Alta de Vehiculo\n");
					printf("2. Baja de Vehiculo\n");
					printf("3. Actualizacion de Vehiculo\n");
					printf("4. Consulta de los vehiculos\n");
					printf("5. Salir\n");
					printf("Elige una opcion: ");
					scanf("%d",&Opc);
					sprintf(opcMenu,"%d",Opc);

					fd1 = open("/tmp/cliente_a_servidor", O_WRONLY);
					write(fd1,opcMenu,sizeof(opcMenu));
					close(fd1);

					switch (Opc)
					{
						case 1:
							system("clear");
							altavehiculo();
							system("sleep 1.2");

						break;
						case 2:
							system("clear");
							/*bajavehiculo();
							system("sleep 1.2");
							*/
						break;
						case 3:
							system("clear");
							/*actualizarvehiculo();
							system("sleep 1.2");
							*/
							
						break;
						case 4:
							system("clear");
							/*consultavehiculo();
							system("sleep 5.0");
							*/
						break;
						default:
							if (Opc >= 6 || Opc == 0){
							system("clear");
								printf("\t\t----------------ERROR------------------\n");
								printf("Mensaje amigo: Opcion incorrecta, intentalo de nuevo\n");
								system("sleep 1.8");
							}
						break;
					}
				} while (Opc != 5);
			break;
			case 2:
				
			break;
			case 3:
		
			break;
			
		}
	}while(Opc != 6);
	return 0;
}
