// PRE-PROCESSOR DIRECTIVES / HEADERS 
#include <SoftwareSerial.h> 

//===GLOBAL VARIABLES===//  
// Serial Pins 
SoftwareSerial tx_rx(2, 3); // TX | RX 

// Values 
int flag = 0; 
const int LED = 13; 

void setup() {   
    // Begin and initialize Serial communication via Arduino 
    Serial.begin(9600); 
    // Start and initialize Serial communication over Bluetooth
    tx_rx.begin(9600); 
    
    pinMode(LED, OUTPUT); 
    
    Serial.println("Serial communication with baud rate of default 9600"); 
    Serial.println("Bluetooth connection is ready to establish \n \n"); 

    // Prompts over Bluetooth Serial
    tx_rx.write("HELLO! from HC-05, Bluetooth Module \n");  
    tx_rx.println("Connection initiated! \n");
    tx_rx.println("Bluetooth communication and pairing with the device is successul \n");
    tx_rx.println("***You can now use the interface!*** \n");
} 

void loop() { 
    /* NOTE: "Arduino doesn't support exception handling...""
     *        "The Arduino reference is not listing try catch 
     *        "...implementing try catch on a µ-controller could be kind of difficult/impossible."
     * https://stackoverflow.com/questions/10228562/try-catch-block-in-arduino
    */
    // Test and find out if Bluetooth communication with a paired device is working!
    // try {
    //     if ((tx_rx.available()) && (tx_rx.isListening())) {
    //         // Feed any data from bluetooth to Serial over terminal.
    //         Serial.write(tx_rx.read()); 
    //         tx_rx.write(tx_rx.isListening()); 
    //     }

    //     else {
    //         throw tx_rx; 
    //     }
    // } 

    // catch(SoftwareSerial err_txRx) {
    //     Serial.println(err_txRx.getWriteError()); 
    //     tx_rx.println(err_txRx.getWriteError()); 

    //     tx_rx.println("Please try to reconnect via Bluetooth or pair mobile device"); 
    // }

    // Condition to see if the Bluetooth Communication is successful with the paired device
    // And if Serial over Bluetooth  is running at baud rate of 9600
        if (tx_rx.available() > 0) { 
            // Start reading buffer data from the Bluetooth communication over Serial communication 
            /* NOTE: reading the buffer returns character/s or string
            */
            flag = tx_rx.read(); 
            // flag = MyBlue.parseInt();
        }

        // else {
        //     throw tx_rx; 
        // }

    if (flag == '1') { 
        digitalWrite(LED, HIGH); 
        Serial.println("LED On"); 
        tx_rx.println("***TURNING ON***"); 
        flag = 0;
    } 

    else if (flag == '0') { 
        digitalWrite(LED, LOW); 
        Serial.println("LED Off"); 
        tx_rx.println("***TURNING OFF***");
        flag = 0;
    } 
}  