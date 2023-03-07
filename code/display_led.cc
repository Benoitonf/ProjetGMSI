#include "display_led.h"

namespace rgb_matrix {
  // tab 2D RGB en param qu'on enverra depuis le main du code
  static void drawCanvas(Canvas *canvas, RGB tab[][32]){
    for(int i = 0; i <= 31; i++) {
      for(int j = 0; j <= 63; j++) {
        canvas->SetPixel(j, i, tab[j][i].r, tab[j][i].g, tab[j][i].b);
      }
    }
  }
}