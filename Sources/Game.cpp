//
// Created by Adi on 5/16/2023.
//

#include "../Headers/Game.h"

Board Game::defaultBoard;

Game::Game() {
    texturi.reserve(20);
    sprites.reserve(20);
    butoane.reserve(20);
    font.loadFromFile("Fonts/MinimalPixel v2.ttf");
    money.setFont(font);
    money.setCharacterSize(36);
    money.setFillColor(sf::Color::White);

    for (const std::string &path: texture_paths) {
        sf::Texture temp;
        temp.loadFromFile(path);
        texturi.emplace_back(temp);
    }

    for (const auto &i: texturi) {
        sf::Sprite temp;
        temp.setTexture(i);
        sprites.emplace_back(temp);
    }

    int bt_count = 0;
    for (int i = 0; i < int(sprites.size()); i += 2) {
        butoane.emplace_back(sprites[i], sprites[i + 1], pozitii[bt_count]);
        bt_count++;
    }
}

[[maybe_unused]] Game::Game(std::vector<Player *> players, const Board &b) : jucatori(std::move(players)) {
    defaultBoard = b;
    texturi.reserve(20);
    sprites.reserve(20);
    butoane.reserve(20);
    font.loadFromFile("Fonts/MinimalPixel v2.ttf");
    money.setFont(font);
    money.setCharacterSize(36);
    money.setFillColor(sf::Color::White);
    for (const std::string &path: texture_paths) {
        sf::Texture temp;
        temp.loadFromFile(path);
        texturi.emplace_back(temp);
    }

    for (const auto &i: texturi) {
        sf::Sprite temp;
        temp.setTexture(i);
        sprites.emplace_back(temp);
    }

    int bt_count = 0;
    for (int i = 0; i < int(sprites.size()); i += 2) {
        butoane.emplace_back(sprites[i], sprites[i + 1], pozitii[bt_count]);
        bt_count++;
    }
}

void Game::play(sf::RenderWindow &window) {
    int end_turn = 0, rolled = 0, in_buy_house_menu = 0;
    Animation idle(0, 3, 0.3f);
    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        sf::Event event{};
        money.setString(std::to_string(jucatori[0]->getMoney()) + "$");
        money.setPosition(20, 20);

        if (in_buy_house_menu) {
            PropSelectMenu menu(jucatori[0]->getProps());
            menu.drawMenu(window);
            money.setPosition(20, 600);
            window.draw(money);
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                for (int i = 0; i < menu.size() - 1; i++) {
                    if (menu[i].checkClick(window)) {
                        //std::cout << *jucatori[0][i] << std::endl;
                        try {
                            jucatori[0]->buy_house((*jucatori[0])[i]);
                        }
                        catch (game_error &error) {
                            std::cout << error.what() << std::endl;
                        }

                        //std::cout << *jucatori[0][i] << std::endl;

                    }
                }
                if (menu[menu.size() - 1].checkClick(window))
                    in_buy_house_menu = 0;
            }

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

            for (int i = 0; i < int(butoane.size()); i++) {
                int ok = 0;
                if (i == 1 &&
                    (defaultBoard[jucatori[0]->position()]->is_buyable() == 0 ||
                     jucatori[0]->getMoney() <
                     dynamic_cast<Property *>(defaultBoard[jucatori[0]->position()])->price())
                        ) {
                    i++;
                    ok = 1;
                }
                if (ok == 1 || i != 2) {
                    butoane[i].isHovered(window);
                    butoane[i].drawButton(window);
                }
            }


            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();


                if (butoane[0].checkClick(window) && !rolled) {
                    rolled = 1;
                    std::cout << "here" << std::endl;
                    jucatori[0]->move(defaultBoard);
                    std::cout << "here" << std::endl;
                    if (!(defaultBoard[jucatori[0]->position()]->is_buyable())) {

                        auto *p = dynamic_cast<Property *>(defaultBoard[jucatori[0]->position()]);
                        if (p) {
                            if (p->id() != 1)
                                jucatori[0]->pay(*jucatori[p->id() - 1], defaultBoard);
                        } else {
                            auto *e = dynamic_cast<Effect *>(defaultBoard[jucatori[0]->position()]);
                            if (e)
                                jucatori[0]->do_effect(*e, defaultBoard);
                        }
                    }

                }

                if (butoane[1].checkClick(window)) {
                    //std::cout<<jucatori[0]<<std::endl;
                    try {
                        jucatori[0]->buy(defaultBoard);
                    }
                    catch (game_error &error) {
                        std::cout << error.what() << std::endl;
                    }
                    //std::cout<<jucatori[0]<<std::endl;
                }
                if (butoane[3].checkClick(window)) {
                    in_buy_house_menu = 1;
                }
                if (butoane[4].checkClick(window) && rolled) {
                    end_turn = 1;
                }
                if (butoane[5].checkClick(window)) {
                    try {
                        jucatori[0]->do_ability();
                        jucatori[0]->do_ability_targeted(jucatori[1]);
                        jucatori[0]->do_ability_on_board(defaultBoard);
                        jucatori[0]->do_ability_on_board_targeted(jucatori[1], defaultBoard);
                    }
                    catch (game_error &err) {
                        std::cout << err.what() << std::endl;
                    }
                }
            }
        }


        if (end_turn == 1) {
            std::cout << end_turn << std::endl;
            end_turn = 0;
            rolled = 0;
            for (int i = 1; i < int(jucatori.size()); i++) {
                jucatori[i]->move(defaultBoard);

                if (!(defaultBoard[jucatori[i]->position()]->is_buyable())) {

                    auto *p = dynamic_cast<Property *>(defaultBoard[jucatori[i]->position()]);
                    if (p) {
                        if (p->id() != i + 1)
                            jucatori[i]->pay(*jucatori[p->id() - 1], defaultBoard);
                    } else {
                        auto *e = dynamic_cast<Effect *>(defaultBoard[jucatori[i]->position()]);
                        if (e)
                            jucatori[i]->do_effect(*e, defaultBoard);
                    }
                } else if (jucatori[i]->getMoney() >
                           dynamic_cast<Property *>(defaultBoard[jucatori[i]->position()])->price())
                    try {
                        jucatori[i]->buy(defaultBoard);
                    }
                    catch (game_error &error) {
                        std::cout << error.what() << std::endl;
                    }


                std::cout << jucatori[i]->getMoney() << std::endl;

                if (jucatori[i]->getMoney() < 0) {
                    jucatori.erase(jucatori.begin() + i);

                }
            }

        }
        if (jucatori[0]->getMoney() < 0) {
            window.clear(sf::Color::Black);
            money.setString("You lost, Shame!");
            money.setPosition(float(window.getSize().x / 2.0), float(window.getSize().y / 2.0));
            window.draw(money);
        } else if (jucatori.size() == 1) {
            window.clear(sf::Color::Black);
            money.setString("You won,GJ");
            money.setPosition(float(window.getSize().x / 2.0), float(window.getSize().y / 2.0));
            window.draw(money);
        }


        window.display();
    }


}

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