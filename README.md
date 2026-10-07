# Robotic Arm

Arduino Uno firmware for a five-channel robotic arm controlled by four
potentiometers and a gripper push button.

## Hardware

- Arduino Uno
- PCA9685 servo driver connected over I2C
- Potentiometers on `A0` (base), `A1` (shoulder), `A2` (elbow), and `A3` (wrist)
- Gripper button between Arduino `D13` and GND
- Servos connected to PCA9685 channels 11 through 15:
  - 11: hand/gripper
  - 12: wrist
  - 13: elbow
  - 14: shoulder
  - 15: base

The button uses the Uno's internal pull-up resistor, so it reads `LOW` when
pressed.

## PlatformIO

Open this repository in VS Code with the PlatformIO extension installed.
PlatformIO will install the board framework and the
`Adafruit PWM Servo Driver Library` dependency from `platformio.ini`.

```text
pio run
pio run --target upload
pio device monitor --baud 9600
```

The firmware waits five seconds during startup so the controller can be moved
to its starting position.
