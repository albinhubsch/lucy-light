// 
// Lucy Light Runner
// 

// 
// Setup
// 
void setup() {
	// Start serial
	Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

// 
// Loop
// 
void loop() {

	int incomingByte = 0;   // for incoming serial data

	// send data only when you receive data:
	while(Serial.available() > 0) {
		// read the incoming byte:
		// Serial.println(incomingByte, DEC);
		incomingByte += Serial.read();
	}

	// say what you got:
	if(incomingByte > 0){
		Serial.print("I received: ");
		Serial.println(incomingByte, DEC);
	}

	delay(10);

}

