#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define WINDOW_WIDTH 32
#define WINDOW_HEIGHT 64
#define FPS 60
#define NBRASTEROID 10
#define TAILLE_VAISSEAU 9

void drawHeader();
void drawVaisseau();
void drawAsteroid();
void initTabAsteroid();
int num_alea();
void moveAsteroid();
void loop();
void remiseAZero();
void collision();
void changeVie();
void clear();

//position du carre dessiné dans drawGame()
int vaisseau_x = 11;
int vaisseau_y = 63;
int compteurloop=0;
int compteurasteroid=0;
int vie=3;

struct rgb {
    int r, g, b, a;
};

struct rgb tab_display[64][32];

void init_game(){
    //mettre votre code d'initialisation ici
    initTabAsteroid();
}

void drawGame(){
    /* Ici je dessine mon jeu
     * exemple position x, y modifiés dans KeyPressed() et utilisés pour
     * pouvoir deplacer la figure à chaque boucle de gameLoop()
     */
    clear();
    drawAsteroid();
    moveAsteroid();
    drawVaisseau();
    collision();
    drawHeader();
    remiseAZero();
    loop();
    usleep(1000000 / FPS); // 60 images par seconde | 1000000 = 1 seconde
}
//void KeyPressed(SDL_Keycode touche){
    /** @brief event.key.keysym.sym renvoi la touche appuyé
     *
     */
    /*switch (touche) {
        // Voir doc SDL_Keycode pour plus de touches https://wiki.libsdl.org/SDL_Keycode
        // ici exemple ou appuyer sur les touches Q | D modifie x (position du carré dans drawGame())
        case SDLK_q:
    //drawSquare(vaisseau_x,vaisseau_y,100); SI ÇA MARCHE PAS C'EST A CAUSE D'ICI
            //touche q appuyé
            if (vaisseau_x>0){
                vaisseau_x--;
            }
            break;
        case SDLK_d:
            //touche d appuyé
            if (vaisseau_x<WINDOW_WIDTH-TAILLE_VAISSEAU){
                vaisseau_x++;
            }
            break;
        case SDLK_ESCAPE:
            freeAndTerminate();
            break;
        default:
            break;
    }
}*/

void gameLoop() {
    int programLaunched = 1;
    while (programLaunched == 1) {
        // Boucle pour garder le programme ouvert
        drawGame();
    }
}

int main(){
    /** @description 3 fonctions dans le main qui permettent de créer l'application et la maintenir ouverte :
     *  init(...) : initialiser la SDL/ fenêtre
     *  gameLoop() : boucle de jeu dans laquelle l'application reste ouverte
     *  clear() : remet a 0 l'ecran pour l'eteindre
     */
    srand(time(NULL));
    init_game();
    gameLoop();
    printf("Fin du programme\n");
    clear();
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
    for (int y = 0; y < 6; y++){  //changeColor(255,0,0); drawRect(19,0,13,6);   // Bouclier en gris
        for (int x = 19; x < WINDOW_WIDTH; x++){
            if (y==0 || y==6 || x==19 || x==WINDOW_WIDTH){
                tab_display[x][y].r = 212;
                tab_display[x][y].g = 212;
                tab_display[x][y].b = 212;
                tab_display[x][y].a = 200;
            }
        }
    }
    changeVie();  
}

void changeVie(){
    switch(vie){
        case 0:
            printf("vous n avez plus de vie");
            clear();
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
        tabAsteroid[i].vitesse=5; // 1 etant le plus rapide, 10 le plus lent
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
        if (tabAsteroid[i].pos_y>WINDOW_HEIGHT){ //Si l'asteroid sort de l'ecran en bas
            tabAsteroid[i].etat=0;
        }
    }
}

int num_alea(int nmax){
    int nbr_alea = rand() % nmax;
    return nbr_alea;
}

void loop(){ // Pour faire apparaitre un asteroid toutes les 200 boucles
    compteurloop++; //Etat de la boucle
    if (compteurloop%200==1){ // Ajouter une variable a la place de 200
        tabAsteroid[compteurasteroid].etat=1; // On passe l'asteroid actuel a l'etat actif (1)
        compteurasteroid++; // on incremente le numero de l'asteroid
        if (compteurasteroid>NBRASTEROID){ // Nous avons seulement 10 asteroid donc on remet à 0 si on depasse le 10eme 
            compteurasteroid=0;
        }
    }
}

void collision(){
    int condition=0;
    for (int i=0;i<NBRASTEROID;i++){
        for (int j=0;j<tabAsteroid[i].taille;j++){
            if (tab_display[tabAsteroid[i].pos_x2][tabAsteroid[i].pos_y+j].a == 255){ // Si l'asteroid touche un pixel qui a un alpha de 255 (nous n'avons que le vaisseau qui a un alpha de 255 dans notre code)
                condition=1;
            }
        }
        if (condition == 1){
            vie--;
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