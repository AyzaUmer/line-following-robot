# line-following-robot
Arduino robot with IR line-following and ultrasonic obstacle avoidance
## Demo

### Obstacle avoidance (maze)


https://github.com/user-attachments/assets/5d98f500-9912-4373-ad9a-8d95e13de5f4


### Photos
<img width="300" alt="bb9980a8-5174-4140-87d4-71c6cdf157e7" src="https://github.com/user-attachments/assets/414124e2-5e69-42ca-9d9f-e1cb0304b59e" />
<img width="400" alt="44f37e21-3481-43c7-af1b-1dc47f8f2471" src="https://github.com/user-attachments/assets/b1773777-96be-48f2-9b40-1022629c23bc" />

## Hardware
- Arduino Mega
- 3 X IR sensors (line following)
- 3 X HC-SR04 ultrasonic sensors (obstacle detection)
- Dual motor driver with DC gear motors

## My Role
I wrote most of the code for this project and helped my teammate with breadboard wiring and sensor debugging. The main challenge was stopping the sensor systems from overriding each other's commands. I solved it by giving obstacle avoidance priority over line following and removing any conflicting commands.
