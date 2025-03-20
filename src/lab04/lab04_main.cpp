#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <array_list.h>
#include <WordReader.h>

class TextCircle
{
private:
	sf::Text my_text;
	sf::CircleShape my_circle;
	float my_size;

public:

	TextCircle(sf::Font& the_font, float size) : my_text(the_font) //creates my_text using the_font, instead of trying to create it then set it later
	{
		my_circle = sf::CircleShape(size);
		my_circle.setOrigin(sf::Vector2(size, size));
		my_size = size;
	}

	void set_position(float x, float y)
	{
		my_circle.setPosition(sf::Vector2f(x, y));
		my_text.setPosition(sf::Vector2f(x, y));
	}

	void set_rotation(float degrees)
	{
		my_text.setRotation(sf::degrees(degrees));
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(my_circle);
		window.draw(my_text);
	}

	void set_text(std::string text)
	{
		my_text.setString(text);
		my_text.setFillColor(sf::Color(255, 50, 120));
		sf::FloatRect text_bounds = my_text.getLocalBounds();
		sf::Vector2f text_size = text_bounds.size;
		my_text.setCharacterSize(my_size / 2);
		my_text.setOrigin(sf::Vector2f(text_size.x / 2.0f, text_size.y / 2.0f));
	}
};


int main(int args, char** argv)
{
	sf::RenderWindow window(sf::VideoMode({ 800,600 }), "Lab 04");

	sf::Clock spawnClock, gameClock;

	sf::Texture background_texture("../../media/pink_background.png");
	sf::Sprite background_sprite(background_texture);
	background_sprite.setScale({ 1.5, 1.5 });

	//load a font and make a text object
	sf::Font my_font("../../media/Oswald/static/Oswald-Regular.ttf");

	/*
	sf::CircleShape test(100.0f);
	test.setFillColor(sf::Color( 255, 255, 255));
	test.setPosition(sf::Vector2f(400.0f, 300.0f));
	test.setOrigin(sf::Vector2f(100.0f, 100.0f));

	sf::Texture background_texture("../../media/pink_background.png");
	sf::Sprite background_sprite(background_texture);
	background_sprite.setScale({ 1.5, 1.5 });
	//background_sprite.setScale({})
	test.setFillColor(sf::Color::White);

	//load a font and make a text object
	sf::Font my_font("../../media/Oswald/static/Oswald-Regular.ttf");
	sf::Text test_text(my_font);
	test_text.setString("Hello");
	test_text.setCharacterSize(24);
	test_text.setPosition(sf::Vector2f(50.0f, 50.0f));
	test_text.setFillColor(sf::Color(0, 0, 0));
	sf::FloatRect test_text_bounds = test_text.getLocalBounds();
	sf::Vector2f test_text_size = test_text_bounds.size;
	test_text.setOrigin(sf::Vector2f(test_text_size.x / 2.0f, test_text_size.y / 2.0f));
	//.setRotation(sf::degrees(45.0f));

	//using array list
	//ssuds::ArrayList<TextCircle> my_circles;
	//TextCircle test_1(my_font);
	//my_circles.append(test);
	*/

	ssuds::ArrayList<float> circle_xlist;
	ssuds::ArrayList<float> circle_ylist;
	ssuds::ArrayList<std::string> circle_strings;
	ssuds::ArrayList<float> circle_sizes;
	ssuds::ArrayList<float> circle_degrees;
	ssuds::ArrayList<float> circle_speed;

	ssuds::ArrayList<float> bullet_xlist;
	ssuds::ArrayList<float> bullet_ylist;
	ssuds::ArrayList<float> bullet_xdir;
	ssuds::ArrayList<float> bullet_ydir;

	ssuds::WordReader reader;

	while (window.isOpen()) //GAME LOOP
	{
		window.clear();
		window.draw(background_sprite);

		if (spawnClock.getElapsedTime().asSeconds() >= 1.0f)
		{
			circle_xlist.append(20 + rand() % 760);
			circle_ylist.append(0);
			circle_sizes.append(30 + std::rand() % 21);
			circle_degrees.append(std::rand() % 91);
			circle_speed.append(50 + std::rand() % 51);
			std::string temp = reader.extractWord();
			circle_strings.append(temp);
			spawnClock.restart();
		}
		float deltaT = gameClock.getElapsedTime().asSeconds();
		gameClock.restart();
		for (int i = 0; i < circle_xlist.size(); i++)
		{
			float x = circle_xlist[i];
			float move = circle_speed[i] * deltaT;
			float y = circle_ylist[i] += move;
			float size = circle_sizes[i];
			float degrees = circle_degrees[i] += 100*deltaT;
			std::string text = circle_strings[i];
			if (y >= (600 + size))
			{
				circle_xlist.remove(i);
				circle_ylist.remove(i);
				circle_sizes.remove(i);
				circle_degrees.remove(i);
				circle_speed.remove(i);
				circle_strings.remove(i);
			}
			else
			{
				TextCircle temp(my_font, size);
				temp.set_text(text);
				temp.set_position(x, y);
				temp.set_rotation(degrees);
				temp.draw(window);
			}
		}

		for (int i = 0; i < bullet_xlist.size(); i++)
		{
			for (int c = 0; c < circle_xlist.size(); c++)
			{
				float dx = bullet_xlist[i] - circle_xlist[c];
				float dy = bullet_ylist[i] - circle_ylist[c];
				float distance = std::sqrt(dx*dx + dy*dy);
				
				if (distance < 10 + circle_sizes[c])
				{
					circle_xlist.remove(c);
					circle_ylist.remove(c);
					circle_sizes.remove(c);
					circle_degrees.remove(c);
					circle_speed.remove(c);
					circle_strings.remove(c);
					bullet_xlist[i] = 1000;
					bullet_ylist[i] = 1000;
					break;
				}
			}

			float velx = bullet_xdir[i] * 150 * deltaT;
			float vely = bullet_ydir[i] * 150 * deltaT;

			float x = bullet_xlist[i] += velx;
			float y = bullet_ylist[i] += vely;
			float size = 10.0f;
			if (y >= (600 + size) || y <= 0 + size || x >= 800 + size || x <= 0)
			{
				bullet_xlist.remove(i);
				bullet_ylist.remove(i);
				bullet_xdir.remove(i);
				bullet_ydir.remove(i);
			}
			else
			{
				sf::CircleShape temp(size);
				temp.setOrigin(sf::Vector2f(size, size));
				temp.setPosition(sf::Vector2(x, y));
				temp.setFillColor(sf::Color(255, 50, 120));
				window.draw(temp);
			}
		}

		//USER INPUT EVENTS
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			
			else if (const sf::Event::KeyPressed* keyEvt = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyEvt->code == sf::Keyboard::Key::Escape)
				{
					window.close();
				}
			}

			else if (const sf::Event::MouseButtonPressed* buttonEvt =
				event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (buttonEvt->button == sf::Mouse::Button::Left)
				{
					sf::Vector2f temp_pos(buttonEvt->position.x, buttonEvt->position.y);
					
					bullet_xlist.append(400.0f);
					bullet_ylist.append(550.0f);

					float dirx = buttonEvt->position.x - 400;
					float diry = buttonEvt->position.y - 550;
					float mag = std::sqrt(dirx * dirx + diry * diry);
					if (mag != 0.0f) {
						dirx = dirx / mag;
						diry = diry / mag;
					}
					bullet_xdir.append(dirx);
					bullet_ydir.append(diry);
					
				}
			}
		}

		window.display();
	}


	return 0;
}


/*
IN_CLASS EXAMPLES ARE ON WITHERELL'S GITHUB REPOSITORY

WORD READER CLASS

10 is the ascii value of a new line character. 11 is the value of the carriage return

in constructor:
open file
get file length

to get random word (extract_word method):
pick a random numbner between 0 and file length,
move file pointer to the random spot picked
move char by char backwards until you get to right after a new-line-boundary (check that posititon-i == new-line-boundary
	fp.seekg(-1, std::ios::cur);
	char = c.fp.peek();
get line and read line
	std::string read_word;
	std::getline(fp, read_word);

destructor:
close the text file (do not close before the constructor)
*/