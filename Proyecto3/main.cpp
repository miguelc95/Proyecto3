//Equipo: Jose Carmelo Ramirez Beltran A01175987 (Clase Lu Ju 12:00pm) y Miguel Cuellar Gauna A01280736 (Clase Lu Ju 3:00pm)
//Algoritmo: Convex Hull (Get close path in a given set of points)
//Bibliografia: made by Rajeev Agrawal, posted in Geeks For Geeks (http://www.geeksforgeeks.org/find-simple-closed-path-for-a-given-set-of-points/)
//Fecha: 17/03/2016
//Proyecto: C - Protecting Beagle Town

#include <iostream>
#include <iomanip>
#include <stack>
#include <stdlib.h>
#include <cmath>
using namespace std;

//Structrua Punto: Incluye un punto X y un punto Y
struct Punto
{
    int iX, iY;
};

// A globle point needed for  sorting points with reference
// to  the first point Used in compare function of qsort()
Punto p0;

//Funcion que encuentra el siguiente punto en el Stack
Punto siguientePunto(stack<Punto> &StackPuntos)
{
    Punto p = StackPuntos.top();
    StackPuntos.pop();
    Punto pSig = StackPuntos.top();
    StackPuntos.push(p);
    return pSig;
}

// Funcion que intercambia dos puntos
void swap(Punto &p1, Punto &p2)
{
    Punto pAux = p1;
    p1 = p2;
    p2 = pAux;
}

// Funcion que encuentra la distancia cuadrarda entre dos puntos
// between p1 and p2
long long distancia(Punto p1, Punto p2)
{
    return pow((p1.iX - p2.iX),2) + pow((p1.iY - p2.iY),2);
}

// Encontrar orientacion entre tres puntos
// Valores retornados:
// 0 --> Estan en linea
// 1 --> Sentido del reloj
// 2 --> Sentido contrario al del reloj
int orientacion(Punto p, Punto q, Punto r)
{
    long long iVal = (q.iY - p.iY) * (r.iX - q.iX) -
    (q.iX - p.iX) * (r.iY - q.iY);
    
    if (iVal == 0)
        return 0;  // En la misma linea
    return (iVal > 0)? 1: 2; // en sentido o en contra del reloj
}

// Ordena una seria de puntos dependiendo del primer punto dado
int comparar(const void *vp1, const void *vp2)
{
    Punto *p1 = (Punto *)vp1;
    Punto *p2 = (Punto *)vp2;
    
    // Recibe la orentiacion
    int iO = orientacion(p0, *p1, *p2);
    if (iO == 0)
        return (distancia(p0, *p2) >= distancia(p0, *p1))? -1 : 1;
    
    return (iO == 2)? -1: 1;
}

// Imprime el perimetro del muro formado entre los puntos
void convexHull(Punto puntos[], int n)
{
    // Encuentra el punto mas bajo
    int iYmin = puntos[0].iY, min = 0;
    for (int i = 1; i < n; i++)
    {
        int iY = puntos[i].iY;
        
        // Elje el punto mas abajo o el de la izquierda en caso de empate
        if ((iY < iYmin) || (iYmin == iY && puntos[i].iX < puntos[min].iX))
            iYmin = puntos[i].iY, min = i;
    }
    
    // Pone el punto encontrado en la primera posicion
    swap(puntos[0], puntos[min]);
    
    // Acomoda los puntos restantes de acuerdo al primer punto
    // el punto p1 esta antes de p2 en un output acomodado si p2 tiene un angulo polar mayor  (en sentido contrario al reloj)que p1
    p0 = puntos[0];
    qsort(&puntos[1], n-1, sizeof(Punto), comparar);
    
    // Si dos o mas puntos tienen el mismo angulo que p0, se remueven todos menos el mas alejado al punto p0
    int m = 1; // Inicializamos el arreglo
    for (int i=1; i<n; i++)
    {
        // Mantener removiendo i mientras  el angulo de i y i+1 es lo mismo respecto a p0
        while (i < n-1 && orientacion(p0, puntos[i], puntos[i+1]) == 0)
        {
            i++;
        }
        puntos[m] = puntos[i];
        m++;  // Actualizamos el tamaÒo del arreglo
    }
    
    // Si el modificado tiene menos de 3 puntos es imposible hacer un convex hull
 if (m < 3) return;
    
    // Creamos un stack vacio
    stack<Punto> StackPuntos;
    StackPuntos.push(puntos[0]);
    StackPuntos.push(puntos[1]);
    StackPuntos.push(puntos[2]);
    
    // Procesamos los siguiente n-3 puntos
    for (int i = 3; i < m; i++)
    {
        // Seguimos removiendo el primero mientras el angulo formado por los puntos siguiente, primero, y punto[i]hacen una vuelta no a la derecha
        while (orientacion(siguientePunto(StackPuntos), StackPuntos.top(), puntos[i]) != 2)
            StackPuntos.pop();
        StackPuntos.push(puntos[i]);
    }
    
    Punto pAux, pFinal, p;
    long double fPer=0;
    pFinal = StackPuntos.top();
    Punto arr[100000];
    int av=0;
    while (!StackPuntos.empty())
    {
        arr[av]=StackPuntos.top();
        av++;
        StackPuntos.pop();
     /*   if(StackPuntos.size() > 1)
        {
            p = StackPuntos.top();
            pAux = p;
            StackPuntos.pop();
            p = StackPuntos.top();
            fPer += sqrt(pow((pAux.iX - p.iX), 2) + pow((pAux.iY - p.iY), 2));
        }
        else
        {
            p = StackPuntos.top();
            StackPuntos.pop();
            fPer += sqrt(pow((pFinal.iX - p.iX), 2) + pow((pFinal.iY - p.iY), 2));
        }
      */
        
    }
    fPer+=sqrt(distancia(arr[0], arr[av-1]));
    
    for (int ix=0; ix<av-1; ix++) {
        fPer+=sqrt(distancia(arr[ix], arr[ix+1]));
    }
    cout<<"The perimeter of the wall is: "<<fixed<<setprecision(2)<<fPer<<endl;
}

// Driver program to test above functions
int main()
{
    int iCant, iX, iY, iTam;
    cin>>iCant;
    Punto puntos[iCant];
    //Agregamos los puntos
    for(int i=0; i < iCant; i++)
    {
        cin>>iX>>iY;
        puntos[i].iX = iX;
        puntos[i].iY = iY;
    }
    iTam = sizeof(puntos)/sizeof(puntos[0]);
    //LLamamos a la funcion para crear el muro
    convexHull(puntos, iTam);
    return 0;
}

