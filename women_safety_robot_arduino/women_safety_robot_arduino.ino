#define RELAY_PIN 2
#define SOUND_SENSOR_PIN A0

// Motor A connections
int in1 = 4;
int in2 = 5;

// Motor B connections
int in3 = 8;
int in4 = 9;

// IR sensor connection
int irPin1 = 12; // Connect the output pin of the IR sensor to digital pin 11
//int irPin2 = 11;

void setup() {
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(irPin1, INPUT);
   // pinMode(irPin2, INPUT);
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(SOUND_SENSOR_PIN, INPUT);
    digitalWrite(RELAY_PIN, LOW); // Start with the relay off
    Serial.begin(9600); // Start serial communication for Bluetooth
}

void loop() {
    int irValue1 = digitalRead(irPin1);
//    int irValue2 = digitalRead(irPin2);

    int sensorValue = analogRead(SOUND_SENSOR_PIN);
    Serial.print("Sound sensor value: ");
    Serial.println(sensorValue);

    // Manual control via Bluetooth
    if (Serial.available()) {
        char command = Serial.read();
        switch (command) {
            case 'f':
                moveForward();
                Serial.println("Moving forward");
                while (irValue1 == HIGH) { // Check for obstacle while moving forward
                    irValue1 = digitalRead(irPin1);
                }
                motorOff(); // Stop if obstacle detected
                break;
            case 'b':
                moveBackward();
                Serial.println("Moving backward");
                delay(1000);
                motorOff(); // Stop if obstacle detected
                break;
            case 'l':
                turnLeft();
                Serial.println("Turning left");
                delay(500);
                motorOff();
                break; 
            case 'r':
                turnRight();
                Serial.println("Turning right");
                delay(500);
                motorOff();
                break;

            case 's':
                Serial.println("Stopping");
                //delay(500);
                motorOff();
                break;    
        }
    }

    if (sensorValue > 350) {
    digitalWrite(RELAY_PIN, LOW); // Turn on the relay
    delay(20000);
  } else {
    digitalWrite(RELAY_PIN, HIGH); // Turn off the relay
  }
}

void moveForward() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}

void motorOff() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}

void moveBackward() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void turnLeft() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void turnRight() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}
