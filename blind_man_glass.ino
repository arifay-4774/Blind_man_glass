// Blind Man Glass - Obstacle Detection
// Components: Arduino Nano, HC-SR04 Ultrasonic Sensor, Active Buzzer

// Define pins for Ultrasonic Sensor and Buzzer
const int trigPin = 10;   // Connect to TRIG on HC-SR04
const int echoPin = 8;  // Connect to ECHO on HC-SR04
const int buzzerPin = 11; // Connect to positive pin of the buzzer

// Variables to store duration and calculated distance
long duration;
int distance;

void setup() {
  // Initialize pins
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  pinMode(buzzerPin, OUTPUT); // Sets the buzzerPin as an Output
  
  // Initialize Serial Monitor for debugging
  Serial.begin(9600);
}

void loop() {
  // 1. Trigger the ultrasonic sensor to send a pulse
  // Clear the trigPin first
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Set the trigPin to HIGH for 10 microseconds to send out a pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 2. Read the echo
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // 3. Calculate the distance
  // Speed of sound is ~0.034 cm/µs. Divide by 2 because the wave travels to the object and back.
  distance = duration * 0.034 / 2;

  // Print the distance on the Serial Monitor for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // 4. Buzzer alerts based on distance thresholds
  if (distance > 0 && distance <= 30) {
    // Obstacle is very close (0 to 30 cm) - Fast beeping
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
  } else {
    // No obstacle within 100 cm - Buzzer stays off
    digitalWrite(buzzerPin, LOW);
    delay(100); // Small delay before next measurement
  }
}
