#include "game.h"
 
void drawHeader();
void drawVaisseau(int rouge, int vert, int bleu);
void drawAsteroid();
void drawShieldRevive();
void initTabAsteroid();
void initShieldRevive();
int num_alea(int nmax);
void moveAsteroid();
void loopAsteroid();
void remiseAZero();
void collision();
void changeVie();
void clear();
void moveVaisseau();
void gameOver();
void sevenDigit();
void numToPixel();
void afficheScore();
 
//position du carre dessiné dans drawGame()
int vaisseau_x = 11;
int vaisseau_y = 63;
int compteurloop=0;
int compteurasteroid=0;
int vie=3;
int shield=1;
int score=0;
int game=1;
int vaisseau_rouge=255; //taux de rouge du vaisseau (0-255)
int vaisseau_vert=255; // taux de vert
int vaisseau_bleu=255; // taux de bleu
 
struct rgb tab_display[32][64];
 
void init_game(){
    //mettre votre code d'initialisation ici
    srand(time(NULL));
    initTabAsteroid();
    initShieldRevive();
}

void updateDisplay() {
    for(int x = 0; x < height; x++) {
        for(int y = 0; y < width; y++) {
            set_pixel(x, y, tab_display[x][y].r, tab_display[x][y].g, tab_display[x][y].b);
        }
    }
    actualize();
}
 
void drawGame(){
    clear();
	changeVie();
    drawAsteroid();
    drawShieldRevive();
    drawVaisseau(vaisseau_rouge,vaisseau_vert,vaisseau_bleu);
    drawHeader();
 
    for(int x = 0; x < height; x++) {
		for(int y = 0; y < width; y++) {
			set_pixel(x, y, tab_display[x][y].r, tab_display[x][y].g, tab_display[x][y].b);
		}
	}
	actualize();
}
 
void gameLoop() {
    if (game==1){
        drawGame();
        moveAsteroid();
        moveBonus();
        collision();
        remiseAZero();
        loopAsteroid();
    }else{
        clear();
        gameOver();
    }
    updateDisplay();
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
        for (int y = 0; y < 7; y++){  //changeColor(255,0,0); drawRect(19,0,13,6);   // Bouclier en bleu 
            for (int x = 18; x < WINDOW_WIDTH; x++){
                if (y==0 || y==6 || x==18 || x==WINDOW_WIDTH-1){
                    tab_display[x][y].r = 0;
                    tab_display[x][y].g = 24;
                    tab_display[x][y].b = 248;
                    tab_display[x][y].a = 200;
                }
            }
        }
    }
    afficheScore();
}

void afficheScore(){
    int unit=score%10;
    int dizaine=(score/10)%10;
    int centaine=(score/100)%10;
    int millier=(score/1000)%10;
    numToPixel(unit,0);
    numToPixel(dizaine,1);
    numToPixel(centaine,2);
    numToPixel(millier,3);
}

void changeVie(){
    switch(vie){
        case 0:
            printf("vous n avez plus de vie\n");
            game=0;
            break;
        case 1:
            for (int y = 1; y < 6; y++){  //changeColor(0,255,0) drawRect(20,1,11,4)    // 1 VIES 
                tab_display[20][y].r = 255;
                tab_display[20][y].g = 0;
                tab_display[20][y].b = 0;
                tab_display[20][y].a = 200;
                tab_display[19][y].r = 255;
                tab_display[19][y].g = 0;
                tab_display[19][y].b = 0;
                tab_display[19][y].a = 200;
            }
            break;
        case 2:
            for (int y = 1; y < 6; y++){  //changeColor(0,255,0) drawRect(20,1,11,4)    // 2 VIES
                for (int x = 19; x < 26; x++){
                    tab_display[x][y].r = 255;
                    tab_display[x][y].g = 176;
                    tab_display[x][y].b = 0;
                    tab_display[x][y].a = 200;
                }
            }
            break;
        case 3:
            for (int y = 1; y < 6; y++){  //changeColor(0,255,0) drawRect(20,1,11,4)    // 3 VIES 
                for (int x = 19; x < height-1; x++){
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

void numToPixel(int chiffre,int grandeur){
    switch(grandeur){
        case 0: // Unite
            switch(chiffre){
                case 0:
                    sevenDigit(1);
                    sevenDigit(2);
                    sevenDigit(3);
                    sevenDigit(5);
                    sevenDigit(6);
                    sevenDigit(7);
                    break;
                case 1:
                    sevenDigit(3);
                    sevenDigit(6);
                    break;
                case 2:
                    sevenDigit(1);
                    sevenDigit(3);
                    sevenDigit(4);
                    sevenDigit(5);
                    sevenDigit(7);
                    break;
                case 3:
                    sevenDigit(1);
                    sevenDigit(3);
                    sevenDigit(4);
                    sevenDigit(6);
                    sevenDigit(7);
                    break;
                case 4:
                    sevenDigit(2);
                    sevenDigit(3);
                    sevenDigit(4);
                    sevenDigit(6);
                    break;
                case 5:
                    sevenDigit(1);
                    sevenDigit(2);
                    sevenDigit(4);
                    sevenDigit(6);
                    sevenDigit(7);
                    break;
                case 6 :
                    sevenDigit(1);
                    sevenDigit(2);
                    sevenDigit(4);
                    sevenDigit(5);
                    sevenDigit(6);
                    sevenDigit(7);
                    break;
                case 7 :
                    sevenDigit(1);
                    sevenDigit(3);
                    sevenDigit(6);
                    break;
                case 8 :
                    sevenDigit(1);
                    sevenDigit(2);
                    sevenDigit(3);
                    sevenDigit(4);
                    sevenDigit(5);
                    sevenDigit(6);
                    sevenDigit(7);
                    break;
                case 9 :
                    sevenDigit(1);
                    sevenDigit(2);
                    sevenDigit(3);
                    sevenDigit(4);
                    sevenDigit(6);
                    sevenDigit(7);
                    break;
                default:
                    break;
            }
            break;
        case 1: // Dizaine
            switch(chiffre){
                case 0:
                    sevenDigit(11);
                    sevenDigit(12);
                    sevenDigit(13);
                    sevenDigit(15);
                    sevenDigit(16);
                    sevenDigit(17);
                    break;
                case 1:
                    sevenDigit(13);
                    sevenDigit(16);
                    break;
                case 2:
                    sevenDigit(11);
                    sevenDigit(13);
                    sevenDigit(14);
                    sevenDigit(15);
                    sevenDigit(17);
                    break;
                case 3:
                    sevenDigit(11);
                    sevenDigit(13);
                    sevenDigit(14);
                    sevenDigit(16);
                    sevenDigit(17);
                    break;
                case 4:
                    sevenDigit(12);
                    sevenDigit(13);
                    sevenDigit(14);
                    sevenDigit(16);
                    break;
                case 5:
                    sevenDigit(11);
                    sevenDigit(12);
                    sevenDigit(14);
                    sevenDigit(16);
                    sevenDigit(17);
                    break;
                case 6 :
                    sevenDigit(11);
                    sevenDigit(12);
                    sevenDigit(14);
                    sevenDigit(15);
                    sevenDigit(16);
                    sevenDigit(17);
                    break;
                case 7 :
                    sevenDigit(11);
                    sevenDigit(13);
                    sevenDigit(16);
                    break;
                case 8 :
                    sevenDigit(11);
                    sevenDigit(12);
                    sevenDigit(13);
                    sevenDigit(14);
                    sevenDigit(15);
                    sevenDigit(16);
                    sevenDigit(17);
                    break;
                case 9 :
                    sevenDigit(11);
                    sevenDigit(12);
                    sevenDigit(13);
                    sevenDigit(14);
                    sevenDigit(16);
                    sevenDigit(17);
                    break;
                default:
                    break;
            }
            break;
        case 2: //Centaine
            switch(chiffre){
                case 0:
                    sevenDigit(21);
                    sevenDigit(22);
                    sevenDigit(23);
                    sevenDigit(25);
                    sevenDigit(26);
                    sevenDigit(27);
                    break;
                case 1:
                    sevenDigit(23);
                    sevenDigit(26);
                    break;
                case 2:
                    sevenDigit(21);
                    sevenDigit(23);
                    sevenDigit(24);
                    sevenDigit(25);
                    sevenDigit(27);
                    break;
                case 3:
                    sevenDigit(21);
                    sevenDigit(23);
                    sevenDigit(24);
                    sevenDigit(26);
                    sevenDigit(27);
                    break;
                case 4:
                    sevenDigit(22);
                    sevenDigit(23);
                    sevenDigit(24);
                    sevenDigit(26);
                    break;
                case 5:
                    sevenDigit(21);
                    sevenDigit(22);
                    sevenDigit(24);
                    sevenDigit(26);
                    sevenDigit(27);
                    break;
                case 6 :
                    sevenDigit(21);
                    sevenDigit(22);
                    sevenDigit(24);
                    sevenDigit(25);
                    sevenDigit(26);
                    sevenDigit(27);
                    break;
                case 7 :
                    sevenDigit(21);
                    sevenDigit(23);
                    sevenDigit(26);
                    break;
                case 8 :
                    sevenDigit(21);
                    sevenDigit(22);
                    sevenDigit(23);
                    sevenDigit(24);
                    sevenDigit(25);
                    sevenDigit(26);
                    sevenDigit(27);
                    break;
                case 9 :
                    sevenDigit(21);
                    sevenDigit(22);
                    sevenDigit(23);
                    sevenDigit(24);
                    sevenDigit(26);
                    sevenDigit(27);
                    break;
                default:
                    break;
            }
            break;
        case 3: // Milliers
            switch(chiffre){
                case 0:
                    sevenDigit(31);
                    sevenDigit(32);
                    sevenDigit(33);
                    sevenDigit(35);
                    sevenDigit(36);
                    sevenDigit(37);
                    break;
                case 1:
                    sevenDigit(33);
                    sevenDigit(36);
                    break;
                case 2:
                    sevenDigit(31);
                    sevenDigit(33);
                    sevenDigit(34);
                    sevenDigit(35);
                    sevenDigit(37);
                    break;
                case 3:
                    sevenDigit(31);
                    sevenDigit(33);
                    sevenDigit(34);
                    sevenDigit(36);
                    sevenDigit(37);
                    break;
                case 4:
                    sevenDigit(32);
                    sevenDigit(33);
                    sevenDigit(34);
                    sevenDigit(36);
                    break;
                case 5:
                    sevenDigit(31);
                    sevenDigit(32);
                    sevenDigit(34);
                    sevenDigit(36);
                    sevenDigit(37);
                    break;
                case 6 :
                    sevenDigit(31);
                    sevenDigit(32);
                    sevenDigit(34);
                    sevenDigit(35);
                    sevenDigit(36);
                    sevenDigit(37);
                    break;
                case 7 :
                    sevenDigit(31);
                    sevenDigit(33);
                    sevenDigit(36);
                    break;
                case 8 :
                    sevenDigit(31);
                    sevenDigit(32);
                    sevenDigit(33);
                    sevenDigit(34);
                    sevenDigit(35);
                    sevenDigit(36);
                    sevenDigit(37);
                    break;
                case 9 :
                    sevenDigit(31);
                    sevenDigit(32);
                    sevenDigit(33);
                    sevenDigit(34);
                    sevenDigit(36);
                    sevenDigit(37);
                    break;
                default :
                    break;
            }
            break;
        default:
            break;
        
    }
}
 
void drawVaisseau(int rouge, int vert, int bleu){
    int i=0;
    int j=0;
    for (int y = 55; y < WINDOW_HEIGHT; y++){  //changeColor(0,255,0) drawRect(20,1,11,4)
        for (int x = vaisseau_x; x < vaisseau_x+TAILLE_VAISSEAU; x++){
            if(((i==0 || i==1) && j==4) || ((i==2 || i==3 || i==4) && (j==3 || j==4 || j==5)) || ((i==5 || i==6 || i==7) && (j>0 && j<8)) || (i==8)){
                tab_display[x][y].r = rouge;
                tab_display[x][y].g = vert;
                tab_display[x][y].b = bleu;
                tab_display[x][y].a = 255;
            }j++;
 
        }
        i++;
        j=0;
    }  
}

struct Bonus{
    int pos_x;
    int pos_y;
    int pos_x2;
    int pos_y2;
    int etat;
} 

struct Bonus shieldRevive;

void initShieldRevive(){
    shieldRevive.pos_x=num_alea(WINDOW_HEIGHT-5);
    shieldRevive.pos_y=8;
    shieldRevive.pos_x2=shieldRevive.pos_x+5;
    shieldRevive.pos_y2=shieldRevive.pos_y+4;
    shieldRevive.etat=0;
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
        tabAsteroid[i].vitesse=10; // 1 etant le plus rapide, 9999 le plus lent
    }
}
 
void drawAsteroid(){
    for (int i=0;i<NBRASTEROID;i++){
        if (tabAsteroid[i].etat==1){
            //drawSquare(tabAsteroid[i].pos_x,tabAsteroid[i].pos_y,tabAsteroid[i].taille);
            for (int y = tabAsteroid[i].pos_y; y < tabAsteroid[i].pos_y2; y++){
                for (int x = tabAsteroid[i].pos_x; x < tabAsteroid[i].pos_x2; x++){
                    if ((y==tabAsteroid[i].pos_y+1 || y==tabAsteroid[i].pos_y+2) && (x==tabAsteroid[i].pos_x+1 || x==tabAsteroid[i].pos_x+2)){
                        tab_display[x][y].r = 97;
                        tab_display[x][y].g = 32;
                        tab_display[x][y].b = 5;
                        tab_display[x][y].a = 200;
                    }else{
                        if (num_alea(5)%5==0){
                            tab_display[x][y].r = 200 + num_alea(56);
                            tab_display[x][y].g = num_alea(256);
                            tab_display[x][y].b = num_alea(256);
                            tab_display[x][y].a = 200;
                        }
                    }
                }
            }
        }
    }
}
 
void moveAsteroid(){
    for (int i=0;i<NBRASTEROID;i++){
        if (tabAsteroid[i].etat==1){
            if (compteurloop%tabAsteroid[i].vitesse==1){ // Il descend d'un pixel sur vitesse de l'asteroid (10 en debut de partie)
                tabAsteroid[i].pos_y++;
                tabAsteroid[i].pos_y2++;
            }
        }
        if (tabAsteroid[i].pos_y2>WINDOW_HEIGHT){ //Si l'asteroid sort de l'ecran en bas
            tabAsteroid[i].etat=0;
        }
    }
}

void moveBonus(){
    if (shieldRevive.etat==1){
        if (compteurloop%(tabAsteroid[0].vitesse+3)==1){ // La vitesse du bonus depend de celle des asteroides
            shieldRevive.pos_y++;
            shieldRevive.pos_y2++;
        }
    }
    if (shieldRevive.pos_y2>WINDOW_HEIGHT){ //Si l'asteroid sort de l'ecran en bas
        shieldRevive.etat=0;
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
    if (compteurloop%2000==1999){ // Fait apparaitre un bonus tous les 2000 loop
        shieldRevive.etat=1;
    }
    if (compteurloop%2000==1999){//augmente la vitesse tous les 2000 loop
        for (int i=0;i<NBRASTEROID;i++){
            if (tabAsteroid[i].vitesse>1){
                tabAsteroid[i].vitesse--;
            }
        }
    }
    if (compteurloop%6==1){ // incremente le score toutes les 6 loop (dizieme de seconde)
        score++;
    }
}

void drawShieldRevive(){ //Coeur bleu qui tombe bonus
    int i=0;
    int j=0;
    if (shieldRevive.etat==1){
        for (int y=shieldRevive.pos_y;y<=shieldRevive.pos_y2;y++){
            for (int x=shieldRevive.pos_x;x<=shieldRevive.pos_x2;x++){
                if ((i==0 && (j==0 || j==1 || j==3 || j==4)) || (i==1 && (j==0 || j==1 || j==2 || j==3 || j==4)) || (i==2 && (j==1 || j==2 || j==3)) || (i==3 && j==2)){
                    tab_display[x][y].r=0;
                    tab_display[x][y].g=24;
                    tab_display[x][y].b=248; // Meme couleur que le shield
                    tab_display[x][y].a=200;
                }
                j++;
            }
            i++;
            j=0;
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
                vaisseau_rouge=255;
                vaisseau_vert=255;
                vaisseau_bleu=255;
            }else{
                vie--;
            }
			condition = 0;
            tabAsteroid[i].etat=0;
        }
    }
    if (tab_display[shieldRevive.pos_x][shieldRevive.pos_y+1].a == 255){
        shieldRevive.etat=0;
        shield=1;
        vaisseau_rouge=0;
        vaisseau_vert=24;
        vaisseau_bleu=248;
    }
    if (tab_display[shieldRevive.pos_x+1][shieldRevive.pos_y+2].a == 255){
        shieldRevive.etat=0;
        shield=1;
        vaisseau_rouge=0;
        vaisseau_vert=24;
        vaisseau_bleu=248;
    }
    if (tab_display[shieldRevive.pos_x+2][shieldRevive.pos_y+3].a == 255){
        shieldRevive.etat=0;
        shield=1;
        vaisseau_rouge=0;
        vaisseau_vert=24;
        vaisseau_bleu=248;
    }
    if (tab_display[shieldRevive.pos_x+3][shieldRevive.pos_y+2].a == 255){
        shieldRevive.etat=0;
        shield=1;
        vaisseau_rouge=0;
        vaisseau_vert=24;
        vaisseau_bleu=248;
    }
    if (tab_display[shieldRevive.pos_x+4][shieldRevive.pos_y+1].a == 255){
        shieldRevive.etat=0;
        shield=1;
        vaisseau_rouge=0;
        vaisseau_vert=24;
        vaisseau_bleu=248;
    }
}
 
void remiseAZero(){
    for (int i=0;i<NBRASTEROID;i++){
        if (tabAsteroid[i].etat==0){
            tabAsteroid[i].pos_y=8;
            tabAsteroid[i].pos_y2=tabAsteroid[i].pos_y+tabAsteroid[i].taille;
            tabAsteroid[i].pos_x=num_alea(WINDOW_WIDTH-tabAsteroid[i].taille);
            tabAsteroid[i].pos_x2=tabAsteroid[i].pos_x+tabAsteroid[i].taille;
            tabAsteroid[i].etat=2; // WARNING SI CA MARCHE PAS C'EST ICI : METTRE CETTE LIGNE EN COMMENTAIRE
            //Ajouter un random pour la vitesse
        }
    }
    if (shieldRevive.etat==0){
        shieldRevive.pos_x=num_alea(WINDOW_HEIGHT-5);
        shieldRevive.pos_y=8;
        shieldRevive.pos_x2=shieldRevive.pos_x+5;
        shieldRevive.pos_y2=shieldRevive.pos_y+4;
        shieldRevive.etat=2;
    }
}
 
void clear(){
    for(int x=0;x<height;x++){
        for (int y=0;y<width;y++){
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
        for (int y=26;y<38;y++){
            if (((y==26) && (x==6 || x==7 || x==8 || x==9 || x==11 || x==12 || x==13 || x==14 || x==16 || x==20 || x==22 || x==23 || x==24 || x==25))
            || ((y==27) && (x==6 || x==11 || x==14 || x==16 || x==17 || x==19 || x==20 || x==22))
            || ((y==28) && (x==6 || x==8 || x==9 || x==11 || x==12 || x==13 || x==14 || x==16 || x==18 || x==20 || x==22 || x==23 || x==24 || x==25))
            || ((y==29) && (x==6 || x==9 || x==11 || x==14 || x==16 || x==20 || x==22))
            || ((y==30) && (x==6 || x==7 || x==8 || x==9 || x==11 || x==14 || x==16 || x==20 || x==22 || x==23 || x==24 || x==25))
            || ((y==33) && (x==6 || x==7 || x==8 || x==9 || x==11 || x==15 || x==17 || x==18 || x==19 || x==20 || x==22 || x==23 || x==24 || x==25))
            || ((y==34) && (x==6 || x==9 || x==11 || x==15 || x==17 || x==22 || x==25))
            || ((y==35) && (x==6 || x==9 || x==12 || x==14 || x==17 || x==18 || x==19 || x==20 || x==22 || x==23 || x==24 || x==25))
            || ((y==36) && (x==6 || x==9 || x==12 || x==14 || x==17 || x==22 || x==24))
            || ((y==37) && (x==6 || x==7 || x==8 || x==9 || x==13 || x==17 || x==18 || x==19 || x==20 || x==22 || x==25))){
                tab_display[x][y].r = 255;
                tab_display[x][y].g = 8;
                tab_display[x][y].b = 244;
                tab_display[x][y].a = 200;
            }
        }
    }
}

void sevenDigit(int digit){
    switch(digit){
        case 1:
            tab_display[13][1].r = 255;
            tab_display[13][1].g = 255;
            tab_display[13][1].b = 255;
            tab_display[13][1].a = 200;
            tab_display[14][1].r = 255;
            tab_display[14][1].g = 255;
            tab_display[14][1].b = 255;
            tab_display[14][1].a = 200;
            tab_display[15][1].r = 255;
            tab_display[15][1].g = 255;
            tab_display[15][1].b = 255;
            tab_display[15][1].a = 200;
            break;
        case 2:
            tab_display[13][1].r = 255;
            tab_display[13][1].g = 255;
            tab_display[13][1].b = 255;
            tab_display[13][1].a = 200;
            tab_display[13][2].r = 255;
            tab_display[13][2].g = 255;
            tab_display[13][2].b = 255;
            tab_display[13][2].a = 200;
            tab_display[13][3].r = 255;
            tab_display[13][3].g = 255;
            tab_display[13][3].b = 255;
            tab_display[13][3].a = 200;
            break;
        case 3:
            tab_display[15][1].r = 255;
            tab_display[15][1].g = 255;
            tab_display[15][1].b = 255;
            tab_display[15][1].a = 200;
            tab_display[15][2].r = 255;
            tab_display[15][2].g = 255;
            tab_display[15][2].b = 255;
            tab_display[15][2].a = 200;
            tab_display[15][3].r = 255;
            tab_display[15][3].g = 255;
            tab_display[15][3].b = 255;
            tab_display[15][3].a = 200;
            break;
        case 4:
            tab_display[13][3].r = 255;
            tab_display[13][3].g = 255;
            tab_display[13][3].b = 255;
            tab_display[13][3].a = 200;
            tab_display[14][3].r = 255;
            tab_display[14][3].g = 255;
            tab_display[14][3].b = 255;
            tab_display[14][3].a = 200;
            tab_display[15][3].r = 255;
            tab_display[15][3].g = 255;
            tab_display[15][3].b = 255;
            tab_display[15][3].a = 200;
            break;
        case 5:
            tab_display[13][3].r = 255;
            tab_display[13][3].g = 255;
            tab_display[13][3].b = 255;
            tab_display[13][3].a = 200;
            tab_display[13][4].r = 255;
            tab_display[13][4].g = 255;
            tab_display[13][4].b = 255;
            tab_display[13][4].a = 200;
            tab_display[13][5].r = 255;
            tab_display[13][5].g = 255;
            tab_display[13][5].b = 255;
            tab_display[13][5].a = 200;
            break;
        case 6:
            tab_display[15][3].r = 255;
            tab_display[15][3].g = 255;
            tab_display[15][3].b = 255;
            tab_display[15][3].a = 200;
            tab_display[15][4].r = 255;
            tab_display[15][4].g = 255;
            tab_display[15][4].b = 255;
            tab_display[15][4].a = 200;
            tab_display[15][5].r = 255;
            tab_display[15][5].g = 255;
            tab_display[15][5].b = 255;
            tab_display[15][5].a = 200;
            break;
        case 7:
            tab_display[13][5].r = 255;
            tab_display[13][5].g = 255;
            tab_display[13][5].b = 255;
            tab_display[13][5].a = 200;
            tab_display[14][5].r = 255;
            tab_display[14][5].g = 255;
            tab_display[14][5].b = 255;
            tab_display[14][5].a = 200;
            tab_display[15][5].r = 255;
            tab_display[15][5].g = 255;
            tab_display[15][5].b = 255;
            tab_display[15][5].a = 200;
            break;
        case 11:
            tab_display[9][1].r = 255;
            tab_display[9][1].g = 255;
            tab_display[9][1].b = 255;
            tab_display[9][1].a = 200;
            tab_display[10][1].r = 255;
            tab_display[10][1].g = 255;
            tab_display[10][1].b = 255;
            tab_display[10][1].a = 200;
            tab_display[11][1].r = 255;
            tab_display[11][1].g = 255;
            tab_display[11][1].b = 255;
            tab_display[11][1].a = 200;
            break;
        case 12:
            tab_display[9][1].r = 255;
            tab_display[9][1].g = 255;
            tab_display[9][1].b = 255;
            tab_display[9][1].a = 200;
            tab_display[9][2].r = 255;
            tab_display[9][2].g = 255;
            tab_display[9][2].b = 255;
            tab_display[9][2].a = 200;
            tab_display[9][3].r = 255;
            tab_display[9][3].g = 255;
            tab_display[9][3].b = 255;
            tab_display[9][3].a = 200;
            break;
        case 13:
            tab_display[11][1].r = 255;
            tab_display[11][1].g = 255;
            tab_display[11][1].b = 255;
            tab_display[11][1].a = 200;
            tab_display[11][2].r = 255;
            tab_display[11][2].g = 255;
            tab_display[11][2].b = 255;
            tab_display[11][2].a = 200;
            tab_display[11][3].r = 255;
            tab_display[11][3].g = 255;
            tab_display[11][3].b = 255;
            tab_display[11][3].a = 200;
            break;
        case 14:
            tab_display[9][3].r = 255;
            tab_display[9][3].g = 255;
            tab_display[9][3].b = 255;
            tab_display[9][3].a = 200;
            tab_display[10][3].r = 255;
            tab_display[10][3].g = 255;
            tab_display[10][3].b = 255;
            tab_display[10][3].a = 200;
            tab_display[11][3].r = 255;
            tab_display[11][3].g = 255;
            tab_display[11][3].b = 255;
            tab_display[11][3].a = 200;
            break;
        case 15:
            tab_display[9][3].r = 255;
            tab_display[9][3].g = 255;
            tab_display[9][3].b = 255;
            tab_display[9][3].a = 200;
            tab_display[9][4].r = 255;
            tab_display[9][4].g = 255;
            tab_display[9][4].b = 255;
            tab_display[9][4].a = 200;
            tab_display[9][5].r = 255;
            tab_display[9][5].g = 255;
            tab_display[9][5].b = 255;
            tab_display[9][5].a = 200;
            break;
        case 16:
            tab_display[11][3].r = 255;
            tab_display[11][3].g = 255;
            tab_display[11][3].b = 255;
            tab_display[11][3].a = 200;
            tab_display[11][4].r = 255;
            tab_display[11][4].g = 255;
            tab_display[11][4].b = 255;
            tab_display[11][4].a = 200;
            tab_display[11][5].r = 255;
            tab_display[11][5].g = 255;
            tab_display[11][5].b = 255;
            tab_display[11][5].a = 200;
            break;
        case 17:
            tab_display[9][5].r = 255;
            tab_display[9][5].g = 255;
            tab_display[9][5].b = 255;
            tab_display[9][5].a = 200;
            tab_display[10][5].r = 255;
            tab_display[10][5].g = 255;
            tab_display[10][5].b = 255;
            tab_display[10][5].a = 200;
            tab_display[11][5].r = 255;
            tab_display[11][5].g = 255;
            tab_display[11][5].b = 255;
            tab_display[11][5].a = 200;
            break;
        case 21:
            tab_display[5][1].r = 255;
            tab_display[5][1].g = 255;
            tab_display[5][1].b = 255;
            tab_display[5][1].a = 200;
            tab_display[6][1].r = 255;
            tab_display[6][1].g = 255;
            tab_display[6][1].b = 255;
            tab_display[6][1].a = 200;
            tab_display[7][1].r = 255;
            tab_display[7][1].g = 255;
            tab_display[7][1].b = 255;
            tab_display[7][1].a = 200;
            break;
        case 22:
            tab_display[5][1].r = 255;
            tab_display[5][1].g = 255;
            tab_display[5][1].b = 255;
            tab_display[5][1].a = 200;
            tab_display[5][2].r = 255;
            tab_display[5][2].g = 255;
            tab_display[5][2].b = 255;
            tab_display[5][2].a = 200;
            tab_display[5][3].r = 255;
            tab_display[5][3].g = 255;
            tab_display[5][3].b = 255;
            tab_display[5][3].a = 200;
            break;
        case 23:
            tab_display[7][1].r = 255;
            tab_display[7][1].g = 255;
            tab_display[7][1].b = 255;
            tab_display[7][1].a = 200;
            tab_display[7][2].r = 255;
            tab_display[7][2].g = 255;
            tab_display[7][2].b = 255;
            tab_display[7][2].a = 200;
            tab_display[7][3].r = 255;
            tab_display[7][3].g = 255;
            tab_display[7][3].b = 255;
            tab_display[7][3].a = 200;
            break;
        case 24:
            tab_display[5][3].r = 255;
            tab_display[5][3].g = 255;
            tab_display[5][3].b = 255;
            tab_display[5][3].a = 200;
            tab_display[6][3].r = 255;
            tab_display[6][3].g = 255;
            tab_display[6][3].b = 255;
            tab_display[6][3].a = 200;
            tab_display[7][3].r = 255;
            tab_display[7][3].g = 255;
            tab_display[7][3].b = 255;
            tab_display[7][3].a = 200;
            break;
        case 25:
            tab_display[5][3].r = 255;
            tab_display[5][3].g = 255;
            tab_display[5][3].b = 255;
            tab_display[5][3].a = 200;
            tab_display[5][4].r = 255;
            tab_display[5][4].g = 255;
            tab_display[5][4].b = 255;
            tab_display[5][4].a = 200;
            tab_display[5][5].r = 255;
            tab_display[5][5].g = 255;
            tab_display[5][5].b = 255;
            tab_display[5][5].a = 200;
            break;
        case 26:
            tab_display[7][3].r = 255;
            tab_display[7][3].g = 255;
            tab_display[7][3].b = 255;
            tab_display[7][3].a = 200;
            tab_display[7][4].r = 255;
            tab_display[7][4].g = 255;
            tab_display[7][4].b = 255;
            tab_display[7][4].a = 200;
            tab_display[7][5].r = 255;
            tab_display[7][5].g = 255;
            tab_display[7][5].b = 255;
            tab_display[7][5].a = 200;
            break;
        case 27:
            tab_display[5][5].r = 255;
            tab_display[5][5].g = 255;
            tab_display[5][5].b = 255;
            tab_display[5][5].a = 200;
            tab_display[6][5].r = 255;
            tab_display[6][5].g = 255;
            tab_display[6][5].b = 255;
            tab_display[6][5].a = 200;
            tab_display[7][5].r = 255;
            tab_display[7][5].g = 255;
            tab_display[7][5].b = 255;
            tab_display[7][5].a = 200;
            break;
        case 31:
            tab_display[1][1].r = 255;
            tab_display[1][1].g = 255;
            tab_display[1][1].b = 255;
            tab_display[1][1].a = 200;
            tab_display[2][1].r = 255;
            tab_display[2][1].g = 255;
            tab_display[2][1].b = 255;
            tab_display[2][1].a = 200;
            tab_display[3][1].r = 255;
            tab_display[3][1].g = 255;
            tab_display[3][1].b = 255;
            tab_display[3][1].a = 200;
            break;
        case 32:
            tab_display[1][1].r = 255;
            tab_display[1][1].g = 255;
            tab_display[1][1].b = 255;
            tab_display[1][1].a = 200;
            tab_display[1][2].r = 255;
            tab_display[1][2].g = 255;
            tab_display[1][2].b = 255;
            tab_display[1][2].a = 200;
            tab_display[1][3].r = 255;
            tab_display[1][3].g = 255;
            tab_display[1][3].b = 255;
            tab_display[1][3].a = 200;
            break;
        case 33:
            tab_display[3][1].r = 255;
            tab_display[3][1].g = 255;
            tab_display[3][1].b = 255;
            tab_display[3][1].a = 200;
            tab_display[3][2].r = 255;
            tab_display[3][2].g = 255;
            tab_display[3][2].b = 255;
            tab_display[3][2].a = 200;
            tab_display[3][3].r = 255;
            tab_display[3][3].g = 255;
            tab_display[3][3].b = 255;
            tab_display[3][3].a = 200;
            break;
        case 34:
            tab_display[1][3].r = 255;
            tab_display[1][3].g = 255;
            tab_display[1][3].b = 255;
            tab_display[1][3].a = 200;
            tab_display[2][3].r = 255;
            tab_display[2][3].g = 255;
            tab_display[2][3].b = 255;
            tab_display[2][3].a = 200;
            tab_display[3][3].r = 255;
            tab_display[3][3].g = 255;
            tab_display[3][3].b = 255;
            tab_display[3][3].a = 200;
            break;
        case 35:
            tab_display[1][3].r = 255;
            tab_display[1][3].g = 255;
            tab_display[1][3].b = 255;
            tab_display[1][3].a = 200;
            tab_display[1][4].r = 255;
            tab_display[1][4].g = 255;
            tab_display[1][4].b = 255;
            tab_display[1][4].a = 200;
            tab_display[1][5].r = 255;
            tab_display[1][5].g = 255;
            tab_display[1][5].b = 255;
            tab_display[1][5].a = 200;
            break;
        case 36:
            tab_display[3][3].r = 255;
            tab_display[3][3].g = 255;
            tab_display[3][3].b = 255;
            tab_display[3][3].a = 200;
            tab_display[3][4].r = 255;
            tab_display[3][4].g = 255;
            tab_display[3][4].b = 255;
            tab_display[3][4].a = 200;
            tab_display[3][5].r = 255;
            tab_display[3][5].g = 255;
            tab_display[3][5].b = 255;
            tab_display[3][5].a = 200;
            break;
        case 37:
            tab_display[1][5].r = 255;
            tab_display[1][5].g = 255;
            tab_display[1][5].b = 255;
            tab_display[1][5].a = 200;
            tab_display[2][5].r = 255;
            tab_display[2][5].g = 255;
            tab_display[2][5].b = 255;
            tab_display[2][5].a = 200;
            tab_display[3][5].r = 255;
            tab_display[3][5].g = 255;
            tab_display[3][5].b = 255;
            tab_display[3][5].a = 200;
            break;
        default:
            break;
    }
}