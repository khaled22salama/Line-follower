# Line Follower Robot with Arduino Mega

This project is an implementation of a line follower robot with 4 motors controlled by an Arduino Mega. The robot uses multiple IR sensors to detect the line and follow it accordingly. Additionally, the robot can be controlled manually via Bluetooth and can pick up or drop objects using a servo arm.

## Hardware Requirements

- Arduino Mega
- 4 DC Motors
- IR Sensors
- 2 Servo Motors
- Bluetooth Module
- L298N Motor Driver
- LED Indicators
- Power Supply

## Pin Configuration

### Motor Pins

- **Right Motors**
  - PWM Pin: `5`
  - Forward Pin: `9`
  - Backward Pin: `10`

- **Left Motors**
  - PWM Pin: `6`
  - Forward Pin: `A3`
  - Backward Pin: `A4`

### Sensors Pins

- Front Sensor: `2`  
- Middle Sensor: `4`
- Middle Right Sensor 1: `7`
- Middle Right Sensor 2: `8`
- Middle Left Sensor 1: `12`
- Middle Left Sensor 2: `13`
- Back Sensor: `A0`

### Arm Motor Pins

- Hold/Drop Motor: `3`
- Up/Down Motor: `11`

### Mode LEDs

- Transporter Mode LED: `A1`
- Line Follower Mode LED: `A2`

## Software Setup

### Arduino Libraries

Include the Servo library for controlling the servo motors:

```cpp
#include <Servo.h>
Servo Hold_Drop;
Servo Up_Down;
```

### Bluetooth Commands

- **Movement Commands**
  - `f` - Forward
  - `b` - Backward
  - `r` - Turn Right
  - `l` - Turn Left
  - `s` - Stop
  - `u` - Arm Up
  - `d` - Arm Down
  - `h` - Hold Object
  - `p` - Drop Object

- **Mode Commands**
  - `T` - Transporter Mode
  - `L` - Line Follower Mode

## How It Works

1. **Initialization**: The robot initializes motor and sensor pins, sets servo positions to 0, and establishes a serial connection for Bluetooth communication.

2. **Mode Control**: The robot can operate in two modes:
   - **Transporter Mode**: Controlled manually via Bluetooth commands.
   - **Line Follower Mode**: Automatically follows a line based on IR sensor input.

3. **Movement Functions**: The robot uses motor control functions (`Forward`, `Back`, `Turn_Right`, `Turn_Left`, `Stop`) to move in different directions.

4. **Arm Functions**: The servo arm can pick up (`Hold`) or drop (`Drop`) objects and move up (`Arm_Up`) or down (`Arm_Down`).

### Main Loop

The `loop` function checks for any Bluetooth data to switch between modes or control the robot's movement and arm positions accordingly.

### Line Follower Logic

In **Line Follower Mode**, the robot reads from the IR sensors to detect the line and adjust its direction to stay on course. Different conditions are checked to determine if the robot should go forward, turn left, turn right, or stop.

## Usage

1. Upload the code to your Arduino Mega.
2. Connect the hardware components as per the pin configuration.
3. Open the serial monitor or use a Bluetooth application to send commands.
4. Switch between the Transporter and Line Follower modes and control the robot accordingly.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

