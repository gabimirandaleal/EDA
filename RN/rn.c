#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct no *No;

typedef struct no{
	int valor;
	char cor;
	No dir, esq, pai;
}no;

struct rubronegra{
	no *raiz;
};

typedef struct rubronegra *RubroNegra;

No externo = NULL;


// int keys[] = {100,50,150,25,75,125,175,13,33,67,80,113,133,167,180, 5, 17, 30, 37, 66, 69, 76, 81, 105, 117, 130, 137, 166, 169, 176, 181};
// int keys[] = {160, 89, 200, 50, 300, 20, 400};
// int keys[] = {13,5,21,2,8,16,26,1,3,6,10,14,18,23,29,4,7,9,11,15,17,19,22,24,27,31,12,20,25,28,30,32,33};


int keys[] = {300, 62, 172, 743, 8, 83, 9, 26, 81, 59, 20, 18, 800};

RubroNegra criarRubroNegra() {
    if (externo == NULL) {
        externo = (No) malloc(sizeof(struct no));
        externo->cor = 'N';
        externo->dir = externo;
        externo->esq = externo;
        externo->pai = externo;
    }
    RubroNegra novaArvore = (RubroNegra) malloc(sizeof(struct rubronegra));
    novaArvore->raiz = externo;
    return novaArvore;
}

No criarNo(int valor) {
    No novo = (No) malloc(sizeof(struct no));
    novo->valor = valor;
    novo->cor = 'R';
    novo->dir = externo;
    novo->esq = externo;
    novo->pai = externo;
    return novo;
}

No sucessor(No x) {
    No y = x;
    while (y->esq != externo)
        y = y->esq;
    return y;
}

void RotacaoEsquerda(RubroNegra arvore, No x) {
    No y;
    y = x->dir;
    x->dir = y->esq;
    if (y->esq != externo){
        y->esq->pai = x;
    } 
    y->pai = x->pai;
    if (x->pai == externo) {
        arvore->raiz = y;
    }else if (x == x->pai->esq) {
        x->pai->esq = y;
    }else{
        x->pai->dir = y;
    }
    y->esq = x;
    x->pai = y;
}

void RotacaoDireita(RubroNegra arvore, No x) {
    No y;
    y = x->esq;
    x->esq = y->dir;
    if (y->dir != externo){ 
        y->dir->pai = x;
    }
    y->pai = x->pai;
    if (x->pai == externo){ 
        arvore->raiz = y;
    }else if (x == x->pai->dir){
        x->pai->dir = y;
    }
    else{
        x->pai->esq = y;
    }
    y->dir = x;
    x->pai = y;
}

void insertFixUP(RubroNegra arvore, No z) {
	No y;
    while (z->pai->cor == 'R') {
        if (z->pai == z->pai->pai->esq) {
        	y = z->pai->pai->dir;
	        if (y->cor == 'R') {
                z->pai->cor = 'N';
                y->cor = 'N';
                z->pai->pai->cor = 'R';
                z = z->pai->pai;
            } else {
            	if (z == z->pai->dir) {
                    z = z->pai;
                    RotacaoEsquerda(arvore, z);
                }
                z->pai->cor = 'N';
                z->pai->pai->cor = 'R';
                RotacaoDireita(arvore, z->pai->pai);
            }
        } else {
            y = z->pai->pai->esq;
            if (y->cor == 'R') {
                z->pai->cor = 'N';
                y->cor = 'N';
                z->pai->pai->cor = 'R';
                z = z->pai->pai;
            } else {
                if (z == z->pai->esq) {
                    z = z->pai;
                    RotacaoDireita(arvore, z);
                }
                z->pai->cor = 'N';
                z->pai->pai->cor = 'R';
            	RotacaoEsquerda(arvore, z->pai->pai);
            }	
        }
    }
    arvore->raiz->cor = 'N';
}



int inserirArvore(RubroNegra arvore, int valor) {
    No y, x, z;
    z = criarNo(valor);

    y = externo;
    x = arvore->raiz;
    
    while (x != externo) {
        y = x;
        if (z->valor == x->valor){
            return 1;
        } 
        if (z->valor < x->valor) {
            x = x->esq;
        }
        else{
             x = x->dir;
        }
    }
    
    z->pai = y;
    if (y == externo){ 
        arvore->raiz = z;
    }
    else if (z->valor < y->valor){ 
        y->esq = z;
    }
    else {
        y->dir = z;
    }
    
    z->esq = externo;
    z->dir = externo;
    z->cor = 'R';

    insertFixUP(arvore, z);
    return 0;
}

void transplantRN(RubroNegra arvore, No u, No v){
    if(u->pai == externo){
        arvore->raiz = v;
    }else if(u==u->pai->esq){ 
        u->pai->esq = v;
    }else{
        u->pai->dir = v;
    }
    v->pai = u->pai;
}

No buscarNo(No x, int valor) {
    if (x == externo || x->valor == valor){
        return x;
    } 
    if (valor < x->valor) {
        buscarNo(x->esq, valor);
    }
    else {
        buscarNo(x->dir, valor);
    }
}



void removerFixup(RubroNegra arvore, No x){
    No w;
    while(x!=arvore->raiz && x->cor == 'N'){
        if(x == x->pai->esq){
            w = x->pai->dir; 
            if (w->cor == 'R'){
                w->cor = 'N';
                x->pai->cor = 'R';
                RotacaoEsquerda(arvore, x->pai);
                w = x->pai->dir;
            }
            if(w->esq->cor == 'N' && w->dir->cor=='N'){
                w->cor = 'R';
                x= x->pai;
            }else{
                if(w->dir->cor == 'N'){
                    w->esq->cor =  'N';
                    w->cor = 'R';
                    RotacaoDireita(arvore, w);
                    w = x->pai->dir;
                }
                w->cor = x->pai->cor;
                x->pai->cor = 'N';
                w->dir->cor = 'N';
                RotacaoEsquerda(arvore, x->pai);
                x = arvore->raiz;
            }
        }else{
            w = x->pai->esq;
            if (w->cor == 'R') {
                w->cor = 'N';
                x->pai->cor = 'R';
                RotacaoDireita(arvore, x->pai);
                w = x->pai->esq;
            }
            if (w->dir->cor == 'N' && w->esq->cor == 'N') {
                w->cor = 'R';
                x = x->pai;
            } else {
                if (w->esq->cor == 'N') {
                    w->dir->cor = 'N';
                    w->cor = 'R';
                    RotacaoEsquerda(arvore, w);
                    w = x->pai->esq;
                }
                w->cor = x->pai->cor;
                x->pai->cor = 'N';
                w->esq->cor = 'N';
                RotacaoDireita(arvore, x->pai);
                x = arvore->raiz;
            }
        }    
    }
    x->cor = 'N';

}


void removerRN(RubroNegra arvore, No z){
    No y = z;
    No x;
    char corOriginalY = y->cor;
    if(z->esq == externo){
        x = z->dir;
        transplantRN(arvore, z, z->dir);
    }else if(z->dir == externo){
        x = z->esq;
        transplantRN(arvore, z, z->esq);
    }else{
        y = sucessor(z->dir);
        corOriginalY = y->cor;
        x= y->dir;
        if(y->pai ==z){
            x->pai = y;
        }else{
            transplantRN(arvore, y, y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        }
        transplantRN(arvore, z, y);
        y->esq = z->esq;
        y->esq->pai = y;
    }
    if(corOriginalY == 'N'){
        removerFixup(arvore, x);
    }

    arvore->raiz->cor = 'N';
}

int remover(RubroNegra arvore, int valor) {
    No z = buscarNo(arvore->raiz, valor);
    No aux = z;
    if (z == externo){
        return 1;
    } 
    else{
        removerRN(arvore, z);
    }        
    free(aux);
    return 0;
}

void imprimeArvore(No x) {
    if (x == externo) return;
    printf("%d(%c)(%d)", x->valor, x->cor, x->pai->valor);
    imprimeArvore(x->esq);
    imprimeArvore(x->dir);
}

void preOrdem(RubroNegra arvore) {
    imprimeArvore(arvore->raiz);
    printf("\n");
}


int main(int argc, char const *argv[]){
    RubroNegra T = criarRubroNegra();
    // inserirArvore(T, 48);    
    // preOrdem(T);  
    // inserirArvore(T, 41);
    // preOrdem(T);
    // inserirArvore(T, 92);    
    // preOrdem(T);
    // inserirArvore(T, 97);    
    // preOrdem(T);
    // inserirArvore(T, 80);    
    // preOrdem(T);
    // inserirArvore(T, 60);    
    // preOrdem(T);
    // inserirArvore(T, 30);    
    // preOrdem(T);
    // inserirArvore(T, 9);    
    // preOrdem(T);
    // inserirArvore(T, 72);    
    // preOrdem(T);
    // inserirArvore(T, 20);    
    // preOrdem(T);
    for (int i = 0; i < 13; i++)
    {
        inserirArvore(T, keys[i]);    
        preOrdem(T);  
    }
    printf("/////////////////////REMOVER /////////////////////\n");


    remover(T, 59);    
    preOrdem(T);  
    // remover(T, 62);    
    // preOrdem(T);  
    // remover(T, 8);    
    // preOrdem(T);  

}