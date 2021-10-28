/*
 ============================================================================
 Name        : PuntosYCajas.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <gtk/gtk.h>
//instrucciones
//humano jugar contra la computadora y a dos programas distintos jugar entre sí.
//tener una estrategia
//material a enviar: código fuente, documentación solicitada y video demostrativo
//permitir elegir quién inicia el juego y qué color será asignado a cada uno.
//El tamaño de tablero también es configurable,
//(valor M que determinará el número de puntos en las filas y columnas del tablero.
//deben poder ser definidas además de forma aleatoria.

#define int *empieza,*dimenciones,*numeroCololorJ,*numeroColorC;
#define char jugador[20],cpu[20]
#define char *pjugador=&jugador,*pcpu=&cpu;
#define MAX_FILA=15;
#define MAX_COLUMNA=15;
//convertir en variables glovales para usar
int f1,f2,c1,c2;
int numeroColor

	//se añade el gtk/gtk.h para utilizar el glade y se declara como variables glovales las partes que seran usadas
gtkWidget *ventana1,*fixed1,*salir,*acerca,*configuracion,*jugar;

gtkWidget *ventana2,*fixed2,*iniciaElJugador,*iniciaLaCpu,iniciaRandom,*quienInicia,*volverAPrincipal,*selectSize;
gtkWidget *entradaT,*textoTam,*textCYN,*colJugador,*nombreJugador,*cpuCYN,*colCpu,*nombreCpu,*entradaCJ,*entradaCC,;

gtkWidget *ventana3,*fixed3,*creador,*volverAPrincipal2;

gtkBuilder *builder;
	//el uso del glade volvio mi main obsoleto
int main(int argc,char *argv[])
{
	//cargo todas las partes que hay en el programa
	gtk_init(&argc,&argv);
	builder=gtk_builder_new_from_file("menu.glade");

	ventana1=GTK_WIDGET(gtk_builder_get_object(builder,"ventana1"));
	g_signal_connect(ventana1,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_builder_connect_signals(builder,NULL);

	salir=GTK_WIDGET(gtk_builder_get_object(builder,"salir"));
	acerca=GTK_WIDGET(gtk_builder_get_object(builder,"acerca"));
	configuracion=GTK_WIDGET(gtk_builder_get_object(builder,"configuracion"));
	jugar=GTK_WIDGET(gtk_builder_get_object(builder,"jugar"));
	gtk_widget_show(ventana1);

	ventana2=GTK_WIDGET(gtk_builder_get_object(builder,"ventana2"));
	fixed2=GTK_WIDGET(gtk_builder_get_object(builder,"fixed2"));
	iniciaElJugador=GTK_WIDGET(gtk_builder_get_object(builder,"iniciaElJugador"));
	iniciaLaCpu=GTK_WIDGET(gtk_builder_get_object(builder,"iniciaLaCpu"));
	iniciaRandom=GTK_WIDGET(gtk_builder_get_object(builder,"iniciaRandom"));
	quienInicia=GTK_WIDGET(gtk_builder_get_object(builder,"quienInicia"));
	textoTam=GTK_WIDGET(gtk_builder_get_object(builder,"textoTam"));
	selectSize=GTK_WIDGET(gtk_builder_get_object(builder,"selectSize"));
	entradaT=GTK_WIDGET(gtk_builder_get_object(builder,"entradaT"));
	textCYN=GTK_WIDGET(gtk_builder_get_object(builder,"textCYN"));
	colJugador=GTK_WIDGET(gtk_builder_get_object(builder,"colJugador"));
	nombreJugador=GTK_WIDGET(gtk_builder_get_object(builder,"nombreJugador"));
	cpuCYN=GTK_WIDGET(gtk_builder_get_object(builder,"cpuCYN"));
	entradaCJ=GTK_WIDGET(gtk_builder_get_object(builder,"entradaCJ"));
	colCpu=GTK_WIDGET(gtk_builder_get_object(builder,"colCpu"));
	entradaCC=GTK_WIDGET(gtk_builder_get_object(builder,"entradaCC"));
	nombreCpu=GTK_WIDGET(gtk_builder_get_object(builder,"nombreCpu"));
	volverAPrincipal=GTK_WIDGET(gtk_builder_get_object(builder,"volverAPrincipal"));


	ventana3=GTK_WIDGET(gtk_builder_get_object(builder,"ventana3"));
	fixed3=GTK_WIDGET(gtk_builder_get_object(builder,"fixed3"));
	creador=GTK_WIDGET(gtk_builder_get_object(builder,"creador"));
	volverAPrincipal2=GTK_WIDGET(gtk_builder_get_object(builder,"volverAPrincipal2"));


	//cerrar el juego
	g_signal_connect(salir,"clicked",G_CALLBACK(gtk_main_quit),NULL);
	//entrar en acerca
	g_signal_connect(acerca,"clicked",G_CALLBACK(gtk_widget_show_all(ventana3)),NULL);
	g_signal_connect(acerca,"clicked",gtk_widget_destroy(ventana1),NULL);
	//devolver que el jugador empieza
	gboolean T=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(iniciaElJugador));
	if(T==1)
		{
			*empieza=0;
		}
	//devolcer que la cpu empieza
	gboolean T=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(iniciaLaCpu));
	if(T==1)
		{
			*empieza=1;
		}
	//devolver uno de los 2 al azar
		gboolean T=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(iniciaRandom));
	if(T==1)
		{
			*empieza=rand()%2;
		}
	//chequea la entrada y dependiendo de cual sea se obtiene el valor de las dimenciones
	g_signal_connect(entradaT,"changed",hallardimencion(entradaT),NULL);
	*jugador=gtk_entry_get_text(nombreJugador);
	g_signal_connect(entradaCJ,"changed",hallarcolor(entradaCJ),NULL);
	*numeroColorJ=numeroColor;
	g_signal_connect(entradaCC,"changed",hallarcolor(entradaCC),NULL);
	*numeroColorC=numeroColor;
	*cpu=gtk_entry_get_text(nombreCpu);
	g_signal_connect(volverAPrincipal,"clicked",gtk_widget_destroy(ventana2),NULL);
	g_signal_connect(ventana2,"destroy",gtk_widget_show_all(ventana1),NULL);

	g_signal_connect(jugar,"clicked",on_jugar_clicked(GtkButton *jugar,empieza,jugador,cpu),NULL);

	g_signal_connect(volverAPrincipal2,"clicked",gtk_widget_destroy(ventana3),NULL);
	g_signal_connect(ventana2,"destroy",gtk_widget_show_all(ventana1),NULL);

	gtk_widget_show_all (ventana1);
	gtk_main();

	return 0;
}
	//cerrar el juego
void on_salir_clicked(GtkButton *salir)//es correcto?
{
	g_signal_connect(salir,"clicked",G_CALLBACK(gtk_main_quit),NULL);
}
	//entrar en acerca
void on_acerca_clicked(GtkButton *acerca)
{
	g_signal_connect(acerca,"clicked",G_CALLBACK(gtk_widget_show_all(ventana3)),NULL);

}
	//devolver que el jugador empieza
void on_iniciaElJugador_toggled(GtkRadioButton *iniciaElJugador)
{
	gboolean T=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(iniciaElJugador));
	if(T)
	{
		*empieza=0
	}
}
	//devolcer que la cpu empieza
void on_iniciaLaCpu_toggled(GtkRadioButton *iniciaLaCpu)
{
	gboolean T=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(iniciaLaCpu));
	if(T)
	{
		*empieza=1
	}
}
	//devolver uno de los 2 al azar
void on_iniciaRandom_toggled(GtkRadioButton *iniciaRandom)
{
	gboolean T=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(iniciaRandom));
	if(T)
	{
		*empieza=rand()%2;
	}
}
	//chequea la entrada y dependiendo de cual sea se obtiene el valor de las dimenciones
void on_entradaT_changed(GtkEntry *entradaT)
{
	switch(*entradaT)
	{
		case 3x3:
			*dimenciones=3;
			break;
		case 4x4:
			*dimenciones=4;
			break;
		case 5x5:
			*dimenciones=5;
			break;
		case 6x6:
			*dimenciones=6;
			break;
		case 7x7:
			*dimenciones=7;
			break;
		case 8x8:
			*dimenciones=8;
			break;
		case 9x9:
			*dimenciones=9;
			break;
		case 10x10:
			*dimenciones=10;
			break;
		case 11x11:
			*dimenciones=11;
			break;
		case 12x12:
			*dimenciones=12;
			break;
		case 13x13:
			*dimenciones=13;
			break;
		case 14x14:
			*dimenciones=14;
			break;
		case 15x15:
			*dimenciones=15;
			break;
		case random:
			*dimenciones=rand()%13+3;
			break;

	}
}
	//la seleccion de color cambio mas, pense en usar color buttons pero no sabia como usarlo, ni como utilizarlo
	//en conjunto con las imagenes que insertaria para hacer el programa
	//dara un numero de 1 a 6, se multiplicaran por 4 y se le sumara un numero qeu dependera de que direccion tome
	//a cada numero le correspondera una linea de un color
void on_entradaCJ_changed(GtkEntry *entradaCJ,GtkEntry *entradaCC)
{

	switch(entradaCJ)
	{
	//si tienen el nombre se les asigna un numero del 0 al 5
			case azul:
				*numeroColorJ=0;
				break;
			case verde:
				*numeroColorJ=1;
				break;
			case rojo:
				*numeroColorJ=2;
				break;
			case marron:
				*numeroColorJ=3;
				break;
			case negro:
				*numeroColorJ=4;
				break;
			case naranja:
				*numeroColorJ=5;
	}
	//para que colores no sean iguales se le cambia el color
	if(entradaCJ==entradaCC && numeroColor!=5)
	{
		*numeroColorJ=numeroColor++;
	}
	if(entradaCJ==entradaCC && numeroColor==5)
	{
		*numeroColorJ=numeroColor--;
	}
}

void on_nombreJugador_changed(GtkEntry *nombreJugador)
{

	*jugador=gtk_entry_get_text(nombreJugador)
	//en la ventana del juego colocar un label que tenga escrito esto, que los 2 tengan el mismo nombre no me preocupa

}

void on_entradaCC_changed(GtkEntry *entradaCJ,GtkEntry *entradaCC)
{

	switch(entradaCC)
	{
	//si tienen el nombre se les asigna un numero del 0 al 5
			case azul:
				*numeroColorC=0;
				break;
			case verde:
				*numeroColorC=1;
				break;
			case rojo:
				*numeroColorC=2;
				break;
			case marron:
				*numeroColorC=3;
				break;
			case negro:
				*numeroColorC=4;
				break;
			case naranja:
				*numeroColorC=5;
	}
	//para que colores no sean iguales se le cambia el color
	if(entradaCJ==entradaCC && numeroColor!=5)
	{
		*numeroColorC=numeroColor++;
	}
	if(entradaCJ==entradaCC && numeroColor==5)
	{
		*numeroColorC=numeroColor--;
	}
}

void on_nombreCpu_changed(GtkEntry *nombreCpu)
{

	*cpu=gtk_entry_get_text(nombreCpu);
}

void on_volverAPrincipal2_clicked(GtkButton *volverAPrincipal2)//en ambos cerrar la ventana en que estoy
{
	gtk_widget_show_all(ventana1);


}
void on_volverAPrincipal_clicked(GtkButton *volverAPrincipal)
{
	gtk_widget_show_all(ventana1);


}

//se debe hacer cambios en el main para que funcione con glade
	//gran parte de mi codigo en el main se enfocaba en conseguir los datos para el juego,
	//gracias al glade no son necesarios

	//lo que mi codigo necesita hacer ahora es el tablero y diseñar los turnos para


void on_jugar_clicked(GtkButton *jugar,empieza,jugador,cpu)//mostrar puntuaciones
{
	gtk_widget_show_all(ventana4);
	eventbox=*crearTablero();
	int juego=1,puntos1=0,puntos0=0;

		while(juego==1 )
	//asignar color, cuando termine el turno colocar color 2 y despues colocar otro juego
		{

			if(empieza=0 && juego==1)
				{

					juego=turno(empieza,puntos0,puntos1,dimenciones);
					empieza=1;
				}
			if(empieza=1 && juego==1)
			{
				juego=turno(empieza,puntos1,puntos0,dimenciones);
			}
				if (juego==0)
	//cuando termina el juego se decide el ganador por los puntos
						{
					if(puntos1==puntos2)
							{
								printf("los puntajes son %d y %d ",puntos1,puntos2);
								printf("es un empate");
							}
					if(puntos1<puntos2)
							{
								printf("los puntajes son %d y %d ",puntos1,puntos2);
								printf("gano la cpu");
							}
					if(puntos1<puntos2)
							{
								printf("los puntajes son %d y %d ",puntos1,puntos2);
								printf("gano el jugador");
							}
						}
				empieza=0;
			}
		}


}

void hallarcolor(entradaCC)
{
	switch(entradaCC)
		{
		//si tienen el nombre se les asigna un numero del 0 al 5
				case azul:
					*numeroColor=0;
					break;
				case verde:
					*numeroColor=1;
					break;
				case rojo:
					*numeroColor=2;
					break;
				case marron:
					*numeroColor=3;
					break;
				case negro:
					*numeroColor=4;
					break;
				case naranja:
					*numeroColor=5;
		}
}

void hallardimencion(GtkEntry *entradaT)
{
	switch(*entradaT)
			{
				case 3x3:
					*dimenciones=3;
					break;
				case 4x4:
					*dimenciones=4;
					break;
				case 5x5:
					*dimenciones=5;
					break;
				case 6x6:
					*dimenciones=6;
					break;
				case 7x7:
					*dimenciones=7;
					break;
				case 8x8:
					*dimenciones=8;
					break;
				case 9x9:
					*dimenciones=9;
					break;
				case 10x10:
					*dimenciones=10;
					break;
				case 11x11:
					*dimenciones=11;
					break;
				case 12x12:
					*dimenciones=12;
					break;
				case 13x13:
					*dimenciones=13;
					break;
				case 14x14:
					*dimenciones=14;
					break;
				case 15x15:
					*dimenciones=15;
					break;
				case random:
					*dimenciones=rand()%13+3;
					break;
			}
}

GtkWidget *crearTablero()//posicion en que se coloca el tablero en ventana 4 coordenadas
{
	int i,j;
	GtkWidget *imagen,eventbox*,*tablero;
	eventbox=gtk_event_box_new();
	tablero=gtk_grid_new();
	for(i=0;i<MAX_FILA*4-4;i++)
	{
		for(j=0;j<MAX_COLUMNA*4-4;j++)
		{
			if(i%4==0 && j%4==0)
			{
			imagen=gtk_image_new_from_file(imagenes[IMG.punto]);//colocar imagenes
			gtk_grid_attach(GTK_GRID(tablero),GTK_WIDGET(imagen),j,i,1,1);
			}else{
				imagen=gtk_image_new_from_file(imagenes[IMG.nada]);
				gtk_grid_attach(GTK_GRID(tablero),GTK_WIDGET(imagen),j,i,1,1);
			}
		}
	}
	gtk_container_add(GTK_CONTAINER(eventbox).tablero);
	g_signal_connect(eventbox,"button_press_event",G_CALLBACK(tablero_cb),tablero);
	return eventbox;
}

void tablero_cb(GtkWidget *eventbox,GdkEventButton *event,gpointer data)
{
	guint i,j;
	i=GUINT_FROM_LE(event->y)/50);//fila
	j=GUINT_FROM_LE(event->x)/50);//columna
	gchar *temp=g_strdup_printf("preciono la coordenada[%d,%d]",i,j);

	gtk_label_set_text(GTK_LABEL(label_estado),temp);
	g_free(temp);

}















/*
int main(void) {
	int empieza,dimenciones,numero,color2=0,color1=0;
	char selecdimencion='a',selecempieza='a',seleccolor='a';
//coloque el tamaño del tablero primero porque aparte de quizas quien empieza primero es la decisicion mas
//importante. al ver que selecciono varias veces entre s y n decidi hacer una funcion para eso

	
	selecdimencion =selec("el tamaño del tablero",selecdimencion);

//para crear el tablero pense en crear una matriz y utilizar el numero en cada posicion para representar
//un nodo de esa forma podria representar si un nodo esta unido a otro,
//se necesita una funcion para crear un tablero
	if(selecdimencion=='s')
	{
		printf("introduzca el tamaño que tendra el cuadrado en el que jugaran(no mayor a 15)\n");
		scanf("%d",&dimenciones);
		dimenciones=dimenciones-1;
		while(dimenciones<2 || 14<dimenciones)
		{
			printf("introduzca tamaño valido (entre 3 y 15)\n");
			scanf("%d",&dimenciones);
			dimenciones=dimenciones-1;
		}
	}
//si no desea elegir un numero quiero que se elija al azar 7 veces un numero entre el 0 y 6 y los sume
//de esta forma trato de que el tablero no sea muy grande ni muy chico la mayoria de las veces
//rand introduce un numero random y tras dividirlo entre 7 su resto es un numero entre el 0 y 6
//al final le sumo 2 para asegurarme que no sea muy chico
	if(selecdimencion=='n')
	{
		for(int i=0;i<4;i++)
		{
			numero = rand() % 3;
			dimenciones=dimenciones+numero;
		}
		dimenciones=dimenciones+3;
	}
//para representar el tablero elegi representar las lineas con 4 asteriscos ****, apareceran
//asteriscos en todos los nodos al inicio y cuando un jugador quiera colocar una linea
//colocara 2 asteriscos de su color conectando los 2 nodos, al colocar una linea se revisaran
// los/el "cuadro" adyacente, si este esta rodeado por asteriscos se revisa de quien es el turno y
//en la posicion del medio se coloca un identificador del jugador que recibe un punto
//revisando note que la cantidad de espacios necesarios para que sea posible en la matriz son 4*(M-1)

	int tablero[(dimenciones-1)*4][(dimenciones-1)*4];
	for(int c=0; c<=(dimenciones-1)*4;c++)
	{
		for(int l=0; l<=(dimenciones-1)*4;l++)
		{
			if(c%4==0 && l%4==0)
			{
				tablero[l][c]='*';
			}else{tablero[l][c]=' ';}
		}
	}
	selecempieza = selec("quien empieza",selecempieza);
	if(selecempieza=='s')
	{
		printf("¿quien empieza?(introducir 1 si quiere comenzar 0 para que lo haga la cpu)\n");
		scanf("%d",&empieza);
//creo un bucle para que tenga que introducir 1 o 0 y guardare ese dato para darselo al juego y
//que este empieze con el jugador correcto
		while(empieza!=0 ||	empieza!=1)
		{
			printf("introducir 1 si quiere comenzar 0 para que lo haga la cpu)\n");
			scanf("%d",&empieza);
		}
	}else{empieza=rand() % 2;}
//los colores deben ser diferentes para que el juego funcione, usare la libreria <conio.h> para
//darle color a mis letras, con el while hare que los colores sean diferentes porque solo saldra del
//bucle cuando lo sean si los inicializo ambos en el mismo numero

	seleccolor = selec("los colores",seleccolor);
	if(seleccolor=='s')
	{
		while(color1==color2)
		{
			printf("los colores de los jugadores deben ser diferentes \n ");
			printf("¿cual sera el color del otro ordenador? seleccione el numero que le corresponda\n");
			printf("azul=1 \n verde=2 \n cyan=3 \n rojo=4 \n magenta=5 \n marron=6 \n gris claro=7 \n gris oscuro=8 \n celeste=9 \n verde claro=10 \n ");
			scanf("%d",&color2);
//usare esta funcion para revisar que tomaron un color valido, recibe el numero que colocaron y si
//no es uno de los permitidos le pide que coloque otro hasta que lo sea
			color2=colorcheck(color2);

			printf("¿cual sera el otro color \n");
			printf("azul=1 \n verde=2 \n cyan=3 \n rojo=4 \n magenta=5 \n marron=6 \n gris claro=7 \n gris oscuro=8 \n celeste=9 \n verde claro=10 \n ");
			scanf("%d",&color1);

			color1=colorcheck(color1);
		}
	}else{ while(color1==color2 || color1==0 || color2==0 ){
		color1=rand()%11;
		color2=rand()%11;
	}}

//terminan los preparativos y empieza el juego
//tablero tiene la matriz en la que se juega el juego, empieza es un numero(0 o 1) que indica
//quien empieza, los colores 1  2 son numeros(del 1 al 10)
	int juego=1,puntos1=0,puntos2=0,fin=0;
	
	while(juego==1 && fin==0)
//asignar color, cuando termine el turno colocar color 2 y despues colocar otro juego
	{

		if(empieza=1)
			{	

				juego=turno(tablero[(dimenciones-1)*4][(dimenciones-1)*4],empieza,color1,(dimenciones-1)*4,puntos1,puntos2);
				if( juego==0)
				{
//por si el jugador desee rendirse
					printf("el jugador se rindio");
					return EXIT_SUCCESS;
				}
				
			
				empieza=0;
			}
		if(empieza=0)
		{
			juego=turno(tablero,empieza,color2,(dimenciones-1)*4,puntos1,puntos2);
			if (juego==0)
//cuando termina el juego se decide el ganador por los puntos
					{
				if(puntos1==puntos2)
						{
							printf("los puntajes son %d y %d ",puntos1,puntos2);
							printf("es un empate");
						}
				if(puntos1<puntos2)
						{
							printf("los puntajes son %d y %d ",puntos1,puntos2);
							printf("gano la cpu");
						}
				if(puntos1<puntos2)
						{
							printf("los puntajes son %d y %d ",puntos1,puntos2);
							printf("gano el jugador");
						}
					}
			empieza=1;
		}
	}

	return EXIT_SUCCESS;
}

*/


	/*no es necesario chequear el color
int colorcheck(color){
	while(color!=1 && color!=2 && color!=3 && color!=4 && color!=5 && color!=6 && color!=7 && color!=8 && color!=9 && color!=10)
	{
	printf("debe ser un numero de la seleccion dada \n");
	printf("azul=1 \n verde=2 \n cyan=3 \n rojo=4 \n magenta=5 \n marron=6 \n gris claro=7 \n gris oscuro=8 \n celeste=9 \n verde claro=10 \n ");
	scanf("%d",&color);
	}
	return(color);
}

char selec(char* queelige,char selecc)
{
	printf("¿desea seleccionar %s? (s/n)\n",queelige);
	scanf("%c",&selecc);
	while(selec!="s" ||	selec!="n" )
		{
			printf("(introducir la letra s o la letra n)\n");
			scanf("%c",&selecc);
		}
	return(selec);
}
	*/
void posicion(GtkWidget *eventbox,GdkEventButton *event,gpointer data,int punto)
{
	if(punto==1)
	{f1=GUINT_FROM_LE(event->y)/50);//fila
	c1=GUINT_FROM_LE(event->x)/50);//columna
	gchar *temp=g_strdup_printf("preciono la coordenada[%d,%d]",c1,f1);}

	gtk_label_set_text(GTK_LABEL(label_estado),temp);
	g_free(temp);
	if(punto==2)
		{f2=GUINT_FROM_LE(event->y)/50);//fila
		c2=GUINT_FROM_LE(event->x)/50);//columna
		gchar *temp=g_strdup_printf("preciono la coordenada[%d,%d]",c2,f2);

		gtk_label_set_text(GTK_LABEL(label_estado),temp);
		g_free(temp);}
}





int turno(,int empieza,int puntos0,int puntos1,int dimenciones,GtkWidget *eventbox)
{

	int varpunto=0,cont4=0;
	int continua=1;
	while(continua==1)
	{

		continua=0;
		if (varpunto!=0)
//si hubo un cambio de puntos y es el turno del jugador otra vez aqui se suman esos a su puntaje
			{
				if(empieza=0)
					{
						puntos0=puntos0+varpunto;
						continua=1;
					}
				if(empieza=1)
					{
						puntos1=puntos1+varpunto;
						continua=1;
					}
			}

	int varpunto=0;
	if(puntos1+puntos0==(dimenciones-1)*(dimenciones-1)
			{
				return 0;
			}


	int validlin=0;
	if(empieza==0)
	{
		printf("es el turno del jugador");
		g_signal_connect(eventbox,"button_press_event",G_CALLBACK(tablero_cb),tablero);


		int punto=1;
		void posicion(GtkWidget *eventbox,GdkEventButton *event,gpointer data,int punto)
		int punto=2;
		void posicion(GtkWidget *eventbox,GdkEventButton *event,gpointer data,int punto)
	while(f1==f2 && c1==c2 || validlin==0)
	{

			if(empieza==1)//es la cpu
					{//tratara de ver movimientos posibles hasta alcanzar un numero random
				//de movimientos y tomara ese movimiento posible como su movimiento

						int convert=0;
						int horizvert=rand()%2;
						if (horizvert==1)
							{
								convert=1;
								horizvert=0;
							}
						if	(horizvert==0)
						{
							int contador=0,limite,contador2=0,contador3=0;
							limite=rand()%70;
							limite=limite+5;
			//si da cerca de 80 vueltas por el circuito y no puso la linea entonces sale del bucle porque
			//se que no lo pondra a esa altura
							while(contador<limite && contador2<70)
							{
								for(int e=0;e<dimencion-1;e++)
							{
									for(int r=0;r<dimencion;r++)
									{
			//para ver si hay movimientos posibles

										if (tablero[2+e*4][r*4)=='*')
											{
												contador3++;
											}
			//para colocar de forma random la linea
										if(tablero[(e*4+(e+1)*4)/2][r*4]==' '
											{
												contador++;
											}
			//para asegurarse de que no continue de forma infinita
										if(e==dimencion-1 && r==dimencion-1)
											{
												contador2++;

											}
			//cuando el contador que aumenta una vez cada vez que pasa por una casilla que puede
			//llenar alcanza el numero random alli coloca la linea

										if(contador==limite-1)
											{
											if convert=0
													{
											validlin=coloclin(e,r,e+4,r,tablero,color);
													}
											}
											if convert=1
													{
											int o=e,p=r;
											horizvert=1;
													}
									}
								}
							}

						}



	}



}

/*
//introduce un turno de la cpu y el jugador
int turno(,int empieza,int color,int dimencion,int puntos1,int puntos2)
{
	char jugador1[20 ],jugador2[20];
	
	if (empieza==1)
		{
			char *jugador1,*jugador2;
			*jugador1="el jugador";
			*jugador2="la cpu";
		}else{*jugador2="el jugador";
		*jugador1="la cpu";}		
			
			
	int varpunto=0,cont4=0;
	int continua=1;
	while(continua==1){
	if(jugador1=="el jugador")
	{
//si hubo un cambio de puntos y es el turno del jugador otra vez aqui se suman esos a su puntaje
		int *ppuntos1=&puntos1;
		*ppuntos1=puntos1+varpunto;
	}
	if(jugador1=="la cpu")
		{
			int *ppuntos2=&puntos2;
			*ppuntos2=puntos2+varpunto;
		}
		
	int f1=0,f2=0,c1=0,c2=0,varpunto=0,	continua=0;
	printf("%d",tablero);
//si empieza es 1 juega el jugador, o lo hace la cpu
	
//anunciar de quien es el turno
	printf("es el turno de %s",jugador1 );
	printf("los puntos son: \n");
	printf("%s",jugador1);
	printf(" %d\n",puntos1);
	printf("%s",jugador2);
	printf(" %d",puntos2);
	
//en caso de que no haya movimientos posibles se suman las lineas posibles verticales y horizontales
	for(int k=0;k<dimencion-1;k=k+4)
	{
			for(int l=0;l<dimencion-1;l=l+4)
			{
				if(tablero[k*4+2][l*4]==' '){
						cont4++;}
				if(tablero[k*4][l*4+2]==' '){
						cont4++;}
				
			}
	}
	
	int validlin=0;
	while(f1==f2 && c1==c2 || validlin==0)
	{
		if(jugador1=="el jugador")
		{
//si la suma las lineas posibles verticales y horizontales es 0 se pasa el turno para que 
//termine el juego en el turno de 	la cpu 
			if(cont4==0)
					{
						printf("no hay forma de colocar otra linea");
						return 1;
					}
//la dimencion es el tamaño real de la matriz
			printf("de posiciones a 2 puntos adyacentes para formar su linea o introduzca 0 para rendirse \n");
			printf("escriba la fila del 1er nodo \n");
			scanf("%d",&f1);
			if(f1==0){return 0;}
			f1=puntoval(f1,dimencion,1,f1);

			printf("ahora la columna del 1er nodo \n");
			scanf("%d",&c1);
			c1=puntoval(c1,dimencion,1,f1);

			printf("escriba la fila del 2do nodo adyacente \n");
			scanf("%d",&f2);
			f2=puntoval(f2,dimencion,2,f1);

			printf("escriba la columna del 2do nodo adyacente \n");
			scanf("%d",&c2);
			c2=puntoval(c2,dimencion,2,c1);
		}
//la cpu debe elegir 2 puntos libres que tengan la caracteristica de estar uno alado del otro para formar una linea
//la computadora usara un numero al azar para ver si la linea sera horizontal o vertical, buscara pociciones donde
//puede colocar una linea y con otro numero al azar recorrera la matriz hasta que con el numero random 
//se detenga y elija los puntos

//															esta estrategia debe cambiar
		if(jugador1=="la cpu")
		{
			int convert=0;
			int horizvert=rand()%2;
			if (horizvert==1)
				{
					convert=1;
					horizvert=0;
				}
			if	(horizvert==0)
			{
				int contador=0,limite,contador2=0,contador3=0;
				limite=rand()%70;
				limite=limite+5;
//si da cerca de 80 vueltas por el circuito y no puso la linea entonces sale del bucle porque 
//se que no lo pondra a esa altura
				while(contador<limite && contador2<80)
				{
					for(int e=0;e<dimencion-1;e++)
				{
						for(int r=0;r<dimencion;r++)
						{
//para ver si hay movimientos posibles
							if (tablero[2+e*4][r*4)=='*')
								{
									contador3++;
								}
//para colocar de forma random la linea
							if(tablero[(e*4+(e+1)*4)/2][r*4]==' '
								{
									contador++;
								}
//para asegurarse de que no continue de forma infinita
							if(e==dimencion-1 && r==dimencion-1)
								{
									contador2++;
									
								}
//cuando el contador que aumenta una vez cada vez que pasa por una casilla que puede
//llenar alcanza el numero random alli coloca la linea
							
							if(contador==limite-1)
								{
								if convert=0
										{
								validlin=coloclin(e,r,e+4,r,tablero,color);
										}
								}
								if convert=1
										{
								int o=e,p=r;
								horizvert=1;
										}
						}
					}
				}
			
			}
//si se cumple esta condicion habra sido porque n hay forma de rellenar un espacio horizontal
			if (contador3==(dimencion-1)*dimencion)
				{
					horizvert=1;
				}
			if horizvert==1
			{
				int contador=0,limite,contador2=0,contador3=0;
				limite=rand()%70;
				limite=limite+5;
				while(contador<limite && contador2<80)
				{
					for(int e=0;e<dimencion;e++)
					{
						for(int r=0;r<dimencion-1;r++)
						{
							if (tablero[2+e*4][r*4)=='*')
								{
									contador3++;
								}
							if(tablero[(e*4][r*4+(r+1)*4)/2]==' '
								{
									contador++;
								}
							if(e==dimencion-1 && r==dimencion-1)
								{
									contador2++;
									
								}
							if(contador==limite-1)
								{
								validlin=coloclin(e,r,e,r+4,tablero,color);
								}
							if contador3==(dimencion-1)*dimencion
								{
									if convert=1
											{
										if (o!=0 && p!=0){
										validlin=coloclin(o,p,o,p+4,tablero,color);
										}else{return 0;}
										
									
											}
								}
						}
					}
				}
			
			}
		
		}
//agregar revisar que no hay nada antes
	
			validlin=coloclin(f1,c1,f2,c2,tablero,color);
//hay que verificar que la linea no este ya en el tablero, para esto pense en ver como el la linea
//con eso sabre que posicion ente ellas debo observar, si en esa posicion hay una * sabre que hay una
//linea alli, se repetira el while hasta que elijan una posicion no ocupada o se rindan
		
		char letra[2];
		switch(color)
		{
			case 1:
				letra="A";
			case 2:
				letra="V";
			case 3:
				letra="Cy";
			case 4:
				letra="R";
			case 5 :
				letra="Mg";
			case 6:
				letra="Mr";
			case 7:
				letra="GC";
			case 8:
				letra="GO";
			case 9:
				letra="Cl";
			case 10:
				letra="VC";
		}
		
		
//para tratar con los puntos use esta forma, 
		switch (validlin)
		{
			case 2:
				if (tablero[f1+4][c1-2]=="*" && tablero[f1+2][c1-4]=="*" && tablero[f1][c1-2]=="*" && tablero[f1+2][c1]=="*" )
				{
					textcolor(color);
					tablero[f1+2][c1+2]==("%s",&letra);
					printf("+10 puntos");
					varpunto=varpunto+10;
					
				}
				if(tablero[f1+4][c1+2]=="*" && tablero[f1+2][c1]=="*" && tablero[f1][c1+2]=="*" && tablero[f1+2][c1+4]=="*" )
				{
					textcolor(color);
					tablero[f1-2][c1-2]==("%s",&letra);
					printf("+10 puntos");
					varpunto=varpunto+10;
					
				}
			case 1:
				if (tablero[f1-4][c1-2]=="*" && tablero[f1-2][c1-4]=="*" && tablero[f1][c1-2]=="*" && tablero[f1-2][c1]=="*" )
				{
					textcolor(color);
					tablero[f1+2][c1+2]==("%s",&letra);
					printf("+10 puntos");
					varpunto=varpunto+10;
									
				}
				if(tablero[f1-4][c1+2]=="*" && tablero[f1-2][c1]=="*" && tablero[f1][c1+2]=="*" && tablero[f1-2][c1+4]=="*" )
				{
					textcolor(color);
					tablero[f1-2][c1-2]==("%s",&letra);
					printf("+10 puntos");
					varpunto=varpunto+10;
				}
			case 3:
				if(tablero[f1-4][c1+2]=="*" && tablero[f1-2][c1]=="*" && tablero[f1][c1+2]=="*" && tablero[f1-2][c1+4]=="*" )
				{
					textcolor(color);
					tablero[f1-2][c1-2]==("%s",&letra);
					printf("+10 puntos");
					varpunto=varpunto+10;
				}
				if(tablero[f1+4][c1+2]=="*" && tablero[f1+2][c1]=="*" && tablero[f1][c1+2]=="*" && tablero[f1+2][c1+4]=="*" )
				{
					textcolor(color);
					tablero[f1-2][c1-2]==("%s",&letra);
					printf("+10 puntos");
					varpunto=varpunto+10;
				}
			case 4:
				if (tablero[f1-4][c1-2]=="*" && tablero[f1-2][c1-4]=="*" && tablero[f1][c1-2]=="*" && tablero[f1-2][c1]=="*" )
				{
					textcolor(color);
					tablero[f1+2][c1+2]==("%s",&letra);
					printf("+10 puntos");
					varpunto=varpunto+10;
													
				}
				if (tablero[f1+4][c1-2]=="*" && tablero[f1+2][c1-4]=="*" && tablero[f1][c1-2]=="*" && tablero[f1+2][c1]=="*" )
				{
					textcolor(color);
					tablero[f1+2][c1+2]==("%s",&letra);
					printf("+10 puntos");
					varpunto=varpunto+10;
				}
				
		}
//si el cambio de cantidad de puntos ocurrio( se logro crear un cuadrado) el jugador continua su turno
		if (0<varpunto)
		{
			continua=1;
		}
	}
	}


//si regresa 1 el juego continua, regresa 0 y para
	return(1);
}
*/

//tengo que confirmar que los puntos son validos el numero recibido en caso del primer punto debe ser
//menor a los limites de la matriz, el segundo punto tiene mas restricciones y debe ser adyacente
//al primero y la linea formada no puede haber existido antes
int puntoval(filaocolumna,dimencion,numero,f1)
{
	int size=dimencion/4;
	filaocolumna=filaocolumna/4;
	while(filaocolumna < 1 || size < filaocolumna)
	{
		printf("el numero debe ser del 1 al %d \n",size);
		scanf("%d",filaocolumna);
//originalmente esta parte y la anterior estban separadas pero se me ocurrio que podrian colocar
//con la segunda parte fuera de la matriz otra vez, le numero sera 2 solo si el punto es el segundo
//para ser adyacente tanto la fila como la columna deben tener los valores de la fila y columna
//anteriores +1 -1 o 0 pero la fila y columna no pueden ser 0 a la vez
		if (numero==2)
		{
			while(filaocolumna != f1 + 1 ||  filaocolumna != f1 - 1 ||  filaocolumna != f1)
			{
				printf("el punto debe ser adyacente al anterior %d (+1 +0 -1) \n",f1);
				scanf("%d",filaocolumna);
			}

		}
	}
	return filaocolumna;
}

//debe retornar 1 y puede colocarse la linea definida entre los 2 puntos y 0 si no, para permitirse los puntos deben
//ser adyacentes
int coloclin(f1,c1,f2,c2,tablero,color){
	int v=0;
	
//inicializo una variable v dependiendo de cual de los condicionales si entre cambiara de valor, si no entra en 
//ninguno retornara 0 y el bucle forzara otra eleccion de puntos, con estos valores puedo saber como es la linea 
//formada, puesto que identifica por cual de los si paso ya que en cada caso seria diferente, lo que ayudaria a
//la hora de ver si se creo un cuadrado
	if(f1 == f2 && c1 != c2 && tablero[f1][(c1+c2)/2]!="*")
		{
		
			textcolor(color);

			for(int i=1;i<3;i++)
			{
				if( c2 == c1 + 4)
				{
					char *pa;
					pa=&tablero[f1][c1+i];
					*pa = "*";
					v=1;
				}
				if( c1 == c2 + 4)
				{
					char *pa;
					pa=&tablero[f1][c1-i];
					*pa = "*";
					
					v=2;
				}
			}
		}

	if(c1 == c2 && f1 != f2 && tablero[(f1+f2)/2][c1]!="*")
		{
		textcolor(color);

		for(int i=1;i<3;i++)
			{
				if(f2 == f1 + 4 )
					{
						char *pa;
						pa=&tablero[f1+i][c1];
						*pa = "*";
						
						v=3;
					}
				if(f1 == f2 + 4 )
					{
						char *pa;
						pa=&tablero[f1-i][c1];
						*pa = "*";
						
						v=4;
					}
			}
		}
	

	return (v);
}

in
t

//para estrategia
//para la cpu, debe revisar el tablero, si puede encerrar casilla considera proximo mov,
//hacer eso hasta que no pueda mas y ver si el otro podra encerrar un numero mayor de casillas
//si se deja el tablero como quedaria,
//si eso ocurre realizar la operacion hasta el punto en que empieza la cadena del otro y parar,
//ver si hay posiciones libres en las que no se podra encerrar y colocar alli la linea
//si no puede encerrar colocar de modo que se pueda encadenar encierres y nunca debe
//tener 3 de los 4 lados del cuadrado si puede
//si no hay espacios libres que no formen parte de una cadena ver cadenas mas cortas que puedas rendir
//tambien si la cadena que uno hace es larga (mas de 3 cuadrados)y no hay espacio rendir los ultimos 2
//cuadrados si fuerza al otro a permitirte encerrar cuadrados
