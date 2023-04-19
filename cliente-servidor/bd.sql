create database so;

create table vehiculo(
	placa varchar (10) primary key,
	capacidad_vol float,
	capacidad_peso float
);

insert into vehiculo values ('FGH-19-56', 7000, 450.50);
insert into vehiculo values ('ADN-18-55', 6000, 400.50);
insert into vehiculo values ('THV-17-54', 5000, 390.50);
insert into vehiculo values ('KIM-16-53', 6000, 300.50);

create table viaje ( 
	num_viaje int PRIMARY KEY,
	placa varchar REFERENCES vehiculo (placa),
	fecha date,
	cantidad_envios int
);
1
insert into viaje values (1, 'FGH-19-56','2022-02-17', 5);
insert into viaje values (2, 'FGH-19-56','2022-03-01', 3);

create table envios (
	num_envio int primary key,
	placa varchar REFERENCES vehiculo (placa),
	fecha_envio date,
	volumen float,
	peso float,
	destino varchar
);

insert into envios values (1, 'FGH-19-56', '2022-02-17', 6000.1, 260.5, 'Monterrey');
insert into envios values (2, 'ADN-18-55', '2022-02-26', 408.30, 200, 'Tapachula,Chiapas');
insert into envios values (3, 'THV-17-54', '2022-03-19', 5000, 180, 'Sinaloita,Sinaloa');
insert into envios values (4, 'KIM-16-53', '2023-09-23', 1500.80, 380, 'Tamaulipas');
insert into envios values (5, 'FGH-19-56', '2023-09-07', 1350.99, 240, 'Tapachula,Chiapas');

create table almacen (
	id_local int primary key,
	nombre varchar,
	direccion varchar
);

insert into almacen values (1, 'Perez Hermanos', 'Monterrey');F
insert into almacen values (2, 'Abarrotes LOO', 'Tapachula');
insert into almacen values (3, 'CHEDRAUI', 'sinaloa');

create table tienda (
	num_local int primary key,
	id_local int REFERENCES almacen (id_local),
	nombre varchar,
	direccion varchar
);

insert into tienda values (1, 1, 'Perez Hermanos', 'Monterrey');
insert into tienda values (2, 2, 'Abarrotes LOO', 'Oaxaca');
insert into tienda values (3, 3, 'CHEDRAUI', 'Veracruz');

CREATE TABLE envio_tienda(
  	num_envio INT,
	num_local INT,
	PRIMARY KEY (num_envio, num_local),
	FOREIGN KEY (num_envio) REFERENCES envios(num_envio),
	FOREIGN KEY (num_local) REFERENCES tienda(num_local) 
);

insert into envio_tienda values (1,1);
insert into envio_tienda values (1,2);
--cuando es entidad DEBIL si van las dos llaves primarias dentro de la entidad
--de muchos a muchos.

--    • Mostrar cada una de las tiendas a las que los camiones entregaron envios.
--    • Mostrar los envios que viajaron en el camion con numero de placa FGH-19-56.
--    • Mostrar los nombres de las tiendas que recibieron envios con un peso mayor que 250kg y un volumen mayor que 5000 unidades.
--    • Mostrar los envios que llegaron a la tienda Perez Hermanos en Monterrey asi también mostrar los camiones que llevaron dichos envios y en que viaje fueron trasladados.
--    • Datos del camion que mas viajes ha realizado a la tienda Perez Hnos. Chiapas
--    • A que tiendas se han realizado envios de mas de 1300 piezas (volumen de mas de 1300) y Cuantos se han sido.
--   • Camiones que han superado su capacidad de peso 4 veces.
--    • Mes en el que se han hecho menos viajes
--    • Mes en el que se han hecho mas viajes
--    • Procedimiento almacenado que realice el reporte siguiente: muestre todos los viajes que ha realizado cada camion en cierto periodo determinado y a que tiendas les ha llevado envio en cada viaje, ordenados según la cantidad de piezas que lleva(volumen). DE parametros debe recibir el rango de fechas
--    • PROCEDMIENTO almacenado que reciba de parametros el nombre de la tienda y el año, y que nos muestre el mes en que esa tienda ha recido mas envios(entregas) y numero de envios, de igual forma el mes en el que han sido menos.



select *
  from envios as a
  right join  envio_ tienda as b
  on codigoautor=a.codigo
  left join editoriales as e
  on codigoeditorial=e.codigo;



CALL tienda_envios('Perez Hermanos', 2022);

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CREATE OR REPLACE PROCEDURE reporte_viajes(rango_fechas daterange)
AS $$
DECLARE
    Viaje INTEGER;
    placa_auto TEXT;
    Tienda INTEGER;
    Nombre TEXT;
    Direccion TEXT;
    No_Envio INTEGER;
    Volumen float;
BEGIN
  SELECT
    v.num_viaje,
    v.placa,
    t.num_local,
    t.nombre,
    t.direccion,
    e.num_envio,
    e.volumen
  FROM
    viaje v
    JOIN envios e ON e.placa = v.placa
    JOIN envio_tienda et ON et.num_envio = e.num_envio
    JOIN tienda t ON t.num_local = et.num_local
  WHERE
    v.fecha <@ rango_fechas
  ORDER BY
    v.placa,
    e.volumen DESC
    INTO Viaje, placa_auto, Tienda, Nombre, Direccion, No_Envio, Volumen;
     
    RAISE NOTICE 'Viaje % PLACA DEL AUTO % TIENDA %, % Direccion % Numero de envio % Con un volumen %',Viaje, placa_auto, Tienda, Nombre, Direccion ,No_Envio, Volumen;
    
END;
$$ LANGUAGE plpgsql;


CALL reporte_viajes('(2022-02-01,2022-03-20)');

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------








