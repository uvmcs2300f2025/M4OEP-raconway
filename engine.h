#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H

#include <vector>
#include <memory>
#include <GLFW/glfw3.h>
#include "shader/shader.h"
#include "shapes/rect.h"
#include "card.h"
#include "deck.h"
#include "hand.h"

using std::vector, std::unique_ptr, std::make_unique;

enum GameState {start, playing, playerWin, playerLose, tie};

class Engine {
private:
    GLFWwindow* window{};
    const unsigned int width = 800, height = 600;
    bool keys[1024];

    Shader shapeShader;
    GameState state;

    Deck deck;
    Hand playerHand;
    Hand dealerHand;

    unique_ptr<Rect> hitButton;
    unique_ptr<Rect> standButton;

    vector<unique_ptr<Rect>> playerCardRects;
    vector<unique_ptr<Rect>> dealerCardRects;

    double MouseX, MouseY;
    bool mousePressedLastFrame = false;

    mat4 PROJECTION;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

public:
    Engine();
    ~Engine();

    unsigned int initWindow(bool debug = false);
    void initShaders();
    void initShapes();

    void dealInitialCards();
    void playerHit();
    void playerStand();
    void dealerTurn();
    void checkWinner();
    void resetGame();

    void processInput();
    void update();
    void render();

    bool shouldClose();
};

#endif