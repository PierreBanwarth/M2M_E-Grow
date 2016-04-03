int pinMoteur = 3;
int USTrig = 8;
int USEcho = 9;
// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      10

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup() {
  pinMode(pinMoteur, OUTPUT);
  pinMode(USTrig, OUTPUT);
  pinMode(USEcho, INPUT);
  digitalWrite(USTrig, LOW);
  Serial.begin(9600);
  pixels.begin();
  int luminosite = 150;
}
void loop() {

  int val;
  // 1. Un état haut de 10 microsecondes est mis sur la broche "Trig"
   digitalWrite(USTrig, HIGH);
   delayMicroseconds(10); //on attend 10 µs
   // 2. On remet à l’état bas la broche Trig
   digitalWrite(USTrig, LOW);

   // 3. On lit la durée d’état haut sur la broche "Echo"
   unsigned long duree = pulseIn(USEcho, HIGH);

   if(duree > 30000)
   {
      // si la durée est supérieure à 30ms, l'onde est perdue
      //Serial.println("Onde perdue, mesure échouée !");
   }
   else
   {
      // 4. On divise cette durée par deux pour n'avoir qu'un trajet
      duree = duree/2;

      // 5. On calcule la distance avec la formule d=v*t
      float temps = duree/1000000.0; //on met en secondes
      float distance = temps*3000; //on multiplie par la vitesse, d=t*v

         Serial.print("/water/distance/");
         Serial.println(distance);
      // 6. On affiche la distance
      //Serial.print("Duree = ");
      //Serial.println(temps); //affiche le temps de vol d'un trajet en secondes
      //Serial.print("Distance = ");
      //Serial.println(distance); //affiche la distance mesurée (en mètres)
   }
  // regarde si quelque chose se trouve dans le buffer
  if (Serial.available()) {
    // lit le premier byte dans la pile (valeur entre 0 to 255)
    val = Serial.read();
    //commande pour ajouter de l'eau
    if (val == '9')
    {
      digitalWrite(pinMoteur, LOW); //le moteur se lance
      delay(1000);
      digitalWrite(pinMoteur, HIGH); //le moteur se lance
      delay(1000);
      digitalWrite(pinMoteur, LOW); //le moteur se lance
    }
    // commande pour augmenter la luminosité
    if(val=='8'){
      luminosite = luminosite + 10;  
    }
    // commande pour baisser la luminosité
    if(val=='7'){
      luminosite = luminosite - 10;  
    }

  }
  for(int i=0;i<NUMPIXELS;i++){
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(0,luminosite,0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(50);
    }
    
}
