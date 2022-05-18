#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using namespace std;
using namespace sf;
#pragma once

class DataCircle : public Drawable
{
public:
	//Объект текста
	mutable Text text;
	//Объект круга
	mutable CircleShape circle;
	//Указатель на отметку
	//Shape - абстрактный класс
	Shape* mark_shape;
	//Объект шрифта
	Font font;
	//Цвет, если вершину выбрали
	Color selected_color;
	//Главный цвет
	Color default_color;
	//Цвет при перемещении
	Color if_moved;
	//Текущий цвет
	Color active;
public:
	//Индекс круга
	int id = 0;
	float dx = 0;
	float dy = 0;
	bool moving = false;
	bool markt = false;
	bool visible = true;

	DataCircle()
	{
		mark_shape = nullptr;
		id = 0;
		this->default_color = Color(147, 0, 119);
		this->active = this->default_color;

		this->if_moved = Color(230, 28, 93);
		font.loadFromFile("timesnewromanpsmt.ttf");
		this->text.setFillColor(Color::White);
		this->text.setFont(font);
		this->text.setCharacterSize(32);
		this->text.setStyle(Text::Bold);

		this->selected_color = Color::Green;
		this->circle.setFillColor(this->default_color);
	};
	//Установка цвета, который активируется при перемещении Вершины мышкой
	void setMovedColor(const Color& c) 
	{
		this->if_moved = c;
	};
	//Установить цвет по умолчанию
	void setDefaultColor(const Color& c) 
	{
		this->default_color = c;
	};
	//Установить цвет выделения
	void setSelectedColor(const Color& c) 
	{
		this->selected_color = c;
	};
	//Установить текстуру Вершине
	void setTexture(sf::Texture& texture) 
	{
		this->circle.setTexture(&texture);
	};
	//Образать Текстуру
	void setTextureRect(const sf::IntRect& rect) 
	{
		this->circle.setTextureRect(rect);
	}
	//Утсановить форму, которая накладывается на вершину при её отметке
	void setMarkShape(Shape* s) 
	{
		this->mark_shape = s;
	};
	// Переключение цветов
	void switchColorToMain()
	{
		this->circle.setFillColor(this->default_color);
		this->active = this->default_color;
		
	};
	void switchColorToSelected() 
	{
		this->circle.setFillColor(this->selected_color);
		this->active = this->selected_color;
	}

	//Установка позиции
	void setPosition(const float& x,const float& y)
	{
		this->circle.setPosition(x, y);
	};
	//Перемещение по вектору
	void move(const float& x,const float& y)
	{
		this->circle.move(x, y);
	};

	//Получить позицию, которая находиться по центру между вершинами
	Vector2f getMid(const DataCircle& second) 
	{
		return {(this->getPosition().x + second.getPosition().x)/2,(this->getPosition().y + second.getPosition().y)/2};
	}
	//Установить внутренний текст
	void setText(const std::string& text)
	{
		this->text.setString(text);
	};
	//Установить радиус
	void setRadius(const float& r)
	{
		this->circle.setRadius(r);
		this->text.setCharacterSize((int)circle.getRadius() / 3);
	};
	//Установить центр афинных преобразований в центр вершины
	void centrize() 
	{
		int w = this->circle.getGlobalBounds().width;
		int h = this->circle.getGlobalBounds().height;
		this->circle.setOrigin(sf::Vector2f(w / 2, h / 2));
	}

	//Имплементация draw
	void draw(RenderTarget& window,RenderStates states = RenderStates::Default)  const override
	{
		if (this->visible) 
		{
			window.draw(this->circle, states);

			unsigned int len_str = this->text.getString().getSize();
			unsigned int size_text = this->text.getCharacterSize();
			if (this->markt && this->mark_shape) 
			{
				mark_shape->setPosition(this->getPosition());
				window.draw(*this->mark_shape);
			}
			Vector2f c_pos = circle.getPosition();
			this->text.setPosition({this->getPosition().x - len_str*5,this->getPosition().y - size_text+5});
			window.draw(this->text);
		}

	};

	//Движение по координатам мыши
	void moveOnMouse(const Vector2f& mouse_pos) 
	{

		circle.setPosition(mouse_pos.x - dx, mouse_pos.y - dy);
	}
	//Проверка вхождения точки в коллизию объекта
	bool contains(const Vector2f& vect) 
	{
		return this->circle.getGlobalBounds().contains(vect);
	};
	bool contains(float x, float y)
	{
		return this->circle.getGlobalBounds().contains(x, y);
	};
	//Получить текст вершины
	std::string getString() const 
	{
		return this->text.getString();
	}
	//Получить позицию
	Vector2f getPosition() const 
	{
		return this->circle.getPosition();
	}
	//Получить радиус
	float getRadius() const
	{
		return this->circle.getRadius();
	}
	//Обработать события мыши
	int handleMouseEvent(const Event& event,const Vector2f& mouse_pos) 
	{
		if (event.type == Event::MouseButtonPressed) 
		{
			if (event.key.code == Mouse::Left) 
			{
				if (this->contains(mouse_pos)) 
				{
					dx = mouse_pos.x - circle.getPosition().x;
					dy = mouse_pos.y - circle.getPosition().y;
					this->circle.setFillColor(if_moved);
					this->moving = true;
					return this->id;
				}
				
			}
		}
		else if (event.type == Event::MouseButtonReleased)
		{
			if (event.key.code == Mouse::Left) 
			{
				this->circle.setFillColor(active);
				moving = false;
			}
		}
		return -1;
	}
	

};
