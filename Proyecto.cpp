#include <iostream>
#include <windows.h>																													//linea para poner color
#include <mmsystem.h>											
#include <ctime>
#include <cstdlib>
#define color SetConsoleTextAttribute																									//linea para poner color
using namespace std;
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
caracteristicas movimiento(int tablero[][7],caracteristicas hassam,posicion adyacentes[]);
caracteristicas mediavuelta(caracteristicas hassam,int i, int casillas);
char UsoAlfombras(int tablero[][7],posicion adyacentes[], bool turno, int NumdeAlfombra);
void imprimirtablero(int tablero[][7],caracteristicas hassam);










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
    caracteristicas hassam;
    bool turno=true;
    posicion adyacentes[4];
    
    
    player1.alfombras=10;																												//establecer valores iniciales
    player2.alfombras=10;
    player1.dirhams=20;
    player2.dirhams=20;
	cout<<"Digite el nombre del primer jugador!"<<endl;
	cin.getline(player1.nombre,30,'\n');
	cout<<"Digite el nombre del segundo jugador!"<<endl;
	cin.getline(player2.nombre,30,'\n');
	
	for(i=0;i<7;i++)																													//llena la matriz de alfombras y coloca a hassam en el medio
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
	color(hConsole,228);
	cout<<endl<<" QUE EMPIECE EL JUEGO!!!"<<endl<<"SE LE OTORGA: "<<endl<<"1) 20 DIRHAMS A CADA UNO"<<endl<<"2) 10 ALFOMBRAS ROJAS A "<<player1.nombre<<" Y 10 ALFOMBRAS AZULES A "<<player2.nombre<<endl;
	color(hConsole,224);
	while(ganador==false)																												//mientras no encuentre ganador, se ejecutará todo el juego
	{
		imprimirtablero(tablero,hassam);
/*		for(i=0;i<7;i++)																												//ACTIVAR PARA IMPRIMIR LA MATRIZ NUMÉRICA
		{
			for(j=0;j<7;j++)
			{
				cout<<tablero[i][j]<<"\t";
			}
			cout<<endl;
		} */
		if(turno==true)
		{
			color(hConsole, 228); 
			cout<<endl<<endl<<"\t\t\t\t\t\t\tTURNO #"<<turnos<<endl;
			turnos++;
			color(hConsole, 224);
			cout<<"A "<<player1.nombre<<" LE QUEDAN "<<player1.alfombras<<" ALFOMBRAS"<<endl;
			cout<<"A "<<player2.nombre<<" LE QUEDAN "<<player2.alfombras<<" ALFOMBRAS"<<endl;
			cout<<endl<<endl<<"Turno de "<<player1.nombre<<" !";
			
			hassam=movimiento(tablero,hassam,adyacentes);
			
            imprimirtablero(tablero,hassam);
/*			for(i=0;i<7;i++)																												//ACTIVAR PARA IMPRIMIR LA MATRIZ NUMÉRICA
			{
				for(j=0;j<7;j++)
				{
					cout<<tablero[i][j]<<"\t";
				}
				cout<<endl;
			} */
            NumdeAlfombra1=UsoAlfombras(tablero,adyacentes,turno,NumdeAlfombra1);
            player1.alfombras--;
            turno=false;
		}
		else
		{
			color(hConsole, 228); 
			cout<<endl<<endl<<"\t\t\t\t\t\t\tTURNO #"<<turnos<<endl;
			turnos++;
			color(hConsole, 224);
			cout<<"A "<<player1.nombre<<" LE QUEDAN "<<player1.alfombras<<" ALFOMBRAS"<<endl;
			cout<<"A "<<player2.nombre<<" LE QUEDAN "<<player2.alfombras<<" ALFOMBRAS"<<endl;
			cout<<endl<<"Turno de "<<player2.nombre<<" !";
			
			hassam=movimiento(tablero,hassam,adyacentes);
						
           imprimirtablero(tablero,hassam);
/*			for(i=0;i<7;i++)																												//ACTIVAR PARA IMPRIMIR LA MATRIZ NUMÉRICA
			{
				for(j=0;j<7;j++)
				{
					cout<<tablero[i][j]<<"\t";
				}
				cout<<endl;
			} */
            NumdeAlfombra2=UsoAlfombras(tablero,adyacentes,turno,NumdeAlfombra2);
            player2.alfombras--;
            turno=true;
		}
	}
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





caracteristicas mediavuelta(caracteristicas hassam,int i, int casillas)
{
	bool vueltarealizada=false;
	if(hassam.pos.posx==-1)
	{
	 	cout<<"Hassam se sale por la izquierda del tablero!!"<<endl<<"Se ha hecho un giro!!"<<endl;										//verificacion de cada una de las posibles salidas del tablero
	 	if(hassam.pos.posy==0)
	 	{
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
	 						hassam.hassam='>';
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
			default: cout<<"opcion inexistente"<<endl;
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
	else
	{
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


char UsoAlfombras(int tablero[][7], posicion adyacentes[], bool turno, int NumdeAlfombra) {
	
    bool posicionValida = true;
    int eleccion=-1;
	int i,esvalido,intentos=0;
	int NumValido[4]={-1,-1,-1,-1}; 																									// Almacena índices de las opciones válidas
	int idx,ady_x,ady_y;
	posicion adyacentes2[4];
	int casillaprevia=-1,casillapreviax,casillapreviay;																												//casilla previa inicia en un valor que nunca estará en más de una posicion (-1 representa a hassam), de este modo cuando se compruebe la segunda alfombra, no tendra problema en verificar que dos casillas sean diferentes				
	
    esvalido = 0;
	
    for (i = 0; i < 4; i++) {     																										// Verificar posiciones adyacentes precalculadas
        ady_x = adyacentes[i].posx;
        ady_y = adyacentes[i].posy;
        if ( (ady_x >= 0) && (ady_x < 7) && (ady_y >= 0) && (ady_y < 7)) {
            cout << esvalido << ". (X= " << ady_x << ", Y= " << ady_y << ") - opcion valida" << endl;
            NumValido[esvalido] = i; 																									// Guardar los índices de las casillas adyacentes válidas
			esvalido++;																						
        }
    }
    cout << "Elija la opcion para la coordenada de la primera mitad de la alfombra (0-" << esvalido-1 << "): ";
    cin >> eleccion;	
    while((eleccion < 0) || (eleccion >= esvalido)) {
    	cout << "Numero de opcion invalido, por favor intente de nuevo." << endl;
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
	
	for (i = 0; i < 4; i++){   																											// Verificar posiciones adyacentes precalculadas
        ady_x = adyacentes2[i].posx;
        ady_y = adyacentes2[i].posy;
        if ( (ady_x >= 0) && (ady_x < 7) && (ady_y >= 0) && (ady_y < 7) && (tablero[ady_y][ady_x]>=0)) {
            cout << esvalido << ". (X= " << ady_x << ", Y= " << ady_y << ") - opcion valida" << endl;
            NumValido[esvalido] = i; 																									// Guardar los índices de las casillas adyacentes válidas
			esvalido++;																						
        }
	}
    cout << "Elija la opcion para la coordenada de la primera mitad de la alfombra (0-" << esvalido-1 << "): ";
    cin >> eleccion;	
    while((eleccion < 0) || (eleccion >= esvalido)) {
    	cout << "Numero de opcion invalido, por favor intente de nuevo." <<endl;
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
