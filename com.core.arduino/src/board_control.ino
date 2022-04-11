/*  @author: Cloyd Van S. Secuya 
 *  Project Description: This is the source file as sketch to configure the Arduino Uno R3 Board.    
*/

// PRE-PROCESSOR DIRECTIVES / HEADERS 
#include <SoftwareSerial.h>
#include <String.h> 

//===GLOBAL VARIABLES===//  
// Set up and define pins 
// Digital Pins 
const int echo_pin = 10; 
const int trigger_pin = 9; 
const int buzz_pin = 8; 
const int ledPin_state_RED =  13;  
const int ledPin_state_YLW =  12;  
const int ledPin_state_GRE =  11;      

// Analog Pins 
const int flame_sens_pin = A0; 

// Serial 
SoftwareSerial tx_rx(2, 3); // TX | RX 
// int rxd_pin = 3; 
// int txd_pin = 2; 

// Values
long duration;
int distance;
int labelDistance;
const int flame_value_minThreshold = 0; 
const int flame_value_maxThreshold = 1024; 

// A function for setting up pins as INPUT or OUTPUT through pinMode()
void setPins_mode() {
     // Print to COM 
    Serial.println("Setting up Pins to respective Modes"); 

    // pinModes to set INPUT or OUTPUT
    /* NOTE: echo_pin is set as INPUT to behave as it is when set to state HIGH in order for it to start sending waves
            flame_sens_pin is set as INPUT for it have a series of values to be read through analogRead() 
            In conclusion, both of these pins are set as INPUT so that we can read values and retrieve their state.
    */ 
    pinMode(echo_pin, INPUT);
    pinMode(trigger_pin, OUTPUT);
    pinMode(flame_sens_pin, INPUT); 
    pinMode(buzz_pin, OUTPUT);
    pinMode(ledPin_state_RED, OUTPUT);
    pinMode(ledPin_state_YLW, OUTPUT);
    pinMode(ledPin_state_GRE, OUTPUT);
}

// A function to turn on LEDs
void set_LED_state(int ledPin) {
    /*  NOTE: ledPin_state_RED = 0 
              ledPin_state_YLW = 1
              ledPin_state_GRE = 2
    */

    switch (ledPin)
    {
        case 0:
            digitalWrite(ledPin_state_RED, HIGH); 
            Serial.println("====> RED LED ON"); 
            break;
        
        case 1: 
            digitalWrite(ledPin_state_YLW, HIGH);
            Serial.println("====> YELLOW LED ON"); 
            break;
        
        case 2: 
            digitalWrite(ledPin_state_GRE, HIGH);
            Serial.println("====> GREEN LED ON");
            break;
        
        default:
            break;
    }
}

// A function to set off and trigger the alarm (buzzer)
void alarm(int check, String type) {
    // Condition when garbage is full 
    if ((check == 1) && (type == "FULL")) {
        tone(buzz_pin, 500, 400);
        delay(200);
        tone(buzz_pin, 800, 200);
        delay(400);
        tone(buzz_pin, 100, 400);
        delay(600);
        digitalWrite(buzz_pin, LOW);
        delay(800);

        // Print message to Serial COM monitor 
        Serial.println("GARBAGE FULL!!!");

        // Check condition to see if Bluetooth communication is available
        if (tx_rx.available() > 0) {
            // Print and send over Bluetooth Serial communication 
            tx_rx.println("Garbage is FULL"); 
        }
    }

    // Condition when there is a fire and flameVal < 1000
    if ((check == 2) && (type == "FIRE")) {
        tone(buzz_pin, 1000, 800);
        delay(200);
        tone(buzz_pin, 600, 800);
        delay(200);

        // Print message to Serial COM monitor 
        Serial.println("FIRE DETECTED!!!");

        // Check condition to see if Bluetooth communication is available
        if (tx_rx.available() > 0) {
            // Print and send over to the Bluetooth Serial communication 
            tx_rx.println("Fire source is detected!!!"); 
        }
    }
}

// This only runs once when program is compiled
void setup() {
    // Begin and initialize Serial communication
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

    //===FLAME SENSOR MAIN LOOP===//
/////////////////////////////////////////////////////////////////////////////
    // Begin reading from flame sensor to see if there is any state. 
    int flame_sensorRead = analogRead(flame_sens_pin); 
    int range = map(flame_sensorRead, flame_value_minThreshold, flame_value_maxThreshold, 0, 3);

        // Begin checking and observing if there is a change in the state of flame sensor

        if (flame_sensorRead < 1000) {
            // SET OFF THE ALARM FOR FIRE STATE
            alarm(2, "FIRE"); 
        }

        switch (range) 
        {
            case 0:    // A fire closer than 1.5 feet away.
                Serial.println("** Close Fire **");
                alarm(2, "FIRE");
                break;
            case 1:    // A fire between 1-3 feet away.
                Serial.println("** Distant Fire **");
                alarm(2, "FIRE");
                break;
            case 2:    // No fire detected.
                Serial.println("No Fire");
                if (tx_rx.available() > 0) 
                    tx_rx.println("No Fire"); 
                break;
        }
            
            // delay(1);  // delay between reads from the flame module sensor
/////////////////////////////////////////////////////////////////////////////



    //===ULTRASONIC MAIN SENSOR LOOP===//
/////////////////////////////////////////////////////////////////////////////
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


    /*  NOTE: ledPin_state_RED = 0 
              ledPin_state_YLW = 1
              ledPin_state_GRE = 2
        
        RED is 100% garbage full 
        YLW is 50% garbage full 
        GRE is 25% garbage full
    */
    if (labelDistance <= 19) {
        // Turn on GREEN LED 
        set_LED_state(2); 
    }

    else {
         // Wait for 1 second
        // delay(1000); 
        // Turn it off
        digitalWrite(ledPin_state_GRE, LOW);  
    }

    if (labelDistance <= 11) {
        // Turn on YELLOW LED 
        set_LED_state(1); 
       
    }

    else {
        // Wait for a second 
        // delay(1000);
        // Turn off 
        digitalWrite(ledPin_state_YLW, LOW); 
    }

    if (labelDistance <= 7) {
        // Turn on RED LED 
        set_LED_state(0); 
        
        // Set off the alarm when garbage is full 
        alarm(1, "FULL"); 
    }

    else {
        // Wait for a second 
        // delay(1000);
        // Turn off 
        digitalWrite(ledPin_state_RED, LOW); 
    }
/////////////////////////////////////////////////////////////////////////////



    //==BLUETOOTH, HC-05==// 
/////////////////////////////////////////////////////////////////////////////
    // Bluetooth series communication 
    // Start looking for streaming of Bluetooth connection. 
    // Find if it available.  
    if (tx_rx.available() > 0) {
        // Print live distance and measuring coming from the Ultrasonic Sensor 
        // NOTE: We will be printing the CALCULATED distance 
        tx_rx.print("Fill level content: "); 
        tx_rx.print(distance); 
        tx_rx.println(" cm"); 
    }    


    // Activate Serial Monitoring and print output to COM
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(100);
}
 
