// Copyright[2024] <Manasvi Boineypally>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
int main()
{sf::RenderWindow window(sf::VideoMode(1000, 1000), "Multiple Moveable Images");
sf::CircleShape sh(30);
sh.setFillColor(sf::Color(255, 255, 255));
sh.setPosition(window.getSize().x/2, 0);
sf::Color backgroundColor = sf::Color(255, 123, 45);
sf::Texture texture1, texture2, texture3, texture4;
if (!texture1.loadFromFile("sprite.png")|| !texture2.loadFromFile("sprite.png")
|| !texture3.loadFromFile("sprite.png") || !texture4.loadFromFile("sprite.png"))
return -1;
sf::Sprite sprite1, sprite2, sprite3, sprite4;
    sprite1.setTexture(texture1);
    sprite2.setTexture(texture2);
    sprite3.setTexture(texture3);
    sprite4.setTexture(texture4);
    sprite1.setOrigin(sprite1.getLocalBounds().width/2 ,
     sprite1.getLocalBounds().height/2);
    sprite2.setOrigin(sprite2.getLocalBounds().width/2 ,
     sprite2.getLocalBounds().height/2);
    sprite3.setOrigin(sprite3.getLocalBounds().width/2 ,
     sprite3.getLocalBounds().height/2);
    sprite4.setOrigin(sprite4.getLocalBounds().width/2 ,
     sprite4.getLocalBounds().height/2);
    sprite1.setScale(0.4f , 0.4f);
    sprite2.setScale(-0.4f , 0.4f);
    sprite3.setScale(0.4f , 0.4f);
    sprite4.setScale(-0.4f , 0.4f);
    sprite1.setPosition(100.f, 100.f);
sprite2.setPosition(500.f, 100.f);
    sprite3.setPosition(100.f, 500.f);
    sprite4.setPosition(500.f, 500.f);
float movementSpeed = 200.f;
    sf::SoundBuffer buffer;
    buffer.loadFromFile("sound.wav");
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();
sf::Clock clock;
    while (window.isOpen())
    {sf::Event event;
        while (window.pollEvent(event))
        {if (event.type == sf::Event::Closed)
                window.close();
        }
sf::Time deltaTime = clock.restart();
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            sprite1.move(-movementSpeed * deltaTime.asSeconds(), 0.f);}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            sprite1.move(movementSpeed * deltaTime.asSeconds(), 0.f);}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            sprite1.move(0.f, -movementSpeed * deltaTime.asSeconds());}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            sprite1.move(0.f, movementSpeed * deltaTime.asSeconds()); }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            sprite3.move(-movementSpeed * deltaTime.asSeconds(), 0.f);}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            sprite3.move(movementSpeed * deltaTime.asSeconds(), 0.f);}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            sprite3.move(0.f, -movementSpeed * deltaTime.asSeconds());}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            sprite3.move(0.f, movementSpeed * deltaTime.asSeconds());}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            sprite4.move(-movementSpeed * deltaTime.asSeconds(), 0.f);}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            sprite4.move(movementSpeed * deltaTime.asSeconds(), 0.f);}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            sprite4.move(0.f, -movementSpeed * deltaTime.asSeconds());}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            sprite4.move(0.f, movementSpeed * deltaTime.asSeconds());}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            sprite2.move(-movementSpeed * deltaTime.asSeconds(), 0.f);}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            sprite2.move(movementSpeed * deltaTime.asSeconds(), 0.f);}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            sprite2.move(0.f, -movementSpeed * deltaTime.asSeconds());}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            sprite2.move(0.f, movementSpeed * deltaTime.asSeconds());}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            backgroundColor = sf::Color::Red;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            backgroundColor = sf::Color::Green;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            backgroundColor = sf::Color::Blue;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {backgroundColor = sf::Color(
                std::rand() % 256,
                std::rand() % 256,
                std::rand() % 256);
        }
        window.clear(backgroundColor);
window.draw(sh);
        window.draw(sprite1);
        window.draw(sprite2);
                window.draw(sprite3);
        window.draw(sprite4);
window.display();
}
return 0;
}
