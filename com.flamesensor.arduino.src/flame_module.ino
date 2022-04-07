//===GLOBAL VARIABLES===//  
// Set up and define pins 
// Analog pins
const int flame_sens_pin = A0; 

// Digital pins 
const int buzz_pin = 8; 
const int ledPin_state_RED =  13;  
const int ledPin_state_YLW =  12;  
const int ledPin_state_GRE =  11;      

// Values 
const int flame_value_minThreshold = 0; 
const int flame_value_maxThreshold = 1024; 


void setPins_mode() {
    // pinModes to set INPUT or OUTPUT
    pinMode(flame_sens_pin, INPUT); 
    pinMode(buzz_pin, OUTPUT);
   
}

void alarm(int check, String type) {
    // Condition when there is a fire and flameVal < 1000
    if ((check == 2) && (type == "FIRE")) {
        tone(buzz_pin, 500, 400);
        tone(buzz_pin, 1000, 800);
        delay(200);
        tone(buzz_pin, 600, 800);
        delay(200);

        // Print message to Serial COM monitor 
        Serial.println("FIRE DETECTED!!!");
    } 
}

void setup() {
    // Call function to set up pins
    setPins_mode(); 
 
    // Initialize Serial Communication 
    Serial.begin(9600); 
    // Print to COM 
    delay(1500);
    Serial.print("Setting up Pins to respective Modes"); 

}

void loop() {
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
                break;
        }
            
            delay(1);  // delay between reads from the flame module sensor

}