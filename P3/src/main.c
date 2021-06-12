/*
NOMBRES: 
 - Xavier Pérez Ruiz            1566276
 - Pablo Andrés Rodriguez       
SESSIÓN: 314
*/

#include <stdio.h>
#include <stdint.h>

void bin(unsigned n)
{
    unsigned int i = 0;
    /* i=i>>1 es el mateix que i=i/2 */
    for (i=0x80000000;i>0;i=i>>1){
        if((n&i)>0){/* Si l'operador AND dona 1, mostrar aquest valor per pantalla*/
            printf("1");
        }
        else{/* En cas contrari, mostrar '0' per pantalla*/
            printf("0");
        }
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    unsigned int moviment = 0x00110011;     //Declarem el sencer
    
//          EXERCICI 1
//==================================

    printf("\n\t\tEXERCICI 1\n");
    printf("===============================================\n");
    moviment = ~moviment | moviment;                                    // Invertim tots els bits de l'enter i el sumem per ell mateix per posar tots els bits a 1  
    printf("moviment = "); bin(moviment); printf("\n");


//          EXERCICI 2
//==================================

    printf("\t\tEXERCICI 2\n");
    printf("===============================================\n");

    unsigned int movimentInvertit;                                      // Declarem dues variables auxiliars que ens serviran per fer el moviment dels zeros
    unsigned int resultat;

    // a)

    for (int i = 0; i < 8; i++)
    {
        movimentInvertit = ~moviment;                                   // Aquesta variable servirà per guardar en tot moment la cadena invertida, ja que després de moure-la
        moviment = (moviment << 4) | 0;                                 // 4 bits a l'esquerra i sumar-li 0, voldrem posar a 1 tot el que no siguin els 4 bits que han d'estar a 0
        resultat = moviment | movimentInvertit;
        printf("moviment[%d] = ", i + 1); bin(resultat);
        asm("nop");
    }
    
    moviment = ~moviment | moviment;                                    // Tornem a deixar la variable moviment com al principi de l'exercici

    // b) 

    for (int i = 8; i > 0; i--)                                         // Seguim els mateixos passos d'abans, però movent els bits cap a la dreta
    {
        movimentInvertit = ~moviment;
        moviment = (moviment >> 4) | 0;
        resultat = moviment | movimentInvertit;
        printf("moviment[%d] = ", i); bin(resultat);
        asm("nop");
    }
    
    return 0;
    
}