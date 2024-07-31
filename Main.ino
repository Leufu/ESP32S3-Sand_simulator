#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Configuración de pines para I2C
#define SDA_PIN 21
#define SCL_PIN 22

// Configuración de la pantalla OLED
#define SCREEN_WIDTH 128 // Ancho de la pantalla OLED
#define SCREEN_HEIGHT 64 // Altura de la pantalla OLED
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

// Crear objeto display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


typedef struct
{
  int id;
  int16_t posX;
  int16_t posY;
  int16_t vel;
}particula;

// Array de partículas
#define NUM_PARTICULAS 8
particula particulas[NUM_PARTICULAS];

void setup() {
  // Iniciar Serial para depuración
  Serial.begin(115200);

  // Iniciar el display OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Dirección 0x3C para SSD1306
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Bucle infinito si falla la inicialización
  }
  // Inicialización de partículas
  particulas[0] = {0, 10,0, 1};
  particulas[1] = {1, 23,1, 1};
  particulas[2] = {2, 23,2, 1};
  particulas[3] = {3, 50,45, 1};
  particulas[4] = {4, 23,37, 1};
  particulas[5] = {5, 23,59, 1};
  particulas[6] = {6, 23,20, 1};
  particulas[7] = {7, 23,10, 1};
  display.clearDisplay();
  for (int i = 0; i < NUM_PARTICULAS; i++) {
    draw_particula(&particulas[i]);
  }
  display.display();
}

void loop() {
    display.clearDisplay();
    for (int i = 0; i < NUM_PARTICULAS; i++) {
        update_particula(&particulas[i]);
    }
    display.display();
    delay(200); // Retardo para visualización
}

void draw_particula(particula *particula_obj)
{
  display.drawPixel(particula_obj->posX,particula_obj->posY,SSD1306_WHITE);
}

void update_particula(particula *particula_obj) {
    if (particula_obj->posY == 60)
    { 
      draw_particula(particula_obj);
      return;
    }
    
    if (!vecino_abajo(particula_obj) && particula_obj->posY < 60) {
        particula_obj->posY += particula_obj->vel;
    } else if (!vecino_izquierda_abajo(particula_obj) && particula_obj->posX>1  )
    {   
        particula_obj->posY+= particula_obj->vel;
        particula_obj->posX-=1;
    }
    else
    {return;}
     


    draw_particula(particula_obj);
}

bool vecino_abajo(particula *particula_obj) {
    for (int i = 0; i < NUM_PARTICULAS; i++) {
        if (particula_obj->id != particulas[i].id && particulas[i].posX == particula_obj->posX) {
            if (particulas[i].posY - 1 == particula_obj->posY) {return true;}
        }
    }
    return false;
}


bool vecino_izquierda_abajo(particula *particula_obj)
{
  for (int i = 0; i<NUM_PARTICULAS ; i++)
  {
    if(particula_obj->id != particulas[i].id&& particulas[i].posX == particula_obj->posX)
    {
      if (particulas[i].posY- 1 == particula_obj->posY &&particulas[i].posX - 1 == particula_obj->posX ) {return true;}
    }
  }
  return false;
  
}


bool vecino_derecha(particula *particula_obj)
{}