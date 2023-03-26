#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int choix_autrePrd;

//structure date
typedef struct date
{
    int jour;
    int mois;
    int annee;
}Date;
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
//structure produit achete //produit qui ne seront pas vendu
typedef struct produit_achete
{
    char label[20];
    float prix;
    char ref[20];
    int qtt;
    Date d;
    moy_pay m;
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
   moy_pay m;
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
float Bank;
float Caisse;
//function 0.1  //les infos de l'entreprise pour la premiere fois
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
        printf("Desirez vous modifier autre choses?\n");
        printf("Saisir 1, pour modifier, saisir 0 si non.\n");
        scanf("%d",&choix_autrePrd);
        fclose(f);
    return chef;
}//fin fonction CEO modification

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

//function supprimer un employe
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
            case 1:{
                //mod nom e 
                printf("Veuiller saisir le nouveau nom de l'employe:\n");
                scanf("%s",tmp->worker.nom_e);
                fprintf(f,"%s\n",tmp->worker.nom_e);
                break;
            }
            case 2:{
            // mpd prenom e
            printf("Veuiller saisir le nouveau prenom de l'employe:\n");
            scanf("%s",tmp->worker.prenom_e);
            fprintf(f,"%s\n",tmp->worker.prenom_e);
                break;
            }
            case 3:{
            //mod num e 
            printf("Veuieller saisir le nouveau numero de l'employe:\n");
            scanf("%d",&tmp->worker.num_e);
            fprintf(f,"%d\n",tmp->worker.num_e);
            break;}
            case 4:{
            //mod montant CNSS
            printf("Veuiller saisir le nouveau montant de la CNSS:\n");
            scanf("%f",&tmp->worker.CNSS);
            fprintf(f,"%f\n",tmp->worker.CNSS);
            break;}
            case 5:{
            //mod montant depense
            printf("Veuiller saisir le nouveau montant de deplacement:\n");
            scanf("%f",&tmp->worker.deplacement);
            fprintf(f,"%f\n",tmp->worker.deplacement);
            break;}
            case 6:{
            //mod salaire
            printf("Veuiller saisir le nouveau montant du salaire:\n ");
            scanf("%f",&tmp->worker.salaire);
            fprintf(f,"%f\n",tmp->worker.salaire);
            break;}
            }//fin switch case
        }
        else
        {
            tmp=tmp->next;
        }
    }
    }
}//fin else
if(tmp==NULL)
    {
        printf("L'employe dont vous avez saisie le numero n'existe pas.\n");
    }
    printf("Vouler vous modifier un autre employee?\n");
    printf("Saisir 1 si oui, 0 si non.\n");
    scanf("%d",&choix_autrePrd);
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

Liste_C* modifier_c(Liste_C *cl){
    char* num ;
    int choix6;
    Liste_C *tmp=cl;
    printf("Veuiller saisir la reference du client que vous voulez modifier:\n");
    scanf("%s",num);
    while (tmp!=NULL)
    {
        if (tmp->customer.ref==num)
        {
            printf("Quel info du clien %s %s voulez vous modifier:\n",tmp->customer.nom, tmp->customer.prenom);
            printf("Veuiller choisir le numero correspondant a votre choix...\n");
            printf("1.Le nom du client:\n");
            printf("2.Le prenom du client:\n");
            printf("3.La reference du client:\n");
            printf("4.La dette du client:\n");
            printf("5.Le numero de telephone du client:\n");
            printf("6.L'adresse' du client:\n");

            do{
            scanf("%d",&choix6);
        }while (1>choix6 && choix6 > 6);
        switch (choix6)
        {
        case 1:
            //mod nom client
            printf("Veuiller saisir le nouveau nom du client :\n");
            scanf("%s",tmp->customer.nom);
            break;
        case 2:
            //mod prenom
            printf("Veuiller saisir le nouveau prenom du client :\n");
            scanf("%s",tmp->customer.prenom);
            break;
        case 3: //mod ref
            printf("Veuiller saisir la nouvelle reference du client :\n");
            scanf("%s",tmp->customer.ref);
            break;
        case 4 : //mod dette
            printf("Veuiller saisir la nouvelle dette du client :\n");
            scanf("%f",&tmp->customer.dette);
            break;
        case 5: //mod num tel
            printf("Veuiller saisir le nouveau numero de telephone du client :\n");
            scanf("%d",&tmp->customer.phone_num);
        case 6: //mod adresse
            printf("Veuiller saisir la nouvelle adresse du client :\n");
            scanf("%s",tmp->customer.adresse);
        }
        }
    else{
        tmp=tmp->next;
    }
    }
    return cl;
}
//ajouter un service 
Liste_service* ajouterServicePourLaVente(Liste_service* LSD)
{
    Liste_service* nv;
    int nbrS,i;
    printf("donner le nombre deservice que vous voulez saisir: ");
    scanf("%d",&nbrS);
    for(i=0;i<nbrS;i++)
    {
        nv=malloc(sizeof(Liste_service));
        printf("\nveuillez saisir le label de votre service:\n");
        scanf("%s",nv->S.label);
        printf("\nveuillez saisir sa référence:\n");
        scanf("%s",nv->S.reference);
        printf("\nveuillez saisir son prix:\n");
        scanf("%f",&nv->S.prix);
        if(LSD==NULL)
        {   nv->next=NULL;  }
        else
        {   nv->next=LSD;   }
        LSD=nv;
    }
 return LSD;
}
//suppression d'un service
Liste_service* supprimerSereviceDispo(Liste_service* LSD)
{
    int nbr,i;
    char ref[20];
    Liste_service *tmp=LSD,*aide;
    printf("Donner le nbr de service que vous voulez supprimer\n");
    scanf("%d",&nbr);
    for(i=0;i<nbr;i++)
    {
        printf("Donner la référence du service que vous voulez supprimer:\n");
        scanf("%s",ref);
        while(tmp!=NULL)
        {
            if(strcmp(tmp->S.reference,ref)==0 && tmp==LSD) //ça veut dire que le service est situé dans le début
            {
                    LSD=tmp->next;
                    free(tmp);
            }
            else if(strcmp(tmp->next->S.reference,ref)==0)
            {
                aide=tmp->next;
                tmp->next=aide->next;
                free(aide);
            }
        }
    }
    printf("voulez vous supprimer un autre service?\n 0.si non\n 1.si oui\n");
    scanf("%d",&choix_autrePrd);
    return LSD;
}
//modifier un service
Liste_service* modificationServiceDispo(Liste_service* LSD)
{
    int nbr,i,j;
    char ref[20];
    Liste_service *tmp=LSD;
    printf("combien de service voulez vous modifier?\n");
    scanf("%d",&nbr);
    for(i=0;i<nbr;i++)
    {
        printf("\ndonner la référence du service que vous voulez modifiez\n");
        scanf("%s",ref);
        printf("\nsaisir un nombre selon le choix de vote modification\n");
        printf("\n1.modification de libelle\n");
        printf("\n2.modification du prix\n");
        printf("\n3.modification du prix et de libelle\n");
        scanf("%d",&j);
        switch (j)
        {
            case 1:
            {
                while(tmp!=NULL)
                {
                    if(strcmp(tmp->S.reference,ref)==0)
                    {
                        printf("donner le nouveau libelle :");
                        scanf("%s",tmp->S.label);
                        break;
                    }
                }
            }
            case 2:
            {
                while(tmp!=NULL)
                {
                    if(strcmp(tmp->S.reference,ref)==0)
                    {
                        printf("donner le nouveau prix :");
                        scanf("%f",&tmp->S.prix);
                        break;
                    }
                }
            }
            case 3:
            {
                while(tmp!=NULL)
                {
                    if(strcmp(tmp->S.reference,ref)==0)
                    {
                        printf("donner le nouveau libelle :");
                        scanf("%s",tmp->S.label);
                        printf("donner le nouveau prix :");
                        scanf("%f",&tmp->S.prix);
                        break;
                    }
                }
            }
        }
    }
    printf("voulez vous supprimer un autre service?\n 0.si non\n 1.si oui\n");
    scanf("%d",&choix_autrePrd);
    return LSD;
}
//ajouter une commande
/**cmd* ajouter_cmd(cmd *c){
    int taille,nbr_p,taille2;
    Liste_produit tmp=c->L.lp;
    printf("Combien de commande voullez vous ajouter ?\n");
    scanf("%d",&taille);
    printf("Combien de produit ?\n");
    scanf("%d",&taille2);
    for (int i = 0; i < taille; i++)
    {
        cmd *ne=malloc(sizeof(cmd));
        for (int j = 0; j < taille2; j++)
        {
            printf("Donner la reference du produit : \n");
            scanf("%s",tmp.product.ref);
            printf("Donner le prix du produit :\n");
            scanf("%f",&tmp.product.prix);
            printf("");
            
        }
        
    }
    return c;
}**/
/**Saisisser la reference du client 
 si le client existe deja on entre automatiquement toutes c donne, 
 sinon on le saisie pour la premiere fois et le stocke dans notre base de donnee**/
Liste_C* saisi_ref_c(Liste_C *cl){
    FILE *f=fopen("client.txt","w");
    char *ref;
    int test=0;
    Liste_C *tmp=cl;
    Liste_C *ne=malloc(sizeof(Liste_C));
    printf("Donner la reference du client :\n");
    scanf("%s",ref);
    while(tmp!=NULL){
        if (tmp->customer.ref==ref)
        {
            fputs(cl->customer.nom,f);
            fputs(cl->customer.prenom,f);
            fputs(cl->customer.ref,f);
            fputs(cl->customer.adresse,f);
            fprintf(f,"%f",cl->customer.dette);
            fprintf(f,"%d",cl->customer.phone_num);
            test++;
        }
        else
        {
            tmp=tmp->next;
        }
        if(test==0){
            tmp=ajout_c(tmp);
        }
    }
    fclose(f);
    return cl;
}
//creation d'une facture
/**Facture create_fac(Facture f, cmd *c){
    float ht;
    f.commande=c; //ici faut corriger
    printf("Donner le numero de la facture :\n");
    scanf("%d",&f.numero);
    printf("Donner la datte de la facture ;\n");
    scanf("%d%d%d",&f.d.jour,&f.d.mois,&f.d.annee);
    printf("Donner le prix TTC :\n");
    scanf("%f",&f.TTC);
    ht=f.TTC-(f.TTC*0.2);
    printf("La TVA : 20‰.\t\tLe prix HT : %2.f\n",ht);
    printf("Quel est le mode de payement ?\n");
    scanf("%s",f.mode_paiment);


    return f;
}**/
//Modification de la facture
Facture modification_fact(Facture f){
    int num;
    int choix;
    FILE *file=fopen("facture.txt","r");
    printf("Donner le numero de la commande que vous souhaitez modifier :\n");
    scanf("%d",&num);
    //pas fini
    return f;
}

//saisie produit pour la premiere fois 
Liste_produit* ajout_Produit (Liste_produit* prd)
{
    float prix_achat_t;
    int choix;
     //ajouter fin
    Liste_produit* tmp=prd;
    Liste_produit *ne=malloc(sizeof(Liste_produit));
    printf("Veuiller saisir le libele de votre produit:\n");
    scanf("%s",ne->product.label);
    printf("Veuiller saisir la reference du produit:\n");
    scanf("%s",ne->product.ref);
    printf("Veuiller saisir la quantite achete:\n");
    scanf("%d",&ne->product.qtt_achete);
    ne->product.qtt_stock+=ne->product.qtt_achete;
    printf("Veuiller saisir le prix d'achat du produit:\n");
    scanf("%f",&ne->product.prix_achat);
    prix_achat_t=ne->product.prix_achat*ne->product.qtt_achete;
    printf("Comment souhaiter vous regler le paiement de ce produit?\n");
    printf("Saisir 1 pour banque 0 pour cash.");
    scanf("%d",&choix);
    if(choix==1)
    {
        Bank-=prix_achat_t;
    }
    else
    {
        Caisse-=prix_achat_t;
    }
    printf("Veuillez saisir le prix unitaire de vente du produit:\n");
    scanf("%f",&ne->product.prix);
   
    ne->next=NULL;
    if(prd==NULL)
    {
        prd=ne;
    }
    else
    {
        while(tmp->next!=NULL)
        {
            tmp=tmp->next;
        }
        tmp->next=ne;
    }
    printf("est ce que  voulez vous ajouter un autre produit:\n0.si non\t 1.si oui\n");
    scanf("%d",&choix_autrePrd);
    return prd;
}

//supprimer les produits
Liste_produit* supprimer_Produit(Liste_produit* prd)
{
    Liste_produit *tmp=prd,*aide;
    char *ref=malloc(sizeof(char*));
    printf("Donner la reference du produit que vous voulez supprimer:\n");
    scanf("%s",ref);
    while(tmp!=NULL)
    {
       if(strcmp(tmp->product.ref,ref)==0 && tmp==prd) //le produit est situé dans le début
            {
                    prd=tmp->next;
                    free(tmp);
            }
            else if(strcmp(tmp->next->product.ref,ref)==0)
            {
                aide=tmp->next;
                tmp->next=aide->next;
                free(aide);
            }
        tmp=tmp->next;
    }
    printf("est ce que  voulez vous supprimer un autre produit:\n0.si non\t 1.si oui\n");
    scanf("%d",&choix_autrePrd);
    return prd;
}//fin
//modifier un produit 
Liste_produit* modifier_prd(Liste_produit* prd)
{
    int test=0;
    char ref[20];
    Liste_produit* tmp=prd;
    int quantite;
    int j;
    printf("donner la reference du produit que vous voulez modifier:\n");
    scanf("%s",ref);
    //lire le fichier produit
    
    while(tmp!=NULL)
    {
        if(strcmp(tmp->product.ref,ref)==0)
        { 
            printf("\nsaisir un nombre selon le choix de vote modification\n");
            printf("0.remplir le stock avec le produit de reference, ref=%s:\n",ref);
            printf("1.modification du libele\n");
            printf("2.modification du prix de vente\n");
            printf("3.modification du prix de vente et du libele\n");
            printf("4.modifier la reference.\n");
            printf("5.modifier le prix d'achat du produit.\n");
            scanf("%d",&j);
            test++;
            switch (j)
            {   
                case 0:
                {
                    printf("donner la quantite que vous voulez ajouter au stock:\n");
                    scanf("%d",&tmp->product.qtt_achete);
                    tmp->product.qtt_stock+=tmp->product.qtt_achete;
                    break;
                }
                case 1:
                {
                    printf("donner le nouveau libele :\n");
                    scanf("%s",tmp->product.label);
                    break;
                }
                case 2:
                {
                    printf("donner le nouveau prix unitaire de vente:\n");
                    scanf("%f",&tmp->product.prix);
                    break;
                }
                case 3:
                {
                    printf("donner le nouveau libelle :\n");
                    scanf("%s",tmp->product.label);
                    printf("donner le nouveau prix unitaire de vente :\n");
                    scanf("%f",&tmp->product.prix);
                    break;
                }
                case 4:
                {//modifier la reference
                    printf("Donner la nouvelle reference.\n");
                    scanf("%s",tmp->product.ref);
                   break; 
                }
                case 5:
                {//modifier le prix d'achat du produit 
                printf("Donner le nouveau prix d'achat.\n");
                scanf("%f",&tmp->product.prix_achat);

                }
            }
        }
        else
        {
            tmp=tmp->next;
            
        }
    }
    if(test==0)
    {
        printf("Le produit saisie n'existe:\n");
        printf("Veuiller revenir a l'acceuil et l'ajouter");
    }
    printf("voulez vous modifier un autre produit?\n 0.si non\n 1.si oui\n");
    scanf("%d",&choix_autrePrd);
    return prd;
}

//saisie des depenses relatifs aux employes
Liste_employe* depenses_employee(Liste_employe *Emp)
{
    int num;
    Liste_employe *tmp=Emp;
    int choix;
    int test=0;
    float tst;
    printf("Veuiller saisir le numero de l'employe auquelle vous voulez ajouter des depense.\n");
    scanf("%d",&num);
    while(tmp!=NULL)
    {
        if(tmp->worker.num_e==num)
        {   test++;
            printf("Quel depense vouler vous saisir:\n");
            printf("\t1.CNSS\n");
            printf("\t2.deplacement\n");
            printf("\t3.salaire\n");
            do{
                scanf("%d",&choix);
            }while(1>choix ||choix>3);
            
            switch (choix)
            {
                case 1:
                {
                    printf("Vous avez choisie de saisir les depenses relatifs a la CNSS.\n");
                    printf("Veuiller saisir le montant depense sur la CNSS de cet employee.\n");
                    scanf("%f",&tmp->worker.CNSS);
                    Bank-=tmp->worker.CNSS;
                    break;
                }
            
                case 2:
                 {
                    printf("Vous avez choisie de saisir les depenses relatifs au deplacement.\n");
                    printf("Veuiller saisir le montant depense sur les deplacements de cet employee.\n");
                    scanf("%f",&tmp->worker.deplacement);
                    tst=tmp->worker.deplacement;
                    Bank=-tst;
                 break;
                }

                case 3:
                {
                    printf("Vous avez choisie de saisir les depenses relatifs au salaire.\n");
                    printf("Veuiller saisir le montant depense sur le salaire de cet employee.\n");
                    scanf("%f",&tmp->worker.salaire);
                    tst=tmp->worker.deplacement;
                    Bank=-tst;
                    break;
                }
               
            }
        }
        else
        {
            tmp=tmp->next;
        }
    }//fin while
    return Emp;
}

Liste_p_achete* saisie (Liste_p_achete* prd)
{
    Liste_p_achete* tmp=prd;
    float prix;
    int tst;
    Liste_p_achete *ne=malloc(sizeof(Liste_p_achete));
    printf("Veuiller saisir la reference du produit achete:\n");
    scanf("%s",ne->prd_a.ref);
    printf("Veuiller saisir le libele de votre produit:\n");
    scanf("%s",ne->prd_a.label);
    printf("Veuiller saisir le prix du produit achete:\n");
    scanf("%f",&prix);
    printf("Veuiller saisir la quantite achete de ce produit:\n");
    scanf("%d",&ne->prd_a.qtt);
    printf("Vous avez la possibilite de payer ce service par cheque, virement ou cash.\n");
    printf("Donner 1 pour casse, 2 pour virement, 3 pour cash .\n");
    scanf("%d",&tst);
        switch (tst)
        {
        case 1:
            scanf("%f",&ne->prd_a.m.caisse);
            Caisse=-ne->prd_a.m.caisse;
            break;
        
        case 2:
            scanf("%f",&ne->prd_a.m.ch.montant);
            Bank=-ne->prd_a.m.ch.montant;
            break;
        case 3:
            scanf("%f",&ne->prd_a.m.ch.montant);
            Bank=-ne->prd_a.m.ch.montant;
            break;
        }
    printf("Veuiller saisir la date dans laquel vous avez acheter ce produit.\n");
    scanf("%d %d %d",&ne->prd_a.d.jour,&ne->prd_a.d.mois,&ne->prd_a.d.annee);
    ne->next=NULL;
    if(prd==NULL)
    {
        prd=ne;
    }
    else
    {
        while(tmp->next!=NULL)
        {
            tmp=tmp->next;
        }
        tmp->next=ne;
    }
    printf("est ce que  voulez vous ajouter un autre produit:\n0.si non\t 1.si oui\n");
    scanf("%d",&choix_autrePrd);
    return prd;
}//fin saisir produit achete

Liste_s_achete* saisirServiceAchete(Liste_s_achete* LSA)
{
        Liste_s_achete *nv=malloc(sizeof(Liste_s_achete));
        float prixT;
        int tst;
        printf("\nveuillez saisir le label de votre service:\n");
        scanf("%s",nv->S.label);
        printf("\nveuillez saisir sa référence:\n");
        scanf("%s",nv->S.reference);
        printf("\nveuillez saisir son prix:\n");
        scanf("%f",&prixT);
        printf("Vous avez la possibilite de payer ce service par cheque, virement ou cash.\n");
        printf("Donner 1 pour casse, 2 pour virement, 3 pour cash .\n");
        scanf("%d",&tst);
        switch (tst)
        {
        case 1:
            scanf("%f",&nv->S.m.caisse);
            Caisse=-nv->S.m.caisse;
            break;
        
        case 2:
            scanf("%f",&nv->S.m.ch.montant);
            Bank=-nv->S.m.ch.montant;
            break;
        case 3:
            scanf("%f",&nv->S.m.ch.montant);
            Bank=-nv->S.m.ch.montant;
            break;
        }
        if(LSA==NULL)
        {   nv->next=NULL;  }
        else
        {   nv->next=LSA;   }
        LSA=nv;
    
    printf("voulez vous saisir un autre service achete?\n 0.si non\n 1.si oui\n");
    scanf("%d",&choix_autrePrd);
    return LSA;

}

//voir le solde de la caisse
void visualiser_caisse()
{
    printf("Le solde de la caisse est %f",Caisse);
}

//voir le solde du compte bancaire
void visualiser_banque()
{
    printf("Le solde de la banque est %f",Bank);
}

void accueille()
{
    system("cls");
    CEO chef;
    Liste_s_achete* LSA=NULL;
    Liste_p_achete* LPA=NULL;
    Liste_employe *Emp=NULL;
    int choix,choix2,choix3;
    Liste_service* LSD=malloc(sizeof(Liste_service));
    Liste_produit *prd=malloc(sizeof(Liste_produit));
    int choix_serviceD;//le choix d'ajout suppression modification du service
    printf("\t\tACCUEILLE:\n");
    printf("\t Saisir le nombre correspondant a votre choix...\n");
    printf("0. Infos de l'entreprise:\n");
    printf("1.Saisie des produits disponibles:\n");
    printf("2. Saisie des produits achete:\n");
    printf("3.Saisie de services disponibles:\n");
    printf("4.La saisie des services achete:\n");
    printf("5.La saisie d'une commande:\n");
    printf("6.Effectuer les depenses relatifs aux employes:\n");//payez les salaires CNSS deplacement des employes
    printf("7.Voir le solde de la caisse:\n");
    printf("8.Voir le solde de la banque:\n");
    printf("9.Visualiser la facture:\n");
    printf("10.Visualiser le bon de livraison:\n");
    do
    {
        scanf("%d",&choix);
    }while(0>choix && choix>10);
    switch (choix)
    {
        case 0:
        {//0.saisie des infos de l'entreprise
            printf("Choisissez un numéro selon votre choix de saisie:\n");
            printf("\t1. Les infos de l'entreprise:\n");
            printf("\t2. Les infos des employes:\n");
             do{
                    scanf("%d",&choix2);
                }while(1>choix2 && choix2>2);
                if(choix2==1)
                {//1.les infos de l'entreprise
                    printf("\t\t 1.La saisie pour la premiere fois:\n");
                    printf("\t\t 2.Modification des infos de l'entreprise :\n");
                    do{
                        scanf("%d",&choix3);
                    }while(1>choix3 && choix3>2);
                
                    if(choix3==1)
                    {   
                         chef=saisie_premiere_fois();
                    }
                    else if(choix3==2)
                    {   //modification infos entreprise
                        do{
                            chef=modification(chef);
                        }while(choix_autrePrd==0);
                    }
                }
                else if(choix2==2)
                {//les infos des employe
                    printf("Faite votre choix...\n");
                    printf("\t1. Ajouter un employe:\n");
                    printf("\t2. Supprimer un employe:\n");
                    printf("\t3. Modifier les infos d'un employe:\n");
                    do
                    {
                        scanf("%d",&choix3);
                    }while(1>choix3 && choix3>3);
                    if(choix3==1)
                    {
                        Emp=ajout(Emp);
                    }
                    else if(choix3==2)
                    {
                        Emp=supprimer_emp(Emp);
                    }
                    else
                    {//modifier les infos d'un emp
                        do{
                            Emp=modifier_info(Emp);
                        }while(choix_autrePrd==0);
                    }
                }//fin 2.infos employes
            break;    
        }    
        case 1:
        {   //1.produit
            printf("\n\n1.Saisie des produits pour la premiere fois:\n");
            printf("2.Supprimer des produits:\n");
            printf("3.Modifier des produits:\n");
            do
            {
                scanf("%d",&choix3);
            }while(1>choix3 && choix3>3);
            switch (choix3)
            {
                case 1:
                {
                    //saisie prd premiere fois
                    do {
                        prd= ajout_Produit(prd);
                    }while(choix_autrePrd==0);
                }
                case 2:
                {
                    //supprimer des prd
                    do {
                        prd= supprimer_Produit(prd);
                    } while(choix_autrePrd==0);
                }
                case 3://modifier des prd
                {
                    do{
                        prd= modifier_prd(prd);
                    }while(choix_autrePrd==0);
                }
            }//fin switch case produit
            break;
        }
        case 2://la saisie des produits achete
        {
            do{
                LPA=saisie(LPA);
            }while(choix_autrePrd==0);
            
            break;
        }
        case 3://services disponibles
        {
            printf("\n\n1.ajouter un service.\n");
            printf("2.supprimer un service.\n");
            printf("3.modifier un service.\n");
            do{
                scanf("%d",&choix_serviceD);
            }while(choix_serviceD < 1 && choix_serviceD > 3);
            switch (choix_serviceD)
            {
                case 1:
                {
                    do{
                        LSD=ajouterServicePourLaVente(LSD);
                    }while(choix_autrePrd==0);
                }                   
                case 2:
                {
                    do{ 
                        LSD=supprimerSereviceDispo(LSD);
                    }while(choix_autrePrd==0);
                }
                case 3:
                {
                    do{
                         LSD=modificationServiceDispo(LSD);
                    }while(choix_autrePrd==0);
                }
            }
            break;
        }
        case 4://la saisie des services achetés
        {
            do{
                LSA=saisirServiceAchete(LSA);
            }while(choix_autrePrd==0);
            break;
        }
        case 5:
        {
            break;
        }
        case 6:
        {
            do {
                Emp=depenses_employee(Emp);
            }while(choix_autrePrd==0);
            break;
        }
        case 7:
        //7.voir le solde de la caisse
        {
            visualiser_caisse();
            break;
        }
        case 8://le solde de la banque
        {
            visualiser_banque();
            break;
        }
        case 9://la facture
        {
            break;
        }
        case 10://le bon de livraison
        {
            break;
        }
    }
}
int main()
{
    CEO chef;
    Liste_employe *Emp=NULL;
    Liste_service* LSD=NULL;
    Liste_s_achete* LSA=NULL;
    Liste_p_achete* LPA=NULL;
    Liste_produit* prd=NULL;
    int accueil;
    do{
        accueille();
        printf("est ce que vous voulez revenir à l'accueil ?;\n");
        printf("saisir 1 si vous voulez revenir ou bien 0 si vous voulez quitter.");
        scanf("%d",&accueil);
    }while(accueil==0);

}