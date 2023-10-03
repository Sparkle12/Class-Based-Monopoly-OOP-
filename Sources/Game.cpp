//
// Created by Adi on 5/16/2023.
//

#include "../Headers/Game.h"

Board Game::defaultBoard;

Game::Game() {

    /// Reserving space for up to 20 buttons (SFML can't copy spriters and textures so when the sprite vector resizes the sprites corrupt)
    texturi.reserve(20);
    sprites.reserve(20);
    butoane.reserve(20);


    font.loadFromFile("Fonts/MinimalPixel v2.ttf");

    money.setFont(font);
    money.setCharacterSize(36);
    money.setFillColor(sf::Color::White);

    /// Loading the textures for the buttons
    for (const std::string &path: texture_paths) {
        sf::Texture temp;
        temp.loadFromFile(path);
        texturi.emplace_back(temp);
    }

    /// Making the sprites for the buttons
    for (const auto &i: texturi) {
        sf::Sprite temp;
        temp.setTexture(i);
        sprites.emplace_back(temp);
    }

    /// Making the buttons
    int bt_count = 0;
    for (int i = 0; i < int(sprites.size()); i += 2) {
        butoane.emplace_back(sprites[i], sprites[i + 1], pozitii[bt_count]);
        bt_count++;
    }
}

[[maybe_unused]] Game::Game(std::vector<Player *> players, const Board &b) : jucatori(std::move(players)) {
    defaultBoard = b;
    /// Reserving space for up to 20 buttons (SFML can't copy spriters and textures so when the sprite vector resizes the sprites corrupt)
    texturi.reserve(20);
    sprites.reserve(20);
    butoane.reserve(20);

    font.loadFromFile("Fonts/MinimalPixel v2.ttf");

    money.setFont(font);
    money.setCharacterSize(36);
    money.setFillColor(sf::Color::White);

    /// Loading the textures for the buttons
    for (const std::string &path: texture_paths) {
        sf::Texture temp;
        temp.loadFromFile(path);
        texturi.emplace_back(temp);
    }

    /// Making the sprites for the buttons

    for (const auto &i: texturi) {
        sf::Sprite temp;
        temp.setTexture(i);
        sprites.emplace_back(temp);
    }

    /// Making the buttons
    int bt_count = 0;
    for (int i = 0; i < int(sprites.size()); i += 2) {
        butoane.emplace_back(sprites[i], sprites[i + 1], pozitii[bt_count]);
        bt_count++;
    }
}

void Game::play(sf::RenderWindow &window) {
    /// Player flags
    int end_turn = 0, rolled = 0, in_buy_house_menu = 0;


    Animation idle(0, 3, 0.3f);
    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event{};

        money.setString(std::to_string(jucatori[0]->getMoney()) + "$");
        money.setPosition(20, 20);

        if (in_buy_house_menu) {
            /// Making and drawing the buy house menu
            PropSelectMenu menu(jucatori[0]->getProps());
            menu.drawMenu(window);

            money.setPosition(20, 600);
            window.draw(money);

            /// Checking which buttons are clicked inside the menu
            menu.checkClick(window, event, jucatori, in_buy_house_menu);

        } else {
            idle.Update(deltaTime);

            window.clear(sf::Color::Green);

            defaultBoard.updateIndici();
            defaultBoard.drawBoard(window);


            for (Player *jucator: jucatori) {
                jucator->setTexture(idle.get_uvRect());
                jucator->drawPlayer(window, defaultBoard);
            }

            window.draw(money);

            /// Drawing the buttons
            /// butoane[0] is the Roll button
            /// butoane[1] is the Buy button
            /// butoane[2] is the can't buy button
            /// butoane[3] is the Buy house button (opens the buy house menu)
            /// butoane[4] is the End turn button
            /// butoane[5] is the Abillity button
            for (int i = 0; i < int(butoane.size()); i++) {
                int not_buyable = 0;

                ///Checking if the Buy button or Not buyable button shuld be drawn
                if (i == 1 &&
                    (defaultBoard[jucatori[0]->position()]->is_buyable() == 0 ||
                     jucatori[0]->getMoney() <
                     dynamic_cast<Property *>(defaultBoard[jucatori[0]->position()])->price())) {
                    i++;
                    not_buyable = 1;
                }

                ///Drawing buttons
                if (not_buyable == 1 || i != 2) {
                    butoane[i].isHovered(window);
                    butoane[i].drawButton(window);
                }
            }


            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                ///Checking the Roll has been pressed
                if (butoane[0].checkClick(window) && !rolled) {
                    rolled = 1;
                    jucatori[0]->move(defaultBoard);

                    ///Checking if the tile is not buyable
                    if (!(defaultBoard[jucatori[0]->position()]->is_buyable())) {

                        auto *p = dynamic_cast<Property *>(defaultBoard[jucatori[0]->position()]);
                        ///If it is a property tile pay the owner the rent
                        if (p) {
                            if (p->id() != 1)
                                jucatori[0]->pay(*jucatori[p->id() - 1], defaultBoard);
                        }
                            ///Else do the effect of the tile (The tax tile for example)
                        else {
                            auto *e = dynamic_cast<Effect *>(defaultBoard[jucatori[0]->position()]);
                            if (e)
                                jucatori[0]->do_effect(*e, defaultBoard);
                        }
                    }

                }

                ///Checking if the Buy button has been pressed
                if (butoane[1].checkClick(window)) {
                    ///Trying to buy the tile if possible and catch any errors thrown by buy menthod
                    try {
                        jucatori[0]->buy(defaultBoard);
                    }
                    catch (game_error &error) {
                        std::cout << error.what() << std::endl;
                    }
                }
                ///Checking if the Buy house button has been pressed
                if (butoane[3].checkClick(window)) {
                    in_buy_house_menu = 1;
                }

                ///Checking if the End turn button has been pressed
                if (butoane[4].checkClick(window) && rolled) {
                    end_turn = 1;
                }
                ///Checking if the Abillity button has been pressed
                if (butoane[5].checkClick(window)) {
                    ///Try to do the players abillity and catching any errors thrown by the do_ability_on_board_targeted method
                    try {
                        jucatori[0]->do_ability_on_board_targeted(jucatori[1], defaultBoard);
                    }
                    catch (game_error &err) {
                        std::cout << err.what() << std::endl;
                    }
                }
            }
        }

        /// Starting Bot logic
        if (end_turn == 1) {
            /// Reseting player flags
            end_turn = 0;
            rolled = 0;

            /// Going through all the Bots
            for (int i = 1; i < int(jucatori.size()); i++) {

                jucatori[i]->move(defaultBoard);

                /// Checking if the tile the bot landed is not buyable
                if (!(defaultBoard[jucatori[i]->position()]->is_buyable())) {

                    auto *p = dynamic_cast<Property *>(defaultBoard[jucatori[i]->position()]);
                    /// Checking if it is a Property tile
                    if (p) {
                        /// Paying the owner the rent
                        if (p->id() != i + 1)
                            jucatori[i]->pay(*jucatori[p->id() - 1], defaultBoard);
                    } else {
                        auto *e = dynamic_cast<Effect *>(defaultBoard[jucatori[i]->position()]);
                        /// Checking if it is an Effect tile and doing its effect
                        if (e)
                            jucatori[i]->do_effect(*e, defaultBoard);
                    }
                } else
                    /// If the property is buyable try and buy and catch any errors thrown by buy method
                if (jucatori[i]->getMoney() >
                    dynamic_cast<Property *>(defaultBoard[jucatori[i]->position()])->price()
                        ) {
                    try {
                        jucatori[i]->buy(defaultBoard);
                    }
                    catch (game_error &error) {
                        std::cout << error.what() << std::endl;
                    }
                }

                std::cout << jucatori[i]->getMoney() << std::endl;

                /// If the bot runs out of money erase it from the player vector
                if (jucatori[i]->getMoney() < 0) {
                    jucatori.erase(jucatori.begin() + i);

                }
            }

        }

        /// If the player runs out of money display the lose screen
        if (jucatori[0]->getMoney() < 0) {
            window.clear(sf::Color::Black);
            money.setString("You lost, Shame!");
            money.setPosition(float(window.getSize().x / 2.0), float(window.getSize().y / 2.0));
            window.draw(money);
        }
            ///If all the bots are erased from the player vector display the win screen
        else if (jucatori.size() == 1) {
            window.clear(sf::Color::Black);
            money.setString("You won,GJ");
            money.setPosition(float(window.getSize().x / 2.0), float(window.getSize().y / 2.0));
            window.draw(money);
        }


        window.display();
    }


}

/// Button texture paths
const std::vector<std::string> Game::texture_paths = {"Textures/dice-roll-hover.png",
                                                      "Textures/dice-roll-nohover.png",
                                                      "Textures/buy-button-hover.png",
                                                      "Textures/buy-button-nohover.png",
                                                      "Textures/cant-buy-button-hover.png",
                                                      "Textures/cant-buy-button-nohover.png",
                                                      "Textures/buy-house-hover.png",
                                                      "Textures/buy-house-nohover.png",
                                                      "Textures/endturn-button-hover.png",
                                                      "Textures/endturn-button-nohover.png",
                                                      "Textures/ability-button-hover.png",
                                                      "Textures/ability-button-nohover.png"
};