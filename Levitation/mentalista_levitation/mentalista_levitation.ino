/* ----------------------------------------------------------------------------------------------------
 * MENTALISTA GUINGUETTE – LEVITATION
 * Update: 08/05/16
 *
 * Light control device by the brain with OpenBCI / Processing
 * Using Adafruit Neopixel & Levitation module with relay
 * 
 * ----------------------------------------------------------------------------------------------------
 */ 
 
#include <Adafruit_NeoPixel.h>

// définition des broches utilisées
#define LEVITATION_PIN  3
#define  NEO_PIXEL_PIN  6
#define      RESET_PIN  4

volatile char inChar;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(50, NEO_PIXEL_PIN, NEO_GRB + NEO_KHZ800);

int difficulty = 2;

int J1[] = {255,0,0};
int nbJoueur1 = difficulty;

int J2[] = {0,0,255};
int nbJoueur2 = difficulty;


void setup() {
  // initialize serial:
  Serial.begin(115200);

  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, HIGH);
  
  pinMode(LEVITATION_PIN, OUTPUT);
  digitalWrite(LEVITATION_PIN, HIGH);
  
  pinMode(NEO_PIXEL_PIN, OUTPUT);
  strip.begin();
  strip.show();

  //SETUP LED POSITION
  //GOAL
  strip.setPixelColor(strip.numPixels()-1, strip.Color(255, 255, 0));
  strip.show();

  //JOUEUR1
  for(int i=0; i<difficulty; i++){
    strip.setPixelColor(i, strip.Color(J1[0], J1[1], J1[2]));
    strip.show();
  }
  //JOUEUR2
  for(int i=nbJoueur1; i<difficulty+nbJoueur1; i++){
    strip.setPixelColor(i, strip.Color(J2[0], J2[1], J2[2]));
    strip.show();
  }
  
  // print help
  Serial.println("LEVITATION Controller: starting..."); 
  Serial.println("Help Commands: ");
  Serial.println("    'P' = JOUEUR 1");
  Serial.println("    '{' = JOUEUR 2");
  
  Serial.println("Waiting for Alpha Brainwaves...");
}

void loop() {}

void serialEvent() {
  while (Serial.available()) {
    char inChar = Serial.read();
    Serial.print("Received :");
    Serial.println(inChar);
    
    if( inChar == 'P' ){
      //JOUEUR1
      nbJoueur1 = nbJoueur1+difficulty;
      
      for(int i=0; i<nbJoueur1; i++){
        strip.setPixelColor(i, strip.Color(J1[0], J1[1], J1[2]));
        strip.show();
      }
      //UPDATE JOUEUR2
      for(int i=nbJoueur1; i<nbJoueur1+nbJoueur2; i++){
        strip.setPixelColor(i, strip.Color(J2[0], J2[1], J2[2]));
        strip.show();
      }
    } else if( inChar == '{' ) {
      //JOUEUR2
      nbJoueur2 = nbJoueur2+difficulty;
      
      for(int i=nbJoueur1; i<nbJoueur1+nbJoueur2; i++){
        strip.setPixelColor(i, strip.Color(J2[0], J2[1], J2[2]));
        strip.show();
      }
    /*UPDATE JOUEUR1 **PAS BESOIN d'UPDATE**
      for(int i=0; i<nbJoueur1; i++){
        strip.setPixelColor(i, strip.Color(J1[0], J1[1], J1[2]));
        strip.show();
      }*/
    }
    
    if(nbJoueur1+nbJoueur2 >= strip.numPixels()){
      digitalWrite(LEVITATION_PIN, LOW);
      win();
    }
    //Serial.println(nbJoueur1 + nbJoueur2 + " / " + strip.numPixels());
  }
}

void win(){
  for(int i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, strip.Color(255,255,0));
    strip.show();
  }

  //STOP LEVITATION
  //digitalWrite(LEVITATION_PIN, LOW);
  
  //STOP 10s and RESET GAME
  delay(10000);

  digitalWrite(RESET_PIN, LOW);
}
