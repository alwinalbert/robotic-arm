#include <Arduino.h>
#include <Wire.h>

#include <Adafruit_PWMServoDriver.h>

namespace {
constexpr uint16_t MIN_PULSE_WIDTH = 650;
constexpr uint16_t MAX_PULSE_WIDTH = 2350;
constexpr uint8_t SERVO_FREQUENCY = 50;

// Arduino Uno analog inputs used by the controller potentiometers.
constexpr uint8_t POT_WRIST = A3;
constexpr uint8_t POT_ELBOW = A2;
constexpr uint8_t POT_SHOULDER = A1;
constexpr uint8_t POT_BASE = A0;

// PCA9685 servo channels.
constexpr uint8_t SERVO_HAND = 11;
constexpr uint8_t SERVO_WRIST = 12;
constexpr uint8_t SERVO_ELBOW = 13;
constexpr uint8_t SERVO_SHOULDER = 14;
constexpr uint8_t SERVO_BASE = 15;

// The gripper button is connected between Arduino Uno D13 and GND.
constexpr uint8_t GRIPPER_BUTTON_PIN = 13;

Adafruit_PWMServoDriver pwm;
}

void moveMotor(uint8_t controlPin, uint8_t servoChannel)
{
  const int potValue = analogRead(controlPin);
  const long pulseWidthMicroseconds = map(
      potValue, 800, 240, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  const int pulseTicks = static_cast<int>(
      static_cast<float>(pulseWidthMicroseconds) / 1000000.0f *
      SERVO_FREQUENCY * 4096.0f);

  pwm.setPWM(servoChannel, 0, pulseTicks);
}

void setup()
{
  // Allow time to move the controller to its starting position.
  delay(5000);

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQUENCY);
  pwm.setPWM(SERVO_HAND, 0, 90);

  pinMode(GRIPPER_BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  moveMotor(POT_WRIST, SERVO_WRIST);
  moveMotor(POT_ELBOW, SERVO_ELBOW);
  moveMotor(POT_SHOULDER, SERVO_SHOULDER);
  moveMotor(POT_BASE, SERVO_BASE);

  const int buttonState = digitalRead(GRIPPER_BUTTON_PIN);
  if (buttonState == LOW) {
    pwm.setPWM(SERVO_HAND, 0, 180);
    Serial.println("Grab");
  } else {
    pwm.setPWM(SERVO_HAND, 0, 90);
    Serial.println("Release");
  }
}
