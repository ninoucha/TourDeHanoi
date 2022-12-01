// Programme C pour resoudre le probleme de la Tour de Hanoi (iteratif et recursif)
#include <stdio.h> 
#include <math.h> 
#include <stdlib.h> 
 
/////////////////////PILE////////////////////////////////////////////

// Une structure pour representer une pile 
struct Stack 
{ 
unsigned capacite; 
int top; 
int *array; 
}; 
 
// Fonction qui cree une pile d'une capacite donnée en entrée
struct Stack* creerPile(unsigned capacite) 
{ 
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack)); 
    stack -> capacite = capacite; 
    stack -> top = -1; 
    stack -> array = (int*) malloc(stack -> capacite * sizeof(int)); 
    return stack; 
} 
 
// Pile est pleine quand top est egal au dernier index 
int isFull(struct Stack* stack) 
{ 
return (stack->top == stack->capacite - 1); 
} 
 
// Pile est vide quand le top est egal ï¿½ -1 
int isEmpty(struct Stack* stack) 
{ 
return (stack->top == -1); 
} 
 
// Fonction qui ajouter un item a la pile. 
// incremente top de 1 
void empiler(struct Stack *stack, int item) 
{ 
    if (isFull(stack)) 
        return; 
    stack -> array[++stack -> top] = item; 
} 
 
// Fonction qui enlever un item de la pile
// decremente top de 1 
int depiler(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return -1; 
    return stack -> array[stack -> top--]; 
} 
 
 
 /////////////////////ITERATIVE////////////////////////////////////////////
 
//Fonction qui affiche les deplacements des disques
void deplacerDisque(char duPole, char auPole, int disk) 
{ 
    printf("Deplacer le disque %d de '%c' a '%c'\n", disk, duPole, auPole); 
}
 
// Fonction qui effectue le deplacement legale des disques
// entre deux poles 
void deplacerDisquesEntreDeuxPoles(struct Stack *src, struct Stack *dest, char s, char d) 
{ 
    int pole1TopDisk = depiler(src); 
    int pole2TopDisk = depiler(dest); 
 
    // quand le premier pole est vide
    if (pole1TopDisk == -1) 
    { 
        empiler(src, pole2TopDisk); 
        deplacerDisque(d, s, pole2TopDisk); 
    } 
 
    // quqnd le deuxieme pole est vide 
    else if (pole2TopDisk == -1) 
    { 
        empiler(dest, pole1TopDisk); 
        deplacerDisque(s, d, pole1TopDisk); 
    } 
 
    // quand disque en top du pole1 > disque en top du pole2 
    else if (pole1TopDisk > pole2TopDisk) 
    { 
        empiler(src, pole1TopDisk); 
        empiler(src, pole2TopDisk); 
        deplacerDisque(d, s, pole2TopDisk); 
    } 
 
    // quand disque en top du pole1 < disque en top du pole2 
    else
    { 
        empiler(dest, pole2TopDisk); 
        empiler(dest, pole1TopDisk); 
        deplacerDisque(s, d, pole1TopDisk); 
    } 
} 
 
//Fonction iterative qui implemente le probleme de la tour de Hanoi 
void tdhIterative(int nb_disques, struct Stack *src, struct Stack *aux, struct Stack *dest) 
{ 
    int i, total_num_of_moves; 
    char s = 'A', d = 'B', a = 'C'; 
 
    //If number of disks is even, then interchange 
    //destination pole and auxiliary pole 
    if (nb_disques % 2 == 0) 
    { 
        char temp = d; 
        d = a; 
        a = temp; 
    } 
    total_num_of_moves = pow(2, nb_disques) - 1; 
 
    //le disque le plus large sera empiler en premier  
    for (i = nb_disques; i >= 1; i--) 
    {
    	empiler(src, i); 
	}
       
 
    for (i = 1; i <= total_num_of_moves; i++) 
    { 
        if (i % 3 == 1) 
        deplacerDisquesEntreDeuxPoles(src, dest, s, d); 
 
        else if (i % 3 == 2) 
        deplacerDisquesEntreDeuxPoles(src, aux, s, a); 
 
        else if (i % 3 == 0) 
        deplacerDisquesEntreDeuxPoles(aux, dest, a, d); 
    } 
} 


/////////////////////RECURSIVE////////////////////////////////////////////
/*
n : nombre de disques utilisé
D : emplacement de départ
A : emplacement d'arrivée
I : emplacement intermédiaire
*/

void tdhRecursive(int n, char D, char A, char I) {
    if (n == 1)
      printf("Deplacer le disque 1 de '%c' a '%c' \n" , D , A);
    else {
      // D a A
      tdhRecursive(n - 1, D, I, A);
      printf("Deplacer le disque %d de '%c' a '%c' \n", n , D ,A);
      //I a A
      tdhRecursive(n - 1, I, A, D);
    }
}
 

int main() 
{ 
    // Entree: nombre de disques
    unsigned nb_disques ; 
    printf("Donner le nombre de disque de la tour:\t");
    scanf("%ul", &nb_disques);
 
    struct Stack *src, *dest, *temp; 
 
    // Creer trois piles de taille: 'nb_disques' 
    // qui vont contenir les disques
    src = creerPile(nb_disques); 
    temp = creerPile(nb_disques); 
    dest = creerPile(nb_disques); 
    
    printf("\n\tVersion iterative\n");
    tdhIterative(nb_disques, src, temp, dest); 
    
    printf("\n\tVersion recursive\n");
    tdhRecursive(nb_disques, 'A', 'B', 'C');
    return 0; 
}  



