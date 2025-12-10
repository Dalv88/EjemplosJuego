#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

// Clase Bala
class Bala
{
public:
    sf::Sprite sprite;
    float velocidad;
    bool esDelJugador;

    Bala(sf::Texture& texture, sf::Vector2f position, bool jugador)
    {
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setScale(0.5f, 0.5f);
        esDelJugador = jugador;
        velocidad = jugador ? -5.0f : 3.0f; // Negativo = arriba, positivo = abajo
    }

    void update()
    {
        sprite.move(0, velocidad);
    }

    bool fueraDePantalla(int altoVentana)
    {
        return sprite.getPosition().y < 0 || sprite.getPosition().y > altoVentana;
    }

    sf::FloatRect getBounds()
    {
        return sprite.getGlobalBounds();
    }
};

// Clase Nave (Jugador)
class Nave
{
public:
    sf::Sprite sprite;
    float velocidad;
    int vidas;
    sf::Clock disparoCooldown;

    Nave(sf::Texture& texture, sf::Vector2f position)
    {
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setScale(0.8f, 0.8f);
        velocidad = 5.0f;
        vidas = 3;
    }

    void moverIzquierda()
    {
        if (sprite.getPosition().x > 0)
            sprite.move(-velocidad, 0);
    }

    void moverDerecha(int anchoVentana)
    {
        if (sprite.getPosition().x + sprite.getGlobalBounds().width < anchoVentana)
            sprite.move(velocidad, 0);
    }

    bool puedeDisparar()
    {
        return disparoCooldown.getElapsedTime().asSeconds() > 0.3f;
    }

    void reiniciarCooldown()
    {
        disparoCooldown.restart();
    }

    sf::FloatRect getBounds()
    {
        return sprite.getGlobalBounds();
    }

    sf::Vector2f getPosicionDisparo()
    {
        return sf::Vector2f(
            sprite.getPosition().x + sprite.getGlobalBounds().width / 2 - 10,
            sprite.getPosition().y
        );
    }
};

// Clase Enemigo (Humanos)
class Enemigo
{
public:
    sf::Sprite sprite;
    int tipo;
    int puntos;
    sf::Clock disparoCooldown;

    Enemigo(sf::Texture& texture, sf::Vector2f position, int tipoEnemigo)
    {
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setScale(0.6f, 0.6f);
        tipo = tipoEnemigo;
        puntos = (tipo + 1) * 10;
    }

    bool puedeDisparar()
    {
        // Disparo aleatorio
        return disparoCooldown.getElapsedTime().asSeconds() > 2.0f && (rand() % 100) < 2;
    }

    void reiniciarCooldown()
    {
        disparoCooldown.restart();
    }

    sf::FloatRect getBounds()
    {
        return sprite.getGlobalBounds();
    }

    sf::Vector2f getPosicionDisparo()
    {
        return sf::Vector2f(
            sprite.getPosition().x + sprite.getGlobalBounds().width / 2 - 10,
            sprite.getPosition().y + sprite.getGlobalBounds().height
        );
    }

    void mover(float offsetX, float offsetY)
    {
        sprite.move(offsetX, offsetY);
    }
};

// Clase Estructura (Protección)
class Estructura
{
public:
    sf::Sprite sprite;
    int resistencia;

    Estructura(sf::Texture& texture, sf::Vector2f position)
    {
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setScale(0.7f, 0.7f);
        resistencia = 5;
    }

    void recibirDanio()
    {
        resistencia--;
        // Hacer más transparente según el daño
        int alpha = (resistencia * 255) / 5;
        sprite.setColor(sf::Color(255, 255, 255, alpha));
    }

    bool estaDestruida()
    {
        return resistencia <= 0;
    }

    sf::FloatRect getBounds()
    {
        return sprite.getGlobalBounds();
    }
};

int main()
{
    srand(static_cast<unsigned>(time(0)));

    // Crear ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "Galaga Invertido - Humanos Atacan!");
    window.setFramerateLimit(60);

    // Cargar texturas
    sf::Texture texturaNave, texturaHuman1, texturaHuman2, texturaHuman3, texturaHuman4;
    sf::Texture texturaBalaAliada, texturaBalaEnemiga, texturaEstructura;

    if (!texturaNave.loadFromFile("assets/images/Nave.png") ||
        !texturaHuman1.loadFromFile("assets/images/Human 1.png") ||
        !texturaHuman2.loadFromFile("assets/images/Human 2.png") ||
        !texturaHuman3.loadFromFile("assets/images/Human 3.png") ||
        !texturaHuman4.loadFromFile("assets/images/human 4.png") ||
        !texturaBalaAliada.loadFromFile("assets/images/BalaAliada.png") ||
        !texturaBalaEnemiga.loadFromFile("assets/images/BalaEnemigo.png") ||
        !texturaEstructura.loadFromFile("assets/images/Estructura.png"))
    {
        return -1;
    }

    // Cargar fuente
    sf::Font fuente;
    if (!fuente.loadFromFile("assets/fonts/Minecraft.ttf"))
    {
        return -1;
    }

    // Cargar música
    sf::Music musica;
    if (!musica.openFromFile("assets/music/musica.ogg"))
    {
        return -1;
    }
    musica.setLoop(true);
    musica.play();

    // Crear jugador
    Nave jugador(texturaNave, sf::Vector2f(360, 520));

    // Crear enemigos (formación de humanos)
    std::vector<Enemigo> enemigos;
    sf::Texture* texturasEnemigos[] = {&texturaHuman1, &texturaHuman2, &texturaHuman3, &texturaHuman4};
    
    int filas = 4;
    int columnas = 8;
    float espacioX = 80;
    float espacioY = 60;
    float inicioX = 80;
    float inicioY = 30;

    for (int fila = 0; fila < filas; fila++)
    {
        for (int col = 0; col < columnas; col++)
        {
            int tipoEnemigo = fila % 4;
            enemigos.push_back(Enemigo(
                *texturasEnemigos[tipoEnemigo],
                sf::Vector2f(inicioX + col * espacioX, inicioY + fila * espacioY),
                tipoEnemigo
            ));
        }
    }

    // Crear estructuras defensivas
    std::vector<Estructura> estructuras;
    int numEstructuras = 4;
    float espacioEstructuras = 800.0f / (numEstructuras + 1);
    
    for (int i = 1; i <= numEstructuras; i++)
    {
        estructuras.push_back(Estructura(
            texturaEstructura,
            sf::Vector2f(espacioEstructuras * i - 40, 420)
        ));
    }

    // Vectores de balas
    std::vector<Bala> balasJugador;
    std::vector<Bala> balasEnemigos;

    // Variables de juego
    int puntuacion = 0;
    bool juegoActivo = true;
    bool victoria = false;
    float movimientoEnemigoX = 1.0f;
    bool moverAbajo = false;

    // Textos del HUD
    sf::Text textoPuntuacion;
    textoPuntuacion.setFont(fuente);
    textoPuntuacion.setCharacterSize(24);
    textoPuntuacion.setFillColor(sf::Color::White);
    textoPuntuacion.setPosition(10, 10);

    sf::Text textoVidas;
    textoVidas.setFont(fuente);
    textoVidas.setCharacterSize(24);
    textoVidas.setFillColor(sf::Color::White);
    textoVidas.setPosition(10, 40);

    sf::Text textoGameOver;
    textoGameOver.setFont(fuente);
    textoGameOver.setCharacterSize(48);
    textoGameOver.setFillColor(sf::Color::Red);
    textoGameOver.setString("GAME OVER");
    textoGameOver.setPosition(250, 250);

    sf::Text textoVictoria;
    textoVictoria.setFont(fuente);
    textoVictoria.setCharacterSize(48);
    textoVictoria.setFillColor(sf::Color::Green);
    textoVictoria.setString("VICTORIA!");
    textoVictoria.setPosition(280, 250);

    // Loop principal del juego
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            // Reiniciar juego si se presiona R y el juego no está activo
            if (!juegoActivo && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
            {
                // Reiniciar variables
                juegoActivo = true;
                victoria = false;
                puntuacion = 0;
                movimientoEnemigoX = 1.0f;
                
                // Reiniciar jugador
                jugador.vidas = 3;
                jugador.sprite.setPosition(360, 520);
                
                // Limpiar balas
                balasJugador.clear();
                balasEnemigos.clear();
                
                // Recrear enemigos
                enemigos.clear();
                for (int fila = 0; fila < filas; fila++)
                {
                    for (int col = 0; col < columnas; col++)
                    {
                        int tipoEnemigo = fila % 4;
                        enemigos.push_back(Enemigo(
                            *texturasEnemigos[tipoEnemigo],
                            sf::Vector2f(inicioX + col * espacioX, inicioY + fila * espacioY),
                            tipoEnemigo
                        ));
                    }
                }
                
                // Recrear estructuras
                estructuras.clear();
                for (int i = 1; i <= numEstructuras; i++)
                {
                    estructuras.push_back(Estructura(
                        texturaEstructura,
                        sf::Vector2f(espacioEstructuras * i - 40, 420)
                    ));
                }
            }
        }

        if (juegoActivo)
        {
            // Controles del jugador
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                jugador.moverIzquierda();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                jugador.moverDerecha(800);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                if (jugador.puedeDisparar())
                {
                    balasJugador.push_back(Bala(texturaBalaAliada, jugador.getPosicionDisparo(), true));
                    jugador.reiniciarCooldown();
                }
            }

            // Mover enemigos en formación
            bool cambiarDireccion = false;
            for (auto& enemigo : enemigos)
            {
                enemigo.mover(movimientoEnemigoX, 0);
                if (enemigo.sprite.getPosition().x <= 0 || 
                    enemigo.sprite.getPosition().x + enemigo.sprite.getGlobalBounds().width >= 800)
                {
                    cambiarDireccion = true;
                }
            }

            if (cambiarDireccion)
            {
                movimientoEnemigoX *= -1;
                for (auto& enemigo : enemigos)
                {
                    enemigo.mover(0, 20); // Bajar una fila
                }
            }

            // Enemigos disparan
            for (auto& enemigo : enemigos)
            {
                if (enemigo.puedeDisparar())
                {
                    balasEnemigos.push_back(Bala(texturaBalaEnemiga, enemigo.getPosicionDisparo(), false));
                    enemigo.reiniciarCooldown();
                }
            }

            // Actualizar balas del jugador
            for (auto it = balasJugador.begin(); it != balasJugador.end();)
            {
                it->update();
                if (it->fueraDePantalla(600))
                {
                    it = balasJugador.erase(it);
                }
                else
                {
                    ++it;
                }
            }

            // Actualizar balas enemigas
            for (auto it = balasEnemigos.begin(); it != balasEnemigos.end();)
            {
                it->update();
                if (it->fueraDePantalla(600))
                {
                    it = balasEnemigos.erase(it);
                }
                else
                {
                    ++it;
                }
            }

            // Colisiones: Balas del jugador vs Enemigos
            for (auto itBala = balasJugador.begin(); itBala != balasJugador.end();)
            {
                bool balaEliminada = false;
                for (auto itEnemigo = enemigos.begin(); itEnemigo != enemigos.end();)
                {
                    if (itBala->getBounds().intersects(itEnemigo->getBounds()))
                    {
                        puntuacion += itEnemigo->puntos;
                        itEnemigo = enemigos.erase(itEnemigo);
                        itBala = balasJugador.erase(itBala);
                        balaEliminada = true;
                        break;
                    }
                    else
                    {
                        ++itEnemigo;
                    }
                }
                if (!balaEliminada)
                    ++itBala;
            }

            // Colisiones: Balas del jugador vs Estructuras
            for (auto itBala = balasJugador.begin(); itBala != balasJugador.end();)
            {
                bool balaEliminada = false;
                for (auto& estructura : estructuras)
                {
                    if (!estructura.estaDestruida() && itBala->getBounds().intersects(estructura.getBounds()))
                    {
                        estructura.recibirDanio();
                        itBala = balasJugador.erase(itBala);
                        balaEliminada = true;
                        break;
                    }
                }
                if (!balaEliminada)
                    ++itBala;
            }

            // Colisiones: Balas enemigas vs Jugador
            for (auto itBala = balasEnemigos.begin(); itBala != balasEnemigos.end();)
            {
                if (itBala->getBounds().intersects(jugador.getBounds()))
                {
                    jugador.vidas--;
                    itBala = balasEnemigos.erase(itBala);
                    if (jugador.vidas <= 0)
                    {
                        juegoActivo = false;
                    }
                }
                else
                {
                    ++itBala;
                }
            }

            // Colisiones: Balas enemigas vs Estructuras
            for (auto itBala = balasEnemigos.begin(); itBala != balasEnemigos.end();)
            {
                bool balaEliminada = false;
                for (auto& estructura : estructuras)
                {
                    if (!estructura.estaDestruida() && itBala->getBounds().intersects(estructura.getBounds()))
                    {
                        estructura.recibirDanio();
                        itBala = balasEnemigos.erase(itBala);
                        balaEliminada = true;
                        break;
                    }
                }
                if (!balaEliminada)
                    ++itBala;
            }

            // Verificar victoria
            if (enemigos.empty())
            {
                juegoActivo = false;
                victoria = true;
            }

            // Verificar game over si los enemigos llegan muy abajo
            for (auto& enemigo : enemigos)
            {
                if (enemigo.sprite.getPosition().y + enemigo.sprite.getGlobalBounds().height > 480)
                {
                    juegoActivo = false;
                }
            }

            // Actualizar HUD
            textoPuntuacion.setString("Puntuacion: " + std::to_string(puntuacion));
            textoVidas.setString("Vidas: " + std::to_string(jugador.vidas));
        }

        // Renderizar
        window.clear(sf::Color::Black);

        if (juegoActivo)
        {
            // Dibujar jugador
            window.draw(jugador.sprite);

            // Dibujar enemigos
            for (auto& enemigo : enemigos)
            {
                window.draw(enemigo.sprite);
            }

            // Dibujar estructuras
            for (auto& estructura : estructuras)
            {
                if (!estructura.estaDestruida())
                {
                    window.draw(estructura.sprite);
                }
            }

            // Dibujar balas
            for (auto& bala : balasJugador)
            {
                window.draw(bala.sprite);
            }
            for (auto& bala : balasEnemigos)
            {
                window.draw(bala.sprite);
            }

            // Dibujar HUD
            window.draw(textoPuntuacion);
            window.draw(textoVidas);
        }
        else
        {
            // Pantalla de fin de juego
            if (victoria)
            {
                window.draw(textoVictoria);
            }
            else
            {
                window.draw(textoGameOver);
            }
            
            sf::Text textoFinal;
            textoFinal.setFont(fuente);
            textoFinal.setCharacterSize(24);
            textoFinal.setFillColor(sf::Color::White);
            textoFinal.setString("Puntuacion final: " + std::to_string(puntuacion));
            textoFinal.setPosition(280, 320);
            window.draw(textoFinal);
            
            sf::Text textoReiniciar;
            textoReiniciar.setFont(fuente);
            textoReiniciar.setCharacterSize(20);
            textoReiniciar.setFillColor(sf::Color::Yellow);
            textoReiniciar.setString("Presiona R para reiniciar");
            textoReiniciar.setPosition(260, 370);
            window.draw(textoReiniciar);
        }

        window.display();
    }

    return 0;
}
