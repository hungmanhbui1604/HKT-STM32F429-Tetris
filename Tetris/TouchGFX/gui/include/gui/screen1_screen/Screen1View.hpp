#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

// Enumeration for different Tetromino types
enum class TetrominoType {
    I, // Line
    O, // Square
    T, // T-shape
    S, // S-shape
    Z, // Z-shape
    J, // J-shape
    L // L-shape
};

constexpr int COUNT = 7;
// Maximum number of tiles per Tetromino
constexpr int TETROMINO_TILE_COUNT = 4;

// Rotation states (0: 0°, 1: 90°, 2: 180°, 3: 270°)
constexpr int ROTATION_STATES = 4;

class TetriTileID{
public:
	touchgfx::BoxWithBorder* tiles[TETROMINO_TILE_COUNT];
};

class Tetromino {
public:
    Tetromino();

    // Initialize the tetromino with a specific type and position
    void initialize(TetrominoType type, int startX, int startY, int tileSize, TetriTileID freeBoxes);

    // Move the tetromino by (dx, dy)
    void move(int dx, int dy);

    // Rotate the tetromino clockwise
    void rotate();

    // Get the tiles for rendering and collision
    touchgfx::BoxWithBorder* getTile(int index);

    // Get the number of tiles
    int getTileCount() const { return TETROMINO_TILE_COUNT; }

    // Reset tetromino to uninitialized state
    void reset();

    // Get current position
    int getPosX() const { return posX; }
    int getPosY() const { return posY; }

private:
    TetrominoType type;
    int posX; // Central X position (in pixels)
    int posY; // Central Y position (in pixels)
    int tileSize;
    int rotationState; // 0-3 for rotation states

    // Relative positions for each rotation state
    // [TetrominoType][RotationState][TileIndex][x or y]
    static const int relativePositions[COUNT][ROTATION_STATES][TETROMINO_TILE_COUNT][2];

    // Tiles composing the tetromino
    touchgfx::BoxWithBorder* tiles[TETROMINO_TILE_COUNT];

    // Update tile positions based on current rotation and central position
    void updateTilePositions();
};


class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View();

    virtual void setupScreen();
    virtual void tearDownScreen();

    void handleTickEvent();
    void Move();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void Rotate();

    // Prevent copy
    Screen1View(const Screen1View&) = delete;
    Screen1View& operator=(const Screen1View&) = delete;

    // Grid parameters
	static const int step = 20;
	static const int maxSubTickCount = 40;
	static const int maxX = 240;
	static const int maxY = 250; // Button position
	static const int MAX_BLOCKS = maxX * maxY / (step * step) + 2; // Additional just to be sure


private:
    void CreateGrid();
    void CreateNewTetromino();
    bool CheckCollision(int newX, int newY, Tetromino& tetromino);
    bool CheckCollisionAfterRotation(const Tetromino& tetromino);
    TetriTileID findFreeTiles();
    void eraseFullRows(bool* checkFullRows);
    void gameOver();

    // Movement helpers
    bool MoveTetromino(int stepx, int stepy);
    void RotateTetromino();

    uint32_t tickCount;
    uint8_t subTickCount;
    uint32_t timerCount;
    uint16_t currentScore;

    // Grid lines
    static const int MAX_LINES = maxX / (step * 2) - 1;
    touchgfx::BoxWithBorder lines[MAX_LINES];

    // Grid rows: the number of active block per rows
    static const int MAX_ROWS = maxY / step;
    static const int MAX_BLOCK_PER_ROW = maxX / step;
    uint8_t rows[MAX_ROWS] = {}; // Initialize all zeros

    // Current active tetromino
    Tetromino currentTetromino;
    bool tetrominoActive;

    // Fixed blocks on the grid
	touchgfx::BoxWithBorder boxes[MAX_BLOCKS];



    // Predefined tetromino types
    TetrominoType tetrominoTypes[static_cast<int>(COUNT)] = {
        TetrominoType::I,
        TetrominoType::O,
        TetrominoType::T,
        TetrominoType::S,
        TetrominoType::Z,
        TetrominoType::J,
        TetrominoType::L
    };

    // Helper to generate random tetromino
    TetrominoType getRandomTetrominoType();
};

#endif // SCREEN1VIEW_HPP
