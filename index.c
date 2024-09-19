#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h> //pour utuliser isupper islower ...

//max number

#define size_max 120

//users
typedef struct {
    char username[50];
    char password[50];
    char role[20];  // admin-agent-client for adminstrator
    int loginAttempts;  // 3 fois => stop
} Clients;

Clients clients[size_max];
//reclamations
typedef struct {
    int id;  
    char motif[100];
    char description[255];
    char category[50];
    char status[20];  // en cour-resolu-rejete
    char date[20]; //il fau genere   
    char client[50];  
    int priority;     // 1: basse, 2: moyenne, 3: haute
} Reclamations;

Reclamations reclamations[size_max];

int choix_menu_signin_signup,choix_menu_administration,choix_menu_statistique,choix_menu_client;
int clients_count = 0;

// prototypes
void menu_administration();
void menu_statistique();
void   menu_signup_signin();
void menu_client();
int validation_password(char password[] , char username[]);
void singup();
int singin();




int main(){

    do{
        menu_signup_signin();
        switch (choix_menu_signin_signup)
        {
        case 1:
            singup();
            break;
        case 2:
            
            if(singin()==1){
                menu_client();
            }else{
                printf("Mote Pass or PassWord Inccorect ,Essayer Aprer 30min .");
                choix_menu_signin_signup=0;
                break;
            }
            break;
        case 0:
        printf("Merci , a La Prochaine .");
            break;
        
        default:
            printf("Merci de Saisir un Nombre Correct .");
            break;
        }

    }while (choix_menu_signin_signup!=0);

    

    return 0;
}

void menu_administration(){//done

    printf("\n####################################################");
    printf("\n########        ADMINISTRATION            ##########");
    printf("\n####################################################");
    printf("\n#### Pour Gerer les roles : 1     ##################");
    printf("\n#### Pour Afficher les reclamations : 2 ############");
    printf("\n#### Pour Modifier une Reclamatio : 3 ##############");
    printf("\n#### Pour Supprimer une Reclamation : 4 ############");
    printf("\n#### Pour Changer le statut d'une reclamation : 5 ##");
    printf("\n#### Pour Rechrecher a Une Reclamation Par ID : 6 ##");
    printf("\n#### Pour Le Rapport et Statistique Click     : 7 ##");
    printf("\n#### Pour LougOut Click : 0          ###############");
    printf("\n####################################################");
    printf("\nVotre Choix : ");
    scanf("%d", &choix_menu_administration);
    
}
void menu_statistique(){//done
    printf("\n####################################################");
    printf("\n########           STATISTIQUE            ##########");
    printf("\n####################################################");
    printf("\n#### Pour Afficher le Total de Reclamations : 1 ####");
    printf("\n#### Pour Afficher le Taux de Resolution    : 2 ####");
    printf("\n#### Pour Calculer le delai moyen de traitement: 3##");
    printf("\n#### Pour Rapport de Jour : 4     ##################");
    printf("\n#### Pour LougOut Click : 0          ###############");
    printf("\n####################################################");
    printf("\nVotre Choix : ");
    scanf("%d", &choix_menu_statistique);

}
void menu_signup_signin(){//done

    printf("\n########################################");
    printf("\n#####            WELLCOM           #####");
    printf("\n########################################");
    printf("\n#### Pour SingUp Click 1          ######");
    printf("\n#### Pour SingIn Click 2          ######");
    printf("\n#### Pour Quity Click 0           ######");
    printf("\n########################################");
    printf("\nVotre Choix : ");
    scanf("%d", &choix_menu_signin_signup);
    
}
void menu_client(){//done

    printf("\n########################################");
    printf("\n#####           CLIENT             #####");
    printf("\n########################################");
    printf("\n#### Pour Craer Une Reaclamation 1 #####");
    printf("\n#### Pour Supprimer Une Reaclamation 2 #");
    printf("\n#### Pour Quitter Click 3          #####");
    printf("\n########################################");
    printf("\nVotre Choix : ");
    scanf("%d", &choix_menu_client);
    
}
int validation_password(char password[], char username[]) {
    int is_majiscule = 0, is_miniscule = 0, is_num = 0, is_special = 0;
    
    if (strlen(password) < 8) return 0;

    for (int i = 0; i < strlen(password); i++) {
        if (isupper(password[i])) is_majiscule = 1;
        if (islower(password[i])) is_miniscule = 1;
        if (isdigit(password[i])) is_num = 1;
        if (strchr("!@#$%^&*", password[i])) is_special = 1;
    }

    if (is_majiscule && is_miniscule && is_num && is_special && strstr(password, username) == NULL){
        return 1;
    }else{
        return 0;
    }
    
}
void singup(){
    Clients noveauclient;
    char password[100];
    printf("\nVeuillez saisir votre username : ");
    getchar();
    fgets(noveauclient.username, sizeof(noveauclient.username),stdin);
    do{
        printf("\nMerci de Saisir un Password Contien 8 Charcter [Majuscule,is_miniscule,Nombres,Symbol :!@#$^&*]: ");
        scanf("%s", password);
    }while(!validation_password(password,noveauclient.username));
    strcpy(password, noveauclient.username);
    clients[clients_count++]=noveauclient;
    printf("\nVotre Compte a ete Cree avec succes.\n");
    noveauclient.loginAttempts=0;
    strcpy(noveauclient.role,"client");
}
int singin(){
    char username_login[50], password_login[50];
    int tantative = 0;
    do{
        printf("\nMerci de Saisir votre username : ");
        getchar();
        fgets(username_login, sizeof(username_login), stdin);
        printf("\nMerci de Saisir votre password : ");
        fgets(password_login,sizeof(password_login),stdin);
        for(int i=0 ; i<clients_count;i++){
            if(strcmp(username_login, clients[i].username)==0 && strcmp(password_login, clients[i].password)==0){
                printf("\nBien Venue.\n");
                strcpy(clients[i].role, "client");
                return 1;
                break;
            }

        }
        tantative++;
    }while(tantative < 3);
    
    return 0;
}