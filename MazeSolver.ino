// ================= Pin Definitions =================
// Ultrasonic Sensors
#define trigLeft   11
#define echoLeft   8
#define trigCenter 12
#define echoCenter 9
#define trigRight  13
#define echoRight  10

// Motor Driver Pins
#define ENA 3    // Left Motor Speed (PWM)
#define IN1 2    // Left Motor Direction
#define IN2 4
#define ENB 6    // Right Motor Speed (PWM)
#define IN3 5    // Right Motor Direction
#define IN4 7

// ================= Speed Settings =================
int leftMotorSpeed  = 100;   // ENA
int rightMotorSpeed = 80;    // ENB

// ================= Functions =================

// Measure distance from ultrasonic sensor
long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 20000); // timeout 20ms
  long distance = duration * 0.034 / 2;          // cm
  return distance == 0 ? 999 : distance;         // if no echo, return large value
}

// Move Forward
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, leftMotorSpeed);
  analogWrite(ENB, rightMotorSpeed);
  Serial.println("Action: Moving Forward");
}

// Stop Motors
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  Serial.println("Action: Stop");
}

// Turn Left (90°)
void turnLeft() {
  Serial.println("Action: Turning Left (90°)");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, leftMotorSpeed);
  analogWrite(ENB, rightMotorSpeed);
  delay(500);  // adjust for exact 90° turn
  stopMotors();
}

// Turn Right (90°)
void turnRight() {
  Serial.println("Action: Turning Right (90°)");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, leftMotorSpeed);
  analogWrite(ENB, rightMotorSpeed);
  delay(500);  // adjust for exact 90° turn
  stopMotors();
}

// Turn Around (180°)
void turnAround() {
  Serial.println("Action: U-Turn (180°)");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, leftMotorSpeed);
  analogWrite(ENB, rightMotorSpeed);
  delay(1000);  // double the time of 90° turn
  stopMotors();
}

// ================= Setup =================
void setup() {
  // Ultrasonic pins
  pinMode(trigLeft, OUTPUT);
  pinMode(echoLeft, INPUT);
  pinMode(trigCenter, OUTPUT);
  pinMode(echoCenter, INPUT);
  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);

  // Motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Serial Monitor
  Serial.begin(9600);
  Serial.println("Maze Solver Bot Started (Left-Hand Rule)...");
  stopMotors();
  delay(1000);
}

// ================= Loop =================
void loop() {
  long leftDist   = getDistance(trigLeft, echoLeft);
  long centerDist = getDistance(trigCenter, echoCenter);
  long rightDist  = getDistance(trigRight, echoRight);

  // Print sensor values
  Serial.print("Left: ");
  Serial.print(leftDist);
  Serial.print(" cm | Center: ");
  Serial.print(centerDist);
  Serial.print(" cm | Right: ");
  Serial.print(rightDist);
  Serial.println(" cm");

  // --- Left-Hand Rule Logic ---
  if (leftDist > 9) {
    turnLeft();       // Rule 1: Prefer Left
  }
  else if (centerDist > 9) {
    moveForward();    // Rule 2: Go Straight
  }
  else if (rightDist > 9) {
    turnRight();      // Rule 3: Else turn Right
  }
  else {
    turnAround();     // Rule 4: Dead-End → U-Turn
  }

  delay(200);
}
