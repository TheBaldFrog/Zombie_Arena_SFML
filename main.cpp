#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main()
{
    enum class State
    {
        PAUSED,
        LEVELING_UP,
        GAME_OVER,
        PLAYING
    };

    State state = State::GAME_OVER;

    // Get the screen resolution and create an SFML window
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    resolution.x = 800;
    resolution.y = 700;

    RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Default);
    window.setFramerateLimit(120);

    View mainView(FloatRect(0, 0, resolution.x, resolution.y));

    Clock clock;

    // how long player has PLAYING
    Time gameTimeTotal;

    // mouse position in relation to world coordinates
    Vector2f mouseWorldPosition;
    Vector2i mouseScreenPosition;

    Player player;

    // The boundaries of the arena
    IntRect arena;

    while (window.isOpen())
    {
        /**
         * **************
         * * Handle input
         * **************
         */

        // Handle events by polling
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                // Pause a game while playing
                if (event.key.code == Keyboard::Return && state == State::PLAYING)
                {
                    state = State::PAUSED;
                }

                else if (event.key.code == Keyboard::Return && state == State::PAUSED)
                {
                    state = State::PLAYING;
                    //! Reset the clock so there isn't a frame jump
                    clock.restart();
                }

                else if (event.key.code == Keyboard::Return && state == State::GAME_OVER)
                {
                    state = State::LEVELING_UP;
                }

                if (state == State::PLAYING)
                {
                }
            }
        } //* End event polling

        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        /* if (event.type == sf::Event::TextEntered)
        {
            if (event.text.unicode < 128)
                std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
        } */

        /* if (event.type == sf::Event::Resized)
        {
            std::cout << "new width: " << event.size.width << std::endl;
            std::cout << "new height: " << event.size.height << std::endl;
        } */

        // Handle the player quitting
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Handle WASD while playing
        if (state == State::PLAYING)
        {
            if (Keyboard::isKeyPressed(Keyboard::W))
            {
                player.moveUp();
            }
            else
            {
                player.stopUp();
            }

            if (Keyboard::isKeyPressed(Keyboard::S))
            {
                player.moveDown();
            }
            else
            {
                player.stopDown();
            }

            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                player.moveLeft();
            }
            else
            {
                player.stopLeft();
            }

            if (Keyboard::isKeyPressed(Keyboard::D))
            {
                player.moveRight();
            }
            else
            {
                player.stopRight();
            }
        } //* End WASD while playing

        // Handle the LEVELING up state
        if (state == State::LEVELING_UP)
        {
            // Handle the player LEVELING up
            if (event.key.code == Keyboard::Num1)
            {
                state = State::PLAYING;
            }
        }

        if (state == State::PLAYING)
        {
            // Prepare the leveling
            arena.width = 500;
            arena.height = 500;
            arena.left = 0;
            arena.top = 0;

            int tileSize = 50;
            // Spawn the player in the middle of the arena
            player.spawn(arena, resolution, tileSize);

            //! Reset the clock so there isn't a frame jump
            clock.restart();
        } //* End LEVELING up

        /*
        ******************
        * UPDATE THE FRAME
        ******************
        */
        if (state == State::PLAYING)
        {
            // Update the delta time
            Time dt = clock.restart();
            gameTimeTotal += dt;

            float dtAsSeconds = dt.asSeconds();

            mouseScreenPosition = Mouse::getPosition();

            mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);

            // Update the player
            player.update(dtAsSeconds, Mouse::getPosition(window));

            //* Make a note of the players new position
            Vector2f playerPosition(player.getCenter());

            mainView.setCenter(player.getCenter());
        } //* End updating the scene

        /*
        ******************
        * UPDATE THE FRAME
        ******************
        */
        if (state == State::PLAYING)
        {
            window.clear();
            window.setView(mainView);
            window.draw(player.getSprite());
        }

        if (state == State::LEVELING_UP)
        {
        }

        if (state == State::PAUSED)
        {
        }

        if (state == State::GAME_OVER)
        {
        }

        window.display();

    } //* End game loop

    return 0;
}