#include <stdio.h>
#include <string.h>
#include <math.h>
//#include <bits/stdc++.h>
using namespace std;
#define INF INT_MAX
#define MAX_LONG_PALABRA 80
#define MAX_NOMBRE_ARCHIVO 80

void printSolution (int p[], int n, char** txt)
{
    if(p[n]>1)
        printSolution (p, p[n]-1,txt);
    for (int i = 1; i < n; i++) {
//        cout<<"From word no. "<<p[n]<<" to "<<n<<endl;
        printf("%s ",txt[i]);
    }
    printf("\n");
//    }
}

void solveWordWrap (int l[], int n, int M, char** txt)
{
    // For simplicity, 1 extra space is used in all below arrays
  
    // extras[i][j] will have number of extra spaces if words from i
    // to j are put in a single line
    int extras[n+1][n+1];
  
    // lc[i][j] will have cost of a line which has words from
    // i to j
    int lc[n+1][n+1];
  
    // c[i] will have total cost of optimal arrangement of words
    // from 1 to i
    int c[n+1];
  
    // p[] is used to print the solution.
    int p[n+1];
  
    int i, j;
  
    // calculate extra spaces in a single line. The value extra[i][j]
    // indicates extra spaces if words from word number i to j are
    // placed in a single line
    for (i = 1; i <= n; i++)
    {
        extras[i][i] = M - l[i-1];
        for (j = i+1; j <= n; j++)
            extras[i][j] = extras[i][j-1] - l[j-1] - 1;
    }
  
    // Calculate line cost corresponding to the above calculated extra
    // spaces. The value lc[i][j] indicates cost of putting words from
    // word number i to j in a single line
    for (i = 1; i <= n; i++)
    {
        for (j = i; j <= n; j++)
        {
            if (extras[i][j] < 0)
                lc[i][j] = INF;
            else if (j == n && extras[i][j] >= 0)
                lc[i][j] = 0;
            else
                lc[i][j] = extras[i][j]*extras[i][j];
        }
    }
  
    // Calculate minimum cost and find minimum cost arrangement.
    // The value c[j] indicates optimized cost to arrange words
    // from word number 1 to j.
    c[0] = 0;
    for (j = 1; j <= n; j++)
    {
        c[j] = INF;
        for (i = 1; i <= j; i++)
        {
            if (c[i-1] != INF && lc[i][j] != INF &&
                           (c[i-1] + lc[i][j] < c[j]))
            {
                c[j] = c[i-1] + lc[i][j];
                p[j] = i;
            }
        }
    }
    printSolution(p, n, txt);
}
//static void pretty(char** txt,int final, int *saltos){
//    if(final > 1){
//        pretty(txt,saltos[final],saltos);
//        for(int k = saltos[final]; k < final; k++)
//            printf("%s " , txt[k]);
//        printf("\n");
//    }
//}

int main(){
    int L;
    char nom_archivo[MAX_NOMBRE_ARCHIVO];
    scanf("%d %s", &L, nom_archivo);

    FILE *descriptor = fopen(nom_archivo, "r");
    char palabra[MAX_LONG_PALABRA];
    char**txt = new char*;
    int res_lectura = fscanf(descriptor, "%s", palabra);
    int count = 1;
    while (res_lectura != EOF){
        txt[count] = new char[sizeof(palabra)];
        strcpy(txt[count], palabra);
        count++;
        res_lectura = fscanf(descriptor, "%s", palabra);
    }
    fclose(descriptor);
//        for (int i = 1; i < count; i++)
//    //        cout<<"From word no. "<<p[n]<<" to "<<n<<endl;
//            printf("%s ",txt[i]);
//            
    int *largo = new int[count];
    largo[0] = 0;
    for (int i = 1; i < count; i++)
        largo[i] = strlen(txt[i]);

    solveWordWrap(largo,count+1,L,txt);
    
    delete[] largo;
    
//   int **puntaje = new int*[count];
//    for(int column = 1; column < count; column++)
//    {
//        puntaje[column] = new int[count];
//    }
//
//    for (int columna = 1; columna < count; columna++)
//    {
//        // printf("\n%d: ", columna);
//
//        for(int fila = 1; fila < count; fila++){
//            int dif = largo[columna] - largo[fila-1];
//            if(dif <= 0)
//                dif = 0;
//            int linea = L-dif;
//            if(linea>0)
//                puntaje[columna][fila] = pow(linea,2);
//            else
//                puntaje[columna][fila] = pow(L,2);
//        // printf("%d ", puntaje[columna][fila]);
//        }
//    }

//    int *opt = new int[count];
//    opt[0] = 0;
//
//    int *saltos = new int[count];
//    for (int r = 0; r < count; r++) {
//        saltos[r] = 0;
//    }
//    for (int column = 1; column < count; column++){
//        int min = puntaje[column][1];
//        saltos[column] = 0;
//        for (int row = 2; row < count; row++){
//            if(puntaje[column][row] + opt[row-1] < min){
//                min = puntaje[column][row] + opt[row-1];
//                saltos[column] = row-1;
//            }
//        }
//        opt[column] = min;
//
//    }
//    pretty(txt,count,saltos);
    for (int d = 1; d < count; d++) {
      delete[] txt[d];
    }
    delete txt;
//    for (int d = 0; d < count; d++) {
//      delete[] puntaje[d];
//    }
//    delete[] puntaje;
//    delete[] opt;
//    delete[] saltos;
//    delete[] largo;

}
