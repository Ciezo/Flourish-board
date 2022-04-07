void setup() {
    // Begin serial communication
    Serial.begin(9600); 
    Serial.println("Begin Serial Communication"); 
}

void loop() {
    // Print message to COM 
    Serial.println("Board init and ready!"); 
    Serial.println("Board is clear!");
    Serial.println("Board has no partial configurations");
}