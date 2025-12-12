#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>

// Estados del juego
enum GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

// Clase Bala
class Bullet {
public:
    sf::RectangleShape shape;
    float speed;
    bool fromPlayer;
    
    Bullet(float x, float y, bool isPlayer) {
        shape.setSize(sf::Vector2f(4, 12));
        shape.setPosition(x, y);
        fromPlayer = isPlayer;
        
        if (isPlayer) {
            shape.setFillColor(sf::Color::Yellow);
            speed = -8.0f; // Arriba
        } else {
            shape.setFillColor(sf::Color::Red);
            speed = 4.0f;  // Abajo
        }
    }
    
    void update() {
        shape.move(0, speed);
    }
    
    bool isOffScreen() {
        return shape.getPosition().y < 0 || shape.getPosition().y > 600;
    }
    
    sf::FloatRect getBounds() {
        return shape.getGlobalBounds();
    }
};

// Clase Jugador
class Player {
public:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    int lives;
    sf::Clock shootCooldown;
    
    Player() {
        // Cargar la textura desde la imagen
        if (!texture.loadFromFile("docs/images/nave.png")) {
            // Si falla la carga, mostrar error en consola
            std::cerr << "Error: No se pudo cargar docs/images/nave.png" << std::endl;
        }
        
        sprite.setTexture(texture);
        
        // Escalar la imagen para que tenga un tamaño apropiado (40x30 pixeles)
        // Ajusta estos valores según el tamaño de tu imagen
        float scaleX = 40.0f / texture.getSize().x;
        float scaleY = 30.0f / texture.getSize().y;
        sprite.setScale(scaleX, scaleY);
        
        sprite.setPosition(380, 540);
        speed = 6.0f;
        lives = 10;
    }
    
    void moveLeft() {
        if (sprite.getPosition().x > 0)
            sprite.move(-speed, 0);
    }
    
    void moveRight() {
        sf::FloatRect bounds = sprite.getGlobalBounds();
        if (sprite.getPosition().x + bounds.width < 800)
            sprite.move(speed, 0);
    }
    
    bool canShoot() {
        return shootCooldown.getElapsedTime().asSeconds() > 0.3f;
    }
    
    void resetShootCooldown() {
        shootCooldown.restart();
    }
    
    sf::Vector2f getShootPosition() {
        sf::FloatRect bounds = sprite.getGlobalBounds();
        return sf::Vector2f(
            sprite.getPosition().x + bounds.width / 2 - 2,
            sprite.getPosition().y
        );
    }
    
    sf::FloatRect getBounds() {
        return sprite.getGlobalBounds();
    }
}; // <-- ESTA LLAVE FALTABA

// Clase Enemigo
class Enemy {
private:
    static sf::Texture texture0;
    static sf::Texture texture1;
    static sf::Texture texture2;
    static sf::Texture texture3;
    static bool texturesLoaded;
    
public:
    sf::Sprite sprite;
    int points;
    sf::Clock shootCooldown;
    
    static void loadTextures() {
        if (!texturesLoaded) {
            texture0.loadFromFile("docs/images/Human 1.png");
            texture1.loadFromFile("docs/images/Human 2.png");
            texture2.loadFromFile("docs/images/Human 3.png");
            texture3.loadFromFile("docs/images/human 4.png");
            texturesLoaded = true;
        }
    }
    
    Enemy(float x, float y, int row) {
        loadTextures();
        
        // Seleccionar la textura según la fila
        sf::Texture* selectedTexture = nullptr;
        switch(row) {
            case 0: selectedTexture = &texture0; break;
            case 1: selectedTexture = &texture1; break;
            case 2: selectedTexture = &texture2; break;
            case 3: selectedTexture = &texture3; break;
        }
        
        if (selectedTexture) {
            sprite.setTexture(*selectedTexture);
        }
        
        // Escalar la imagen para que tenga un tamaño apropiado (45x35 píxeles)
        if (selectedTexture && selectedTexture->getSize().x > 0 && selectedTexture->getSize().y > 0) {
            float scaleX = 45.0f / selectedTexture->getSize().x;
            float scaleY = 35.0f / selectedTexture->getSize().y;
            sprite.setScale(scaleX, scaleY);
        }
        
        sprite.setPosition(x, y);
        points = (row + 1) * 10;
    }
    
    bool canShoot() {
        return shootCooldown.getElapsedTime().asSeconds() > 2.0f && (rand() % 100) < 1;
    }
    
    void resetShootCooldown() {
        shootCooldown.restart();
    }
    
    sf::Vector2f getShootPosition() {
        sf::FloatRect bounds = sprite.getGlobalBounds();
        return sf::Vector2f(
            sprite.getPosition().x + bounds.width / 2 - 2,
            sprite.getPosition().y + bounds.height
        );
    }
    
    sf::FloatRect getBounds() {
        return sprite.getGlobalBounds();
    }
};

// Inicializar las texturas estáticas
sf::Texture Enemy::texture0;
sf::Texture Enemy::texture1;
sf::Texture Enemy::texture2;
sf::Texture Enemy::texture3;
bool Enemy::texturesLoaded = false;

// Clase Estructura de Protección
class Bunker {
public:
    sf::RectangleShape shape;
    int health;
    
    Bunker(float x, float y) {
        shape.setSize(sf::Vector2f(80, 60));
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Yellow);
        shape.setOutlineColor(sf::Color(150, 150, 0));
        shape.setOutlineThickness(2);
        health = 10;
    }
    
    void takeDamage() {
        health--;
        int alpha = (health * 255) / 10;
        sf::Color color = shape.getFillColor();
        color.a = alpha;
        shape.setFillColor(color);
    }
    
    bool isDestroyed() {
        return health <= 0;
    }
    
    sf::FloatRect getBounds() {
        return shape.getGlobalBounds();
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));
    
    // Crear ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "Galaga Invertido");
    window.setFramerateLimit(60);
    
    // Cargar fuente
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/Minecraft.ttf")) {
        return -1;
    }
    
    // Música (opcional)
    sf::Music music;
    if (music.openFromFile("assets/music/musica.ogg")) {
        music.setLoop(true);
        music.play();
    }
    
    // Estado del juego
    GameState gameState = MENU;
    int score = 0;
    bool victory = false;
    
    // Jugador
    Player player;
    
    // Balas
    std::vector<Bullet> playerBullets;
    std::vector<Bullet> enemyBullets;
    
    // Enemigos
    std::vector<Enemy> enemies;
    float enemyMoveX = 1.5f;
    
    // Estructuras
    std::vector<Bunker> bunkers;
    
    // Textos del menú
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::Cyan);
    titleText.setString("GALAGA INVERTIDO");
    titleText.setPosition(200, 200);
    
    sf::Text startText;
    startText.setFont(font);
    startText.setCharacterSize(24);
    startText.setFillColor(sf::Color::Green);
    startText.setString("Presiona ENTER para iniciar");
    startText.setPosition(220, 350);
    
    // Textos del HUD
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);
    
    sf::Text livesText;
    livesText.setFont(font);
    livesText.setCharacterSize(20);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(10, 35);
    
    // Textos de Game Over
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER");
    gameOverText.setPosition(250, 250);
    
    sf::Text victoryText;
    victoryText.setFont(font);
    victoryText.setCharacterSize(48);
    victoryText.setFillColor(sf::Color::Green);
    victoryText.setString("VICTORIA!");
    victoryText.setPosition(280, 250);
    
    sf::Text finalScoreText;
    finalScoreText.setFont(font);
    finalScoreText.setCharacterSize(24);
    finalScoreText.setFillColor(sf::Color::White);
    finalScoreText.setPosition(280, 330);
    
    sf::Text restartText;
    restartText.setFont(font);
    restartText.setCharacterSize(20);
    restartText.setFillColor(sf::Color::Yellow);
    restartText.setString("R: Reiniciar | ESC: Menu");
    restartText.setPosition(250, 400);
    
    // Función para inicializar el juego
    auto initGame = [&]() {
        gameState = PLAYING;
        score = 0;
        victory = false;
        enemyMoveX = 1.5f;
        
        // Reiniciar jugador
        player.lives = 10;
        player.sprite.setPosition(380, 540);
        
        // Limpiar balas
        playerBullets.clear();
        enemyBullets.clear();
        
        // Crear enemigos
        enemies.clear();
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 8; col++) {
                enemies.push_back(Enemy(
                    100 + col * 80,
                    50 + row * 60,
                    row
                ));
            }
        }
        
        // Crear bunkers
        bunkers.clear();
        for (int i = 0; i < 4; i++) {
            bunkers.push_back(Bunker(100 + i * 180, 450));
        }
    };
    
    // Loop principal
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyPressed) {
                // Desde el menú
                if (gameState == MENU && event.key.code == sf::Keyboard::Enter) {
                    initGame();
                }
                
                // Desde Game Over
                if (gameState == GAME_OVER) {
                    if (event.key.code == sf::Keyboard::R) {
                        initGame();
                    } else if (event.key.code == sf::Keyboard::Escape) {
                        gameState = MENU;
                    }
                }
            }
        }
        
        // Lógica del juego
        if (gameState == PLAYING) {
            // Controles del jugador
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                player.moveLeft();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                player.moveRight();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (player.canShoot()) {
                    sf::Vector2f pos = player.getShootPosition();
                    playerBullets.push_back(Bullet(pos.x, pos.y, true));
                    player.resetShootCooldown();
                }
            }
            
            // Mover enemigos
            bool changeDirection = false;
            for (auto& enemy : enemies) {
                enemy.sprite.move(enemyMoveX, 0);
                sf::FloatRect bounds = enemy.sprite.getGlobalBounds();
                if (enemy.sprite.getPosition().x <= 0 || 
                    enemy.sprite.getPosition().x + bounds.width >= 800) {
                    changeDirection = true;
                }
            }
            
            if (changeDirection) {
                enemyMoveX *= -1;
                for (auto& enemy : enemies) {
                    enemy.sprite.move(0, 10); // Bajar un poco
                }
            }
            
            // Enemigos disparan
            for (auto& enemy : enemies) {
                if (enemy.canShoot()) {
                    sf::Vector2f pos = enemy.getShootPosition();
                    enemyBullets.push_back(Bullet(pos.x, pos.y, false));
                    enemy.resetShootCooldown();
                }
            }
            
            // Actualizar balas del jugador
            for (auto it = playerBullets.begin(); it != playerBullets.end();) {
                it->update();
                if (it->isOffScreen()) {
                    it = playerBullets.erase(it);
                } else {
                    ++it;
                }
            }
            
            // Actualizar balas enemigas
            for (auto it = enemyBullets.begin(); it != enemyBullets.end();) {
                it->update();
                if (it->isOffScreen()) {
                    it = enemyBullets.erase(it);
                } else {
                    ++it;
                }
            }
            
            // Colisiones: Balas del jugador vs Enemigos
            for (auto itBullet = playerBullets.begin(); itBullet != playerBullets.end();) {
                bool bulletRemoved = false;
                for (auto itEnemy = enemies.begin(); itEnemy != enemies.end();) {
                    if (itBullet->getBounds().intersects(itEnemy->getBounds())) {
                        score += itEnemy->points;
                        itEnemy = enemies.erase(itEnemy);
                        itBullet = playerBullets.erase(itBullet);
                        bulletRemoved = true;
                        break;
                    } else {
                        ++itEnemy;
                    }
                }
                if (!bulletRemoved)
                    ++itBullet;
            }
            
            // Colisiones: Balas del jugador vs Bunkers
            for (auto itBullet = playerBullets.begin(); itBullet != playerBullets.end();) {
                bool bulletRemoved = false;
                for (auto& bunker : bunkers) {
                    if (!bunker.isDestroyed() && itBullet->getBounds().intersects(bunker.getBounds())) {
                        bunker.takeDamage();
                        itBullet = playerBullets.erase(itBullet);
                        bulletRemoved = true;
                        break;
                    }
                }
                if (!bulletRemoved)
                    ++itBullet;
            }
            
            // Colisiones: Balas enemigas vs Jugador
            for (auto itBullet = enemyBullets.begin(); itBullet != enemyBullets.end();) {
                if (itBullet->getBounds().intersects(player.getBounds())) {
                    player.lives--;
                    itBullet = enemyBullets.erase(itBullet);
                    if (player.lives <= 0) {
                        gameState = GAME_OVER;
                        victory = false;
                    }
                } else {
                    ++itBullet;
                }
            }
            
            // Colisiones: Balas enemigas vs Bunkers
            for (auto itBullet = enemyBullets.begin(); itBullet != enemyBullets.end();) {
                bool bulletRemoved = false;
                for (auto& bunker : bunkers) {
                    if (!bunker.isDestroyed() && itBullet->getBounds().intersects(bunker.getBounds())) {
                        bunker.takeDamage();
                        itBullet = enemyBullets.erase(itBullet);
                        bulletRemoved = true;
                        break;
                    }
                }
                if (!bulletRemoved)
                    ++itBullet;
            }
            
            // Verificar victoria
            if (enemies.empty() && score > 0) {
                gameState = GAME_OVER;
                victory = true;
            }
            
            // Verificar si los enemigos llegaron muy abajo
            for (auto& enemy : enemies) {
                if (enemy.sprite.getPosition().y > 520) {
                    gameState = GAME_OVER;
                    victory = false;
                }
            }
            
            // Actualizar HUD
            scoreText.setString("Puntos: " + std::to_string(score));
            livesText.setString("Vidas: " + std::to_string(player.lives));
        }
        
        // Renderizar
        window.clear(sf::Color::Black);
        
        if (gameState == MENU) {
            window.draw(titleText);
            window.draw(startText);
        }
        else if (gameState == PLAYING) {
            // Dibujar jugador
            window.draw(player.sprite);
            
            // Dibujar enemigos
            for (auto& enemy : enemies) {
                window.draw(enemy.sprite);
            }
            
            // Dibujar bunkers
            for (auto& bunker : bunkers) {
                if (!bunker.isDestroyed()) {
                    window.draw(bunker.shape);
                }
            }
            
            // Dibujar balas
            for (auto& bullet : playerBullets) {
                window.draw(bullet.shape);
            }
            for (auto& bullet : enemyBullets) {
                window.draw(bullet.shape);
            }
            
            // Dibujar HUD
            window.draw(scoreText);
            window.draw(livesText);
        }
        else if (gameState == GAME_OVER) {
            if (victory) {
                window.draw(victoryText);
            } else {
                window.draw(gameOverText);
            }
            
            finalScoreText.setString("Puntos finales: " + std::to_string(score));
            window.draw(finalScoreText);
            window.draw(restartText);
        }
        
        window.display();
    }
    
    return 0;
}