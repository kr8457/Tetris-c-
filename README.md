  Tetris Game in C++ with SFML
  ![image](https://github.com/user-attachments/assets/87ab2f4c-0277-4deb-bb8d-e69783b07856)




Overview
This is a classic Tetris Game implemented in C++ using the SFML library. The project provides smooth gameplay with vibrant graphics, dynamic level progression, and immersive background music.

The resources (images and sounds) required for the game are already included in the project folder for convenience.

Features
Classic Gameplay: Move, rotate, and drop Tetrimino blocks to clear rows.
Dynamic Difficulty: Game speed increases as you level up.
Pause and Restart: Pause the game or restart it anytime with keyboard controls.
Music Integration: Background music enhances the gaming experience.
Modern UI: Colorful tiles and an easy-to-read score display.
Game Controls
Action	Key
Move Left	Left Arrow
Move Right	Right Arrow
Rotate Piece	Up Arrow
Drop Piece	Down Arrow
Pause/Resume	P
Restart Game	R
Exit Game	E
Getting Started
Prerequisites
SFML Library: Ensure SFML 2.5 or later is installed.
Visual Studio: Recommended for building and running the project.
Setup in Visual Studio
Clone the Repository:

bash
Copy code
git clone https://github.com/your-username/tetris-sfml.git
cd tetris-sfml
Open in Visual Studio:

Open Visual Studio.
Navigate to File > Open > Project/Solution.
Open the project .sln file provided in the repository.
Configure SFML:

Ensure SFML is linked in the project settings.
Copy the sfml-graphics, sfml-window, sfml-system, and sfml-audio DLLs to the executable folder (e.g., Debug or Release).
Run the Game:

Click on Start (green play button) in Visual Studio.
Resources in the Project Folder
Images:
images/tiles.png: Tileset for Tetrimino blocks.
Sounds:
sounds/th.mp3: Background music for the game.
How to Play
Arrange Tetrimino blocks to fill rows.
Filled rows will disappear, earning you points.
The game ends when no space is left for a new piece.
Pause or restart the game anytime using the controls.
Preview



License
This project is licensed under the MIT License.
