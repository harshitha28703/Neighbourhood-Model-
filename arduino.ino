// assigning constant pins numbers
const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 11;
const int ledPinRed = 13;
const int ledPinGreen = 12;
const int ledPinTrafficRed = 4;
const int ledPinTrafficYellow = 3;
const int ledPinTrafficGreen = 2;
int DELAY_GREEN = 500;
int DELAY_YELLOW = 5000;
int DELAY_RED = 500;
// set pin numbers
// const won't change
const int ledstreetPin = 7; // the number of the LED pin
const int ldrPin = A0;      // the number of the LDR pin

// defines variables
long duration;
int distance;
int safetyDistance;

void setup()
{
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
    pinMode(buzzer, OUTPUT);
    pinMode(ledPinRed, OUTPUT);
    pinMode(ledPinGreen, OUTPUT);
    pinMode(ledPinTrafficGreen, OUTPUT);
    pinMode(ledPinTrafficRed, OUTPUT);
    pinMode(ledPinTrafficYellow, OUTPUT);

    Serial.begin(9600);            // Starts the serial communication
    pinMode(ledstreetPin, OUTPUT); // initialize the LED pin as an output
    pinMode(ldrPin, INPUT);        // initialize the LDR pin as an input
}

void loop()
{

    // prepare to start new signal
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculating the distance
    distance = duration * 0.034 / 2;

    safetyDistance = distance;

    green_light();
    int ldrStatus = analogRead(ldrPin); // read the voltage of the LDR value

    // check if the LDR status is <= 300(digital value)
    // if it is, the LED is HIGH

    if (ldrStatus <= 300)
    {

        digitalWrite(ledstreetPin, HIGH); // turn LED on
        Serial.println("LDR is DARK, LED is ON");
    }
    else
    {

        digitalWrite(ledstreetPin, LOW); // turn LED off
        Serial.println("---------------");
    }

    if (safetyDistance <= 5)
    { // check if pedestrian is present on footpath
        delay(3000);
        // Clears the trigPin
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);

        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH);

        // Calculating the distance
        distance = duration * 0.034 / 2;

        safetyDistance = distance;
        if (safetyDistance <= 5)
        { // if pedestrian  wants to cross
            delay(2000);
            yellow_light(); // traffic signal
            delay(DELAY_YELLOW);
            red_light();
            delay(5000);

            digitalWrite(ledPinRed, LOW);

            delay(500);

            digitalWrite(ledPinGreen, HIGH);
            digitalWrite(buzzer, HIGH);
            delay(7000);
            digitalWrite(ledPinGreen, LOW);
            delay(100);
            digitalWrite(buzzer, LOW);
            delay(100);
            digitalWrite(ledPinRed, HIGH);
            delay(3000);
            yellow_light();
            delay(3000);
        }
    }

    else
    {

        digitalWrite(ledPinGreen, LOW);
        delay(100);
        digitalWrite(buzzer, LOW);
        delay(100);

        digitalWrite(ledPinRed, HIGH);
    }
    Serial.print("Distance: ");
    Serial.println(distance);
    // Prints the distance on the Serial Monitor
}
void red_light()
{
    digitalWrite(ledPinTrafficGreen, HIGH);
    digitalWrite(ledPinTrafficYellow, LOW);
    digitalWrite(ledPinTrafficRed, LOW);
}

void yellow_light()
{
    digitalWrite(ledPinTrafficGreen, LOW);
    digitalWrite(ledPinTrafficYellow, HIGH);
    digitalWrite(ledPinTrafficRed, LOW);
}

void green_light()
{
    digitalWrite(ledPinTrafficGreen, LOW);
    digitalWrite(ledPinTrafficYellow, LOW);
    digitalWrite(ledPinTrafficRed, HIGH);
}
