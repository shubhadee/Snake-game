# Snake Game

**Author**: Shubhadeep Subal Devnath  
**Company**: CODTECH IT SOLUTIONS  
**Employee ID**: CT08EVR  
**Domain**: C++ Programming  
**Project Duration**: December 20th, 2024 - January 20th, 2025  

## Objective

This project is a modern implementation of the classic Snake Game using the C++ programming language and the **Raylib** library. The primary objective of the project is to create a simple yet engaging game while adhering to clean coding practices and demonstrating advanced C++ concepts like object-oriented programming, exception handling, and real-time game mechanics.

The game is designed for anyone interested in retro gaming or learning about the development of small-scale games in C++.

---

## Features

### Gameplay Mechanics
- **Classic Snake Movement**: The snake moves in the specified direction and grows upon consuming food.
- **Dynamic Speed Adjustment**: The game becomes progressively challenging as the snake’s speed increases with the score.
- **Collision Detection**: The game detects when the snake collides with itself or the boundaries, leading to a game-over state.
- **Food Mechanics**: Randomly placed food items for the snake to consume, each increasing the score by one point.

### Visual and Audio Effects
- **Retro Graphics**: Minimalistic grid-based graphics providing a nostalgic look.
- **Sound Effects**: Interactive sound feedback for eating food and collisions.
- **Background Music**: Continuous music to enhance the gaming experience.

### User Interaction
- **Keyboard Controls**: Control the snake’s movement using arrow keys.
- **Game Over Screen**: Displays the final score and a message to end the game.

---

## Project Structure

The project is modular, ensuring separation of concerns:
- **Snake Class**: Handles the snake’s body, movement, growth, and collision detection.
- **Food Class**: Manages the food’s position and appearance.
- **Main Loop**: Orchestrates game mechanics, rendering, and user inputs.

---

## How to Play

- **Objective**: Guide the snake to eat as much food as possible without colliding with itself or the boundaries.
- **Controls**:
  - **Arrow Keys**: Change the snake’s direction.
  - **Escape**: Exit the game.
- **Game Over**: When the snake collides with itself or the wall, the game ends and displays the final score.

---

## Dependencies

The game relies on the following libraries:

- **Raylib**: A simple and easy-to-use library for rendering graphics, handling audio, and managing inputs.
- **Standard C++ Libraries**: For core programming features such as data structures, input/output, and exception handling.

---

## Challenges and Learnings

Developing this project presented multiple challenges and opportunities for learning:

1. **Real-Time Game Loop**: Managing the game loop to ensure smooth gameplay and responsive controls.
2. **Collision Detection**: Implementing reliable algorithms to detect collisions between the snake, walls, and itself.
3. **Object-Oriented Design**: Structuring the code with classes for better readability, maintainability, and scalability.
4. **Randomization**: Generating random positions for the food within the game grid while avoiding invalid placements.
5. **Performance Optimization**: Ensuring that the game runs smoothly even with increasing complexity.

---

## Future Enhancements

1. **Levels and Difficulty**: Introducing levels with increasing complexity and new challenges.
2. **Power-Ups**: Adding special items that provide temporary boosts or effects.
3. **Multiplayer Mode**: Enabling two players to compete on the same screen.
4. **High Score System**: Saving and displaying the top scores.
5. **Mobile Compatibility**: Porting the game to mobile platforms with touch controls.

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---

Enjoy playing this retro Snake Game and relive the nostalgia of classic gaming!
