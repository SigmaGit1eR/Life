#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <chrono>
#include <cstdlib>  
#include <ctime>    

using namespace sf;
using namespace std;
using namespace chrono;

enum State {
    DEAD = 0,
    ALIVE = 1
};

class Tile {
public:
    Tile(unsigned int size, Vector2u position);
    void setState(State newState);
    State getState() const;
    Vector2u getPosition() const;
    bool contains(Vector2i point) const;
    void prepareNextState(int neighbors);
    void updateState();
private:
    const unsigned int m_TileSize;
    State m_currentState;
    State m_nextState;
    Vector2u m_position;
};

Tile::Tile(unsigned int size, Vector2u position) :
    m_TileSize(size),
    m_position(position),
    m_currentState(State::DEAD),
    m_nextState(State::DEAD)
{
}

void Tile::setState(State newState) {
    m_currentState = newState;
}

State Tile::getState() const {
    return m_currentState;
}

Vector2u Tile::getPosition() const {
    return m_position;
}

bool Tile::contains(Vector2i point) const {
    return (point.x >= static_cast<int>(m_position.x) && point.x < static_cast<int>(m_position.x + m_TileSize) &&
        point.y >= static_cast<int>(m_position.y) && point.y < static_cast<int>(m_position.y + m_TileSize));
}

void Tile::prepareNextState(int neighbors) {
    if (m_currentState == State::ALIVE) {
        m_nextState = (neighbors == 2 || neighbors == 3) ? State::ALIVE : State::DEAD;
    }
    else {
        m_nextState = (neighbors == 3) ? State::ALIVE : State::DEAD;
    }
}

void Tile::updateState() {
    m_currentState = m_nextState;
}

class GameOfLife {
public:
    GameOfLife(unsigned int width, unsigned int height, unsigned int tileSize);
    void handleInput(Vector2i mousePos, bool mousePressed);
    void update(int seconds);
    void render(RenderWindow& window);
    void togglePause();
    void clear();
    void randomize();
private:
    vector<Tile> m_tiles;
    unsigned int m_tileSize;
    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_tileCountX;
    unsigned int m_tileCountY;
    bool m_isPaused;
    bool m_mouseWasPressed;
    steady_clock::time_point m_lastUpdate;

    int countNeighbors(int x, int y) const;
};

GameOfLife::GameOfLife(unsigned int width, unsigned int height, unsigned int tileSize) :
    m_width(width),
    m_height(height),
    m_tileSize(tileSize),
    m_tileCountX(width / tileSize),
    m_tileCountY(height / tileSize),
    m_isPaused(true),         
    m_mouseWasPressed(false)
{
    
    for (unsigned int y = 0; y < m_tileCountY; y++) {
        for (unsigned int x = 0; x < m_tileCountX; x++) {
            m_tiles.emplace_back(m_tileSize, Vector2u(x * m_tileSize, y * m_tileSize));
        }
    }
    m_lastUpdate = steady_clock::now();
}

void GameOfLife::handleInput(Vector2i mousePos, bool mousePressed) {
    if (mousePressed && !m_mouseWasPressed) {
        for (auto& tile : m_tiles) {
            if (tile.contains(mousePos)) {
                tile.setState(tile.getState() == State::DEAD ? State::ALIVE : State::DEAD);
                break;
            }
        }
    }
    m_mouseWasPressed = mousePressed;
}

int GameOfLife::countNeighbors(int x, int y) const {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;

            int nx = x + i;
            int ny = y + j;

            
            if (nx < 0) nx = m_tileCountX - 1;
            if (nx >= static_cast<int>(m_tileCountX)) nx = 0;
            if (ny < 0) ny = m_tileCountY - 1;
            if (ny >= static_cast<int>(m_tileCountY)) ny = 0;

            int index = ny * m_tileCountX + nx;
            if (m_tiles[index].getState() == State::ALIVE) {
                count++;
            }
        }
    }
    return count;
}

void GameOfLife::update(int seconds) {
    if (m_isPaused) return;

    auto now = steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - m_lastUpdate).count() < seconds) return;

    m_lastUpdate = now;

  
    for (unsigned int y = 0; y < m_tileCountY; y++) {
        for (unsigned int x = 0; x < m_tileCountX; x++) {
            int idx = y * m_tileCountX + x;
            int neighbors = countNeighbors(x, y);
            m_tiles[idx].prepareNextState(neighbors);
        }
    }
  
    for (auto& tile : m_tiles) {
        tile.updateState();
    }
}

void GameOfLife::render(RenderWindow& window) {
    window.clear(Color::Black);
    for (auto& tile : m_tiles) {
        if (tile.getState() == State::ALIVE) {
            RectangleShape cell(Vector2f(m_tileSize - 1, m_tileSize - 1));
            cell.setFillColor(Color::White);
            cell.setPosition(Vector2f(tile.getPosition()));
            window.draw(cell);
        }
    }
}

void GameOfLife::togglePause() {
    m_isPaused = !m_isPaused;
}

void GameOfLife::clear() {
    for (auto& tile : m_tiles) {
        tile.setState(State::DEAD);
    }
}

void GameOfLife::randomize() {
    srand(static_cast<unsigned>(time(nullptr)));
    for (auto& tile : m_tiles) {
        tile.setState((rand() % 4 == 0) ? State::ALIVE : State::DEAD);
    }
}

int main() {
    const Vector2u windowSize(1920, 1080);
    const unsigned int tileSize = 40;

    RenderWindow window(VideoMode(windowSize.x, windowSize.y), "Game of Life", Style::Fullscreen);
    window.setFramerateLimit(60);

    GameOfLife game(windowSize.x, windowSize.y, tileSize);

    int UpdateTime = 30;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed ||
                (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Space) {
                    game.togglePause();
                }
                if (event.key.code == Keyboard::C) {
                    game.clear();
                }
                if (event.key.code == Keyboard::R) {
                    game.randomize();
                }
            }
        }

        Vector2i mousePos = Mouse::getPosition(window);
        bool mouseIsPressed = Mouse::isButtonPressed(Mouse::Left);
        game.handleInput(mousePos, mouseIsPressed);

        game.update(UpdateTime);
        game.render(window);
        window.display();
    }

    return 0;
}
