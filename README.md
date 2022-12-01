# Vanilla-Ice-Snow-Plow


## Dependencies
- DueTimer by Ivan Seidel
- HCSR04 ultrasonic sensor by gamegine

These can be installed from the libraries tab in Arduino IDE

## Planned Architecture
Code architecture is planned to be done as such:

- Main logic will be done in main loop of arduino code
- Sensor setup and interrupts will be done in classes
- Sensor functions will be used to check for flags and various sensor properties

### Example
- The Ultrasonic Sensor will have a UltrasonicSensor.h header file
- The Ultrasonic Sensor will have a UltrasonicSensor.cpp class file
- Each sensor will be intialized in the constructor when the object of that sensor is created

## Motor Layout
|Motor Location | Connection |
|----------- |-------|
|Rear Left   | M1 |
|Rear Right  | M2 |
|Front Left  | M3 |
|Front Right | M4 |
