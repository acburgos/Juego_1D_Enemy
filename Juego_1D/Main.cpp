#include <conio.h>
#include <Windows.h>
#include <stdio.h>


// Caracteristicas pantalla
#define ANCHO 60
#define PRIMERA_LINEA  10
#define PRIMERA_COLUMNA 20
#define FPS 20


// Elementos Juego
#define PERSONAJE '*'
#define FONDO_PANTALLA '-'
#define BALA 'o'
#define JOSICO 'A'


// Definicion de variables globales

int posicionJugador;
int posicionBala;
int posicionJosico;
int estadoJosico; // 1-> moviendo hacia izquiera, 2 -> moviendo hacia derecha, 0-> muerto
int estadoBala; // 1-> bala izquierda, 2 -> bala derecha, 0-> no hay bala
char caracterActual;
int estadoJuego;


// Declaracion de funciones

void dibujar();
void actualizarEstados(); // Funcion de actualizacion de estados
void colocarLinea(); // Colocacion de la pantalla en consola
void init(); // Funcion de inicilizacion de estados


int main()
{
	init(); // Llamada a inicializacion

	// Bucle de juego
	while (1)
	{
		system("cls"); // Limpiar consola
		colocarLinea();
		actualizarEstados();
		dibujar();

		// Calcula de espera para cumplir FPS deseados
		Sleep(1000 / FPS);
	}
	return 0;
}


// Definicion de funciones
void dibujar()
{
	// Colocamos el inicio de la pantalla en la columna deseada
	for (int i = 0; i < PRIMERA_COLUMNA; i++) printf(" ");

	// Imprimimos por pantalla las posiciones de los elementos
	for (int i = 1; i < ANCHO+1; i++)
	{
		if (!estadoJuego)
		{
			printf("GAME OVER. PRESS 'R' TO RESTART");
			break;
		}
		else if (i == posicionJugador) printf("%c", PERSONAJE);
		else if (i == posicionBala & estadoBala > 0) printf("%c", BALA);
		else if (i == posicionJosico & estadoJosico > 0) printf("%c", JOSICO);
		else printf("%c", FONDO_PANTALLA);
	}
}

void actualizarEstados()
{
	// Comprobacion de entrada 
	if (_kbhit())
	{
		// Obtencion del caracter pulsado
		caracterActual = _getch();
		
		// Movimiento del jugador
		if (!estadoJuego & caracterActual=='r') init();
		else if (posicionJugador < ANCHO & caracterActual == 'p') posicionJugador++;
		else if (posicionJugador > 1 & caracterActual == 'o') posicionJugador--;

		// Comprobacion de disparo del jugador
		else if (!estadoBala & caracterActual == 'q')
		{ 
			estadoBala = 1;
			posicionBala = posicionJugador;
		}
		else if (!estadoBala & caracterActual == 'w')
		{
			estadoBala = 2;
			posicionBala = posicionJugador;
		}	
	}

	// Actualizacion si hay bala en pantalla: colision con enemigo y movimiento
	if (posicionJosico==posicionBala+1 | posicionJosico == posicionBala - 1 | posicionJosico==posicionBala)
	{
		estadoJosico = 0;
		estadoBala = 0;
	}
	else if (posicionBala > ANCHO | posicionBala < 1) estadoBala = 0; 
	else if (estadoBala == 1) posicionBala--;
	else if (estadoBala == 2) posicionBala++;

	// Actualizacion de enemigo: colision con jugador y movimiento
	if (!estadoJosico)
	{
		estadoJosico = (rand() % 2 ? 1 : 2);
		posicionJosico = (estadoJosico > 1 ? 1 : ANCHO);
	}
	else if (posicionJugador == posicionJosico + 1 | posicionJugador == posicionJosico + 1 | posicionJugador == posicionJosico) estadoJuego = 0;
	else if (estadoJosico == 1) posicionJosico--;
	else if (estadoJosico == 2) posicionJosico++;

}

void colocarLinea()
{
	for (int i = 0; i < PRIMERA_LINEA; i++) printf("\n");
}

void init()
{
	posicionJugador = ANCHO/2;
	estadoBala = 0;
	estadoJosico = 0;
	estadoJuego = 1;
}