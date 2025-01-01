#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <string>
using namespace sf;

const int M = 25; // Number of rows in the game grid
const int N = 10; // Number of columns in the game grid
int field[M][N] = { 0 }; // The game grid, initialized to 0 (empty cells)

// Structure to hold x, y coordinates of points
struct Point {
    int x, y;
} a[4], b[4]; // Arrays to store the current and previous positions of the Tetrimino

// Predefined Tetrimino shapes
int figures[7][4] = {
    1, 3, 5, 7,  // I
    2, 4, 5, 7,  // Z
    3, 5, 4, 6,  // S
    3, 5, 4, 7,  // T
    2, 3, 5, 7,  // L
    3, 5, 7, 6,  // J
    2, 3, 4, 5   // O
};
bool gameOver = false;   // Initializing these variables as global variables 
bool pause =false;
// Check if the current piece's position is valid
bool check() {
    for (int i = 0; i < 4; i++) {
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return false; // Out of bounds
        if (a[i].y >= 0 && field[a[i].y][a[i].x]) return false;     // Collides with the grid
    }
    return true;
}

// Reset or spawn a new piece
void resetPiece() {
    int n = rand() %7; // Select a random Tetrimino shape
    for (int i = 0; i < 4; i++) {
        a[i].x = figures[n][i] % 2 + N / 2 - 1; // Set x-coordinate relative to the grid center
        a[i].y = figures[n][i] / 2;            // Set y-coordinate

        // Check for game over if the spawn location is occupied
        if (field[a[i].y][a[i].x]) {
            std::cout << "Game Over: Piece cannot spawn!\n";
            gameOver = true; // Set gameOver to true 
            pause = true; // Pause the game 
            return; // Exit the function
        }
    }
}
void stopMusic(Music& backgroundMusic) {
    backgroundMusic.stop();
}


// Draw the game grid frame
void drawFrame(RenderWindow& window) {
    RectangleShape frame; // Create a rectangle for the frame
    frame.setSize(Vector2f(N * 18, M * 18)); // Set size based on grid dimensions
    frame.setOutlineThickness(10);           // Thickness of the border
    frame.setOutlineColor(Color::Cyan);    // Color of the border
    frame.setPosition(50, 50);              // Position the frame on the window
    frame.setFillColor(Color::Yellow); // Make the frame background transparent
    window.draw(frame);                     // Draw the frame
}

bool rotatePiece(Point p, int type) {
    for (int i = 0; i < 4; i++) {
        int x = a[i].y - p.y;
        int y = a[i].x - p.x;

        // Rotate coordinates for the line piece or other shapes
        a[i].x = p.x - x;
        a[i].y = p.y + y;
    }

    // Check if the rotation is valid
    if (!check()) {
        for (int i = 0; i < 4; i++) a[i] = b[i]; // Undo rotation
        return false;
    }
    return true;
}

bool handleWallKicks(Point p, int type) {
    if (rotatePiece(p, type)) return true; // Try normal rotation

   
    // Try wall kicks for other pieces
    static int wallKickTests[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
    for (auto& test : wallKickTests) {
        for (int i = 0; i < 4; i++) a[i] = b[i]; // Reset position
        for (int i = 0; i < 4; i++) {
            a[i].x += test[0];
            a[i].y += test[1];
        }
        if (rotatePiece(p, type)) return true;
    }

    return false; // Rotation failed
}




int main() {
    srand(time(0)); // Seed random number generator

    RenderWindow window(VideoMode(400, 600), "Tetris Game!"); // Create game window
    window.setFramerateLimit(60); // Limit frame rate to 60 FPS

    Texture t1;
    t1.loadFromFile("images/tiles.png"); // Load Tetrimino tile texture
    Sprite s(t1); // Create sprite for Tetrimino tiles

    Font font;
    font.loadFromFile("fonts/arial.ttf"); // Load font for displaying text
    Text text("", font, 18); // Create text object
    text.setFillColor(Color::Blue); // Set text color

    // Load background music
    Music backgroundMusic;
    if ((!backgroundMusic.openFromFile("sounds/th.mp3") )) {
        std::cerr << "Error loading background music\n";
        return -1;
    }
    if (!pause) {
        backgroundMusic.setLoop(true); // Set music to loop
        backgroundMusic.play(); // Start playing background music
    }
   
    int dx = 0, colorNum = 1, score = 0, level = 1;
    bool rotate = false;
    float timer = 0, delay = 0.3f;

    Clock clock; // Create a clock to track time

    resetPiece(); // Initialize the first Tetrimino
    colorNum = 1 + rand() % 7; // Assign a random color to the Tetrimino

    //game loop

    while (window.isOpen()) {
        float time = clock.restart().asSeconds(); // Restart clock and get elapsed time
        if (!pause && !gameOver) {
            timer += time; // Increment timer if game is running
          }

        // Check if the game is paused or over and stop the music
        if (pause || gameOver) {
            stopMusic(backgroundMusic);
        }
        else {
            // If the game is running, ensure the music is playing
            if (backgroundMusic.getStatus() != Music::Playing) {
                backgroundMusic.play();
            }
        }


        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close(); // Close the window on user request

            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Up) {
                    rotate = true; // Rotate the Tetrimino
                }
                else if (e.key.code == Keyboard::Left) {
                    dx = -1; // Move Tetrimino left
                }
                else if (e.key.code == Keyboard::Right) {
                    dx = 1; // Move Tetrimino right
                }
                else if (e.key.code == Keyboard::P) pause = !pause; // Toggle pause
                else if (e.key.code == Keyboard::R) { // Restart game
                    for (int i = 0; i < M; i++)
                        for (int j = 0; j < N; j++)
                            field[i][j] = 0; // Clear the grid
                    gameOver = false;
                    score = 0;
                    pause = false;
                    level = 1;
                    resetPiece(); // Reset the Tetrimino
                    colorNum = 1 + rand() % 7;
                }
                else if (e.key.code == Keyboard::E) window.close(); // Exit the game
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05f; // Accelerate Tetrimino drop

        for (int i = 0; i < 4; i++) {
            b[i] = a[i]; // Save current position
            a[i].x += dx; // Apply horizontal movement
        }
        if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i]; // Revert if invalid

        if (rotate) {
            Point p = a[1]; // Center of rotation
            handleWallKicks(p, 0); // Pass the type (0 for line-shaped Tetrimino)
        }


        if (timer > delay) {
            for (int i = 0; i < 4; i++) {
                b[i] = a[i]; // Save current position
                a[i].y += 1; // Move Tetrimino down
            }

            if (!check()) {
                for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = colorNum; // Place Tetrimino on grid
                colorNum = 1 + rand() % 7; // Generate new color
                resetPiece(); // Spawn new Tetrimino
            }
            timer = 0; // Reset timer
        }

        dx = 0; // Reset horizontal movement
        rotate = false; // Reset rotation flag
        delay = 0.3f - (level * 0.02f); // Adjust speed based on level

        int k = M - 1; // Start from the bottom row
        for (int i = M - 1; i >= 0; i--) {
            int count = 0;
            for (int j = 0; j < N; j++) {
                if (field[i][j]) count++; // Count filled cells
                field[k][j] = field[i][j]; // Copy row
            }
            if (count == N) { // Full row detected
                score += 100; // Increase score
                if (score / 200 > level - 1) level++; // Increase level every 200 points
            }
            if (count < N) k--; // Move to the next row if not full
        }

        window.clear(Color::Black); // Clear the screen

        int offsetX = 50, offsetY = 50; // Offsets for the grid

        drawFrame(window); // Draw the game frame

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (field[i][j] == 0) continue; // Skip empty cells
                s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18)); // Set texture for grid cell
                s.setPosition(j * 18 + offsetX, i * 18 + offsetY); // Position the cell
                window.draw(s); // Draw the cell
            }
        }

        for (int i = 0; i < 4; i++) {
            s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18)); // Set texture for Tetrimino
            s.setPosition(a[i].x * 18 + offsetX, a[i].y * 18 + offsetY); // Position the Tetrimino
            window.draw(s); // Draw the Tetrimino
        }

        

        text.setString(
            "Controls:\n"
            "Move Left:  \nLeft Arrow\n"
            "\nMove Right: \nRight Arrow\n"
            "\nRotate: Up Arrow\n"
            "Drop: Down Arrow\n"
            "Pause: P\n"
            "Restart: R\n"
            "Exit: E\n\n"
            "Score: " + std::to_string(score) +
            "\nLevel: " + std::to_string(level) +
            "\nStatus: " + std::string(gameOver ? "Game Over" : (pause ? "Paused" : "Running")));
        text.setPosition(250, 50); // Position the text
        window.draw(text); // Draw the text

        window.display(); // Display the frame
    }

    return 0;
}
