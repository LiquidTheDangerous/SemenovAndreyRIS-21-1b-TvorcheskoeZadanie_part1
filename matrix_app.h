#pragma once
#include <vector>
#include <string>
#include "DataArrow.h"
#include "MenuEvent.h"
#include <SFML/Graphics.hpp>
#include <iostream>



class matrix_app
{
private:
	std::vector<std::string>* verts;
	std::vector < std::vector<int> >* adj_matrix;
	sf::Font font;
	sf::Text text;
	sf::Color color;
	int w;
	int h;
	bool renamed_flag;
	struct
	{
		int w;
		int h;
		const sf::Uint8* pixPtr;
		bool init = false;
	} Icon;

	//Изменение ширины колонн по длине текста
	void resize_w() 
	{
		if (this->verts->size())
		{
			int max_w = this->verts->operator[](0).size();
			for (int i = 1; i < this->verts->size(); ++i)
			{
				if (this->verts->operator[](i).size() > max_w)
				{
					max_w = (int)this->verts->operator[](i).size();
				}
			}
			this->w = max_w * this->text.getCharacterSize() / 4 + 96;
		};
	};

public:
	matrix_app()
	{
		this->renamed_flag = false;
		this->w = 96;
		this->h = 96;
		this->color = sf::Color::Black;
		this->font.loadFromFile("timesnewromanpsmt.ttf");
		this->text.setFont(this->font);
		this->text.setCharacterSize(25);
		this->text.setFillColor(this->color);
	};

	bool is_renamed() 
	{
		return this->renamed_flag;
	}
	
	void setIcon(const int& w, const int& h,const sf::Uint8* pixPtr) 
	{
		this->Icon.w = w;
		this->Icon.h = h;
		this->Icon.pixPtr = pixPtr;
		this->Icon.init = true;
	};
	//Установить длину и ширину клетки
	void setWidth(const int& w) 
	{
		this->w = w;
	}
	void setHeight(const int& h) 
	{
		this->h = h;
	}

	void setColor(const sf::Color& color) 
	{
		this->color = color;
	};
	void setVerts(std::vector<std::string>* verts) 
	{
		this->verts = verts;
	};
	void setAdjMatrix(std::vector < std::vector<int> >* matrix)
	{
		this->adj_matrix = matrix;
	};
	void setUnRenamed() 
	{
		this->renamed_flag = false;
	};
	void showWindow() 
	{
		this->resize_w();

		int s_size = this->verts->size();
		sf::RenderWindow window(sf::VideoMode(this->w*(s_size + 1), this->h*(s_size + 1)), "Matrix",sf::Style::Close);
		if (this->Icon.init)
		{
			window.setIcon(this->Icon.w, this->Icon.h, this->Icon.pixPtr);
		};

		DataArrow line;
		line.setColor(this->color);
		line.show_text = false;
		line.show_arrow = false;




		RectangleShape rect(sf::Vector2f(this->w,this->h));
		rect.setFillColor(sf::Color(210,210,210));
		std::string str;
		//rect.setPosition(100,100);
		while (window.isOpen()) 
		{
			static int i(0);
			static int j(0);
			static MenuEvent MEvent;
			sf::Event event;
			Vector2i mouse_pos = Mouse::getPosition(window);
			while (window.pollEvent(event)) 
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::MouseMoved:
					j = mouse_pos.x / this->w;
					i = mouse_pos.y / this->h;
					if (i < this->adj_matrix->size() && j < this->adj_matrix->size()) 
					{
						rect.setPosition(sf::Vector2f(j * this->w,i * this->h));
					}
					break;
				case sf::Event::MouseButtonPressed:
					if (event.key.code == Mouse::Left && MEvent.what != MenuEvent::What::Chosen) 
					{
						MEvent.index_first = mouse_pos.x / this->w;
						MEvent.index_second = mouse_pos.y / this->h;
						MEvent.what = MenuEvent::What::Chosen;
						rect.setFillColor(sf::Color(150,150,150));
					}
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
					case Keyboard::Enter:
						if (MEvent.what == MenuEvent::What::Chosen) 
						{
							if (MEvent.index_first == 0 || MEvent.index_second == 0)
							{
								if (MEvent.index_first == 0 && MEvent.index_second != 0)
								{
									this->verts->at(MEvent.index_second - 1) = str;
								}
								else if (MEvent.index_second == 0 && MEvent.index_first != 0)
								{
									this->verts->at(MEvent.index_first - 1) = str;
								};

								if (!this->renamed_flag) 
								{
									this->renamed_flag = true;
								}
							}
							else
							{
								this->adj_matrix->at(MEvent.index_second - 1)[MEvent.index_first - 1] = std::stoi(str);
								//std::cout << this->adj_matrix->at(i-1)[j - 1] << std::endl;
							}
							this->resize_w();
							window.setSize(sf::Vector2u(this->w * (s_size + 1), this->h * (s_size + 1)));
							window.setView(sf::View(sf::Vector2f(window.getSize().x/2, window.getSize().y/2),sf::Vector2f(window.getSize().x, window.getSize().y)));
							rect.setSize(sf::Vector2f(this->w,this->h));
							str = "";
							MEvent.what = MenuEvent::What::Nothing;
							MEvent.index_first = -1;
							MEvent.index_second = -1;
						}
						break;
					default:
						break;
					}
					break;
				case sf::Event::MouseButtonReleased:
					if (event.key.code == Mouse::Left) 
					{
						rect.setFillColor(sf::Color(210,210,210));
					}
					break;
				case sf::Event::TextEntered:
					if (MEvent.what == MenuEvent::What::Chosen) 
					{
						if (event.text.unicode < 128)
						{

							if (event.text.unicode == 8)
							{
								if (str.size())
								{
									str.pop_back();
								}
							}
							else
							{
								str += static_cast<char>(event.text.unicode);
							}
						}
					}
					break;
				default:
					break;
				}
			}
			window.clear(sf::Color::White);
			window.draw(rect);
			for (int i = 1; i <= s_size + 1; ++i)
			{
				if (i != s_size + 1) 
				{
				
					if (!(MEvent.index_second == 0 || MEvent.index_first == 0) || (MEvent.index_first == 0 && MEvent.index_second == 0))
					{

						this->text.setPosition(sf::Vector2f(i * this->w,this->h/4));
						this->text.setString(this->verts->at(i - 1));
						window.draw(this->text);
						this->text.setPosition(sf::Vector2f(0, i * this->h +this->h/4));
						this->text.setString(this->verts->at(i - 1));
						window.draw(this->text);
					}
					else 
					{
						if (i == MEvent.index_first || i == MEvent.index_second) 
						{
							this->text.setPosition(sf::Vector2f(i * this->w, this->h/4));
							this->text.setString(str);
							window.draw(this->text);
							this->text.setPosition(sf::Vector2f(0, i * this->h + this->h/4));
							this->text.setString(str);
							window.draw(this->text);
						}
						else
						{
							this->text.setPosition(sf::Vector2f(i * this->w, this->h/4));
							this->text.setString(this->verts->at(i - 1));
							window.draw(this->text);
							this->text.setPosition(sf::Vector2f(0, i * this->h + this->h/4));
							this->text.setString(this->verts->at(i - 1));
							window.draw(this->text);
						}
					}
				}
					line.setStart(sf::Vector2f(i * this->w, 0));
					line.setEnd(sf::Vector2f(i * this->w, (s_size + 1) * this->h));
					window.draw(line);
					line.setStart(sf::Vector2f(0, i * this->h));
					line.setEnd(sf::Vector2f((s_size + 1) * this->w, i * this->h));
					window.draw(line);
			};

			

			for (int i = 1; i <= s_size; ++i) 
			{
				for (int j = 1; j <= s_size; ++j) 
				{
					if (i == MEvent.index_first && j == MEvent.index_second) 
					{
						this->text.setString(str);
					}
					else
					{
						this->text.setString(std::to_string(this->adj_matrix->at(j - 1)[i - 1]));
					}
						this->text.setPosition(sf::Vector2f(i*this->w,j*this->h + this->h / 4));
						window.draw(this->text);
				}
			}
			window.display();
		}
	}
};

