#include "game.h"

void drawHeader();
void drawVaisseau();
void drawAsteroid();
void initTabAsteroid();
int num_alea(int nmax);
void moveAsteroid();
void loopAsteroid();
void remiseAZero();
void collision();
void changeVie();
void clear();
void moveVaisseau();
void gameOver();

//position du carre dessiné dans drawGame()
int vaisseau_x = 11;
int vaisseau_y = 63;
int compteurloop=0;
int compteurasteroid=0;
int vie=3;
int shield=1;

struct rgb tab_display[64][32];

void init_game(){
    //mettre votre code d'initialisation ici
    srand(time(NULL));
    initTabAsteroid();
}

void drawGame(){
    clear();
    drawAsteroid();
    drawVaisseau();
    drawHeader();
}

void gameLoop() {
    int programLaunched = 1;
    while (programLaunched == 1) {
        // Boucle pour garder le programme ouvert
        drawGame();
        moveVaisseau();
        moveAsteroid();
        collision();
        remiseAZero();
        loopAsteroid();
        changeVie();  
    }
}

void drawHeader(){
    for (int x=0; x<WINDOW_WIDTH; x++){ //drawLine(0,7,32,7)  // Ligne horizontale du header (cyan)
        tab_display[x][7].r = 27;
        tab_display[x][7].g = 215;
        tab_display[x][7].b = 218;
        tab_display[x][7].a = 200;
    }
    for (int y=0;y<7;y++){ //drawLine(17,0,17,7);  // Ligne verticale du header (cyan)
        tab_display[17][y].r = 27;
        tab_display[17][y].g = 215;
        tab_display[17][y].b = 218;
        tab_display[17][y].a = 200;
    }
    if (shield==1){
        for (int y = 0; y < 6; y++){  //changeColor(255,0,0); drawRect(19,0,13,6);   // Bouclier en gris
            for (int x = 19; x < WINDOW_WIDTH; x++){
                if (y==0 || y==5 || x==19 || x==WINDOW_WIDTH-1){
                    tab_display[x][y].r = 0;
                    tab_display[x][y].g = 24;
                    tab_display[x][y].b = 248;
                    tab_display[x][y].a = 200;
                }
            }
        }
    }
}

void changeVie(){
    switch(vie){
        case 0:
            printf("vous n avez plus de vie");
            clear();
            gameOver();
            sleep(10);
            break;
        case 1:
            for (int y = 1; y < 5; y++){  //changeColor(0,255,0) drawRect(20,1,11,4)    // 1 VIES 
                tab_display[20][y].r = 255;
                tab_display[20][y].g = 0;
                tab_display[20][y].b = 0;
                tab_display[20][y].a = 200;
            }
            break;
        case 2:
            for (int y = 1; y < 5; y++){  //changeColor(0,255,0) drawRect(20,1,11,4)    // 2 VIES
                for (int x = 20; x < 26; x++){
                    tab_display[x][y].r = 255;
                    tab_display[x][y].g = 176;
                    tab_display[x][y].b = 0;
                    tab_display[x][y].a = 200;
                }
            }
            break;
        case 3:
            for (int y = 1; y < 5; y++){  //changeColor(0,255,0) drawRect(20,1,11,4)    // 3 VIES 
                for (int x = 20; x < WINDOW_WIDTH-1; x++){
                    tab_display[x][y].r = 0;
                    tab_display[x][y].g = 255;
                    tab_display[x][y].b = 0;
                    tab_display[x][y].a = 200;
                }
            }    
            break;
        default:
            break;
    }
}

void drawVaisseau(){
    int i=0;
    int j=0;
    for (int y = 22; y < WINDOW_HEIGHT; y++){  //changeColor(0,255,0) drawRect(20,1,11,4)
        for (int x = vaisseau_x; x < vaisseau_x+TAILLE_VAISSEAU; x++){
            if(((i==0 || i==1) && j==4) || ((i==2 || i==3 || i==4) && (j==3 || j==4 || j==5)) || ((i==5 || i==6 || i==7) && (j>0 && j<8)) || (i==8)){
                tab_display[x][y].r = 255;
                tab_display[x][y].g = 255;
                tab_display[x][y].b = 255;
                tab_display[x][y].a = 255;
            }j++;

        }
        i++;
        j=0;
    }  
}

struct Asteroid{
    int taille;
    int pos_x;
    int pos_x2;
    int pos_y;
    int pos_y2;
    int etat; // 0 = hors de l'ecran et 1 = a l'ecran
    int vitesse;
};

struct Asteroid tabAsteroid[NBRASTEROID];

void initTabAsteroid(){
    int i;
    for (i=0;i<NBRASTEROID;i++){
        tabAsteroid[i].taille=4;
        tabAsteroid[i].pos_x=num_alea(WINDOW_WIDTH-tabAsteroid[i].taille);
        tabAsteroid[i].pos_y=8;
        tabAsteroid[i].pos_y2=tabAsteroid[i].pos_y+tabAsteroid[i].taille;
        tabAsteroid[i].pos_x2=tabAsteroid[i].pos_x+tabAsteroid[i].taille;
        tabAsteroid[i].etat=0;
        tabAsteroid[i].vitesse=7; // 1 etant le plus rapide, 10 le plus lent
    }
}

void drawAsteroid(){
    for (int i=0;i<NBRASTEROID;i++){
        if (tabAsteroid[i].etat==1){
            //drawSquare(tabAsteroid[i].pos_x,tabAsteroid[i].pos_y,tabAsteroid[i].taille);
            for (int y = tabAsteroid[i].pos_y; y < tabAsteroid[i].pos_y2; y++){
                for (int x = tabAsteroid[i].pos_x; x < tabAsteroid[i].pos_x2; x++){
                    tab_display[x][y].r = 162;
                    tab_display[x][y].g = 80;
                    tab_display[x][y].b = 7;
                    tab_display[x][y].a = 200;
                }
            }
        }
    }
}

void moveAsteroid(){
    for (int i=0;i<NBRASTEROID;i++){
        if (tabAsteroid[i].etat==1){
            if (compteurloop%tabAsteroid[i].vitesse==1){
                tabAsteroid[i].pos_y++;
                tabAsteroid[i].pos_y2++;
            }
        }
        if (tabAsteroid[i].pos_x2>WINDOW_HEIGHT){ //Si l'asteroid sort de l'ecran en bas
            tabAsteroid[i].etat=0;
        }
    }
}

int num_alea(int nmax){
    int nbr_alea = rand() % nmax;
    return nbr_alea;
}

void loopAsteroid(){ // Pour faire apparaitre un asteroid toutes les 200 boucles
    compteurloop++; //Etat de la boucle
    if (compteurloop%200==1){ // Ajouter une variable a la place de 200
        tabAsteroid[compteurasteroid].etat=1; // On passe l'asteroid actuel a l'etat actif (1)
        compteurasteroid++; // on incremente le numero de l'asteroid
        if (compteurasteroid>NBRASTEROID){ // Nous avons seulement 10 asteroid donc on remet à 0 si on depasse le 10eme 
            compteurasteroid=0;
        }
    }
    if (compteurloop%2000==1){
        for (int i=0;i<NBRASTEROID;i++){
            if (tabAsteroid[i].vitesse>1){
                tabAsteroid[i].vitesse--;
            }
        }
    }
}

void collision(){
    int condition=0;
    for (int i=0;i<NBRASTEROID;i++){
        for (int j=0;j<tabAsteroid[i].taille;j++){
            if (tab_display[tabAsteroid[i].pos_x+j][tabAsteroid[i].pos_y2].a == 255){ // Si l'asteroid touche un pixel qui a un alpha de 255 (nous n'avons que le vaisseau qui a un alpha de 255 dans notre code)
                condition=1;
            }
        }
        if (condition == 1){
            if (shield==1){
                shield--;
            }else{
                vie--;
            }
            tabAsteroid[i].etat=0;
        }
    }
}

void remiseAZero(){
    for (int i=0;i<NBRASTEROID;i++){
        if (tabAsteroid[i].etat==0){
            tabAsteroid[i].pos_y=8;
            tabAsteroid[i].pos_y2=tabAsteroid[i].pos_y+tabAsteroid[i].taille;
            tabAsteroid[i].pos_x=num_alea(WINDOW_WIDTH-tabAsteroid[i].taille);
            tabAsteroid[i].pos_x2=tabAsteroid[i].pos_x+tabAsteroid[i].taille;
            //Ajouter un random pour la vitesse
        }
    }
}

void clear(){
    for(int x=0;x<WINDOW_WIDTH;x++){
        for (int y=0;y<WINDOW_HEIGHT;y++){
            tab_display[x][y].r = 0;
            tab_display[x][y].g = 0;
            tab_display[x][y].b = 0;
            tab_display[x][y].a = 0;
        }
    }
}

void moveVaisseau(int pas){
    vaisseau_x=vaisseau_x+pas;
}

void gameOver(){
    for(int x=6;x<26;x++){
        for (int y=25;y<37;y++){
            if (((y==25) && (x==6 || x==7 || x==8 || x==9 || x==11 || x==12 || x==13 || x==14 || x==16 || x==17 || x==18 || x==19 || x==20 || x==22 || x==23 || x==24 || x==25))
            || ((y==26) && (x==6 || x==11 || x==14 || x==16 || x==17 || x==19 || x==20 || x==22))
            || ((y==27) && (x==6 || x==8 || x==9 || x==11 || x==12 || x==13 || x==14 || x==16 || x==18 || x==20 || x==22 || x==23 || x==24 || x==25))
            || ((y==28) && (x==6 || x==9 || x==11 || x==14 || x==16 || x==20 || x==22))
            || ((y==29) && (x==6 || x==7 || x==8 || x==9 || x==11 || x==14 || x==16 || x==20 || x==22 || x==23 || x==24 || x==25))
            || ((y==32) && (x==6 || x==7 || x==8 || x==9 || x==11 || x==15 || x==17 || x==18 || x==19 || x==20 || x==22 || x==23 || x==24 || x==25))
            || ((y==33) && (x==6 || x==9 || x==11 || x==15 || x==17 || x==22 || x==25))
            || ((y==34) && (x==6 || x==9 || x==12 || x==14 || x==17 || x==18 || x==19 || x==20 || x==22 || x==23 || x==24 || x==25))
            || ((y==35) && (x==6 || x==9 || x==12 || x==14 || x==17 || x==22 || x==24))
            || ((y==36) && (x==6 || x==7 || x==8 || x==9 || x==13 || x==17 || x==18 || x==19 || x==20 || x==22 || x==25))){
                tab_display[x][y].r = 255;
                tab_display[x][y].g = 8;
                tab_display[x][y].b = 244;
                tab_display[x][y].a = 200;
            }
        }
    }
}