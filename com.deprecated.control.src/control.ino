//SMART GARBAGE BIN 101(code tweaked by Cloyd)
//KEY FEATURES: Fire Detection, Level Monitoring, Temperature and Humidity,LED indicators,
//define and set input pins


#define echoPin 10                //set CONSTANT Echo Pin to D/O 10. ALWAYS REMEMBER CLOYD! "ECHOPIN IS 10"
#define trigPin 9                 //set CONSTANT Trigger Pin D/O 9. REMEMBER THIS AGAIN! TRIGGER IS 9
#define flameSens A0              //set flame sensor to pin A0
int flameVal;                     //set up the data variable for flame sensor if HIGH
#define DHT11 A1                  //set DHT11 pin to Analog 1
const int buzz = 8;               //set buzzer to pin 8
const int ledPin1 = 13;           //led GREEN 25% fill
const int ledPin2 = 12;            //led YELLOW 50% fill
const int ledPin3 = 11;           //led RED 100% fill
const int ledPin4 = 7;            //led BLUE indicator for fire detection


//define variables gathering
long duration;
int distance;
int labelDistance;


void setup() {
  // put your setup code here, to run once:
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(flameSens, INPUT); //define flame sensor as an input and variable data maker if HIGH else all output LOW
 pinMode(buzz, OUTPUT);
 pinMode(ledPin1, OUTPUT);
 pinMode(ledPin2, OUTPUT);
 pinMode(ledPin3, OUTPUT);
 pinMode(ledPin4, OUTPUT);
 Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);

 int flameVal = analogRead(flameSens); //read sensor value and make variable data then deliver to ledPin4 output
 duration = pulseIn(echoPin, HIGH);
 distance = duration*0.034/2 + 2;
 labelDistance = distance;


 if (labelDistance <= 19) //19 cm or 25% fill set buzzer and ledPin1 GREEN HIGH
 {
    digitalWrite(ledPin1, HIGH);
 }


 else
 {
      digitalWrite(ledPin1, LOW);
 }


 if (labelDistance <= 11) //11 cm or 50% fill set buzzer and YELLOW ledPin2 HIGH
 {
      digitalWrite(ledPin2, HIGH);
 }


 else
 {
      digitalWrite(ledPin2, LOW);
 }


 if (labelDistance <= 7) //7 cm or 100% fill set buzzer and RED ledPin3 HIGH
 {
     digitalWrite(ledPin3, HIGH);
     digitalWrite(buzz, HIGH);
     tone(buzz, 500, 400);
     delay(200);
     tone(buzz, 800, 200);
     delay(400);
     tone(buzz, 100, 400);
     delay(600);
     digitalWrite(buzz, LOW);
     delay(800);
 }


 else
 {
     digitalWrite(buzz, LOW);
     digitalWrite(ledPin3, LOW);
 }


 if (flameVal <1000)
 {
     digitalWrite(ledPin4, HIGH);
     delay(200);
     tone(buzz, 1000, 800);
     delay(200);
     tone(buzz, 600, 800);
     delay(200);
 }

 else
 {
     digitalWrite(ledPin4, LOW);
 }


//Activate Serial Monitoring
Serial.print("Distance = ");
Serial.print(distance);
Serial.println(" cm");
delay(100);
}