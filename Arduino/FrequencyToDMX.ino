#include <DmxSimple.h>
#define STROBE 4
#define RESET 5
#define DC_One A0
#define DC_Two A1

int Frequencies_One[7];
int Frequencies_Two[7];
int Frequencies_Average[7];

#define DMX_PIN 3
#define DMX_MULTIPLIER 5
#define DMX_DEVICES 1

#define DEBUG 1

enum DMX_channels { BRIGHTNESS = 1, RED = 2, GREEN = 3 , BLUE = 4 , DMX_STROBE = 5};

void setup() {
  // put your setup code here, to run once:
  DmxSimple.usePin(DMX_PIN);
  DmxSimple.maxChannel(DMX_DEVICES * DMX_MULTIPLIER);

  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(DC_One, INPUT);
  pinMode(DC_Two, INPUT);

  //Initialize Spectrum Analyzers
  digitalWrite(STROBE, LOW);
  digitalWrite(RESET, LOW);
  delay(5);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Read_Frequencies();
#if (DEBUG == 1)
  //Print_Frequencies();
#endif
  Output_Frequencies();
}

void Read_Frequencies() {
  digitalWrite(RESET, HIGH);
  delayMicroseconds(200);
  digitalWrite(RESET, LOW);
  delayMicroseconds(200);

  //Read frequencies for each band
  for (int freq_amp = 0; freq_amp < 7; freq_amp++)
  {
    digitalWrite(STROBE, HIGH);
    delayMicroseconds(50);
    digitalWrite(STROBE, LOW);
    delayMicroseconds(50);

    int max_value = 1024;
    //There's some weirdness with low frequencies
    if(freq_amp == 0)
    {
      max_value = 512;
    }
    if(freq_amp == 1)
    {
      max_value = 640;
    }
    int read1 = analogRead(DC_One);
    int read2 = analogRead(DC_Two);

    Serial.print("Band ");
    Serial.print(freq_amp);
    Serial.print(": " );
    Serial.print(read1);
    Serial.print(" ");
    Serial.print(read2);

    //Clipping
    if(read1 < 75)
    {
      read1 = 0;
    }
    if(read2 < 75)
    {
      read2 = 0;
    }
    
    Frequencies_One[freq_amp] = map(read1, 0, max_value, 0, 255);
    Frequencies_Two[freq_amp] = map(read2, 0, max_value, 0, 255);

    Frequencies_Average[freq_amp] = (Frequencies_One[freq_amp] + Frequencies_Two[freq_amp]) / 2;
  }
  Serial.println();
}

void Output_Frequencies()
{
  //3 colors over 7 bands.
  //Biased towards midrange; however,
  //people like red more than green
  //B = 0 - 2
  //R = 2 - 5
  //G = 4 - 6

  int blueAverage  = (Frequencies_Average[0] + Frequencies_Average[1] + Frequencies_Average[2]) / 3;
  int redAverage   = (Frequencies_Average[2] + Frequencies_Average[3] + Frequencies_Average[4] + Frequencies_Average[5]) / 4;
  int greenAverage = (Frequencies_Average[4] + Frequencies_Average[5] + Frequencies_Average[6]) / 3;

  //TODO: Slide pots for brightness and strobe
  for(int device = 1; device <= DMX_DEVICES; ++device)
  {
    DmxSimple.write(device * BRIGHTNESS, 255);  //max brightness
    DmxSimple.write(device * RED, redAverage);
    DmxSimple.write(device * GREEN, greenAverage);
    DmxSimple.write(device * BLUE, blueAverage);
    DmxSimple.write(device * DMX_STROBE, 0); //turn off strobe
  }
}

void Print_Frequencies() {
  //Read frequencies for each band
  for (int x = 0; x < 7; x++)
  {
    Serial.print("Band ");
    Serial.print(x);
    Serial.print(": ");
    Serial.print( Frequencies_Average[x]); 
    Serial.print("  ");
  }
  Serial.println();
  
}
