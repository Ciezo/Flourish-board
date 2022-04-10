// PRE-PROCESSOR DIRECTIVES / HEADERS 
#include <SoftwareSerial.h>


//===GLOBAL VARIABLES===//  
// Set up and define pins 
// Serial
SoftwareSerial tx_rx(2, 3); // TX | RX 

// Digital Pins 
const int echo_pin = 10; 
const int trigger_pin = 9; 


// Values 
long duration;
int distance;
int labelDistance;
int read_data, write_data; 


void setPins_mode() {
     // Print to COM 
    Serial.print("Setting up Pins to respective Modes"); 

    // pinModes to set INPUT or OUTPUT
    /* NOTE: echo_pin is set as INPUT to behave as it is when set to state HIGH in order for it to start sending waves
            flame_sens_pin is set as INPUT for it have a series of values to be read through analogRead() 
            In conclusion, both of these pins are set as INPUT so that we can read values and retrieve their state.
    */ 
    pinMode(echo_pin, INPUT);
    pinMode(trigger_pin, OUTPUT);
}

void setup() {
    // Begin Serial Communication 
    Serial.begin(9600); 
    // Prompt over Serial communication
    Serial.println("Serial communication with baud rate of default 9600"); 
    Serial.println("Bluetooth connection is ready to establish"); 

    // Begin Bluetooth Serial Communication 
    tx_rx.begin(9600);
    // Prompts over Bluetooth Serial
    tx_rx.println("Connection initiated!");
    tx_rx.println("Bluetooth communication and pairing with the device is successul");
    tx_rx.println("***ENTER 1 to wake up Bluetooth connection***");

    // Call function to set up pins 
    setPins_mode(); 

}

void loop() {
    // Start a series of sending waves from ultrasonic sensor. Must set echo_pin to HIGH
    // And measure the time it takes to get back. Store to duration variable. 
    digitalWrite(trigger_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger_pin, LOW);

    // Calculation of distance to measure it back into centimeters based on the time in microseconds it got back. 
    // This formula is based on D = V/T
    // Where, sound waves are travelling at constant of 300 m/s and convert it into microseconds, Hence 0.034
    duration = pulseIn(echo_pin, HIGH); 
    distance = (duration*0.0343)/2;
    labelDistance = distance;               // assign and store the distance value to this.

    // Print Distance to Serial Monitor over COM
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm"); 
    delay(100);

    // Bluetooth series communication 
    // Start looking for streaming of Bluetooth connection. 
    // Find if it available.  
    if (tx_rx.available() > 0) {
        // Print live distance and measuring coming from the Ultrasonic Sensor 
        // NOTE: We will be printing the CALCULATED distance 
        tx_rx.print("Distance: "); 
        tx_rx.println(distance); 
        tx_rx.println(" cm"); 
    }    

}