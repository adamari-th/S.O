#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libpq-fe.h>
#include <time.h>
#include <string.h>

//gcc -o proyectoSer proyecto_servidor.c -I /usr/include/postgresql -lpq

PGconn *conn;   	// conexion
PGresult *res;  	// resultado


void altavehiculo(){
	int fd1,fd2;
	char consulta[1024], mensaje[200];

	fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
	read(fd1, consulta, sizeof(consulta));
	res = PQexec(conn, consulta);
	
	//printf("%s", consulta);
	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		fd2 = open("/tmp/servidor_a_cliente", O_WRONLY);
		sprintf(mensaje, "Error al insertar");
		write(fd2,mensaje, sizeof(mensaje));
		PQclear(res);
		PQfinish(conn);
		close(fd2);
		exit(1);
	}
	
	PQclear(res);
	
	close(fd1);
	
	//
}


int main(){
	
	time_t tiempo = time(0);
	struct tm *tlocal = localtime(&tiempo);
	char output[128];
	
	/// CONEXION A LA BASE DE DATOS //
	conn = PQsetdbLogin("localhost","5432",NULL,NULL,"camioneros","postgres","passwordseguro"); 	
	printf("CONECTANDO CON POSTGRESQL\n");


	// SE COMPRUEBA QUE HAYA CONECTADO ///
	if (PQstatus(conn) != CONNECTION_BAD){
		strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
		printf("\t\tSERVIDOR %s\n",output);
			
		mkfifo("/tmp/servidor_a_cliente", 0666);
		mkfifo("/tmp/cliente_a_servidor", 0666);

		char opcionMenu[2];
		int fd1,fd2, Opc;
		do{
			/// MENU PRINCIPAL PARA ENTRAR A LA TABLAS //
	       	        printf("Servidor - Inicio\n");
			fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);

			read(fd1,opcionMenu,sizeof(opcionMenu));
			close(fd1);
			Opc = atoi(opcionMenu);
		         switch(Opc){
			   case 1:
			    	  do{
				      	system("sleep 2");
				      	printf("Servidor Menu - Vehiculo\n");
				      	memset(opcionMenu, '\0', sizeof(opcionMenu));
					fd1 = open("/tmp/cliente_a_servidor", O_RDONLY);
					read(fd1,opcionMenu,sizeof(opcionMenu));
					close(fd1);
					Opc = atoi(opcionMenu);
						
					switch (Opc){
						case 1:
							system("clear");
							printf("SERVIDOR - ALTA DEL CAMION\n");
							close(fd1);
							altavehiculo();
							system("sleep 2");
							break;
						case 2:
							system("clear");
							printf("SERVIDOR - BAJA DE PROPIETARIO\n");
							//close(fd1);
							//bajavehiculo();
							system("sleep 2");
							break;
						case 3:
							printf("SERVER - Actualizacion de propietario\n\n ");
							//close(fd1);
							//actualizarvehiculo();
							system("sleep 2");
							break;
						case 4:
							system("clear");
							printf("SERVIDOR - LISTA DE PROPIETARIOS\n ");
							//close(fd1);
							//consultavehiculo();
							system("sleep 2");
							break;
						
						default:
							if(Opc >= 6 || Opc == 0){
								printf("OPCION INVALIDA En el servidor.\n");
								system("sleep 1.8");
								system("clear");
							}
							break;
						}
					}while (Opc != 5);
			   break;
									
			   case 2:
			    system("clear");
				printf("\tSistema de Envios\n");
				/* 
			          Aqui iran todo el ingreso de los envios hecho o a realizar
			        
			        */
                                				  
			   break;
			   
			   case 3:
			   system("clear");
				printf("\tSistema de Viaje\n");
				/* 
			          Aqui iran el registro de los viajes realizados, con
			          sus diferentes campos a llenar.
			        */
                                
			   break;
				
			   case 4:
			   system("clear");
				printf("\tSistema de Tienda\n");
			   	/* 
			          Aqui iran el ingreso de las tiendas
			          para que asi se obtenga el id de la tienda
			          y se estructure con el envio y el lugar del destino.
			        */
                                
			   break;
			   
			   case 5:
			   system("clear");
				printf("\tSistema de Almacen\n");
			   	/* 
			          Se mostraran los almacenes existentes en una tabla
			        
			        */
                                
			   break;
				
		         }
		}while(Opc!=6);
	}
	 else{
	 	/// MENSAJE EN CASO DE MOSTRAR FALLO A LA CONEXION A POSTGRES //
		printf("Fallo la conexion\n");
	 }
}
