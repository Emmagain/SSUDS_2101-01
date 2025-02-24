#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main(int args, char** argv)
{
	sf::RenderWindow window(sf::VideoMode({ 800,600 }), "Lab 04");
	sf::CircleShape test(100.0f);
	sf::Texture background_texture("../../media/pink_background.png");
	sf::Sprite background_sprite(background_texture);
	background_sprite.setScale({ 1.5, 1.5 });
	//background_sprite.setScale({})
	test.setFillColor(sf::Color::White);

	while (window.isOpen())
	{
		window.clear();
		window.draw(background_sprite);
		window.draw(test);
		window.display();
	}

	return 0;
}