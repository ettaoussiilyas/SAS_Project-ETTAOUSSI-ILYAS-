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
void supprimer_reclamation_24h();
void afficher_reclamations_client(char client_username[50]);
void calculer_temps_moyen_traitement();

//**********************************************************


int main(){

    super_clients();

    do{
        menu_signup_signin();
        switch (choix_menu_signin_signup)
        {
        case 1:
            singup();
            break;
        case 2:
            singin();
            break;
        case 0:
            printf("Merci , a La Prochaine .");
            exit(0);
            break;
        
        default:
            printf("Merci de Saisir un Nombre Correct .");
            break;
        }

    }while (choix_menu_signin_signup!=0);

    

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
        printf("\n#### Pour ID Reclamtion Rechecher : 4    ###########");//done
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
        printf("\nVotre Choix : ");
        scanf("%d", &choix_menu_administration);
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
                printf("le Total de Reclamations: %d\n", reclamation_count);
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
                printf("Merci, a La Prochaine.");
                main();
                break;
            default:
                printf("Merci de Saisir Le Choix Correctement !\n");
                break;
        }
    }while (choix_menu_administration!=0);  
}
void menu_signup_signin(){

    printf("\n########################################");
    printf("\n#####            WELLCOM           #####");
    printf("\n########################################");
    printf("\n#### Pour SingUp Click 1          ######");//done
    printf("\n#### Pour SingIn Click 2          ######");//done
    printf("\n#### Pour Quity Click 0           ######");
    printf("\n########################################");
    printf("\nVotre Choix : ");
    scanf("%d", &choix_menu_signin_signup);
    
}
void menu_client(char client_username[]){
    do{
        printf("\n########################################");
        printf("\n#####           CLIENT             #####");
        printf("\n########################################");
        printf("\n#### Pour Craer Une Reaclamation 1 #####");//done
        printf("\n#### Pour Afficher Une Reaclamation 2 ##");//done
        printf("\n#### Pour Supprimer Une Reaclamation 3 #");//done
        printf("\n#### Pour Logout Click 0          ######");
        printf("\n########################################");
        printf("\nVotre Choix : ");
        scanf("%d", &choix_menu_client);
        switch(choix_menu_client){
        case 1:
            ajouter_reclamation(client_username);
            break;
        case 2:
            //afficher_reclamation();
            afficher_reclamations_client(client_username);
            break;
        case 3:
            supprimer_reclamation_24h();
            break;
        case 0:
            printf("Merci, a La Prochaine.");
            main();
        default:
            printf("Merci de Saisir un Nombre Correct.");
            break;
        }
    }while(choix_menu_client!=0);
    
}
void menu_agent(){//done
    do{
        printf("\n#############################################");
        printf("\n#########         AGENT           ###########");
        printf("\n#############################################");
        printf("\n#### Pour Afficher Les Reclamation : 1 ######");//done
        printf("\n#### Pour Supprimer Une Reclamation : 2 #####");//done
        printf("\n#### Pour Modifier Status Reclamation : 3 ###");//done
        printf("\n#### Pour ID Reclamtion Rechecher : 4 #######");//done
        printf("\n#### Pour Rechecher Status Reclamtion : 5 ###");//done
        printf("\n#### Pour Modifier Une Reclamation : 6 ######");//done
        printf("\n#### Pour Logout Click 0          ###########");
        printf("\n#############################################");
        printf("\nVotre Choix : ");
        scanf("%d", &choix_menu_agent);
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
                printf("Merci, a La Prochaine.");
                main();
                break;
            default:
                printf("Merci de Saisir Le Choix Correctement !\n");
                break;
        }
    }while (choix_menu_agent!=0);    
}
void get_current_date(char *date_str) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    sprintf(date_str, "%d-%02d-%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
}
int validation_password(char password[], char username[]) {

    int is_majiscule = 0, is_miniscule = 0, is_num = 0, is_special = 0;
    
    if (strlen(password) < 8){
        printf("le mot de passe doit contenir au moins 8 caracteres !!");
        return 0;
    }
    for (int i = 0; i < strlen(password); i++) {
        if (isupper(password[i])) is_majiscule = 1;
        if (islower(password[i])) is_miniscule = 1;
        if (isdigit(password[i])) is_num = 1;
        if (strchr("!@#$^&*", password[i])) is_special = 1;
    }
    if (strstr(password, username) != NULL) {
        printf("le mot pass il faut pas matcher avec le nome de utilisateur !!");
        return 0;
    }

    for (int i = 0; i < clients_count; i++) {
        if (strcmp(clients[i].username, username) == 0) {
            printf("le nome d'utilisateur deja existe !");
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
    // printf("\nVeuillez saisir votre username : ");
    // getchar();
    // fgets(noveauclient.username, sizeof(noveauclient.username),stdin);
    // noveauclient.username[strcspn(noveauclient.username, "\n")] = '\0';
    do{
        printf("\nVeuillez saisir votre username : ");
        getchar();
        fgets(noveauclient.username, sizeof(noveauclient.username),stdin);
        noveauclient.username[strcspn(noveauclient.username, "\n")] = '\0';
        printf("\nMerci de Saisir un Password Contien 8 Charcter [Majuscule,is_miniscule,Nombres,Symbol :!@#$^&*]: ");
        scanf("%s", password);
    }while(!validation_password(password,noveauclient.username));
    //strcmp(noveauclient.username,noveauclient.username);
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
                clients[i].loginAttempts = 0; 
                printf("Le compte de %s a ete debloque.\n", clients[i].username);
            }
        }
    }
}
void singin(){
    char username_login[50], password_login[50];
    int tentative = 0, trouve = 0;
    unlock_compte();
    do {
        int c;
        while ((c = getchar()) != '\n' && c != EOF); 
        printf("\nMerci de Saisir votre username : ");
        fgets(username_login, sizeof(username_login), stdin);
        username_login[strcspn(username_login, "\n")] = '\0';  
        printf("\nMerci de Saisir votre password : ");
        fgets(password_login, sizeof(password_login), stdin);
        password_login[strcspn(password_login, "\n")] = '\0';
        for(int i = 0; i < clients_count; i++){
            if(strcmp(username_login, clients[i].username) == 0){
                
                if (clients[i].locked) {
                    printf("Votre compte encore verrouille. Ressayer dans 30 minutes.\n");
                    return; 
                }
                if(strcmp(password_login, clients[i].password) == 0) {
                    printf("\nBienvenu %s.\n", clients[i].username);
                    clients[i].loginAttempts = 0;
                    if (strcmp(clients[i].role, "admin") == 0){
                        menu_administration();
                    } else if (strcmp(clients[i].role, "agent") == 0){
                        menu_agent();
                    } else if (strcmp(clients[i].role, "client") == 0){
                        menu_client(clients[i].username);
                    } else {
                        printf("Role inconnu.\n");
                    }

                    return; 
                }else{
                    tentative++;
                    clients[i].loginAttempts++;
                    printf("\nIdentifiants incorrects. Tentative %d/3.\n", tentative);

                    if(clients[i].loginAttempts == 3){
                        clients[i].locked = 1;
                        clients[i].lock_time = time(NULL);
                        printf("\nMantant votre compte est bloque pour 30 minutes.\n");
                    }
                }
    
            }
        }
    } while (tentative < 3);
}
void supprimer_reclamation_24h(){
    int id_supprimer;
    printf("Enter ID of reclamation to delete: ");
    scanf("%d", &id_supprimer);

    for(int i = 0; i < reclamation_count; i++){
        if(reclamations[i].id == id_supprimer){
            time_t current_time = time(NULL);
            double check_def_time = difftime(current_time, reclamations[i].creation_time);

            
            if(check_def_time > 60){
                printf("Impossible de supprimer la reclamation. Elle depasse 24H.\n");// (86400 s)
                return;
            }

            for (int j = i; j < reclamation_count - 1; j++) {
                reclamations[j] = reclamations[j+1];
            }
            reclamation_count--;
            printf("Reclamation Bien Supprimer.\n");
            return;
        }
    }
    printf("Reclamation ID non trouve.\n");
}
void afficher_reclamation() {
    int id_search;
    printf("Saisir l'ID de la reclamation : ");
    scanf("%d", &id_search);
    if (reclamation_count == 0) {
        printf("Aucune reclamation disponible.\n");
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

    printf("Reclamation avec l'ID %d non trouvee.\n", id_search);
}
void supprimer_reclamation(){//adimn - agent
    int id_supprimer;
    printf("Enter ID of reclamation to delete: ");
    scanf("%d", &id_supprimer);

    for (int i = 0; i < reclamation_count; i++) {
        if (reclamations[i].id == id_supprimer) {
            for (int j = i; j < reclamation_count - 1; j++) {
                reclamations[j] = reclamations[j + 1];
            }
            reclamation_count--;
            printf("Reclamation Bien Supprimer.\n");
            return;
        }
    }
    printf("Id de Reclamation Pas Trouver.\n");
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
void afficher_tout_reclamations(){//admin-agent
    int trouver = 0;
    printf("\nVoila Tout Les Reclamations : \n");
    if (reclamation_count == 0) {
        printf("Aucune reclamation disponible.\n");
        return;
    }
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
    printf("Saisir l'ID de la reclamation : ");
    scanf("%d", &id_search);
    printf("Saisir le nouveau statut [0: en cours, 1: en attente, 2: resolu]: ");
    scanf("%d", &statut_change);

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
            printf("Statut Bien Modifie.\n");
            return;
        }
    }
    printf("\nAucun Reclamation avec l'ID %d !!\n", id_search);
}
void recherche_par_status(){
    if(reclamation_count==0){
        printf("Aucune reclamation disponible.\n");
        return;
    }
    int statut_recherche;
    printf("Saisir le statut recherche [0: en cours, 1: en attente, 2: resolu]: ");
    scanf("%d", &statut_recherche);
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
            printf("Choix Invalide.\n");
            return;
    }
    int trouver = 0;
    for(int i = 0; i < reclamation_count; i++){
        if(strcmp(reclamations[i].status,statut_str)==0){
            printf("\n#####################\n");
            printf("ID: %d\nMotif: %s\nDescription: %s\nCategorie: %s\nStatut: %s\nDate: %s\n\n",
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
        printf("Aucune reclamation disponible.\n");
        return;
    }
    int id_recherche;
    int trouve=0;
    printf("Saisir l'ID de la reclamation : ");
    scanf("%d", &id_recherche);
    for (int i = 0; i < reclamation_count; i++) {
        if (reclamations[i].id == id_recherche) {
            printf("Saisir la nouvelle description : ");
            getchar();
            fgets(reclamations[i].description, sizeof(reclamations[i].description), stdin);
            printf("Saisir le nouveau motif : ");
            fgets(reclamations[i].motif, sizeof(reclamations[i].motif), stdin);
            printf("Saisir la nouvelle categorie : ");
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
    printf("Saisir le Nome d'utilisateur : ");
    scanf("%s", username_search);
    //fgets(username_search, sizeof(username_search), stdin);
    //username_search[strcspn(username_search, "\n")] = '\0';
    for (int i = 0; i < clients_count; i++) {
        if(strcmp(clients[i].username, username_search) == 0){
            int role_choice;
            printf("Saisir le Nouveau Role [Administrateur: 0, Agent: 1, Client: 2]: ");
            scanf("%d", &role_choice);

            switch (role_choice) {
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
                    return;
            }

            printf("\nLe role de l'utilisateur %s a ete bien modifie en %s.\n", username_search, clients[i].role);
            return;
        }
    }

    // If the user was not found
    printf("\nAucun Nome d'utilisateur Avec : %s !!\n", username_search);
}
int definir_priorite(char description[]) {
    if (strstr(description, "urgent") || strstr(description, "critique"))
        return 3;  
    else if (strstr(description, "important") || strstr(description, "presse"))
        return 2;  
    return 1;  
}
void afficher_reclamations_par_priorite(){
    if (reclamation_count == 0) {
        printf("Aucune reclamation disponible.\n");
        return;
    }
    int indices[reclamation_count];  
    for (int i = 0; i < reclamation_count; i++){
        indices[i] = i;
    }
    for (int i = 0; i < reclamation_count - 1; i++){
        for (int j = 0; j < reclamation_count - i - 1; j++) {
            if (definir_priorite(reclamations[indices[j]].description) < definir_priorite(reclamations[indices[j + 1]].description)) {
                
                int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }


    printf("\nReclamations par Priorite :\n");
    for(int i = 0; i < reclamation_count; i++){
        int index = indices[i];
        printf("\n###############\n");
        printf("ID: %d\nMotif: %s\nDescription: %s\nCategorie: %s\nStatut: %s\nDate: %s\nPriorite: %d\n\n",
               reclamations[index].id, reclamations[index].motif, reclamations[index].description,
               reclamations[index].category, reclamations[index].status, reclamations[index].date,
               definir_priorite(reclamations[index].description));
    }
}
void taux_resolution(){
    if (reclamation_count == 0) {
        printf("Aucune reclamation disponible.\n");
        return;
    }

    int resolu_taux = 0;
    for (int i = 0; i < reclamation_count; i++) {
        if (strcmp(reclamations[i].status, "resolu") == 0) {
            resolu_taux += 1;
        }
    }
    float result = (float)resolu_taux / reclamation_count * 100;
    printf("Le Taux de Resolution: %.2f%%\n", result); 
}
void rapport_de_jour(){
    int nombre_en_coures = 0;
    int nombre_resolues = 0;
    int nombre_en_attente = 0;

    printf("### Rapport Journalier des Reclamations ###\n\n");
    printf("###########################################");
    
    printf("\nReclamations resolues aujourd'hui :\n");
    for (int i = 0; i < reclamation_count; i++) {
        if (strcmp(reclamations[i].status, "resolu") == 0) {
            // Afficher les reclamations resolues
            printf("ID: %d, Motif: %s, Date Traitement: %s\n", reclamations[i].id, reclamations[i].description, reclamations[i].date);
            nombre_resolues++;
        }
    }

    if (nombre_resolues == 0) {
        printf("Aucune reclamation resolue aujourd'hui.\n");
    }
   
    printf("\nReclamations en Traitement aujourd'hui :\n");
    for(int i = 0; i < reclamation_count; i++){
        if (strcmp(reclamations[i].status, "en attente") == 0) {
            // Afficher les reclamations resolues
            printf("ID: %d, Motif: %s, Date Traitement: %s\n", reclamations[i].id, reclamations[i].description, reclamations[i].date);
            nombre_en_attente++;
        }
    }

    if(nombre_en_attente == 0){
        printf("Aucune reclamation en attente aujourd'hui.\n");
    }

    printf("\nNouvelles reclamations en cours :\n");
    for(int i = 0; i < reclamation_count; i++){
        if (strcmp(reclamations[i].status, "en cours") == 0) {
            // Afficher les nouvelles reclamations non encore traitees
            printf("ID: %d, Motif: %s, Date Soumission: %s\n", reclamations[i].id, reclamations[i].description, reclamations[i].date);
            nombre_en_coures++;
        }
    }

    if(nombre_en_coures == 0){
        printf("Aucune en cours traiter reclamation aujourd'hui.\n");
    }
    printf("\nNombre total de reclamations resolues : %d\n", nombre_resolues);
    printf("Nombre total de nouvelles reclamations : %d\n", nombre_en_coures);
    printf("=== Fin du rapport ===\n");
}
void ajouter_reclamation(char client_username[]) {
    Reclamations nouveau_reclamation;
    nouveau_reclamation.creation_time = time(NULL);
    nouveau_reclamation.id = reclamation_count + 1;
    get_current_date(nouveau_reclamation.date);  
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
void afficher_reclamations_client(char client_username[]) {
    int found = 0;
    printf("\nReclamations de %s :\n", client_username);
    for (int i = 0; i < reclamation_count; i++) {
        if (strcmp(reclamations[i].client_username, client_username) == 0) {
            printf("\n##################");
            printf("ID: %d\nMotif: %s\nDescription: %s\nCategorie: %s\nStatus: %s\nDate: %s\n",
                   reclamations[i].id, reclamations[i].motif, reclamations[i].description,
                   reclamations[i].category, reclamations[i].status, reclamations[i].date);
            found = 1;
        }
    }

    if (!found) {
        printf("Aucune reclamation trouvee pour ce client.\n");
    }
}
void calculer_temps_moyen_traitement() {
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
        printf("Le temps moyen de traitement des reclamations resolues est de %.2f min .\n", average_time/60);
    } else {
        printf("Aucune reclamation resolue pour calculer le temps moyen de traitement.\n");
    }
}



