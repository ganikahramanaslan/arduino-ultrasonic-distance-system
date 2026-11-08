
/*
 * Project: Ultrasonic Distance Measurement System
 * Platform: Arduino Uno
 * Sensor: HC-SR04
 * Language: C++
 */

#define TRIG_PIN 9
#define ECHO_PIN 10

#define GREEN_LED 2
#define YELLOW_LED 3
#define RED_LED 4

#define BUZZER_PIN 5

float distance = 0;

float measureDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH, 30000);

    if (duration == 0) {
        return -1;
    }

    float measuredDistance = duration * 0.0343 / 2;

    return measuredDistance;
}

void setup() {
    Serial.begin(9600);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    pinMode(GREEN_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);

    pinMode(BUZZER_PIN, OUTPUT);

    Serial.println("Ultrasonic Distance System");
}

void loop() {
    distance = measureDistance();

    if (distance < 0) {
        Serial.println("No valid measurement!");
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(YELLOW_LED, LOW);
        digitalWrite(RED_LED, LOW);
        noTone(BUZZER_PIN);
    }
    else {
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");

        if (distance > 50) {
            digitalWrite(GREEN_LED, HIGH);
            digitalWrite(YELLOW_LED, LOW);
            digitalWrite(RED_LED, LOW);
            noTone(BUZZER_PIN);
        }

        else if (distance > 20) {
            digitalWrite(GREEN_LED, LOW);
            digitalWrite(YELLOW_LED, HIGH);
            digitalWrite(RED_LED, LOW);

            tone(BUZZER_PIN, 1000, 100);
        }

        else {
            digitalWrite(GREEN_LED, LOW);
            digitalWrite(YELLOW_LED, LOW);
            digitalWrite(RED_LED, HIGH);

            tone(BUZZER_PIN, 2000);
        }
    }

    delay(200);
}
