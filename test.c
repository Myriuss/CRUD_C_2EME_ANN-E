#include <stdio.h>
#include <stdlib.h>

//structure produit achete //produit qui ne seront pas vendu
typedef struct produit_achete
{
    char label[20];
    float prix;
    char ref[20];
    int qtt;
}Produit_achete;

//liste produit achete
typedef struct liste_p_achete
{
    Produit_achete prd_a;
    struct liste_p_achete *next;
}Liste_p_achete;
//structure produit
typedef struct produit
{
    char label[20]; //libele du produit
    int fonction;//1 pour achat et 2 pour vente
    char ref[20];
    float prix; // prix de ventre
    int qtt_stock;
    float prix_achat;
    int qtt_achete;
}Produit;
//liste produit
typedef struct Liste_produit
{
    Produit product;
    struct Liste_produit *next;
}Liste_produit;
//service d'achat
typedef struct service_achete
{
   char label[20];
   char reference[20];
   float prix;
}Service_achete;

//liste service achete
typedef struct liste_s_achete
{
    Service_achete S;
    struct liste_s_achete *next;
}Liste_s_achete;
//structure service
typedef struct service
{
    char *label;
    char *reference;
    float prix;
}Service;
//liste service
typedef struct liste_service
{
    Service S;
    struct liste_service *next;
}Liste_service;
// structure client 
typedef struct client
{
    char nom[20]; 
    char prenom[20];
    char ref[20];
    char adresse[20];
    int phone_num;
    float dette; //concerne les dettes du client
}Client;
//liste de client pour avoir une tracabilite sur les diff clients
typedef struct liste_C
{
    Client customer;
    struct liste_C *next;
}Liste_C;

//structure date
typedef struct date
{
    int jour;
    int mois;
    int annee;
}Date;
//ligne de commande
typedef struct ligne
{
    Liste_produit lp;
    int qtcom; // quantite commandé
}Ligne;

//commande est une liste
typedef struct cmd
{
    Ligne L;
    struct cmd *next;
}cmd;

//structure CEO pour les informations sur l'utilisateur de l'application aka l'entreprise
typedef struct ceo
{
    char nom_e[20];
    int phone_num;
    char mail[20];
    char HQ[20]; //pour l'adresse du siege social de l'entreprise
}CEO;

//structure facture
typedef struct facture
{
    cmd commande;
    int numero;//le numero de la facture
    Date d;
    char mode_paiment[10]; //cheque virement ou espece , add fct pour si <6000
    float TTC; // le prix tout tax compris
    float HT; //le prix hors tax
    float TVA; //20%
}Facture;

//structure employe
typedef struct employe
{
    char nom_e[20];
    char prenom_e[20];
    int num_e;
    float CNSS;//le montant depense sur la CNSS de l'employe
    char mode_pc[10]; // le mode de paiement de la CNSS
    float deplacement;//le montant depense sur le deplacement de l'employe
    char mode_pd[10];//le mode de paiement des deplacements
    float salaire;//le montant de paiement de salaire
    char mode_ps[10];//le mode de paiement des salaire
}Employe;

//liste employe
typedef struct liste_employe
{
    Employe worker;
    struct liste_employe *next;

}Liste_employe;
//cheque sortant
typedef struct cheque_s
{
    char *motif, *nom_benefic;
    float montant;
}Cheque_s;
//structure cheque sortant
typedef struct element
{
    Cheque_s ch;
    struct element *suiv;
}Element;
//Moyen de payement
typedef struct moy_pay{
    float caisse;
    Cheque_s ch;
}moy_pay;
//-----------------------------------------------

//partie ceo 
CEO saisie_premiere_fois ()
{
    CEO chef; 
    FILE *f=fopen("ceo.txt","w");

    printf("\t\t Veuiller saisir le nom de votre entreprise:\n");
    scanf("%s",chef.nom_e);
    fprintf(f,"%s\n",chef.nom_e);

    printf("\t\t Veuiller saisir le numero de telephone de votre entreprise:\n");
    scanf("%d",&chef.phone_num);
    fprintf(f,"%d\n",chef.phone_num);

    printf("\t\t Veuiller saisir l'adresse mail de l'entreprise:\n");
    scanf("%s",chef.mail);
    fprintf(f,"%s\n",chef.mail);

    printf("\t\t Veuiller saisir l'adresse de votre siege social:\n");
    scanf("%s",chef.HQ);
    fprintf(f,"%s\n",chef.HQ);
    fclose(f);

    return chef;
}

//function 0.1 //modification des infos de l'entreprise
CEO modification(CEO chef)
{
    FILE *f=fopen("ceo.txt","w");
    int choix4;
    printf("\t\t Que vouler vous modifier:\n");
    printf("\t\t 1. Le nom de l'entreprise:\n");
    printf("\t\t 2. Le numero de telephone:\n");
    printf("\t\t 3. L'email\n");
    printf("\t\t 4. L'adresse du siege social:\n");
    do
    {
        scanf("%d",&choix4);
    }while(choix4==1 || choix4==2 || choix4==3||choix4==4);
    
        switch(choix4)
        {
            case 1:
            {   //modification du nom de l'entreprise
                printf("L'ancient nom de votre entreprise est:%s",chef.nom_e);
                printf("Veuiller saisir le nouveau nom de votre entreprise:\n");
                scanf("%s",chef.nom_e);
                fprintf(f,"%s\n",chef.nom_e);
            }
            case 2:
            {
                //modification du num de telephone
                printf("L'ancient numero de telephone est:%d",chef.phone_num);
                printf("Veuiller saisir le nouveau numero de l'entreprise:\n");
                scanf("%d",&chef.phone_num);
                fprintf(f,"%d\n",chef.phone_num);
                             
            }
            case 3:
            {
                //modification de l'email
                printf("L'ancient email est:%s",chef.mail);
                printf("Veuiller saisir la nouvelle adresse e-mail:\n");
                scanf("%s",chef.mail);
                fprintf(f,"%s\n",chef.mail);
            }
            case 4:
            {
                //modification de l'adresse
                printf("L'ancient siege social est:%s",chef.HQ);
                printf("Veuiller saisir la nouvelle adresse du siege social:\n");
                scanf("%s",chef.HQ);
                fprintf(f,"%s\n",chef.HQ);
            }
                    
        }
        fclose(f);
    return chef;
}//fin fonction CEO modification

//function ajouter employe, returns liste d'employe
Liste_employe* ajout(Liste_employe *Emp)
{
    int taille,i;
    FILE *f=fopen("employe.txt","w");
    printf("Combien d'employer vouler vous ajouter?\n");
    scanf("%d",&taille);
    for(i=0;i<taille;i++)
    {
    Liste_employe *ne=malloc(sizeof(Liste_employe));
    printf("Veuiller saisir le nom de votre employe %d:\n",i+1);
    scanf("%s",ne->worker.nom_e);
    fprintf(f,"%s\n",ne->worker.nom_e);
    printf("Veuiller saisir le prenom de votre l'employe %s:\n",ne->worker.nom_e);
    scanf("%s",ne->worker.prenom_e);
    fprintf(f,"%s\n",ne->worker.prenom_e);
    printf("Veuiller saisir le numero de votre employe %s %s:\n",ne->worker.nom_e,ne->worker.prenom_e);
    scanf("%d",&ne->worker.num_e);
    fprintf(f,"%d\n",ne->worker.num_e);
    printf("Veuiller saisir le montant depense sur la CNSS de l'employe %s %s:\n",ne->worker.nom_e,ne->worker.prenom_e);
    scanf("%f",&ne->worker.CNSS);
    fprintf(f,"%f\n",ne->worker.CNSS);
    printf("Veuiller saisir le montant de deplacement de l'employe %s %s:\n",ne->worker.nom_e,ne->worker.prenom_e);
    scanf("%f",&ne->worker.deplacement);
    fprintf(f,"%f\n",ne->worker.deplacement);
    printf("Veuiller saisir le montant du salaire de l'employe %s %s:\n",ne->worker.nom_e,ne->worker.prenom_e);
    scanf("%f",&ne->worker.salaire);
    fprintf(f,"%f\n",ne->worker.salaire);
        if(Emp->next!=NULL)
        {
            Liste_employe *tmp=Emp;
            while(tmp!=NULL)
            {
                tmp=tmp->next;
            }
            tmp->next=ne;
            ne->next=NULL;
        }
        
        else
        {
        Emp=ne;
        ne->next=NULL;
        }
        
        
    }//boucle for
    fclose(f);
    return Emp;
}//fin ajout employee
Liste_employe* supprimer_emp(Liste_employe *Emp)
{
    FILE *f1=fopen("employe.txt","r");
    FILE *f2=fopen("employe_updated.txt","w");
    int num;
    Liste_employe *tmp=Emp;
    Liste_employe *aide;
    int taille,i;
    if(f1==NULL){
        printf("erreur.\n");
    }
    else{
        if(f2==NULL){
            printf("erreur.\n");
        }
        else{  
    printf("Combien d'employe voulez vous supprimer :\n");
    scanf("%d",&taille);
    for(i=0;i<taille;i++)
    {
        while(!feof(f1)){  
        printf("Veuiller saisir le numero de l'employe %d que vous voulez supprimer:\n",i+1);
        scanf("%d",&num);
        while(tmp!=NULL)
        {
            fscanf(f1,"%s\n%s\n%f\n%f\n%f",Emp->worker.nom_e,Emp->worker.prenom_e,&Emp->worker.CNSS,&Emp->worker.deplacement,&Emp->worker.salaire);
            if(tmp->next->worker.num_e!=num)
            {
            fprintf(f2,"%s\n%s\n%f\n%f\n%f",Emp->worker.nom_e,Emp->worker.prenom_e,Emp->worker.CNSS,Emp->worker.deplacement,Emp->worker.salaire);
            }
            else if(tmp->next->worker.num_e==num){
            aide=tmp->next;
            tmp->next=aide->next;
            free(aide);
            }
            else
            tmp=tmp->next;
        }
    }
        }//end while
        }//end else
    }
    fclose(f1);
    fclose(f2);
    return Emp;
}//fin supprimer employe

//function modifier info employe
Liste_employe* modifier_info(Liste_employe *Emp)
{
    FILE *f=fopen("employe.txt","r+");
    int num;
    int choix4;
    Liste_employe *tmp=Emp;
    if(f==NULL){
        printf("erreur");
    }
else{
    printf("Veuiller saisir le numero de l'employe que vous voulez modifier:\n");
    scanf("%d",&num);
    while(tmp!=NULL)
    {
        while(!feof(f)){
        fscanf(f,"%d\n",&tmp->worker.num_e);
        if(tmp->worker.num_e==num)
        {
            printf("Quel info de l'employe %s %s voulez vous modifier:\n",tmp->worker.nom_e,tmp->worker.prenom_e);
            printf("Veuiller choisir le numero correspondant a votre choix...\n");
            printf("1.Le nom de l'employe:\n");
            printf("2.Le prenom de l'employe:\n");
            printf("3.Le numero de l'employe:\n");
            printf("4.Le montant depense sur la CNSS de cet employe:\n");
            printf("5.Le montant depense sur les deplacements de cet employe:\n");
            printf("6.Le montant du salaire:\n");
            do
            {
                scanf("%d",&choix4);
            }while(1 >choix4 && choix4>6);

            switch (choix4)
            {
            case 1:
                //mod nom e 
                printf("Veuiller saisir le nouveau nom de l'employe:\n");
                scanf("%s",tmp->worker.nom_e);
                fprintf(f,"%s\n",tmp->worker.nom_e);
                break;
            
            case 2:
            // mpd prenom e
            printf("Veuiller saisir le nouveau prenom de l'employe:\n");
            scanf("%s",tmp->worker.prenom_e);
            fprintf(f,"%s\n",tmp->worker.prenom_e);
                break;
            case 3:
            //mod num e 
            printf("Veuieller saisir le nouveau numero de l'employe:\n");
            scanf("%d",&tmp->worker.num_e);
            fprintf(f,"%d\n",tmp->worker.num_e);
            break;
            case 4:
            //mod montant CNSS
            printf("Veuiller saisir le nouveau montant de la CNSS:\n");
            scanf("%f",&tmp->worker.CNSS);
            fprintf(f,"%f\n",tmp->worker.CNSS);
            break;
            case 5:
            //mod montant depense
            printf("Veuiller saisir le nouveau montant de deplacement:\n");
            scanf("%f",&tmp->worker.deplacement);
            fprintf(f,"%f\n",tmp->worker.deplacement);
            break;
            case 6:
            //mod salaire
            printf("Veuiller saisir le nouveau montant du salaire:\n ");
            scanf("%f",&tmp->worker.salaire);
            fprintf(f,"%f\n",tmp->worker.salaire);
            break;
            }//fin switch case
        }
        else
        {
            tmp=tmp->next;
        }
    }
    }
}//fin else
    fclose(f);
    return Emp;
}//fin fonction modifier employe

//ajouter client
Liste_C* ajout_c(Liste_C *cl){
    int taille;
    FILE *f=fopen("client.txt","w");
    printf("Combien de client voulez vous ajouter ?\n");
    scanf("%d",&taille);
    for(int i=0; i<taille; i++ ){
        Liste_C *ne=malloc(sizeof(Liste_C));
        printf("Veuiller saisir le nom de votre client %d:\n",i+1);
        scanf("%s",ne->customer.nom);
        fprintf(f,"%s\n",ne->customer.nom);
        printf("Veuiller saisir le prenom de votre client %s:\n",ne->customer.nom);
        scanf("%s",ne->customer.prenom);
        fprintf(f,"%s\n",ne->customer.prenom);
        printf("Veuiller saisir le numero de votre client %s %s:\n",ne->customer.nom,ne->customer.prenom);
        scanf("%d",&ne->customer.phone_num);  
        fprintf(f,"%d\n",ne->customer.phone_num);
        printf("Veuiller saisir l'adresse de votre client %s %s:\n",ne->customer.nom,ne->customer.prenom);
        scanf("%s",ne->customer.adresse);
        fprintf(f,"%s\n",ne->customer.adresse);
        printf("Veuiller saisir la reference de votre client %s %s:\n",ne->customer.nom,ne->customer.prenom);
        scanf("%s",ne->customer.ref);
        fprintf(f,"%s\n",ne->customer.ref);
        printf("Veuillez donner la dette du client %s %s", ne->customer.nom, ne->customer.prenom);
        scanf("%f",&ne->customer.dette);
        fprintf(f,"%f\n",ne->customer.dette);
    if (cl!=NULL)
    {
        Liste_C *tmp=cl;
        while (tmp->next!=NULL)
        {
            tmp=tmp->next;
        }
        tmp->next=ne;
        ne->next=NULL;
        
    }
    else
    {
        cl=ne;
        ne->next=NULL;
    }
    }
    fclose(f);
    return cl;
}//fin ajout client

Liste_C* supprimer_c(Liste_C *cl){
    char *ref;
    Liste_C *tmp=cl;
    Liste_C *aide;
    int taille, i;
    FILE *f1=fopen("client.txt","r");
    FILE *f2=fopen("client_updated.txt","w");
    printf("Combien de client voulez vous supprimer ?\n");
    scanf("%d",&taille);
    for ( i = 0; i < taille; i++)
    {
        printf("Veuiller saisir la reference du client %d:\n", i+1);
        scanf("%s",ref);
        while (tmp!=NULL)
        {
            fscanf(f1,"%s\n%s\n%s\n%d\n%s\n%f\n",tmp->customer.nom,tmp->customer.prenom,tmp->customer.adresse,&tmp->customer.phone_num,tmp->customer.adresse,&tmp->customer.dette);
            if (tmp->next->customer.ref!=ref)
            {
                fprintf(f2,"%s\n%s\n%s\n%d\n%s\n%f\n",tmp->customer.nom,tmp->customer.prenom,tmp->customer.adresse,tmp->customer.phone_num,tmp->customer.adresse,tmp->customer.dette);
            }
            else if(tmp->next->customer.ref==ref){
                //supprimer de la liste
                aide=tmp->next;
                tmp->next=aide->next;
                free(aide);
            }
            else
                tmp=tmp->next;    
        }   
    }
    fclose(f1);
    fclose(f2);
    return cl;
}//fin supprimer client



//MAIN 
int main(){
    CEO chef;

    chef=saisie_premiere_fois();
    return 0;
}


