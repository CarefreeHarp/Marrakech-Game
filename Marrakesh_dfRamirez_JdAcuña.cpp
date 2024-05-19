#include <iostream>
#include <windows.h>																													//librería para poner color
#include <fstream>																														//librería para archivoc
#include <ctime>																														//Librería para el dado						
using namespace std;

#define color SetConsoleTextAttribute																									//linea para poder poner color




struct player																															//declaracion de player como estructura
{
	char nombre[30];
	int alfombras;
	int dirhams;
};
struct posicion
{
	int posx;
	int posy;
};
struct caracteristicas
{
	posicion pos;
	char hassam;
};
struct Resultadoimpuestos
{
	int impuestos;
	int posdelvector;
};
struct Puntosfinales
{
	int puntos1=0;
	int puntos2=0;
};




caracteristicas movimiento(int tablero[][7],caracteristicas hassam,posicion adyacentes[]);
caracteristicas mediavuelta(caracteristicas hassam,int i, int casillas);
char UsoAlfombras(int tablero[][7],posicion adyacentes[], int NumdeAlfombra);
void imprimirtablero(int tablero[][7],caracteristicas hassam);
Resultadoimpuestos evaluarimpuestos(int tablero[][7],int posx,int posy,bool turno,posicion evaluadas[],Resultadoimpuestos resultadoimpuestos);
Puntosfinales calculo(int tablero[][7],player player1,player player2,Puntosfinales puntosfinales);





int main() 
{
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );																				//linea para poner color
    system("color e0");																													//linea cambio de color a fondo amarillo
	color(hConsole, 224);																												//linea cambio de color a letra negra y fondo amarillo
    player player1,player2;																												//declaracion de variables
    bool ganador=false;
    int tablero[7][7];				   
    int i,j,turnos=1;
    int NumdeAlfombra1=3,NumdeAlfombra2=2;
    int posx,posy;
    int op;
    bool turno;
    bool partidacargada=false;
    char nombrepartida[100];
    char eliminador[1];
    caracteristicas hassam;
    posicion adyacentes[4],evaluadas[49];
    Resultadoimpuestos resultadoimpuestos;
    Puntosfinales puntosfinales;
    
    cout<<"Bienvenido, que desea hacer?"<<endl<<"1. Cargar una partida"<<endl<<"x. presione cualquier numero para empezar a jugar"<<endl;
    cin>>op;																															//despues del cin>>op, se lee la opción pero en la memoria queda un \n como el enter que da el usuario para continuar
    cin.getline(eliminador,1,'\n');																										//getline lee lo que habia previamente en la memoria y que no quedó en "op" por lo cual lee \n y eso queda en eliminador[0]
    switch(op)
	{																														
    	case 1: {
    		cout<<"Con que nombre aparece su archivo de partida?"<<endl;
    			cin.getline(nombrepartida,100,'\n');																					//de no ser por el comentario de arriba, este getline leería el \n del cin y se cerraría automáticamente
    			ifstream partida(nombrepartida);																						//declara la entrada para leer un tablero guardado en un archivo .txt
    			if(!partida){
    				cout<<"Su archivo de partida no ha sido encontrado, verifique: "<<endl<<"1. Haber escrito .txt al final del nombre del archivo"<<endl<<"2. Tener el archivo en la misma carpeta donde tiene este programa"<<endl<<"3. De ser el caso, haber escrito los respectivos espacios en el nombre del archivo "<<endl<<endl;
				}
				else{
					partidacargada=true;
					partida>>hassam.hassam;
					for(i=0;i<7;i++)
					{
						for(j=0;j<7;j++)
						{
							partida>>tablero[i][j];
							if(tablero[i][j]<0)
							{
								hassam.pos.posx=j;
								hassam.pos.posy=i;
							}
						}
					}
					partida>>player1.alfombras;
					partida>>player1.dirhams;
					partida>>player2.alfombras;
					partida>>player2.dirhams;
					partida>>turnos;
					partida>>turno;
				}
    			break;
		}
		default: break;
    
	}
	if(partidacargada==false){
		for(i=0;i<7;i++)																												//llena la matriz de alfombras y coloca a hassam en el medio en caso de que no se haya cargado una partida
		{
			for(j=0;j<7;j++)
			{
				tablero[i][j]=0;
				if((i==3)&&(j==3))
				{
					tablero[i][j]=-1;
					hassam.pos.posx=j;
					hassam.pos.posy=i;
					hassam.hassam='v';
				}
			}
		}
  	    player1.alfombras=10;																												//establecer valores iniciales
   	    player2.alfombras=10;
    	player1.dirhams=20;
   		player2.dirhams=20;
   		turno=true;
	}
	
	cout<<endl<<"Digite el nombre del primer jugador! (jugador rojo)"<<endl;
	cin.getline(player1.nombre,30,'\n');
	cout<<"Digite el nombre del segundo jugador! (jugador azul)"<<endl;
	cin.getline(player2.nombre,30,'\n');
	

	while(ganador==false)																												//mientras no encuentre ganador, se ejecutará todo el juego
	{
		imprimirtablero(tablero,hassam);																								//DESACTIVAR PARA IMPRIMIR LA MATRIZ EN FORMA NUMÉRICA
/*		for(i=0;i<7;i++)																												//ACTIVAR PARA IMPRIMIR LA MATRIZ EN FORMA NUMÉRICA
    	{
			for(j=0;j<7;j++)
			{
				cout<<tablero[i][j]<<"\t";
			}
			cout<<endl;
		}*/
		if(turnos!=1){
			cout<<endl<<"Desea guardar esta partida?"<<endl<<"1. Guardar"<<endl<<"2. Seguir jugando"<<endl<<"0. Salir del juego"<<endl;
			cin>>op;
			switch(op)
			{
				case 1: 
				{
					cout<<"Digite el nombre de su partida con .txt al final"<<endl;
						cin.getline(eliminador,1,'\n');
						cin.getline(nombrepartida,100,'\n');
						ofstream guardar(nombrepartida);
						if(!guardar)
						{
							cout<<"No se pudo crear el archivo de la partida"<<endl;
						}
						else
						{
							guardar<<hassam.hassam<<endl;
							for(i=0;i<7;i++)
							{
								for(j=0;j<7;j++)
								{
									guardar<<tablero[i][j]<<" ";
								}
								guardar<<endl;
							}	
							guardar<<player1.alfombras<<" "<<player1.dirhams<<" "<<player2.alfombras<<" "<<player2.dirhams;
							guardar<<" "<<turnos<<" "<<turno;
						}	
					
					break;
				}
						
				case 2:	break;
				
				case 0: exit(1);
						break;
						
				default: break;
			}	
		}

		
		color(hConsole,228); 																											//Decoración de cada turno
		cout<<endl<<endl<<"\t\t\t\t\t\t\tTURNO #"<<turnos<<endl;
		turnos++;
		color(hConsole,224);
		
		color(hConsole,228);
		cout<<"A "<<player1.nombre;
		color(hConsole,224);
		cout<<" LE QUEDAN "<<player1.alfombras<<" ALFOMBRAS Y "<<player1.dirhams<<" DIRHAMS"<<endl;
			
		color(hConsole,233);
		cout<<"A "<<player2.nombre;
		color(hConsole,224);
		cout<<" LE QUEDAN "<<player2.alfombras<<" ALFOMBRAS Y "<<player2.dirhams<<" DIRHAMS"<<endl;										//Fin de la decoración de cada turno
			
		if(turno==true){																												//Indica el turno del jugador correspondiente																								
			cout<<endl<<"Turno de ";
			color(hConsole,228);
			cout<<player1.nombre;
			color(hConsole,224);
			cout<<" !";
		}
		else{
			cout<<endl<<"Turno de ";
			color(hConsole,233);
			cout<<player2.nombre;
			color(hConsole,224);
			cout<<" !";
		}
		
		hassam=movimiento(tablero,hassam,adyacentes);																					//Movimiento de hassam
		
		for(i=0;i<49;i++)																												//Reinicio de variables para la función de impuestos
		{
			evaluadas[i].posx=-1;
			evaluadas[i].posy=-1;
		}
		resultadoimpuestos.posdelvector=0;																								//EL VECTOR EVALUADAS ES CREADO CON EL OBJETIVO DE QUE EN LA FUNCIÓN RECURSIVA, YA SE SEPA QUE CASILLAS SE EVALUARON
		resultadoimpuestos.impuestos=0;																									
		posy=hassam.pos.posy;
		posx=hassam.pos.posx;																											//La posicion inicial que recibe la funcion de calcular impuestos es la de hassam para verificar si en un comienzo, debe pagar almenos 1 dirham
		
		resultadoimpuestos=evaluarimpuestos(tablero,posx,posy,turno,evaluadas,resultadoimpuestos);
		if(turno==true){
			if(player1.dirhams>resultadoimpuestos.impuestos){
				player1.dirhams-=resultadoimpuestos.impuestos;																			//Se cobran los impuestos
				player2.dirhams+=resultadoimpuestos.impuestos;
			}
			else{
				player2.dirhams+=player1.dirhams;
				player1.dirhams=0;																										//Se cobran los impuestos
			}
			if(resultadoimpuestos.impuestos>1)																							//Si hay impuestos para cobrar, se da el mensaje
			{		
				color(hConsole,228);
				cout<<endl<<player1.nombre;
				color(hConsole,224);
				cout<<" TUVO QUE PAGAR "<<resultadoimpuestos.impuestos<<" DIRHAMS A ";
				color(hConsole,233);
				cout<<player2.nombre<<endl;
				color(hConsole,224);
			}
		}
		else{
			if(player1.dirhams>resultadoimpuestos.impuestos){
				player2.dirhams-=resultadoimpuestos.impuestos;																			//Se cobran los impuestos
				player1.dirhams+=resultadoimpuestos.impuestos;
			}
			else{
				player1.dirhams+=player1.dirhams;
				player2.dirhams=0;																										//Se cobran los impuestos
			}
			if(resultadoimpuestos.impuestos>1)
			{
				color(hConsole,233);
				cout<<endl<<player2.nombre;
				color(hConsole,224);
				cout<<" TUVO QUE PAGAR "<<resultadoimpuestos.impuestos<<" DIRHAMS A ";
				color(hConsole,228);
				cout<<player1.nombre<<endl;
				color(hConsole,224);
			}	
		}			
		
		
        imprimirtablero(tablero,hassam);																								//DESACTIVAR PARA IMPRIMIR LA MATRIZ EN FORMA NUMÉRICA
/*		for(i=0;i<7;i++)																												//ACTIVAR PARA IMPRIMIR LA MATRIZ EN FORMA NUMÉRICA
		{
			for(j=0;j<7;j++)
			{
				cout<<tablero[i][j]<<"\t";
			}
			cout<<endl;
		} */
		if(turno==true){																												//Coloca las alfombras respectivas
            NumdeAlfombra1=UsoAlfombras(tablero,adyacentes,NumdeAlfombra1);
            player1.alfombras--;
		}
		else{
			NumdeAlfombra2=UsoAlfombras(tablero,adyacentes,NumdeAlfombra2);	
            player2.alfombras--;
		}
		
		if(turno==true){																												//Cambia de turno
			turno=false;
		}
		else{
			turno=true;
		}
		
		if((player1.alfombras==0)&&(player2.alfombras==0)){
			puntosfinales=calculo(tablero,player1,player2,puntosfinales);
			color(hConsole,228);
			cout<<"EL ";
			color(hConsole,233);
			cout<<"GANADOR ";
			color(hConsole,228);
			cout<<"DE ";
			color(hConsole,233);
			cout<<"ESTA ";
			color(hConsole, 228);
			cout<<"PARTIDA ";
			color(hConsole, 233);
			cout<<"ES ";
			if(puntosfinales.puntos1==puntosfinales.puntos2){
				if(player1.dirhams>player2.dirhams){
					color(hConsole, 228);
					cout<<player1.nombre<<" !!!!!!!!!!";
					color(hConsole, 224);
				}
				else if(player2.dirhams>player1.dirhams){
					cout<<player2.nombre<<" !!!!!!!!!!";
					color(hConsole, 224);
				}
				else{
					color(hConsole, 224);
					cout<<" EMPATE ";
				}
			}
			else{
				if(puntosfinales.puntos1>puntosfinales.puntos2){
					color(hConsole, 228);
					cout<<player1.nombre<<" !!!!!!!!!!";
					color(hConsole, 224);
				}
				else{
					cout<<player2.nombre<<" !!!!!!!!!!";
					color(hConsole, 224);
				}
			}
			ganador=true;
		}
	}
	cout<<endl<<endl<<"RESULTADOS FINALES:"<<endl;
	color(hConsole, 228);
	cout<<player1.nombre;
	color(hConsole, 224);
	cout<<": puntos totales = "<<puntosfinales.puntos1;
	cout<<", alfombras en pantalla = "<<puntosfinales.puntos1-player1.dirhams;
	cout<<", dirhams = "<<player1.dirhams<<endl;
	color(hConsole, 233);
	cout<<player2.nombre;
	color(hConsole, 224);
	cout<<": puntos totales = "<<puntosfinales.puntos2;
	cout<<", alfombras en pantalla = "<<puntosfinales.puntos2-player2.dirhams;
	cout<<", dirhams = "<<player2.dirhams<<endl<<endl<<endl;
	imprimirtablero(tablero,hassam);
	cout<<"Digite una tecla para salir"<<endl;
	cin>>op;
	return 0;
}


void imprimirtablero(int tablero[][7],caracteristicas hassam)																			//imprime el tablero
{
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );																				//linea para poner color
	int i,j;
		cout<<"                    X"<<endl<<endl<<"        0   1   2   3   4   5   6"<<endl;
		cout<<"       "<<char(201)<<char(187)<<"   ";
		for(i=0;i<3;i++)
		{
			cout<<char(201)<<char(205)<<char(205)<<char(205)<<char(187)<<"   ";
		}
		cout<<endl;
		for(i=0;i<7;i++)																    	
		{
			if(i!=3)
			{
				cout<<"     "<<i<<" ";
			}
			else
			{
				cout<<" Y   "<<i<<" ";
			}
			if(i%2==0)
			{
				cout<<char(200);     
			}
			else
			{
				cout<<char(201);
			}
			for(j=0;j<7;j++)
			{
				if(j<6)
				{
					if(tablero[i][j]==0)
					{
						cout<<char(0xDB)<<"   ";
					}
					else if(tablero[i][j]==-1)
					{
						cout<<hassam.hassam<<"   ";
					}
					else if(tablero[i][j]%2==0)
					{
						color(hConsole, 233);
						if(tablero[i][j]<0)
						{
							cout<<hassam.hassam<<"   ";
						}
						else
						{
							cout<<char(0xDB)<<"   ";
						}
						color(hConsole, 224);
					}
					else
					{
						color(hConsole, 228);
						if(tablero[i][j]<0)
						{
							cout<<hassam.hassam<<"   ";
						}
						else
						{
							cout<<char(0xDB)<<"   ";
						}
						color(hConsole, 224);
					}
				}
				else
				{
					if(tablero[i][j]==0)
					{
						cout<<char(0xDB);
					}
					else if(tablero[i][j]==-1)
					{
						cout<<hassam.hassam;
					}
					else if(tablero[i][j]%2==0)
					{
						color(hConsole, 233);
						if(tablero[i][j]<0)
						{
							cout<<hassam.hassam;
						}
						else
						{
							cout<<char(0xDB);
						}
						color(hConsole, 224);
					}
					else
					{
						color(hConsole, 228);
						if(tablero[i][j]<0)
						{
							cout<<hassam.hassam;
						}
						else
						{
							cout<<char(0xDB);
						}
						color(hConsole, 224);
					}
				}
			}
			if(i%2==0)
			{
				cout<<char(187);
			}
			else
			{
				cout<<char(188);
			}
			cout<<endl;
			if(i<6)
			{
				if(i%2!=0)
				{
					cout<<"       "<<char(186)<<"                         ";
				}
				else
				{ 
					cout<<"                                 "<<char(186);;
				} 
			}
			if(i!=6)
			{
				cout<<endl;	
			}
		}
		cout<<"        ";
		for(i=0;i<3;i++)
		{
			if(i!=2)
			{
				cout<<char(200)<<char(205)<<char(205)<<char(205)<<char(188)<<"   ";
			}
			else
			{
				cout<<char(200)<<char(205)<<char(205)<<char(205)<<char(188);	
			}
		}
		cout<<"   "<<char(200)<<char(188);
		cout<<endl;     																												//termina de imprimir el tablero
}





caracteristicas mediavuelta(caracteristicas hassam,int i, int casillas){
	bool vueltarealizada=false;
	if(hassam.pos.posx==-1){
	 	cout<<"Hassam se sale por la izquierda del tablero!!"<<endl<<"Se ha hecho un giro!!"<<endl;										//verificacion de cada una de las posibles salidas del tablero
	 	if(hassam.pos.posy==0){
	 		hassam.pos.posx=0;
	 		hassam.hassam='v';
	 		hassam.pos.posy+=casillas-i;
	 		hassam.pos.posx+=casillas-i;
	 		vueltarealizada=true;
		}
		if(vueltarealizada==false)
		{
			hassam.hassam='>';
			if(hassam.pos.posy%2==0)
			{
				hassam.pos.posy--;
				hassam.pos.posx+=(casillas-i)*2+1;
			}
			else
			{
				hassam.pos.posy++;
				hassam.pos.posx+=(casillas-i)*2+1;
			}
		}
	}	
	else if(hassam.pos.posx==7)
		 {
		 	cout<<"Hassam se sale por la derecha del tablero!!"<<endl<<"Se ha hecho un giro!!"<<endl;
			if(hassam.pos.posy==6)
     		{
	 			hassam.pos.posx=6;
	 			hassam.hassam='^';
	 			hassam.pos.posy-=casillas-i;
	 			hassam.pos.posx-=casillas-i;
	 			vueltarealizada=true;
		  	}
	     	if(vueltarealizada==false)
	     	{
				hassam.hassam='<';
				if(hassam.pos.posy%2==0)
				{
					hassam.pos.posy++;
					hassam.pos.posx-=(casillas-i)*2+1;
				}
				else
				{
					hassam.pos.posy--;
					hassam.pos.posx-=(casillas-i)*2+1;
				}
			}
		}
		else if(hassam.pos.posy==-1)
     	 	  {
				 	cout<<"Hassam se sale por arriba del tablero!!"<<endl<<"Se ha hecho un giro!!"<<endl;								//verificacion de cada una de las posibles salidas del tablero
	 				if(hassam.pos.posx==0)
	 				{
	 					hassam.pos.posy=0;
	 					hassam.hassam='>';
	 					hassam.pos.posx+=casillas-i;
	 					hassam.pos.posy+=casillas-i;
	 					vueltarealizada=true;
					}
					if(vueltarealizada==false)
					{
						hassam.hassam='v';
						if(hassam.pos.posx%2==0)
						{
							hassam.pos.posx--;
							hassam.pos.posy+=(casillas-i)*2+1;
						}
						else
						{
							hassam.pos.posx++;
							hassam.pos.posy+=(casillas-i)*2+1;
						}
					}
			  }
			  else if(hassam.pos.posy==7)
     			   {
     			   		cout<<"Hassam se sale por abajo del tablero!!"<<endl<<"Se ha hecho un giro!!"<<endl;							//verificacion de cada una de las posibles salidas del tablero
	 					if(hassam.pos.posx==6)
	 					{
	 						hassam.pos.posy=6;
	 						hassam.hassam='<';
	 						hassam.pos.posx-=casillas-i;
	 						hassam.pos.posy-=casillas-i;
	 						vueltarealizada=true;
						}
						if(vueltarealizada==false)
						{
							hassam.hassam='^';
							if(hassam.pos.posx%2==0)
							{
								hassam.pos.posx++;
								hassam.pos.posy-=(casillas-i)*2+1;
							}
							else
							{
								hassam.pos.posx--;
								hassam.pos.posy-=(casillas-i)*2+1;
							}
						}	
     			   	
		  			}
	return hassam;
}





caracteristicas movimiento(int tablero[][7],caracteristicas hassam,posicion adyacentes[])
{
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );	   																			//linea para poner color
	int casillas,op=0,direccion;
	int i,aux;
	bool cumple=false;
	srand(time(0));
	cout<<endl<<"Hacia que lado quiere girar a hassam"<<endl<<"Digite ";
	color(hConsole, 228);
	cout<<"1";
	color(hConsole, 224); 
	cout<<" si quiere hacia arriba, digite ";
	color(hConsole, 228); 
	cout<<"2";
	color(hConsole, 224); 
	cout<<" si quiere hacia abajo"<<endl<<"Digite ";
	color(hConsole, 228); 
	cout<<"3";
	color(hConsole, 224); 
	cout<<" si quiere hacia la derecha, digite ";
	color(hConsole, 228);
	cout<<"4";
	color(hConsole, 224); 
	cout<<" si quiere a la izquierda"<<endl;
	do
	{	color(hConsole, 228);
		cin>>direccion;																													//se pide la direccion en la que se va a mover a hassam																												
		switch(direccion)																												//se prohibe que gire 180 grados
		{
			case 1: if(hassam.hassam!='v')
					{
						if((tablero[hassam.pos.posy][hassam.pos.posx]<0)&&(tablero[hassam.pos.posy][hassam.pos.posx]!=-1))
						{
							tablero[hassam.pos.posy][hassam.pos.posx]-=tablero[hassam.pos.posy][hassam.pos.posx]*2;
						}
						else if(tablero[hassam.pos.posy][hassam.pos.posx]==-1)
						{
							tablero[hassam.pos.posy][hassam.pos.posx]=0;
						}
						hassam.hassam='^';
						cumple=true;
					}
					else
					{
						cout<<"Hassam esta mirando en la direccion contraria y no puede voltear 180 grados, intente de nuevo!"<<endl;
					}
						break;
			case 2:	if(hassam.hassam!='^')
					{
						if((tablero[hassam.pos.posy][hassam.pos.posx]<0)&&(tablero[hassam.pos.posy][hassam.pos.posx]!=-1))
						{
							tablero[hassam.pos.posy][hassam.pos.posx]-=tablero[hassam.pos.posy][hassam.pos.posx]*2;
						}
						else if(tablero[hassam.pos.posy][hassam.pos.posx]==-1)
						{
							tablero[hassam.pos.posy][hassam.pos.posx]=0;
						}
						hassam.hassam='v';
						cumple=true;
					}
					else
					{
						cout<<"Hassam esta mirando en la direccion contraria y no puede voltear 180 grados, intente de nuevo!"<<endl;
					}
						break;
			case 3:	if(hassam.hassam!='<')
					{
						if((tablero[hassam.pos.posy][hassam.pos.posx]<0)&&(tablero[hassam.pos.posy][hassam.pos.posx]!=-1))
						{
							tablero[hassam.pos.posy][hassam.pos.posx]-=tablero[hassam.pos.posy][hassam.pos.posx]*2;
						}
						else if(tablero[hassam.pos.posy][hassam.pos.posx]==-1)
						{
							tablero[hassam.pos.posy][hassam.pos.posx]=0;
						}
						hassam.hassam='>';
						cumple=true;
					}
					else
					{
						cout<<"Hassam esta mirando en la direccion contraria y no puede voltear 180 grados, intente de nuevo!"<<endl;
					}
						break;
			case 4:	if(hassam.hassam!='>')
					{
						if((tablero[hassam.pos.posy][hassam.pos.posx]<0)&&(tablero[hassam.pos.posy][hassam.pos.posx]!=-1))
						{
							tablero[hassam.pos.posy][hassam.pos.posx]-=tablero[hassam.pos.posy][hassam.pos.posx]*2;
						}
						else if(tablero[hassam.pos.posy][hassam.pos.posx]==-1)
						{
							tablero[hassam.pos.posy][hassam.pos.posx]=0;
						}
						hassam.hassam='<';
						cumple=true;
					}
					else
					{
						cout<<"Hassam esta mirando en la direccion contraria y no puede voltear 180 grados, intente de nuevo!"<<endl;
					}
						break;	
			default: 	cout<<"opcion inexistente"<<endl;
						cumple=false;
						break;
		}	
	}while(cumple==false);
	color(hConsole, 224);																												//linea cambio de color a letra negra y fondo amarillo
	cout<<endl<<"Digite 1 para tirar el dado!! "<<endl<<"Recuerde que el minimo numero es 1 y el maximo es 4"<<endl;					//lanzamiento del dado, numero maximo=4, numero minimo=1
	do
	{
		color(hConsole, 228);
		cin>>op;
		color(hConsole, 224);
		switch(op)
		{
			case 1: casillas=(1+rand()%4);
					break;
			default: cout<<"Esa opcion no existe, intente de nuevo"<<endl;
					break;
		}
	}while(op!=1);
	
	cout<<endl<<"El dado marca el numero "<<casillas<<" !!"<<endl;		
														
	if(direccion==1)																													//De acuerdo a la direccion, hassam se mueve las casillas marcadas por el dado
	{																																	//Por cada paso que da hassam, se verifica si se ha salido del tablero
		for(i=1;i<=casillas;i++)																										//En caso de salida del tablero, hassam dará la vuelta correspondiente
		{
			hassam.pos.posy--;
			hassam=mediavuelta(hassam,i,casillas);	
		}
	}
	else if(direccion==2)
	{
		for(i=1;i<=casillas;i++)
		{
			hassam.pos.posy++;
			hassam=mediavuelta(hassam,i,casillas);	
		}
	}
	else if(direccion==3)
	{
		for(i=1;i<=casillas;i++)
		{
			hassam.pos.posx++;	
			hassam=mediavuelta(hassam,i,casillas);
		}
	}
	else{
		for(i=1;i<=casillas;i++)
		{
			hassam.pos.posx--;	
			hassam=mediavuelta(hassam,i,casillas);
		}
	}
	
	if((tablero[hassam.pos.posy][hassam.pos.posx]%2==0)&&(tablero[hassam.pos.posy][hassam.pos.posx]!=0))
	{
		tablero[hassam.pos.posy][hassam.pos.posx]-=tablero[hassam.pos.posy][hassam.pos.posx]*2;
	}
	else if(tablero[hassam.pos.posy][hassam.pos.posx]%2!=0)
	{
		tablero[hassam.pos.posy][hassam.pos.posx]-=tablero[hassam.pos.posy][hassam.pos.posx]*2;
	}
	else if(tablero[hassam.pos.posy][hassam.pos.posx]==0)
	{
		tablero[hassam.pos.posy][hassam.pos.posx]=-1;
	}
	adyacentes[0].posy=hassam.pos.posy+1;
	adyacentes[0].posx=hassam.pos.posx;
	adyacentes[1].posx=hassam.pos.posx+1;
	adyacentes[1].posy=hassam.pos.posy;
	adyacentes[2].posy=hassam.pos.posy-1;
	adyacentes[2].posx=hassam.pos.posx;
	adyacentes[3].posx=hassam.pos.posx-1;
	adyacentes[3].posy=hassam.pos.posy;

	return hassam;
}


char UsoAlfombras(int tablero[][7], posicion adyacentes[], int NumdeAlfombra) {
	
    bool posicionValida = true;
    int eleccion=-1;
	int i,esvalido,intentos=0;
	int NumValido[4]={-1,-1,-1,-1}; 																									// Almacena índices de las opciones válidas
	int idx,ady_x,ady_y;
	posicion adyacentes2[4];
	int casillaprevia=-1,casillapreviax,casillapreviay;																												//casilla previa inicia en un valor que nunca estará en más de una posicion (-1 representa a hassam), de este modo cuando se compruebe la segunda alfombra, no tendra problema en verificar que dos casillas sean diferentes				
	
    esvalido = 0;
	
	cout << "Elija la opcion para la coordenada de la primera mitad de la alfombra "<<endl;
    for (i = 0; i < 4; i++) {     																										// Verificar posiciones adyacentes precalculadas
        ady_x = adyacentes[i].posx;
        ady_y = adyacentes[i].posy;
        if ( (ady_x >= 0) && (ady_x < 7) && (ady_y >= 0) && (ady_y < 7)) {
            cout << esvalido << ". (X= " << ady_x << ", Y= " << ady_y << ") - opcion" << endl;
            NumValido[esvalido] = i; 																									// Guardar los índices de las casillas adyacentes válidas
			esvalido++;																						
        }
    }
    cout<<"Opcion: ";
    cin >> eleccion;	
    while((eleccion < 0) || (eleccion >= esvalido)) {
    	cout << "Numero de opcion invalido, por favor intente de nuevo." << endl;
    	cout<<"Opcion: ";
    	cin >> eleccion;																												//eleccion es la posicion del vector donde se guardan los indices de las casillas adyacentes validas
    }

	idx = NumValido[eleccion];																											//idx es el índice de la casilla adyacente a hassam elegida por el usuario
	ady_x = adyacentes[idx].posx;
    ady_y = adyacentes[idx].posy;
   if(tablero[ady_y][ady_x]!=0){
   	casillaprevia=tablero[ady_y][ady_x];																								//Guarda el valor de la casilla donde se pone la alfombra solo en caso de que haya otra alfombra 
  	casillapreviax=ady_x;
  	casillapreviay=ady_y;
   }
    
   	tablero[ady_y][ady_x] = NumdeAlfombra;																								//coloca la primera mitad de alfombra
    cout << "Primera mitad de alfombra colocada correctamente en (X= " << ady_x << ", Y= " << ady_y << ")" << endl<<endl;
    
    esvalido=0;
    
   	adyacentes2[0].posy=adyacentes[idx].posy+1;
   	adyacentes2[0].posx=adyacentes[idx].posx;
   	adyacentes2[1].posy=adyacentes[idx].posy;
   	adyacentes2[1].posx=adyacentes[idx].posx+1;
   	adyacentes2[2].posy=adyacentes[idx].posy-1;
   	adyacentes2[2].posx=adyacentes[idx].posx;
   	adyacentes2[3].posy=adyacentes[idx].posy;
   	adyacentes2[3].posx=adyacentes[idx].posx-1;
   	
   	for(i=0;i<4;i++){
   		NumValido[i]=-1;
	}
	eleccion=-1;
	cout << "Elija la opcion para la coordenada de la segunda mitad de la alfombra "<<endl;
	for (i = 0; i < 4; i++){   																											// Verificar posiciones adyacentes precalculadas
        ady_x = adyacentes2[i].posx;
        ady_y = adyacentes2[i].posy;
        if ( (ady_x >= 0) && (ady_x < 7) && (ady_y >= 0) && (ady_y < 7) && (tablero[ady_y][ady_x]>=0)) {
            cout << esvalido << ". (X= " << ady_x << ", Y= " << ady_y << ") - opcion" << endl;
            NumValido[esvalido] = i; 																									// Guardar los índices de las casillas adyacentes válidas
			esvalido++;																						
        }
	}
	cout<<"Opcion: ";
    cin >> eleccion;	
    while((eleccion < 0) || (eleccion >= esvalido)) {
    	cout << "Numero de opcion invalido, por favor intente de nuevo." <<endl;
    	cout<<"Opcion: ";
    	cin >> eleccion;																												//eleccion es la posicion del vector donde se guardan los indices de las casillas adyacentes validas
    }
    
	idx = NumValido[eleccion];																											//idx es ahora el índice de la casilla adyacente a la primera mitad elegida por el usuario
   	ady_x = adyacentes2[idx].posx;
	ady_y = adyacentes2[idx].posy;
    while(tablero[ady_y][ady_x]==casillaprevia){
    	intentos++;
    	cout<<"No puede colocar una alfombra completa encima de otra completa, intente de nuevo: intento "<<intentos+1<<"/4"<<endl;
    	cin>>eleccion;
   		idx = NumValido[eleccion];	 																									//verifica si se esta cubriendo una alfombra completa
   		ady_x = adyacentes2[idx].posx;
   		ady_y = adyacentes2[idx].posy;
   		if(intentos>2){
   			tablero[casillapreviay][casillapreviax]=casillaprevia;
   			cout<<" No se puede colocar ninguna alfombra en este turno "<<endl<<endl;
   			return NumdeAlfombra;
		   }
	}

    
    tablero[ady_y][ady_x] = NumdeAlfombra;																								//coloca la segunda mitad de alfombra
	NumdeAlfombra+=2; 
    cout << "Segunda mitad de alfombra colocada correctamente en (X= " << ady_x << ", Y= " << ady_y << ")" <<endl<<"No se cubre ninguna alfombra por completo"<<endl<<endl;
    
    return NumdeAlfombra;
}




Resultadoimpuestos evaluarimpuestos(int tablero[][7],int posx,int posy,bool turno,posicion evaluadas[],Resultadoimpuestos resultadoimpuestos){
	bool evaluada=false;
	int i;
		for(i=0;i<49;i++){
			if((posx==evaluadas[i].posx)&&(posy==evaluadas[i].posy)){
				evaluada=true;
			}
		}
		if(evaluada==false){
			if(turno==true){
				if((tablero[posy][posx]%2==0)&&(tablero[posy][posx]!=0)){
					evaluadas[resultadoimpuestos.posdelvector].posx=posx;
					evaluadas[resultadoimpuestos.posdelvector].posy=posy;
					resultadoimpuestos.posdelvector++;
					resultadoimpuestos.impuestos++;
					if(posx<6){
						posx++;
						resultadoimpuestos=evaluarimpuestos(tablero,posx,posy,turno,evaluadas,resultadoimpuestos);
						posx--;
					}
					if(posy<6){
						posy++;
						resultadoimpuestos=evaluarimpuestos(tablero,posx,posy,turno,evaluadas,resultadoimpuestos);
						posy--;
					}
					if(posx>0){
						posx--;
						resultadoimpuestos=evaluarimpuestos(tablero,posx,posy,turno,evaluadas,resultadoimpuestos);
						posx++;
					}
					if(posy>0){
						posy--;
						resultadoimpuestos=evaluarimpuestos(tablero,posx,posy,turno,evaluadas,resultadoimpuestos);
					}
				}
			}
			else{
				if((tablero[posy][posx]%2!=0)&&(tablero[posy][posx]!=-1)){
					evaluadas[resultadoimpuestos.posdelvector].posx=posx;
					evaluadas[resultadoimpuestos.posdelvector].posy=posy;
					resultadoimpuestos.posdelvector++;
					resultadoimpuestos.impuestos++;
					if(posx<6){
						posx++;
						resultadoimpuestos=evaluarimpuestos(tablero,posx,posy,turno,evaluadas,resultadoimpuestos);
						posx--;
					}
					if(posy<6){
						posy++;
						resultadoimpuestos=evaluarimpuestos(tablero,posx,posy,turno,evaluadas,resultadoimpuestos);
						posy--;
					}
					if(posx>0){
						posx--;
						resultadoimpuestos=evaluarimpuestos(tablero,posx,posy,turno,evaluadas,resultadoimpuestos);
						posx++;
					}
					if(posy>0){
						posy--;
						resultadoimpuestos=evaluarimpuestos(tablero,posx,posy,turno,evaluadas,resultadoimpuestos);
						posy++;
					}
				}
			}
		}
	return resultadoimpuestos;
}



Puntosfinales calculo(int tablero[][7],player player1,player player2,Puntosfinales puntosfinales){
	int i,j;
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			if((tablero[i][j]%2!=0)&&(tablero[i][j]!=-1)){
				puntosfinales.puntos1++;
			}
			else if((tablero[i][j]%2==0)&&(tablero[i][j]!=0)){
				puntosfinales.puntos2++;
			}
		}
	}
	puntosfinales.puntos1+=player1.dirhams;
	puntosfinales.puntos2+=player2.dirhams;
	return puntosfinales;
}