Tetris Game in C++ with SFML
A classic Tetris game implemented in C++ using the SFML library. This project includes smooth gameplay mechanics, colorful Tetrimino shapes, a scoring system, dynamic level-ups, and background music.

Features
Classic Tetris Gameplay: Move, rotate, and drop Tetrimino pieces to fill rows.
Dynamic Level Progression: Increases game speed as you score more points.
Background Music: Enjoy in-game background music with options to pause.
Game Controls: Full keyboard-based controls for seamless gameplay.
Pause and Restart: Pause the game or restart anytime.
Game Over Detection: Automatically stops when no space is left for new Tetrimino.
Controls
Move Left: Left Arrow Key
Move Right: Right Arrow Key
Rotate: Up Arrow Key
Drop: Down Arrow Key
Pause: P Key
Restart: R Key
Exit: E Key
Requirements
SFML Library: Install SFML for handling graphics, textures, fonts, and audio.
C++ Compiler: Compatible with modern C++ compilers (e.g., GCC, Clang, MSVC).
Installation and Setup
Clone the Repository:

bash
Copy code
git clone https://github.com/your-username/tetris-sfml.git
cd tetris-sfml
Install Dependencies: Ensure SFML is installed on your system. Refer to the SFML Installation Guide.

Add Resources:

Place the Tetrimino tile texture in images/tiles.png.
Place a font file in fonts/arial.ttf.
Place a background music file in sounds/th.mp3.
Compile and Run: Use a C++ compiler to compile the program:

bash
Copy code
g++ -o TetrisGame main.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./TetrisGame
How to Play
The objective is to clear rows by arranging Tetrimino pieces.
Use arrow keys to move or rotate pieces.
Rows filled completely will disappear, and your score will increase.
The game speeds up as you progress to higher levels.
Preview

Replace preview.png with a screenshot of your game.

Contributing
Contributions, suggestions, and improvements are welcome! Feel free to open an issue or submit a pull request.

License
This project is licensed under the MIT License.
