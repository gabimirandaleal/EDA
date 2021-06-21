#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int keys[] = {13,5,1,2,3,4};
//     4,7,9,11,15,17,19,22,24,27,31,12,20,25,28,30,32,33};
//int keys[] = {20, 10, 30};

typedef struct no{
    int chave;
    int bal; /* hdir - hesq */
    struct no *esq, *dir;
} No;

No *cria(int chave){
    No *n = (No *)malloc(sizeof(No));
    n->chave = chave;
    n->bal = 0;
    n->esq = NULL;
    n->dir = NULL;
    return n;
}

void caso1(No **pt, int *h){
    No *ptu = (*pt)->esq;
    if(ptu->bal<=0){
        (*pt)->esq = ptu->dir;
        ptu->dir = *pt;
        if(ptu->bal==0){
            (*pt)->bal=1;
            ptu->bal = -1;
            *h=0;
        }else{
            (*pt)->bal = 0;
            ptu->bal=0;
        }
        *pt = ptu;
    }else{
        printf("entrei caso else\n");
        No *ptv = ptu->dir;
        ptu->dir = ptv->esq;
        ptv->esq=ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = *pt;
        if(ptv->bal==-1){
            (*pt)->bal=1;
        }else{
            (*pt)->bal=0;
        }
        if(ptv->bal==1){
            ptu->bal=-1;
        }else{
            ptu->bal=0;
        }
        *pt=ptv;
        (*pt)->bal = 0;
    }
    
}

void caso2(No **pt, int *h){
    No *ptu = (*pt)->dir;
    if(ptu->bal>=0){
        (*pt)->dir = ptu->esq;
        ptu->esq = *pt;
        if(ptu->bal==0){
            (*pt)->bal=1;
            ptu->bal = -1;
            *h=0;
        }else{
            (*pt)->bal = 0;
            ptu->bal=0;
        }
        *pt = ptu;
    }else{
        printf("entrei caso else\n");
        No *ptv = ptu->esq;
        ptu->esq = ptv->dir;
        ptv->dir=ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = *pt;
        if(ptv->bal==1){
            (*pt)->bal=-1;
        }else{
            (*pt)->bal=0;
        }
        if(ptv->bal==-1){
            ptu->bal=1;
        }else{
            ptu->bal=0;
        }
        *pt=ptv;
        (*pt)->bal = 0;
    }
    
}


No * sucessor(No **pt, No **spai){
    No *s = (*pt)->dir;
    *spai = (*pt);
    if(s != NULL){
        while (s->esq!=NULL)
        {
            
            (*spai) = s;
            s = s->esq;
        }
        
    }
    return s;
}

void inserirAVL(int x, No **pt, int *h){
    
    if (*pt == NULL)
    {
        *pt = cria(x);
        *h = 1;
    }
    else
    {
        if (x == (*pt)->chave)
        {
            printf("Elemento ja existe\n");
            return;
        }
        else if (x < (*pt)->chave)
        {
            inserirAVL(x, &(*pt)->esq, h);
            if (*h == 1)
            {
                switch ((*pt)->bal)
                {
                case 0:
                    (*pt)->bal = -1;
                    break;
                case 1:
                    (*pt)->bal = 0;
                    *h = 0;
                    break;
                case -1:
                    caso1(&(*pt), h);
                    *h=0;
                    break;
                default:
                    break;
                }
            }
        }
        else
        {
            inserirAVL(x, &(*pt)->dir, h);
            if (*h == 1)
            {
                switch ((*pt)->bal)
                {
                case 0:
                    (*pt)->bal = 1;
                    break;
                case 1:
                    caso2(&(*pt), h);
                    *h=0;
                    break;
                case -1:
                    (*pt)->bal = 0;
                    *h = 0;
                    break;
                default:
                    break;
                }
            }
        }
    }
}


void removerAVL(int x, No **pt, int *h){
    No *aux;
    if((*pt)==NULL){
        printf("Elemento não encontrado\n");
    }else if(x < (*pt)->chave){      
        removerAVL(x, &(*pt)->esq, h);
        if(*h==1){
            
            switch ((*pt)->bal)
            {
                case -1 :
                    printf("entrei caso -1\n");
                    (*pt)->bal = 0;
                    break;
                case 0 :
                    printf("entrei caso 0\n");
                    (*pt)->bal = 1;
                    *h = 0;
                    break;
                case 1 :
                    printf("entrei no caso 2\n");
                    caso2(&(*pt), h);
                    break;
            }
        }
    }else if(x > (*pt)->chave){                
                removerAVL(x, &(*pt)->dir, h);   
                if(*h==1){
                    
                    switch ((*pt)->bal)
                    {
                    case 1:
                        (*pt)->bal = 0;
                        break;
                    case 0:
                        (*pt)->bal = -1;
                        *h = 0;
                        break;
                    case -1:
                        printf("entrei caso 1\n");
                        caso1(&(*pt), h);
                        break;
                    }
                }
    }else{
        aux = (*pt);
        if(aux->dir == NULL){
            (*pt)=aux->esq;
            *h = 1;
        }else if(aux->esq == NULL){
            (*pt)=aux->dir;
            *h = 1;
        }else{
            No *pai_s;
            aux = sucessor(&aux, &pai_s);
            (*pt)->chave = aux->chave;
            removerAVL(aux->chave, &(*pt)->dir, h);
            if(aux->dir == NULL && aux->esq==NULL){
                if(*h==1){
                switch ((*pt)->bal){
                    case 1 :
                        (*pt)->bal = 0;
                        break;
                    case 0 :
                        (*pt)->bal = -1;
                        *h = 0;
                        break;
                    case -1 :
                        printf("entrei caso 1 - 2\n");
                        caso1(&(*pt), h);
                        break;
                }
            
                }
            }
            else{
            if(*h==1){
                switch ((*pt)->bal){
                    case 1 :
                        (*pt)->bal = 0;
                        break;
                    case 0 :
                        (*pt)->bal = -1;
                        *h = 0;
                        break;
                    case -1 :
                        printf("entrei caso 2 - 2\n");
                        caso2(&(*pt), h);
                        break;
                }
            
            }
            }
            free(aux);
        }  
    }  
}

void preOrdem(No *pt){
    if (pt != NULL)
    {
        printf("%d(%d)", pt->chave, pt->bal);
        preOrdem(pt->esq);
        preOrdem(pt->dir);
    }
}
void inOrdem(No *pt){
    if (pt != NULL)
    {
        inOrdem(pt->esq);
        printf("%d (%d) ", pt->chave, pt->bal);
        inOrdem(pt->dir);
    }
}
void posOrdem(No *pt){
    if (pt != NULL)
    {
        posOrdem(pt->esq);      
        posOrdem(pt->dir);
        printf("%d(%d)", pt->chave, pt->bal);
    }
}

int main(){
    No *pt = NULL;
    int h=0;
    
    for (int i = 0; i < 6; i++)
    {
        inserirAVL(keys[i], &pt, &h);
        preOrdem(pt);
        printf("\n");
    }
    

    printf("\n//////////////////REMOVER/////////////////////\n\n");

    // for (int i = 0; i < 33; i++)
    // {
    //     //printf("%d\n", keys[i]);
        removerAVL(2, &pt, &h);
        removerAVL(1, &pt, &h);
        preOrdem(pt);
        printf("\n");
    // }

}