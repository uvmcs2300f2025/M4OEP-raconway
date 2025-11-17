#include "engine.h"

color red(1, 0, 0);
color black(0, 0, 0);
color green(0, 1, 0);
color white(1, 1, 1);
color gray(0.5, 0.5, 0.5);

Engine::Engine() : keys() {
    this->initWindow();
    this->initShaders();
    this->initShapes();

    state = start;
    deck.shuffle();
}

Engine::~Engine() {}

unsigned int Engine::initWindow(bool debug) {
    // Same as Confetti project
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);

    window = glfwCreateWindow(width, height, "Blackjack", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glViewport(0, 0, width, height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSwapInterval(1);

    return 0;
}

void Engine::initShaders() {
    // Same as Confetti project
    shaderManager = make_unique<ShaderManager>();
    shapeShader = shaderManager->loadShader("../res/shaders/shape.vert", "../res/shaders/shape.frag", nullptr, "shape");
    textShader = shaderManager->loadShader("../res/shaders/text.vert", "../res/shaders/text.frag", nullptr, "text");
    fontRenderer = make_unique<FontRenderer>(shaderManager->getShader("text"), "../res/fonts/MxPlus_IBM_BIOS.ttf", 24);

    PROJECTION = ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
    shapeShader.use();
    shapeShader.setMatrix4("projection", PROJECTION);
}

void Engine::initShapes() {
    // Create buttons
    hitButton = make_unique<Rect>(shapeShader, vec2(250, 100), vec2(100, 50), green);
    standButton = make_unique<Rect>(shapeShader, vec2(450, 100), vec2(100, 50), red);
}

void Engine::dealInitialCards() {
    // Clear old cards
    playerHand.clear();
    dealerHand.clear();
    playerCardRects.clear();
    dealerCardRects.clear();

    // Deal 2 cards to each
    playerHand.addCard(deck.dealCard());
    playerHand.addCard(deck.dealCard());
    dealerHand.addCard(deck.dealCard());
    dealerHand.addCard(deck.dealCard());

    // Create visual rectangles for player cards
    for (int i = 0; i < 2; i++) {
        Card card = playerHand.getCard(i);
        color cardColor = (card.getSuit() == "Hearts" || card.getSuit() == "Diamonds") ? red : black;
        playerCardRects.push_back(make_unique<Rect>(shapeShader,
                                   vec2(200 + i * 80, 250),
                                   vec2(60, 90),
                                   cardColor));
    }

    // Create visual rectangles for dealer cards
    for (int i = 0; i < 2; i++) {
        Card card = dealerHand.getCard(i);
        color cardColor = (card.getSuit() == "Hearts" || card.getSuit() == "Diamonds") ? red : black;
        dealerCardRects.push_back(make_unique<Rect>(shapeShader,
                                   vec2(200 + i * 80, 450),
                                   vec2(60, 90),
                                   cardColor));
    }
}

void Engine::playerHit() {
    playerHand.addCard(deck.dealCard());

    // Add visual card
    int i = playerCardRects.size();
    Card card = playerHand.getCard(i);
    color cardColor = (card.getSuit() == "Hearts" || card.getSuit() == "Diamonds") ? red : black;
    playerCardRects.push_back(make_unique<Rect>(shapeShader,
                               vec2(200 + i * 80, 250),
                               vec2(60, 90),
                               cardColor));

    // Check if bust
    if (playerHand.getValue() > 21) {
        state = playerLose;
    }
}

void Engine::playerStand() {
    dealerTurn();
    checkWinner();
}

void Engine::dealerTurn() {
    while (dealerHand.getValue() < 17) {
        dealerHand.addCard(deck.dealCard());

        // Add visual card
        int i = dealerCardRects.size();
        Card card = dealerHand.getCard(i);
        color cardColor = (card.getSuit() == "Hearts" || card.getSuit() == "Diamonds") ? red : black;
        dealerCardRects.push_back(make_unique<Rect>(shapeShader,
                                   vec2(200 + i * 80, 450),
                                   vec2(60, 90),
                                   cardColor));
    }
}

void Engine::checkWinner() {
    int playerValue = playerHand.getValue();
    int dealerValue = dealerHand.getValue();

    if (dealerValue > 21 || playerValue > dealerValue) {
        state = playerWin;
    } else if (playerValue == dealerValue) {
        state = tie;
    } else {
        state = playerLose;
    }
}

void Engine::resetGame() {
    deck.shuffle();
    state = playing;
    dealInitialCards();
}

void Engine::processInput() {
    glfwPollEvents();

    for (int key = 0; key < 1024; ++key) {
        if (glfwGetKey(window, key) == GLFW_PRESS)
            keys[key] = true;
        else if (glfwGetKey(window, key) == GLFW_RELEASE)
            keys[key] = false;
    }

    if (keys[GLFW_KEY_ESCAPE])
        glfwSetWindowShouldClose(window, true);

    // Start screen
    if (state == start && keys[GLFW_KEY_S]) {
        resetGame();
    }

    // Reset after win/lose
    if ((state == playerWin || state == playerLose || state == tie) && keys[GLFW_KEY_R]) {
        resetGame();
    }

    // Mouse input for buttons
    glfwGetCursorPos(window, &MouseX, &MouseY);
    MouseY = height - MouseY;

    bool mousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    bool mouseReleased = mousePressedLastFrame && !mousePressed;

    if (state == playing && mouseReleased) {
        if (hitButton->isOverlapping(vec2(MouseX, MouseY))) {
            playerHit();
        } else if (standButton->isOverlapping(vec2(MouseX, MouseY))) {
            playerStand();
        }
    }

    mousePressedLastFrame = mousePressed;
}

void Engine::update() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Engine::render() {
    glClearColor(0.1f, 0.5f, 0.1f, 1.0f); // Green felt background
    glClear(GL_COLOR_BUFFER_BIT);

    shapeShader.use();

    switch (state) {
        case start: {
            string message = "Press S to start Blackjack";
            fontRenderer->renderText(message, width/2 - (12 * message.length()), height/2, PROJECTION, 1, vec3{1, 1, 1});
            break;
        }
        case playing: {
            // Draw dealer cards
            for (auto& card : dealerCardRects) {
                card->setUniforms();
                card->draw();
            }

            // Draw player cards
            for (auto& card : playerCardRects) {
                card->setUniforms();
                card->draw();
            }

            // Draw buttons
            hitButton->setUniforms();
            hitButton->draw();
            standButton->setUniforms();
            standButton->draw();

            // Draw text
            fontRenderer->renderText("Dealer: " + to_string(dealerHand.getValue()), 50, 500, PROJECTION, 0.7, vec3{1, 1, 1});
            fontRenderer->renderText("Player: " + to_string(playerHand.getValue()), 50, 200, PROJECTION, 0.7, vec3{1, 1, 1});
            fontRenderer->renderText("HIT", hitButton->getPos().x - 18, hitButton->getPos().y - 5, PROJECTION, 0.5, vec3{1, 1, 1});
            fontRenderer->renderText("STAND", standButton->getPos().x - 30, standButton->getPos().y - 5, PROJECTION, 0.5, vec3{1, 1, 1});
            break;
        }
        case playerWin: {
            string message = "You Win! Press R to play again";
            fontRenderer->renderText(message, width/2 - (12 * message.length()), height/2, PROJECTION, 1, vec3{0, 1, 0});
            break;
        }
        case playerLose: {
            string message = "You Lose! Press R to play again";
            fontRenderer->renderText(message, width/2 - (12 * message.length()), height/2, PROJECTION, 1, vec3{1, 0, 0});
            break;
        }
        case tie: {
            string message = "Tie! Press R to play again";
            fontRenderer->renderText(message, width/2 - (12 * message.length()), height/2, PROJECTION, 1, vec3{1, 1, 0});
            break;
        }
    }

    glfwSwapBuffers(window);
}

bool Engine::shouldClose() {
    return glfwWindowShouldClose(window);
}