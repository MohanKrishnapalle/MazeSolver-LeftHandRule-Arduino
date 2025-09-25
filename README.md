## Maze Solver Robot using Left Hand Rule

This Arduino project implements an autonomous maze solver robot that uses the left hand rule for navigation. The bot is designed to follow walls and systematically discover a maze solution using IR sensors and motor control through the Arduino platform.

### Features

- Left hand rule maze navigation algorithm
- Real-time sensor feedback with three IR sensors
- Modular code for easy adaptation and extension
- Detailed comments for clear understanding and further customization

### Hardware Requirements

- Arduino Nano (or compatible)
- L298N Motor Driver Module
- 2 DC Motors (for movement)
- 3 IR Sensors (for line/edge detection)
- Power supply and chassis

### Getting Started

1. Connect the hardware components according to the circuit diagram provided in the code comments.
2. Upload `MazeSolver.ino` to the Arduino board using the Arduino IDE.
3. Place the robot at the start of the maze, ensuring sensors are properly calibrated for your surface.
4. Monitor serial output for debugging and path discovery information.

### How It Works

The robot employs the classic left hand rule strategy: always keep the left "hand" on the wall. The IR sensors detect junctions and walls, while the PID-based control ensures stable movement and accurate turns.

### Customization

- Pin configurations and sensor calibration can be changed in the initial code section.
- The algorithm logic is modular and can be extended for additional features like path optimization or mapping.

### Contribution

Feel free to fork the repository, submit issues, and open pull requests for improvements.

### License

This project is open-source and available under the MIT License.

***

This README template summarizes the project and will help others easily understand and deploy the maze solver robot. Make sure to adjust the details based on your exact hardware or any special features in your implementation.
