#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dep{
    float salaire, CNSS;
    float deplacement;
    char moy_pay[30]; //espece ou cheque
}depense_employe;

typedef struct Emp{
    char nom[30], prenom[30], cin[30];
    depense_employe depE;
}Emp;
typedef struct element{
    Emp infoE;
    struct element *suiv;
}element;
typedef struct element *ListEmp;
typedef struct Cheque{
    float montant;
    char nom_benef[30];
}Cheque;
typedef struct element0{
    Cheque ch;
    struct element0 *suiv;
}ele_ch;
//typedef struct ele_ch *Liste_ch;

//creer une liste d'employé
ListEmp initialisation(ListEmp l,int nbr_emp){
    ListEmp nv_emp;

    for (int i = 0; i < nbr_emp; i++)
    {
    nv_emp=malloc(sizeof(element)); 
    printf("\nDonner le nom et le prenom de l'employé :"); fflush(stdin);
    gets(nv_emp->infoE.nom); fflush(stdin);
    gets(nv_emp->infoE.prenom); fflush(stdin);
    printf("\nDonner sa CIN : "); 
    gets(nv_emp->infoE.cin);

    //partie depense (info)
    printf("\nDonner son salaire : ");
    scanf("%f",&nv_emp->infoE.depE.salaire);
    printf("\nPrecisez si c'est par cheque ou espece :"); fflush(stdin);
    gets(nv_emp->infoE.depE.moy_pay);
    printf("\nDonner le montant de deplacement  : ");
    scanf("%f",&nv_emp->infoE.depE.deplacement);
    printf("\nPrecisez si c'est par cheque ou espece :"); fflush(stdin);
    gets(nv_emp->infoE.depE.moy_pay);
    printf("\nDonner le montant de CNSS  : ");
    scanf("%f",&nv_emp->infoE.depE.CNSS);
    printf("\nPrecisez si c'est par cheque ou espece :"); fflush(stdin);
    gets(nv_emp->infoE.depE.moy_pay);

    nv_emp->suiv=l;
    l=nv_emp;
    }
    l->suiv=NULL;
    return nv_emp;
}

//la fonction va retourner le montant de depense
float depense_calcul(ListEmp l){
    float somme=0,x;
    x=l->infoE.depE.CNSS+l->infoE.depE.deplacement+l->infoE.depE.salaire;
    while (l->suiv!=NULL)
    {
        somme=somme+x;
        l=l->suiv;
    }

    return somme;
}


int main(){
    int nbr_emp;
    ListEmp e;
    float somme_dep;

    printf("Donner le nombre des employés :");
    scanf("%d",&nbr_emp);

    e=initialisation(e,nbr_emp);

    somme_dep=depense_calcul(e);
    printf("\nLa somme des depense de l'entreprise est ‰f",somme_dep);


}