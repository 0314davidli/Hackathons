#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
int clearFrequency = 0;

float startTime;
float currentTime;
float timeDiff;
// int notDetecting = 1; // start by not detecting with color sensor

// Stores the red. green and blue colors
int redColor = 0;
int greenColor = 0;
int blueColor = 0;
int clearColor = 0;

const int stirrer_rot_speed = 255;

const int trans_ctrl = 10; // Connect pwm pin to pin 10
const int motor = 11;

void setup() {
  // Color Sensor Code
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  pinMode(motor, OUTPUT);
  analogWrite(motor, 0);

  pinMode(trans_ctrl, OUTPUT);

  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);         // initialize serial
}

void loop() {
// Setting RED (R) filtered photodiodes to be read
    digitalWrite(S2,LOW);
    digitalWrite(S3,LOW);
    
    currentTime = millis();
    timeDiff = currentTime - startTime;
    
    // Reading the output frequency
    redFrequency = pulseIn(sensorOut, LOW);
    
    // Setting GREEN (G) filtered photodiodes to be read
    digitalWrite(S2,HIGH);
    digitalWrite(S3,HIGH);
    
    // Reading the output frequency
    greenFrequency = pulseIn(sensorOut, LOW);
  
    // Setting BLUE (B) filtered photodiodes to be read
    digitalWrite(S2,LOW);
    digitalWrite(S3,HIGH);
    
    // Reading the output frequency
    blueFrequency = pulseIn(sensorOut, LOW);

    // Setting Clear (C) filtered photodiodes to be read
    digitalWrite(S2,HIGH);
    digitalWrite(S3,LOW);
    
    // Reading the output frequency
    clearFrequency = pulseIn(sensorOut, LOW);
    delay(500); // adjust how frequently you want the colours to update; decided 0.5 s was optimal

    Serial.print("R: "); Serial.print(redFrequency, DEC); Serial.print(" ");
    Serial.print("G: "); Serial.print(greenFrequency, DEC); Serial.print(" ");
    Serial.print("B: "); Serial.print(blueFrequency, DEC); Serial.print(" ");
    Serial.print("C: "); Serial.print(clearFrequency, DEC); Serial.print(" ");
    Serial.println(" ");

  // if(notDetecting){
  //     // start detecting with color sensor after 10 seconds to account for stirring instability for the first few seconds
  //     if(timeDiff > 10000){
  //       notDetecting=0;
  //       }
  //   }else{

  analogWrite(trans_ctrl, 255);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.print("Time Diff:"); Serial.print(timeDiff, DEC);

  if (timeDiff >= 3000){ // after a 3 second time delay, turn the motor on
      analogWrite(motor, 255); // this allows for adequate time for the reactions team to finish putting the reactiion for the clock
    }

  if (timeDiff > 5000){ // after 5 seconds, turn off the stir and continuously check for the colour of the reaction
    analogWrite(trans_ctrl, 0);
    digitalWrite(LED_BUILTIN, LOW);
    while(true){
    if (greenFrequency <= 23){ // once the reaction becomes clear (denoted by the value for greenFrequency <= 23) turn the car motor off
      analogWrite(motor, 0);
      Serial.print("STOP");
      Serial.println(" ");
      Serial.print(timeDiff, DEC);
      while(true); // to prevent anything else happening to the car
    }
    }
  }
}
