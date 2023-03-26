#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//variable globale pour repeter une foonction
int choix_autrePrd;
//structure date
typedef struct
{
    int jour,mois,annee;
}date;
//structure produit achete //produit qui ne seront pas vendu
typedef struct
{
    char label[20];
    float moy_pay[3];
    //1 virement
   //2 cash
   //3 cheque
    date d;
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
typedef struct
{
    char label[20]; //libele du produit
    char ref[20];
    float moy_pay_e[3]; // moyen de paiement entrant
    //1 virement
   //2 cash
   //3 cheque
    int qtt_stock ;
    float prix_a;
    int qtt_achete;
    float prix_v;
}Produit;

//liste produit
typedef struct liste_produit
{
    Produit product;
    struct liste_produit *next;
}Liste_produit;

//service d'achat
typedef struct
{
   char label[20];
   char reference[20];
   float moy_pay[3];
   //0 virement
   //1 cash
   //2 cheque
}Service_achete;

//liste service achete
typedef struct liste_s_achete
{
    Service_achete S;
    struct liste_s_achete *next;
}Liste_s_achete;

//structure service offert par l'entreprise
typedef struct
{
    char label[20];
    char reference[20];
    float prix;
    float moy_pay[3];
}Service;

//liste service
typedef struct liste_service
{
    Service S;
    struct liste_service *next;
}Liste_service;

// structure client
typedef struct
{
    char nom[20];
    char prenom[20];
    char ref[20];
    char adresse[20];
    int phone_num;
    float dette; //concerne les dettes du client
}Client;

//liste de client
typedef struct liste_C
{
    Client customer;
    struct liste_C *next;
}Liste_C;

//ligne de commande
typedef struct
{
    Produit p;
    int qtcom; // quantite commandÃ©
    float prix_t;
}Ligne;

//commande est une liste de ligne
typedef struct cm
{
    Ligne L;
    struct cm *next;
}cmd;

//structure CEO pour les informations sur l'utilisateur de l'application aka l'entreprise
typedef struct
{
    char nom_e[20];
    int phone_num;
    char mail[40];
    char HQ[20]; //pour l'adresse du siege social de l'entreprise
}CEO;

//structure facture
typedef struct
{
    int numero;//le numero de la facture
    date d;
    float TTC; // le prix tout tax compris
    float HT; //le prix hors tax
    float TVA;
    float moy_pay[3]; //est la somme des prix unitaires * la quantite de chaque prd
    cmd *com; //liste de lignes
    Liste_service *serv;
}Facture;

//structure employe
typedef struct
{
    char nom_e[20];
    char prenom_e[20];
    int num_e;
   float CNSS;
   float deplacement;
   float salaire;
}Employe;

//liste employe
typedef struct liste_employe
{
    Employe worker;
    struct liste_employe *next;

}Liste_employe;

//Variable Banque
float Bank=0;
//Variable Caisse
float Caisse=0;

//function 0.1  //les infos de l'entreprise pour la premiere fois
CEO saisie_premiere_fois ()
{
    CEO chef;
     printf("\t\t Veuiller saisir le nom de votre entreprise:\n");
    scanf("%s",chef.nom_e);
    printf("\t\t Veuiller saisir le numero de telephone de votre entreprise:\n");
    scanf("%d",&chef.phone_num);
    printf("\t\t Veuiller saisir l'adresse mail de l'entreprise:\n");
    scanf("%s",chef.mail);
    printf("\t\t Veuiller saisir l'adresse de votre siege social:\n");
    scanf("%s",chef.HQ);
    return chef;
}

CEO modification(CEO chef)
{
    int choix4;
    printf("\t\t Que vouler vous modifier:\n");
    printf("\t\t 1. Le nom de l'entreprise:\n");
    printf("\t\t 2. Le numero de telephone:\n");
    printf("\t\t 3. L'email\n");
    printf("\t\t 4. L'adresse du siege social:\n");
    do
    {
        scanf("%d",&choix4);
    }while(1>choix4 ||choix4>4);

        switch(choix4)
        {
            case 1:
            {   //modification du nom de l'entreprise
                printf("L'ancient nom de votre entreprise est:%s",chef.nom_e);
                printf("Veuiller saisir le nouveau nom de votre entreprise:\n");
                scanf("%s",chef.nom_e);
            }
            case 2:
            {
                //modification du num de telephone
                printf("L'ancient numero de telephone est:%d",chef.phone_num);
                printf("Veuiller saisir le nouveau numero de l'entreprise:\n");
                scanf("%d",&chef.phone_num);

            }
            case 3:
            {
                //modification de l'email
                printf("L'ancient email est:%s",chef.mail);
                printf("Veuiller saisir la nouvelle adresse e-mail:\n");
                scanf("%s",chef.mail);
            }
            case 4:
            {
                //modification de l'adresse
                printf("L'ancient siege social est:%s",chef.HQ);
                printf("Veuiller saisir la nouvelle adresse du siege social:\n");
                scanf("%s",chef.HQ);
            }

        }//fin switch case
        printf("Desirez vous modifier autre choses?\n");
        printf("Saisir 1, pour modifier, saisir 0 si non.\n");
        scanf("%d",&choix_autrePrd);
    return chef;
}//fin fonction CEO modification

//function ajouter employe, returns liste d'employe
Liste_employe* ajout(Liste_employe *Emp)
{
    int taille,i;
    Liste_employe *ne,*tmp;
     tmp=Emp;
    printf("Combien d'employer vouler vous ajouter?\n");
    scanf("%d",&taille);
    for(i=0;i<taille;i++)
    {
        ne=malloc(sizeof(Liste_employe));
        printf("Veuiller saisir le nom de votre employe %d:\n",i+1);
        scanf("%s",ne->worker.nom_e);
        printf("Veuiller saisir le prenom de votre l'employe %s:\n",ne->worker.nom_e);
        scanf("%s",ne->worker.prenom_e);
        printf("Veuiller saisir le numero de votre employe %s %s:\n",ne->worker.nom_e,ne->worker.prenom_e);
        scanf("%d",&ne->worker.num_e);
        printf("Veuiller saisir le montant depense sur la CNSS de l'employe %s %s:\n",ne->worker.nom_e,ne->worker.prenom_e);
        scanf("%f",&ne->worker.CNSS);
        printf("Veuiller saisir le montant de deplacement de l'employe %s %s:\n",ne->worker.nom_e,ne->worker.prenom_e);
        scanf("%f",&ne->worker.deplacement);
        printf("Veuiller saisir le montant du salaire de l'employe %s %s:\n",ne->worker.nom_e,ne->worker.prenom_e);
        scanf("%f",&ne->worker.salaire);
        ne->next=NULL;
        if(Emp!=NULL)
        {
            while(tmp->next!=NULL)
            {
                tmp=tmp->next;
            }
            tmp->next=ne;
        }
        else
        {
            Emp=ne;
        }
    }//boucle for
    return Emp;
}//fin ajout employee

//function supprimer un employe
Liste_employe* supprimer_emp(Liste_employe *Emp)
{
    int num;
    Liste_employe *tmp=Emp;
    Liste_employe *aide;
    int taille,i;
    printf("Combien d'employe voulez vous supprimer :\n");
    scanf("%d",&taille);
    for(i=0;i<taille;i++)
    {
        printf("Veuiller saisir le numero de l'employe %d que vous voulez supprimer:\n",i+1);
        scanf("%d",&num);

        while(tmp!=NULL)
        {
            if(tmp->next->worker.num_e==num && tmp==Emp)
            {
                Emp=tmp->next;
                free(tmp);
            }
                else if(tmp->next->worker.num_e==num)
                {
                    //supprimer
                    aide=tmp->next;
                    tmp->next=aide->next;
                    free(aide);
                }
            tmp=tmp->next;
        }
    }
    return Emp;
}//fin supprimer employe

//function modifier info employe
Liste_employe* modifier_info(Liste_employe *Emp)
{
    int num;
    int choix4;
    Liste_employe *tmp=Emp;
    printf("Veuiller saisir le numero de l'employe que vous voulez modifier:\n");
    scanf("%d",&num);
    while(tmp!=NULL)
    {
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
            }while(1 >choix4 || choix4>6);

            switch (choix4)
            {
            case 1:
            {
                //mod nom e
                printf("Veuiller saisir le nouveau nom de l'employe:\n");
                scanf("%s",tmp->worker.nom_e);
                break;
            }
            case 2:
            {    // mpd prenom e
                printf("Veuiller saisir le nouveau prenom de l'employe:\n");
                scanf("%s",tmp->worker.prenom_e);
                break;
            }
            case 3:
            {   //mod num e
                printf("Veuieller saisir le nouveau numero de l'employe:\n");
                scanf("%d",&tmp->worker.num_e);
                break;
            }
            case 4:
            {
                // montant CNSS
                printf("Veuiller saisir le nouveau montant de la CNSS:\n");
                 scanf("%f",&tmp->worker.CNSS);
                break;
            }

            case 5:
            {
                //mod montant depense
                printf("Veuiller saisir le nouveau montant de deplacement:\n");
                scanf("%f",&tmp->worker.deplacement);
                break;
            }

            case 6:
            {
                //mod salaire
                printf("Veuiller saisir le nouveau montant du salaire:\n ");
                scanf("%f",&tmp->worker.salaire);
                 break;
            }
            }//fin switch case


        }
        else
        {
            tmp=tmp->next;
        }
    }
    if(tmp==NULL)
    {
        printf("L'employe dont vous avez saisie le numero n'existe pas.\n");
    }
    printf("Vouler vous modifier un autre employee?\n");
    printf("Saisir 1 si oui, 0 si non.\n");
    scanf("%d",&choix_autrePrd);

    return Emp;
}//fin fonction modifier employe

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
    scanf("%f",&ne->product.prix_a);
    prix_achat_t=ne->product.prix_a*ne->product.qtt_achete;
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
    scanf("%f",&ne->product.prix_v);

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
    Liste_produit* tmp=prd;
    Liste_produit* aide;
    char ref[20];
    printf("Donner la reference du produit que vous voulez supprimer:\n");
    scanf("%s",ref);
    while(tmp!=NULL)
    {
       if(strcmp(tmp->product.ref,ref)==0 && tmp==prd) //le produit est situÃ© dans le dÃ©but
            {
                    prd==tmp->next;
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
                    scanf("%f",tmp->product.prix_v);
                    break;
                }
                case 3:
                {
                    printf("donner le nouveau libelle :\n");
                    scanf("%s",tmp->product.label);
                    printf("donner le nouveau prix unitaire de vente :\n");
                    scanf("%f",tmp->product.prix_v);
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
                scanf("%f",&tmp->product.prix_a);

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

//ajouter un service
Liste_service* ajouterServicePourLaVente(Liste_service* LSD)
{
        Liste_service* nv;
        float prix;
        nv=malloc(sizeof(Liste_service));
        printf("\tveuillez saisir le label de votre service:\n");
        scanf("%s",nv->S.label);
        printf("\tveuillez saisir sa rÃ©fÃ©rence:\n");
        scanf("%s",nv->S.reference);
        printf("\tveuillez saisir son prix:\n");
        scanf("%f",&prix);
        printf("Vous avez la possibilite de regler le montant par virement, cash ou par cheque.\n");
        //virement
        printf("Veuiller saisir le montant du prix que vous vouler regler par virement.\n");
        printf("Saisir 0 si vous vouler regler votre achat par autres moyen seulement.\n");
        scanf("%f",&nv->S.moy_pay[0]);
        Bank-=nv->S.moy_pay[0];
        //cash
        printf("Veuiller saisir le montant du prix que vous vouler regler par cash.\n");
        printf("Saisir 0 si vous ne vouler pas regler votre achat par cash.\n");
        scanf("%f",&nv->S.moy_pay[1]);
        Caisse-=nv->S.moy_pay[1];
        //cheque
        printf("Veuiller saisir le montant du prix que vous vouler regler par cheque.\n");
        printf("Saisir 0 si vous ne vouler pas regler votre achat par cheque.\n");
        scanf("%f",&nv->S.moy_pay[2]);
        Bank-=nv->S.moy_pay[2];

        if(LSD==NULL)
        {   nv->next=NULL;  }
        else
        {   nv->next=LSD;   }
        LSD=nv;

    printf("voulez vous saisir  un autre service?\n 0.si non\n 1.si oui\n");
    scanf("%d",&choix_autrePrd);
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
        printf("Donner la rÃ©fÃ©rence du service que vous voulez supprimer:\n");
        scanf("%s",ref);
        while(tmp!=NULL)
        {
            if(strcmp(tmp->S.reference,ref)==0 && tmp==LSD) //Ã§a veut dire que le service est situÃ© au le dÃ©but
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
    int j;
    char ref[20];
    Liste_service *tmp=LSD;

        printf("\ndonner la rÃ©fÃ©rence du service que vous voulez modifiez\n");
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
                        printf("Saisir le nouveau libelle :\n");
                        scanf("%s",tmp->S.label);
                        break;
                    }
                    else
                    {
                        tmp=tmp->next;
                    }
                }
            }
            case 2:
            {
                while(tmp!=NULL)
                {
                    if(strcmp(tmp->S.reference,ref)==0)
                    {
                        printf("Donner le nouveau prix :");
                        scanf("%f",&tmp->S.prix);
                        break;
                    }
                    else
                    {
                        tmp=tmp->next;
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
                    else
                    {
                        tmp=tmp->next;
                    }
                }
            }
        }

    printf("voulez vous apporter une modification a un autre service?\n 0.si non\n 1.si oui\n");
    scanf("%d",&choix_autrePrd);
    return LSD;
}

//pour le main on demande vouler vous saisir un prd si oui on apelle la fct encore une fois
//else on sort
Liste_p_achete* saisie (Liste_p_achete* prd)
{
    //ajouter fin
    Liste_p_achete* tmp=prd;
    float prix;
    Liste_p_achete *ne=malloc(sizeof(Liste_p_achete));
    printf("Veuiller saisir la reference du produit achete:\n");
    scanf("%s",ne->prd_a.ref);
    printf("Veuiller saisir le libele de votre produit:\n");
    scanf("%s",ne->prd_a.label);
    printf("Veuiller saisir le prix du produit achete:\n");
    scanf("%f",&prix);
    printf("Veuiller saisir la quantite achete de ce produit:\n");
    scanf("%d",&ne->prd_a.qtt);
    //virement
    printf("Veuiller saisir le montant du prix que vous vouler regler par virement.\n");
    printf("Saisir 0 si vous vouler regler votre achat par autres moyen seulement.\n");
    scanf("%f",&ne->prd_a.moy_pay[0]);
    Bank-=ne->prd_a.moy_pay[0];
    //cash
    printf("Veuiller saisir le montant du prix que vous vouler regler par cash.\n");
    printf("Saisir 0 si vous ne vouler pas regler votre achat par cash.\n");
    scanf("%f",&ne->prd_a.moy_pay[1]);
    Caisse-=ne->prd_a.moy_pay[1];
    //cheque
    printf("Veuiller saisir le montant du prix que vous vouler regler par cheque.\n");
    printf("Saisir 0 si vous ne vouler pas regler votre achat par cheque.\n");
    scanf("%f",&ne->prd_a.moy_pay[2]);
    Bank-=ne->prd_a.moy_pay[2];
    //ecrire sur fichier svvppppppp //cheque sortaaaaaaaant
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

//saisir service achete //Sia //to check
Liste_s_achete* saisirServiceAchete(Liste_s_achete* LSA)
{
        Liste_s_achete *nv;
        float prixT;

        nv=malloc(sizeof(Liste_s_achete));
        printf("\nveuillez saisir le label de votre service:\n");
        scanf("%s",nv->S.label);
        printf("\nveuillez saisir sa rÃ©fÃ©rence:\n");
        scanf("%s",nv->S.reference);
        printf("\nveuillez saisir son prix:\n");
        scanf("%f",&prixT);
        printf("Vous avez la possibilite de payer ce service par cheque, virement ou cash.\n");
        //virement
        printf("Veuiller saisir le montant du prix que vous vouler regler par virement.\n");
        printf("Saisir 0 si vous vouler regler votre achat par autres moyen seulement.\n");
        scanf("%f",nv->S.moy_pay[0]);
        Bank-=nv->S.moy_pay[0];
        //cash
        printf("Veuiller saisir le montant du prix que vous vouler regler par cash.\n");
        printf("Saisir 0 si vous ne vouler pas regler votre achat par cash.\n");
        scanf("%f",&nv->S.moy_pay[1]);
        Caisse-=nv->S.moy_pay[1];
        //cheque
        printf("Veuiller saisir le montant du prix que vous vouler regler par cheque.\n");
        printf("Saisir 0 si vous ne vouler pas regler votre achat par cheque.\n");
        scanf("%f",&nv->S.moy_pay[2]);
        Bank-=nv->S.moy_pay[2];
        //cheque sortannnnt iciiiiii svpppppppp aaaaaaa



        if(LSA==NULL)
        {   nv->next=NULL;  }
        else
        {   nv->next=LSA;   }
        LSA=nv;

    printf("voulez vous saisir un autre service achete?\n 0.si non\n 1.si oui\n");
    scanf("%d",&choix_autrePrd);
    return LSA;
}

//saisie d'une commande //Lily
//...

//saisie des depenses relatifs aux employes
Liste_employe* depenses_employee(Liste_employe *Emp)
{
    char num[20];
    Liste_employe *tmp=Emp;
    int choix;
    printf("Veuiller saisir le numero de l'employe auquelle vous voulez ajouter des depense.\n");
    scanf("%s",&num);
    while(tmp!=NULL)
    {
        if(strcmp(tmp->worker.num_e,num)==0)
        {
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
                    Bank-=tmp->worker.deplacement;
                 break;
                }

                case 3:
                {
                    printf("Vous avez choisie de saisir les depenses relatifs au salaire.\n");
                    printf("Veuiller saisir le montant depense sur le salaire de cet employee.\n");
                    scanf("%f",&tmp->worker.salaire);
                    Bank-=tmp->worker.deplacement;
                    break;
                }

            }
        }
        else
        {
            tmp=tmp->next;
        }
    }//fin while
    printf("voulez vous saisir les depenses relatives a un autre employe?\n 0.si non\n 1.si oui\n");
    scanf("%d",&choix_autrePrd);
    return Emp;
}

//voir le solde de la caisse
void visualiser_caisse()
{
    printf("Le solde de la caisse est %f",&Caisse);
}

//voir le solde du compte bancaire
void visualiser_banque()
{
    printf("Le solde de la banque est %f",&Bank);
}
void accueille()
{
    CEO chef;
    Liste_employe *Emp=NULL;
    Liste_service* LSD=NULL;
    Liste_s_achete* LSA=NULL;
    Liste_p_achete* LPA=NULL;
    Liste_produit* prd=NULL;
    system("cls");
    int choix,choix2,choix3;
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
            printf("Choisissez un numÃ©ro selon votre choix de saisie:\n");
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
        case 4://la saisie des services achetÃ©s
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
        printf("est ce que vous voulez revenir Ã  l'accueil ?;\n");
        printf("saisir 1 si vous voulez revenir ou bien 0 si vous voulez quitter.");
        scanf("%d",&accueil);
    }while(accueil!=0);
    return 0;
}


