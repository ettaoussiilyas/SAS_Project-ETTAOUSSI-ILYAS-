#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h> //pour utuliser isupper islower ...

#define size_max 120

//users
typedef struct {
    char username[50];
    char password[50];
    char role[20];  // admin-agent-client for adminstrator
    int loginAttempts;  // 3 fois => stop
    int locked;
    time_t lock_time;
} Clients;

Clients clients[size_max];

//reclamations
typedef struct {
    int id;
    char motif[100];
    char description[255];
    char category[50];
    char status[20];
    char date[20];   
    char client_username[50];
    time_t creation_time;
    time_t resolution_time; 
} Reclamations;

Reclamations reclamations[size_max];

int clients_count = 0;
int reclamation_count = 0;
int choix_menu_signin_signup,choix_menu_administration,choix_menu_client,choix_menu_agent;

// prototypes
void menu_administration();
void menu_signup_signin();
void menu_client(char client_username[]);
void menu_agent();
int validation_password(char password[] , char username[]);
void singup();
void singin();
void ajouter_reclamation();
void afficher_reclamation();
void supprimer_reclamation();
void super_clients();
void super_reclamations();
void afficher_tout_reclamations();
void changement_statu();
void recherche_par_status();
void modifier_reclamation();
void changement_role_utilisateur();
int definir_priorite(char description[]);
void afficher_reclamations_par_priorite();
void taux_resolution();
void rapport_de_jour();
void unlock_compte();
void supprimer_reclamation_24h(char client_username[]);
void afficher_reclamations_client(char client_username[]);
void calculer_temps_moyen_traitement();
void modifier_reclamation_24(char client_username[]);


//*************************main****************************

int main(){

    super_clients();//clients definir 
    super_reclamations();
    do{
        menu_signup_signin();
        switch(choix_menu_signin_signup){
            case 1:
                singup();
                break;
            case 2:
                singin();
                break;
            case 0:
                printf("\nMerci , a La Prochaine .");
                exit(0);
                break;

            default:
                printf("\nMerci de Saisir un Nombre Correct .");
                break;
        }

    }while(choix_menu_signin_signup!=0);

    

    return 0;
}

//**********************************************************

void menu_administration(){

    do{
        printf("\n####################################################");
        printf("\n############       ADMINISTRATOR      ##############");
        printf("\n####################################################");
        printf("\n#### Pour Afficher Les Reclamation : 1       #######");//done
        printf("\n#### Pour Supprimer Une Reclamation : 2     ########");//done
        printf("\n#### Pour Modifier Status Reclamation : 3 ##########");//done
        printf("\n#### Pour Rechecher ID Reclamtion : 4    ###########");//done
        printf("\n#### Pour Rechecher Status Reclamtion : 5 ##########");//done
        printf("\n#### Pour Modifier Une Reclamation : 6     #########");//done
        printf("\n#### Pour Changer Les Roles : 7             ########");//done
        printf("\n#### Pour Afficher les Reclamations Trier: 8 #######");//done
        printf("\n####################################################");
        printf("\n########           STATISTIQUE            ##########");
        printf("\n####################################################");
        printf("\n#### Pour Afficher le Total de Reclamations : 9 ####");//done
        printf("\n#### Pour Afficher le Taux de Resolution    : 10 ###");//done
        printf("\n#### Pour Calcule Tempes de Traitement : 11       ##");//done
        printf("\n#### Pour Rapport de Jour : 12                     #");//done
        printf("\n####################################################");
        printf("\n###########     Pour Logout Click 0     ############");
        printf("\n####################################################");

        char ch;
        while (1){ //condition vrai donc loop exite quand l'utilisateur entry un nombre
            printf("\n\nVotre Choix : ");
            if (scanf("%d", &choix_menu_administration) != 1) {//le reteur de scanf c'est 1 donc quand le reteur deferent loop fonctioner

                printf("\nErreur: Merci d'entrer un nombre valide.\n");
                while ((ch = getchar()) != '\n' && ch != EOF);  //vider la memoire temporaire

            } else {
                break;
            }
        }

        switch(choix_menu_administration){
            case 1:
                afficher_tout_reclamations();
                break;
            case 2:
                supprimer_reclamation();
                break;
            case 3:
                changement_statu();
                break;
            case 4:
                afficher_reclamation();
                break;
            case 5:
                recherche_par_status();
                break;
            case 6:
                modifier_reclamation();
                break;
            case 7:
                changement_role_utilisateur();
                break;
            case 8:
                afficher_reclamations_par_priorite();
                break;
            case 9:
                printf("\nle Total de Reclamations: %d\n", reclamation_count);
                break;
            case 10:
                taux_resolution();
                break;
            case 11:
                calculer_temps_moyen_traitement();
                break;
            case 12:
                rapport_de_jour();
                break;
            case 0:
                printf("\nMerci, a La Prochaine.");
                main();
                break;
            default:
                printf("\nMerci de Saisir Le Choix Correctement !\n");
                break;
        }
    }while (choix_menu_administration!=0);  
}
void menu_signup_signin(){

    printf("\n########################################");
    printf("\n#####            WELLCOM           #####");
    printf("\n########################################");
    printf("\n##### Pour SingUp Click 1         ######");//done
    printf("\n########################################");
    printf("\n##### Pour SingIn Click 2         ######");//done
    printf("\n########################################");
    printf("\n##### Pour Quity Click 0          ######");
    printf("\n########################################");
    char ch;
    while(1){ 
        printf("\n\nVotre Choix : ");
        
        if(scanf("%d", &choix_menu_signin_signup) != 1){
            printf("\nErreur: Merci d'entrer un nombre valide.\n");
            
            while ((ch = getchar()) != '\n' && ch != EOF);  
            // vider la memoire temporaire de input jusqua ch defeent de neveau line ou la dernier input
        }else{
            break;
        }
    }  
}
void menu_client(char client_username[]){
    do{
        printf("\n########################################");
        printf("\n#####           CLIENT             #####");
        printf("\n########################################");
        printf("\n#### Pour Craer Une Reaclamation 1     #");//done
        printf("\n########################################");
        printf("\n#### Pour Afficher Les Reaclamation 2  #");//done
        printf("\n########################################");
        printf("\n#### Pour Supprimer Une Reaclamation 3 #");//done
        printf("\n########################################");
        printf("\n#### Pour Modifier Une Reaclamation 4  #");//done
        printf("\n########################################");
        printf("\n#### Pour Logout Click 0               #");
        printf("\n########################################");

        char ch;
        while(1){ 
            printf("\n\nVotre Choix : ");
            if(scanf("%d", &choix_menu_client) != 1){

                printf("\nErreur: Merci d'entrer un nombre valide.\n");
                while ((ch = getchar()) != '\n' && ch != EOF);  // flush the buffer

            }else{
                break;
            }
        }
        switch(choix_menu_client){
        case 1:
            ajouter_reclamation(client_username);//noveau struct abject
            break;
        case 2:
            afficher_reclamations_client(client_username);//rechrche par user name
            break;
        case 3:
            supprimer_reclamation_24h(client_username);//deff de date creation et carrunte date
            break;
        case 4:
            modifier_reclamation_24(client_username);
            break;
        case 0:
            printf("\nMerci, a La Prochaine.\n");
            main();
        default:
            printf("\nMerci de Saisir un Nombre Correct.");
            break;
        }
    }while(choix_menu_client!=0);
    
}
void menu_agent(){
    do{
        printf("\n#############################################");
        printf("\n#########         AGENT           ###########");
        printf("\n#############################################");
        printf("\n#### Pour Afficher Les Reclamation : 1  #####");//done
        printf("\n#### Pour Supprimer Une Reclamation : 2  ####");//done
        printf("\n#### Pour Modifier Status Reclamation : 3 ###");//done
        printf("\n#### Pour ID Reclamtion Rechecher : 4     ###");//done
        printf("\n#### Pour Rechecher Status Reclamtion : 5 ###");//done
        printf("\n#### Pour Modifier Une Reclamation : 6 ######");//done
        printf("\n#### Pour Logout Click 0          ###########");
        printf("\n#############################################");

        char ch;
        while (1){ 
            printf("\n\nVotre Choix : ");
            if(scanf("%d", &choix_menu_agent) != 1){

                printf("\nErreur: Merci d'entrer un nombre valide.\n");
                while ((ch = getchar()) != '\n' && ch != EOF);  // vider la memoire temporaire

            }else{
                break;
            }
        }
        switch(choix_menu_agent){
            case 1:
                afficher_tout_reclamations();
                break;
            case 2:
                supprimer_reclamation();
                break;
            case 3:
                changement_statu();
                break;
            case 4:
                afficher_reclamation();
                break;
            case 5:
                recherche_par_status();
                break;
            case 6:
                modifier_reclamation();
                break;
            case 0:
                printf("\nMerci, a La Prochaine.");
                main();
                break;
            default:
                printf("\nMerci de Saisir Le Choix Correctement !\n");
                break;
        }
    }while (choix_menu_agent!=0);    
}
void get_current_date(char *date_str){//done
    time_t now = time(NULL);//1970 ,pour aprend le temp actulle
    struct tm *t = localtime(&now);//pour stocker par la structure deja definer de tm dans le pointeur
    sprintf(date_str, "%d-%02d-%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);//pour stocker un chain structurer
}
int validation_password(char password[], char username[]){//done

    int is_majiscule = 0, is_miniscule = 0, is_num = 0, is_special = 0;
    
    if (strlen(password) < 8){
        printf("\nle mot de passe doit contenir au moins 8 caracteres !!");
        return 0;
    }
    for (int i = 0; i < strlen(password); i++) {//ctype
        if (isupper(password[i])) is_majiscule = 1;
        if (islower(password[i])) is_miniscule = 1;
        if (isdigit(password[i])) is_num = 1;
        if (strchr("!@#$^&*", password[i])) is_special = 1;
    }
    if (strstr(password, username) != NULL) {
        printf("\nLe mot pass il faut pas contien le nome de utilisateur !!");
        return 0;
    }

    for (int i = 0; i < clients_count; i++) {
        if (strcmp(clients[i].username, username) == 0) {
            printf("\nle nome d'utilisateur deja existe !");
            return 0; 
        }
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

    do{
        printf("\nVeuillez saisir votre username : ");
        getchar();
        fgets(noveauclient.username, sizeof(noveauclient.username),stdin);
        noveauclient.username[strcspn(noveauclient.username, "\n")] = '\0';
        printf("\nMerci de Saisir un Password Contien 8 Charcter [Majuscule,is_miniscule,Nombres,Symbol :!@#$^&*]: ");
        scanf("%s", password);
    }while(!validation_password(password,noveauclient.username));

    strcpy(noveauclient.password,password);
    strcpy(noveauclient.role,"client");
    noveauclient.loginAttempts=0;
    noveauclient.locked=0;
    clients[clients_count++]=noveauclient;
    printf("\nVotre Compte a ete Cree avec succes.\n");
}
void unlock_compte(){

    time_t current_time = time(NULL);
    for(int i = 0; i < clients_count; i++){
        if(clients[i].locked){
            if (difftime(current_time, clients[i].lock_time) >= 60){ // 30 min  
                clients[i].locked = 0; 
                clients[i].loginAttempts = 0;//re init
            }
        }
    }
}
void singin(){//done
    char username_login[50], password_login[50];
    int tentative = 0, trouve = 0;
    unlock_compte();  //pour check

    do {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);  

        printf("\nMerci de Saisir votre username : ");
        scanf("%s",&username_login);
        // fgets(username_login,sizeof(username_login), stdin);
        // username_login[strcspn(username_login, "\n")] = '\0';//check le dernier c'est noveau line et eviter le

        printf("\nMerci de Saisir votre password : ");
        scanf("%s",&password_login);
        // fgets(password_login,sizeof(password_login), stdin);
        // password_login[strcspn(password_login, "\n")] = '\0'; 
        trouve = 0; 

        for(int i = 0; i < clients_count; i++){
            if(strcmp(username_login, clients[i].username) == 0){
                trouve = 1;

                if (clients[i].locked) {
                    printf("\nVotre compte encore verrouille. Ressayer dans 30 minutes.\n");
                    return; 
                }

                if(strcmp(password_login, clients[i].password) == 0){
                    printf("\n\nBienvenu %s...\n", clients[i].username);
                    clients[i].loginAttempts = 0; 

                    if(strcmp(clients[i].role, "admin") == 0){
                        menu_administration();
                    }else if (strcmp(clients[i].role, "agent") == 0){
                        menu_agent();
                    }else if (strcmp(clients[i].role, "client") == 0){
                        menu_client(clients[i].username);
                    }else {
                        printf("\nRole inconnu.\n");
                    }
                    return;
                }else{
                    tentative++;
                    clients[i].loginAttempts++;
                    printf("\nIdentifiants incorrects. Tentative %d/3.\n", tentative);

                    if(clients[i].loginAttempts == 3){
                        clients[i].locked = 1;
                        clients[i].lock_time = time(NULL);
                        printf("\nMaintenant votre compte est bloque pour 30 minutes.\n");
                    }
                    break;
                }
            }
        }

        if (!trouve) {
            printf("\nNom d'utilisateur introuvable. Veuillez essayer.\n");
            return; 
        }

    } while (tentative < 3);
}
void supprimer_reclamation_24h(char client_username[]){
    int id_supprimer;
    char ch;
    while(1){ 
        printf("\n\nEnter ID de reclamation pour Supprimer: ");
        if(scanf("%d", &id_supprimer) != 1){
            printf("\nErreur: Merci d'entrer un nombre valide.\n");
            while ((ch = getchar()) != '\n' && ch != EOF);  
        }else{
            break;
        }
    }

    for(int i = 0; i < reclamation_count; i++){
        if(reclamations[i].id == id_supprimer && strcmp(reclamations[i].client_username,client_username)==0){
            time_t current_time = time(NULL);
            double check_def_time = difftime(current_time, reclamations[i].creation_time);

            
            if(check_def_time > 86400){
                printf("\nImpossible de supprimer la reclamation. Elle depasse 24H.\n");// (86400 s)
                return;
            }

            for (int j = i; j < reclamation_count - 1; j++) {
                reclamations[j] = reclamations[j+1];
            }
            reclamation_count--;
            printf("\nReclamation Bien Supprimer.\n");
            return;
        }
    }
    printf("\nAucun Reclamation avec ce Id.\n");
}
void afficher_reclamation(){
    int id_search;
    char ch;
    while(1){ 
        printf("\n\nSaisir l'ID de la reclamation : ");
        if(scanf("%d", &id_search) != 1){
            printf("\nErreur: Merci d'entrer un nombre valide.\n");
            while ((ch = getchar()) != '\n' && ch != EOF);  
        }else{
            break;
        }
    }
    if (reclamation_count == 0) {
        printf("\nAucune reclamation disponible.\n");
        return;
    }

    for(int i = 0; i < reclamation_count; i++){
        if(reclamations[i].id == id_search){
            printf("\n#################");
            printf("\nID: %d\nMotif: %s\nDescription: %s\nCategorie: %s\nStatut: %s\nDate: %s\n\n",
                   reclamations[i].id, reclamations[i].motif, reclamations[i].description,
                   reclamations[i].category, reclamations[i].status, reclamations[i].date);
            return;
        }
    }

    printf("\nReclamation avec l'ID %d non trouvee.\n", id_search);
}
void supprimer_reclamation(){//adimn - agent
    int id_supprimer;
    char ch;
    while(1){ 
        printf("\n\nEnter ID de reclamation pour Supprimer: ");
        if(scanf("%d", &id_supprimer) != 1){
            printf("\nErreur: Merci d'entrer un nombre valide.\n");
            while ((ch = getchar()) != '\n' && ch != EOF);  
        }else{
            break;
        }
    }

    for (int i = 0; i < reclamation_count; i++) {
        if (reclamations[i].id == id_supprimer) {
            for (int j = i; j < reclamation_count - 1; j++) {
                reclamations[j] = reclamations[j + 1];
            }
            reclamation_count--;
            printf("\nReclamation Bien Supprimer.\n");
            return;
        }
    }
    printf("\nId de Reclamation Pas Trouver.\n");
}
void super_clients(){//test
    strcpy(clients[0].username, "admin1");
    strcpy(clients[0].password, "AdminPass1!");
    strcpy(clients[0].role, "admin");
    clients[0].loginAttempts = 0;
    clients[0].locked = 0;

    strcpy(clients[1].username, "agent1");
    strcpy(clients[1].password, "AgentPass1!");
    strcpy(clients[1].role, "agent");
    clients[1].loginAttempts = 0;
    clients[1].locked = 0;

    strcpy(clients[2].username, "client1");
    strcpy(clients[2].password, "ClientPass1!");
    strcpy(clients[2].role, "client");
    clients[2].loginAttempts = 0;
    clients[2].locked = 0;

    strcpy(clients[3].username, "client2");
    strcpy(clients[3].password, "ClientPass2!");
    strcpy(clients[3].role, "client");
    clients[3].loginAttempts = 0;
    clients[3].locked = 0;

    clients_count += 4;
}
void super_reclamations(){
    if(reclamation_count == 0){
        reclamations[0].id = 1;
        strcpy(reclamations[0].motif, "Problem de Pyment");
        strcpy(reclamations[0].description, "Le paiement pas ete effectue, mais l argent a ete pronee.");
        strcpy(reclamations[0].category, "argent");
        strcpy(reclamations[0].status, "en cours");
        strcpy(reclamations[0].date, "2024-09-25");
        strcpy(reclamations[0].client_username, "client1");
        reclamations[0].creation_time = time(NULL);  // Current time

        reclamations[1].id = 2;
        strcpy(reclamations[1].motif, "compte blocker");
        strcpy(reclamations[1].description, "urgent mon compte verrouille en raison de tentatives de mot de passe incorrectes.");
        strcpy(reclamations[1].category, "Account");
        strcpy(reclamations[1].status, "en cours");
        strcpy(reclamations[1].date, "2024-09-25");
        strcpy(reclamations[1].client_username, "client1");
        reclamations[1].creation_time = time(NULL) - 3600;  // avant 1h

        reclamations[2].id = 3;
        strcpy(reclamations[2].motif, "probleme technique");
        strcpy(reclamations[2].description, "Impossible d'acceder a certaines fonctionnalites de la plateforme mais c'est important.");
        strcpy(reclamations[2].category, "technique");
        strcpy(reclamations[2].status, "en cours");
        strcpy(reclamations[2].date, "2024-09-24");
        strcpy(reclamations[2].client_username, "client1");
        reclamations[2].creation_time = time(NULL) - 86401;  //avant 24h+1s
        reclamation_count = 3;
    }
    
}
void afficher_tout_reclamations(){//admin-agent
    int trouver = 0;
    if (reclamation_count == 0) {
        printf("\nAucune reclamation disponible.\n");
        return;
    }
    printf("\nVoila Tout Les Reclamations : \n");
    for (int i = 0; i < reclamation_count; i++) {

        printf("\n###############");
        printf("\nID: %d\nMotif: %s\nDescription: %s\nCategorie: %s\nStatut: %s\nDate: %s\n\n",
        reclamations[i].id, reclamations[i].motif, reclamations[i].description,
        reclamations[i].category, reclamations[i].status, reclamations[i].date);
        trouver = 1;
    }
    if(trouver==0){
        printf("\nAucun Reclamation Trouver Avec Ce ID !\n");
    }
}
void changement_statu(){
    int id_search, statut_change;
    char ch;
    while(1){ 
        printf("\n\nEnter ID de reclamation pour Chenger le Status: ");
        if(scanf("%d", &id_search) != 1){
            printf("\nErreur: Merci d'entrer un nombre valide.\n");
            while ((ch = getchar()) != '\n' && ch != EOF);  
        }else{
            break;
        }
    }
    char c;
    while(1){ 
        printf("\n\nSaisir le nouveau statut [0: en cours, 1: en attente, 2: resolu]: ");
        if(scanf("%d", &statut_change) != 1){
            printf("\nErreur: Merci d'entrer un nombre valide.\n");
            while ((c = getchar()) != '\n' && c != EOF);  
        }else{
            break;
        }
    }

    for (int i = 0; i < reclamation_count; i++) {
        if (reclamations[i].id == id_search) {
            if(statut_change==0){
                strcpy(reclamations[i].status, "en cours");
            }else if(statut_change==1){
                strcpy(reclamations[i].status, "en attente");
            } else if(statut_change==2){
                reclamations[i].resolution_time = time(NULL);
                strcpy(reclamations[i].status, "resolu");

            }
            printf("\nStatut Bien Modifie.\n");
            return;
        }
    }
    printf("\nAucun Reclamation avec l'ID %d !!\n", id_search);
}
void recherche_par_status(){
    if(reclamation_count==0){
        printf("\nAucune reclamation disponible.\n");
        return;
    }
    int statut_recherche;

    char ch;
    while(1){ 
        printf("\n\nSaisir le statut recherche [0: en cours, 1: en attente, 2: resolu]: ");
        if(scanf("%d", &statut_recherche) != 1){
            printf("\nErreur: Merci d'entrer un nombre valide.\n");
            while ((ch = getchar()) != '\n' && ch != EOF);  
        }else{
            break;
        }
    }
    char statut_str[20];
    switch(statut_recherche) {
        case 0:
            strcpy(statut_str,"en cours");
            break;
        case 1:
            strcpy(statut_str,"en attente");
            break;
        case 2:
            strcpy(statut_str,"resolu");
            break;
        default:
            printf("\nChoix Invalide.\n");
            return;
    }
    int trouver = 0;
    for(int i = 0; i < reclamation_count; i++){
        if(strcmp(reclamations[i].status,statut_str)==0){
            printf("\n#####################\n");
            printf("\nID: %d\nMotif: %s\nDescription: %s\nCategorie: %s\nStatut: %s\nDate: %s\n\n",
            reclamations[i].id, reclamations[i].motif, reclamations[i].description,
            reclamations[i].category, reclamations[i].status, reclamations[i].date);
            trouver = 1;
        }
    }
    if(trouver==0){
        printf("\nAucune Reclamation Trouver Avec Ce Statut!!\n");
    }
        
}
void modifier_reclamation(){
    if(reclamation_count==0){
        printf("\nAucune reclamation disponible.\n");
        return;
    }
    int id_recherche;
    int trouve=0;
    char ch;
    while(1){ 
        printf("\n\nEnter ID de reclamation pour Modifier: ");
        if(scanf("%d", &id_recherche) != 1){
            printf("\nErreur: Merci d'entrer un nombre valide.\n");
            while ((ch = getchar()) != '\n' && ch != EOF);  
        }else{
            break;
        }
    }
    for (int i = 0; i < reclamation_count; i++) {
        if (reclamations[i].id == id_recherche) {
            printf("\nSaisir la nouvelle description : ");
            getchar();
            fgets(reclamations[i].description, sizeof(reclamations[i].description), stdin);
            printf("\nSaisir le nouveau motif : ");
            fgets(reclamations[i].motif, sizeof(reclamations[i].motif), stdin);
            printf("\nSaisir la nouvelle categorie : ");
            fgets(reclamations[i].category, sizeof(reclamations[i].category), stdin);
            trouve = 1;
            return;
        }
    }
    if(trouve==0){
        printf("\nAucune Reclamation avec l'ID %d!!\n", id_recherche);
        return;
    }
}
void changement_role_utilisateur(){
    char username_search[50];
    printf("\nSaisir le Nome d'utilisateur : ");
    scanf("%s", username_search);
    //fgets(username_search, sizeof(username_search), stdin);
    //username_search[strcspn(username_search, "\n")] = '\0';
    for (int i = 0; i < clients_count; i++) {
        if(strcmp(clients[i].username, username_search) == 0){
            int role_choice;
            // printf("\nSaisir le Nouveau Role [Administrateur: 0, Agent: 1, Client: 2]: ");
            // scanf("%d", &role_choice);
            char ch;
            while(1){ 
                printf("\n\nSaisir le Nouveau Role [Administrateur: 0, Agent: 1, Client: 2]: ");
                if(scanf("%d", &role_choice) != 1){
                    printf("\nErreur: Merci d'entrer un nombre valide.\n");
                    while ((ch = getchar()) != '\n' && ch != EOF);  
                }else{
                    break;
                }
            }

            switch(role_choice){
                case 0:
                    strcpy(clients[i].role, "admin");
                    break;
                case 1:
                    strcpy(clients[i].role, "agent");
                    break;
                case 2:
                    strcpy(clients[i].role, "client");
                    break;
                default:
                    printf("\nChoix invalide. Veuillez entrer 0, 1 ou 2.\n");
                    changement_role_utilisateur();
            }

            printf("\nLe role de l'utilisateur %s a ete bien modifie en %s.\n", username_search, clients[i].role);
            return;
        }
    }

    // If the user was not found
    printf("\nAucun Nome d'utilisateur Avec : %s !!\n", username_search);
}
int definir_priorite(char description[]){
    if(strstr(description, "urgent") || strstr(description, "critique")){
        return 3; 
    }else if(strstr(description, "important") || strstr(description, "presse")){
        return 2;
    }
    return 1;  
}
void afficher_reclamations_par_priorite(){
    if (reclamation_count == 0) {
        printf("\nAucune reclamation disponible.\n");
        return;
    }
    int indices[reclamation_count];
    for(int i = 0; i < reclamation_count; i++){
        indices[i] = i;
    }
    for(int i = 0; i < reclamation_count - 1; i++){
        for(int j = 0; j < reclamation_count - i - 1; j++){
            if(definir_priorite(reclamations[indices[j]].description) < definir_priorite(reclamations[indices[j + 1]].description)){
                
                int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }


    printf("\nReclamations par Priorite :\n");
    for(int i = 0; i < reclamation_count; i++){
        int index = indices[i];
        printf("\n###############################\n");
        printf("ID: %d\nMotif: %s\nDescription: %s\nCategorie: %s\nStatut: %s\nDate: %s\nPriorite: %d\n\n",
               reclamations[index].id, reclamations[index].motif, reclamations[index].description,
               reclamations[index].category, reclamations[index].status, reclamations[index].date,
               definir_priorite(reclamations[index].description));
    }
}
void taux_resolution(){
    if (reclamation_count == 0) {
        printf("\nAucune reclamation disponible.\n");
        return;
    }

    int resolu_taux = 0;
    for (int i = 0; i < reclamation_count; i++) {
        if (strcmp(reclamations[i].status, "resolu") == 0) {
            resolu_taux += 1;
        }
    }
    float result = (float)resolu_taux / reclamation_count * 100;
    printf("\nLe Taux de Resolution: %.2f%%\n", result); 
}
void rapport_de_jour(){
    int nombre_en_coures = 0;
    int nombre_resolues = 0;
    int nombre_en_attente = 0;
    
    FILE *fichier = fopen("rapport_jour.txt", "w");

    if(fichier == NULL){
        printf("Erreur lors de l'ouverture du fichier!\n");
        return;
    }
    
    fprintf(fichier, "\n###########################################");
    fprintf(fichier, "\n### Rapport Journalier des Reclamations ###");
    fprintf(fichier, "\n###########################################\n");

    fprintf(fichier, "\nReclamations Resolues Jusqua Maintenant :");
    fprintf(fichier, "\n#########################################\n");
    for(int i = 0; i < reclamation_count; i++){
        if (strcmp(reclamations[i].status, "resolu") == 0){
            fprintf(fichier, "\nID: %d, Motif: %s, Date Creation: %s\n", reclamations[i].id, reclamations[i].description, reclamations[i].date);
            nombre_resolues++;
        }
    }

    if(nombre_resolues == 0){
        fprintf(fichier, "\nAucune reclamation resolue aujourd'hui.\n");
    }

    fprintf(fichier, "\nReclamations en Traitement aujourd'hui :");
    fprintf(fichier, "\n########################################\n");
    for(int i = 0; i < reclamation_count; i++) {
        if (strcmp(reclamations[i].status, "en attente") == 0) {
            fprintf(fichier, "\nID: %d, Motif: %s, Date Traitement: %s\n", reclamations[i].id, reclamations[i].description, reclamations[i].date);
            nombre_en_attente++;
        }
    }

    if(nombre_en_attente == 0){
        fprintf(fichier, "\nAucune reclamation en attente aujourd'hui.\n");
    }

    fprintf(fichier, "\nNouvelles reclamations en cours :");
    fprintf(fichier, "\n#################################\n");
    for(int i = 0; i < reclamation_count; i++){
        if (strcmp(reclamations[i].status, "en cours") == 0) {
            fprintf(fichier, "\nID: %d | Motif: %s || Date : %s\n", reclamations[i].id, reclamations[i].motif, reclamations[i].date);
            nombre_en_coures++;
        }
    }

    if(nombre_en_coures == 0){
        fprintf(fichier, "\nAucune en cours traiter reclamation aujourd'hui.\n");
    }

    fprintf(fichier, "\nNombre total de reclamations resolues : %d\n", nombre_resolues);
    fprintf(fichier, "\nNombre total de reclamations en attente : %d\n", nombre_en_attente);
    fprintf(fichier, "\nNombre total de nouvelles reclamations : %d\n", nombre_en_coures);
    fprintf(fichier, "\n################### Fin du Rapport ###################");
    fprintf(fichier, "\n######################################################\n");
    fclose(fichier);

    printf("\nRapport de jour creer dans 'rapport_jour.txt'\n");
}
void rapport_de_jour_console(){
    int nombre_en_coures = 0;
    int nombre_resolues = 0;
    int nombre_en_attente = 0;
    printf("\n###########################################");
    printf("\n### Rapport Journalier des Reclamations ###");
    printf("\n###########################################");
    
    printf("\nReclamations Resolues Jusqua Maintenant :");
    printf("\n#########################################");
    for(int i = 0; i < reclamation_count; i++){
        if (strcmp(reclamations[i].status, "resolu") == 0) {
            // Afficher les reclamations resolues
            printf("\nID: %d, Motif: %s, Date Creation: %s\n", reclamations[i].id, reclamations[i].description, reclamations[i].date);
            nombre_resolues++;
        }
    }

    if(nombre_resolues == 0){
        printf("\nAucune reclamation resolue aujourd'hui.\n");
    }
   
    printf("\nReclamations en Traitement aujourd'hui :");
    printf("\n########################################");
    for(int i = 0; i < reclamation_count; i++){
        if (strcmp(reclamations[i].status, "en attente") == 0) {
            // Afficher les reclamations resolues
            printf("\nID: %d, Motif: %s, Date Traitement: %s\n", reclamations[i].id, reclamations[i].description, reclamations[i].date);
            nombre_en_attente++;
        }
    }

    if(nombre_en_attente == 0){
        printf("\nAucune reclamation en attente aujourd'hui.\n");
    }

    printf("\nNouvelles reclamations en cours :");
    printf("\n#################################");
    for(int i = 0; i < reclamation_count; i++){
        if (strcmp(reclamations[i].status, "en cours") == 0) {
            // Afficher les nouvelles reclamations non encore traitees
            printf("\nID: %d | Motif: %s || Date Soumission: %s\n", reclamations[i].id, reclamations[i].motif, reclamations[i].date);
            nombre_en_coures++;
        }
    }

    if(nombre_en_coures == 0){
        printf("\nAucune en cours traiter reclamation aujourd'hui.\n");
    }
    printf("\nNombre total de reclamations resolues : %d\n", nombre_resolues);
    printf("\nNombre total de reclamations en attente  : %d\n", nombre_en_attente);
    printf("\nNombre total de nouvelles reclamations : %d\n", nombre_en_coures);
    printf("\n################### Fin du Rapport ###################");
    printf("\n######################################################\n");
}
void ajouter_reclamation(char client_username[]){
    Reclamations nouveau_reclamation;
    nouveau_reclamation.creation_time = time(NULL);
    nouveau_reclamation.id = reclamation_count + 1;
    get_current_date(nouveau_reclamation.date);//prond le dte pour le remplire avec la date actuelle
    printf("\nSaisir la Description : ");
    getchar();
    fgets(nouveau_reclamation.description, sizeof(nouveau_reclamation.description), stdin);
    printf("\nSaisir le Motif : ");
    fgets(nouveau_reclamation.motif, sizeof(nouveau_reclamation.motif), stdin);
    printf("\nSaisir la Categorie : ");
    fgets(nouveau_reclamation.category, sizeof(nouveau_reclamation.category), stdin);

    strcpy(nouveau_reclamation.status, "en cours"); 
    strcpy(nouveau_reclamation.client_username, client_username);

    reclamations[reclamation_count++] = nouveau_reclamation;

    printf("\nReclamation Bien Enregistree ID %d.\n", nouveau_reclamation.id);
}
void afficher_reclamations_client(char client_username[]){
    int found = 0;
    printf("\nReclamations de %s :\n", client_username);
    for (int i = 0; i < reclamation_count; i++) {
        if (strcmp(reclamations[i].client_username, client_username) == 0) {
            printf("\n####################");
            printf("\nID: %d\nMotif: %s\nDescription: %s\nCategorie: %s\nStatus: %s\nDate: %s\n",
                   reclamations[i].id, reclamations[i].motif, reclamations[i].description,
                   reclamations[i].category, reclamations[i].status, reclamations[i].date);
            found = 1;
        }
    }

    if(!found){
        printf("\nAucune reclamation trouvee pour %s.\n",client_username);
    }
}
void calculer_temps_moyen_traitement(){
    double total_time = 0;
    int resolved_count = 0;

    for (int i = 0; i < reclamation_count; i++) {
        if (strcmp(reclamations[i].status, "resolu") == 0) {
            double processing_time = difftime(reclamations[i].resolution_time, reclamations[i].creation_time);
            total_time += processing_time;
            resolved_count++;
        }
    }

    if (resolved_count > 0) {
        double average_time = total_time / resolved_count;
        printf("\nLe temps moyen de traitement des reclamations resolues est de %.2f min .\n", average_time/60);
    } else {
        printf("\nAucune reclamation resolue pour calculer le temps moyen de traitement.\n");
    }
}
void modifier_reclamation_24(char client_username[]) {
    if (reclamation_count == 0) {
        printf("\nAucune reclamation disponible.\n");
        return;
    }

    int id_supprimer;
    int trouve = 0;
    char ch;

    while (1) { 
        printf("\n\nEntrer ID de reclamation pour modifier: ");
        if (scanf("%d", &id_supprimer) != 1) {
            printf("\nErreur: Merci d'entrer un nombre valide.\n");
            while ((ch = getchar()) != '\n' && ch != EOF);  
        } else {
            break;
        }
    }

    for (int i = 0; i < reclamation_count; i++) {
    
        if (reclamations[i].id == id_supprimer && strcmp(reclamations[i].client_username, client_username) == 0) {
        
            time_t current_time = time(NULL);
            double time_diff = difftime(current_time, reclamations[i].creation_time);

            if(time_diff > 86400){
                printf("\nErreur: tu peux pas modifier la reclamation apres 24h.\n");
                return;
            }

            printf("\nSaisir la nouvelle description : ");
            getchar();
            fgets(reclamations[i].description, sizeof(reclamations[i].description), stdin);
            strtok(reclamations[i].description, "\n");

            if (strlen(reclamations[i].description) <= 1) {
                printf("\nErreur: Description vide non autorisee.\n");
                return;
            }

            printf("\nSaisir le nouveau motif : ");
            fgets(reclamations[i].motif, sizeof(reclamations[i].motif), stdin);
            strtok(reclamations[i].motif, "\n");

        
            if (strlen(reclamations[i].motif) <= 1) {
                printf("\nErreur: Motif vide non autorise.\n");
                return;
            }

            printf("\nSaisir la nouvelle categorie : ");
            fgets(reclamations[i].category, sizeof(reclamations[i].category), stdin);
            strtok(reclamations[i].category, "\n");

            if (strlen(reclamations[i].category) <= 1) {
                printf("\nErreur: Categorie vide non autorisee.\n");
                return;
            }

            trouve = 1;
            printf("\nReclamation modifiee avec succes.\n");
            return;
        }
    }

    if (trouve == 0) {
        printf("\nAucune reclamation avec l'ID %d trouvee pour %s!!\n", id_supprimer, client_username);
    }
}


