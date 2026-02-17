// I/O pins
int sensor = A3;
int pot = A1;
int led = 5;
int red = 10;
int blue = 9;
int green = 6;

// color control
int rVal = 0;
int gVal = 0;
int bVal = 5;
int threshold = 80;

// rawVal computation
int peakValue = 0;
int decayRate = 5;
int p = 6;

void setup() {
  pinMode(sensor, INPUT);
  pinMode(pot, INPUT);
  pinMode(led, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  Serial.begin(9600);
}


void loop() {

  // potentiometer controls the rawVal computation
  int potVal = analogRead(pot);
  threshold = map(potVal, 0, 1023, 0, 120);
  
  int rawVal = analogRead(sensor);
  
  if (rawVal > peakValue) {
    peakValue = rawVal; 
  } else {
    if (peakValue > 0) {
      peakValue -= decayRate; 
    }
  }

  // compute power of rawVal to make it noticible of change 
  int v = pow(peakValue, p);  

  // RGB LED
  if (v > threshold) {
    analogWrite(red, threshold);
    v -= threshold;
    if (v > threshold) {
      analogWrite(blue, threshold + bVal);
      v -= threshold;
      analogWrite(green, v);
    } else {
      analogWrite(blue, v + bVal);
      analogWrite(green, 0);
    }
  } else {
    analogWrite(red, v);
    analogWrite(blue, 0 + bVal);
    analogWrite(green, 0);
  }

  // normal LED
  analogWrite(led, peakValue);

  // serial debugging: visualizing rawVal
  for(int i = rawVal; i > 0; i--) {
    Serial.print("-");
  }
  Serial.println();
  delay(0);
}
