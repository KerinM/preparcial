
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cctype>
#include <limits>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <conio.h>
#include <windows.h>



using namespace std;

int gotoxy(USHORT x,USHORT y){                                  
COORD cp={x,y};                                                 
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cp);   
}

struct NODO {
       char IDEN[30] ;
       char nom[50];
       char ape[50];
       char sexo[2];
       char edad[3];
       char codmun[10];
       NODO  *SIG;
};

int MENU();
void  CAPTURA();
void ARCHIVO();
void  CONSULTA();
void GUARDAR();
void  ELIMINAR();

int  VALIDACION( char IDEN  ,int SW);

NODO  *CABEZA, *FIN ;



 main()
   {
   char OP = 'S';
   int  TIPO ;
   CABEZA = NULL ;
   while ( OP == 'S')
     {
     TIPO = MENU();
     switch (TIPO) {
        case 1 : CAPTURA();
                 break;
        case 2 : ARCHIVO();
		         break;
		case 3 : CONSULTA();
		         break;
		case 4 : GUARDAR();
		         break;
	    case 5 : ELIMINAR();
		         break;
		case 6 : 
		        cout << "IRMA MONTAÑO 2024-1";
		        OP = 'N';
           }
        }
    }



int MENU()
  {
  int OPCION ;
  system("cls");
  system("color F0");
  gotoxy(26,6) ; cout << " LISTAS ENLAZADAS SIMPLES";
  gotoxy(25,7) ; cout << "CAPTURA, CONSULTA Y ELIMINACION" ;
  gotoxy(30,11); cout << "1. CAPTURA DE DATOS" ;
  gotoxy(30,12); cout << "2. CAPTURA DE DATOS DESDE ARCHIVO" ;
  gotoxy(30,13); cout << "3. CONSULTA DE DATOS";
  gotoxy(30,14); cout << "4. GUARDAR A ARCHIVO";
  gotoxy(30,15); cout << "5. ELIMINAR";
  gotoxy(30,16); cout << "6. SALIR";
  do {
     gotoxy(22,22); cout << "SELECIONE UNA DE LAS ALTERNATIVAS : ";
     cin >> OPCION ;
   } while((OPCION < 1) || (OPCION > 6)) ;
  return OPCION ;
  }


void  CAPTURA()
  {
  NODO *P ;
  int SW, iden ;
  char OP = 'S';
  while (OP == 'S')
    {
    system("cls");
    gotoxy(26,5) ; cout << "LISTAS ENLAZADAS SIMPLES";
    gotoxy(36,7) ; cout << "CAPTURA DE DATOS";
    gotoxy(20,11); cout <<"IDENTIFICACION :      ";
    gotoxy(20,12); cout <<"NOMBRE :      ";
    gotoxy(20,13); cout <<"APELLIDO :      ";
    gotoxy(20,14); cout << "SEXO :";
    gotoxy(20,15); cout << "EDAD :";
    gotoxy(20,16); cout << "CODIGO MUNICIPIO :";
    P = new NODO;
    do{
    	gotoxy(40,11); cin >> P->IDEN ;
    	iden=atoi(P->IDEN);
	}while(iden<0||iden>9999999999||iden==isdigit(iden));
	
    gotoxy(32,12); cin >> P->ape ;
    gotoxy(32,13); cin >> P->nom ;
    gotoxy(32,14); cin >> P->sexo ;
    gotoxy(32,15); cin >> P->edad ;
    gotoxy(40,16); cin >> P->codmun ;
	SW = 0;
    SW = VALIDACION(P-> IDEN[15], SW);
    if (SW == 1)
       delete P;
      else
		{
		P->SIG = NULL ;
 	    if (CABEZA == NULL)
	       CABEZA =  P ;
	      else
	       FIN->SIG = P;
        FIN = P;
        }
      do {
	     gotoxy(29,20); cout <<"DESEA CONTINUAR S/N : ";
	     OP = toupper(getch());
	  } while((OP != 'S') && (OP != 'N'));
     }
  }
 
 
void CONSULTA()
{ 
    NODO *P = CABEZA;
    int Y = 12;
    int contador = 0; 
    if (CABEZA == NULL)
    {
        gotoxy(22,24); cout << " NO EXISTE LISTA";
        getch();
    }
    else
    {
        system("cls");
        gotoxy(26,5) ; cout << "LISTAS ENLAZADAS SIMPLES";
        gotoxy(31,7) ; cout << "CONSULTA SIMPLE";
        gotoxy(20,11); cout << "IDENTIFICACION          APELLIDO         NOMBRE         SEXO        EDAD      CODIGO DE MUNICIPIO";
    
        while (P != NULL)         
        {
            if((strcmp(P->sexo, "F") == 0 ) /*&& (strcmp(P->codmun, "787")==0)*/)
            {
                gotoxy(20,Y);cout << P -> IDEN << "  ";
                gotoxy(45,Y);cout << P -> ape << "  ";
                gotoxy(60,Y);cout << P -> nom << "  ";
                gotoxy(78,Y);cout << P -> sexo << "  ";
                gotoxy(90,Y);cout << P -> edad << "  ";
                gotoxy(110,Y);cout << P -> codmun << "  ";
                Y++;
                contador++; 
            }
            P = P -> SIG ;
        }
        cout << "\nRegistros encontrados: " << contador; 
        cout << "\nPulse cualquier tecla para Continuar";
        getch();
    }
    
    P = CABEZA;
}

void GUARDAR(){
    NODO *P = CABEZA;
    int cont = 0;
    FILE *archivo = fopen("C://UPC2024//ARCHIVO//PARCIAL.txt", "w");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
    } else {
        while (P != NULL) {
            if (strcmp(P->sexo, "F") == 0) {
              
                if (atoi(P->edad ) <18) {
                	  cont++;
                    fprintf(archivo,"%s,%s,%s,%s,%s,%s\n", P->IDEN, P->ape, P->nom, P->sexo, P->edad, P->codmun);
                }
            }
            P = P->SIG;
        }
       
        fprintf(archivo, "Cantidad de mujeres en tamalameque: %d\n", cont);
       
        fclose(archivo);
        cout << "Los datos han sido guardados en el archivo." << endl;
    }
}

 
  

void ARCHIVO(){
 string s;
 ifstream f("C://UPC2024//ARCHIVO//USUARIOS.txt");
 if (!f.is_open())
  {
    cout << "Error al abrir USUARIOS.txt\n";
    exit(EXIT_FAILURE);
  }
else{ 
	string linea;
	while (getline(f, linea)) {
		NODO *nuevo = new NODO;
		size_t pos1 = linea.find(',');
        size_t pos2 = linea.find(',', pos1 + 1);
        size_t pos3 = linea.find(',', pos2 + 1);
        size_t pos4 = linea.find(',', pos3 + 1);
        size_t pos5 = linea.find(',', pos4 + 1);
        size_t pos6 = linea.find(',', pos5 + 1);
		strcpy(nuevo->IDEN,linea.substr(0, pos1).c_str());
        strcpy(nuevo->ape,linea.substr(pos1 + 1, pos2 - pos1 - 1).c_str());
        strcpy(nuevo->nom,linea.substr(pos2 + 1, pos3 - pos2 - 1).c_str());
        strcpy(nuevo->sexo,linea.substr(pos3 + 1,pos4 - pos3 - 1).c_str());
        strcpy(nuevo->edad,linea.substr(pos4 + 1,pos5 - pos4 - 1).c_str());
        strcpy(nuevo->codmun,linea.substr(pos5 + 1,pos6-linea.length()-1).c_str());
        
        if (CABEZA == NULL) {
                CABEZA = nuevo;
                FIN = nuevo;
            } else {
                FIN->SIG = nuevo;
                FIN = nuevo;
            }
	}

 }
 
}


// *********************** FUNCION ELIMINAR **********************

void ELIMINAR()
   {
   int  SW ;
   char DATO[15];
   NODO *K, *P ;
   char  OP = 'S';
   while (OP == 'S')
      {
      if (CABEZA == NULL)
	     {
	     gotoxy(22,24); cout << " NO EXISTE LISTA";
	     OP = 'N' ; getch() ;
	     }
       else
	     {
	     P = CABEZA;
	     system("cls");
	     gotoxy(26,5) ; cout << "LISTAS ENLAZADAS SIMPLES";
	     gotoxy(33,7) ; cout << "ELIMINAR ELEMENTO";
	     gotoxy(20,11); cout << "IDENTIFICACION: ";
	     gotoxy(35,11); cin >> DATO;
	     SW = 0;
	     while ((P != NULL) && (SW == 0))
	        {
	        if (DATO[15] == P->IDEN[15])
	           {
	           SW = 1;
	           if  (P == CABEZA)
		           CABEZA = P->SIG;
	             else
	               {
				   K->SIG = P->SIG;
                   if (FIN == P)
		              FIN = K;
		           }
		       delete(P);
	            cout <<"ELEMENTO ELIMINADO"; 
	           }
	         else
	           {
	           K  = P;
	           P  = P->SIG ;
	           }
	        }
	     if  (SW == 0)
	         {
	         gotoxy(40,11); cout << "ELEMENTO NO ENCONTRADO"; 
			 }
	     do {
	        gotoxy(29,20); cout <<"DESEA CONTINUAR S/N : ";
	        OP = toupper(getche());
	     } while((OP != 'S') && (OP != 'N'));
       }
    }
 }
 
 // *********************** FUNCION VALIDACION **********************
   
 int VALIDACION(char IDEN, int SW)
  {
  NODO *P = CABEZA;
  while ((P != NULL) && (SW == 0))
    {
    if ( IDEN == P->IDEN[15])
       {
       SW = 1;
       gotoxy(40,11); cout << " REGISTRO EXISTE " ;
       }
    P  = P->SIG;
    }
  return SW;
  }

