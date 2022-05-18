#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using namespace std;
using namespace sf;
#pragma once

class DataCircle : public Drawable
{
public:
	//������ ������
	mutable Text text;
	//������ �����
	mutable CircleShape circle;
	//��������� �� �������
	//Shape - ����������� �����
	Shape* mark_shape;
	//������ ������
	Font font;
	//����, ���� ������� �������
	Color selected_color;
	//������� ����
	Color default_color;
	//���� ��� �����������
	Color if_moved;
	//������� ����
	Color active;
public:
	//������ �����
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
	//��������� �����, ������� ������������ ��� ����������� ������� ������
	void setMovedColor(const Color& c) 
	{
		this->if_moved = c;
	};
	//���������� ���� �� ���������
	void setDefaultColor(const Color& c) 
	{
		this->default_color = c;
	};
	//���������� ���� ���������
	void setSelectedColor(const Color& c) 
	{
		this->selected_color = c;
	};
	//���������� �������� �������
	void setTexture(sf::Texture& texture) 
	{
		this->circle.setTexture(&texture);
	};
	//�������� ��������
	void setTextureRect(const sf::IntRect& rect) 
	{
		this->circle.setTextureRect(rect);
	}
	//���������� �����, ������� ������������� �� ������� ��� � �������
	void setMarkShape(Shape* s) 
	{
		this->mark_shape = s;
	};
	// ������������ ������
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

	//��������� �������
	void setPosition(const float& x,const float& y)
	{
		this->circle.setPosition(x, y);
	};
	//����������� �� �������
	void move(const float& x,const float& y)
	{
		this->circle.move(x, y);
	};

	//�������� �������, ������� ���������� �� ������ ����� ���������
	Vector2f getMid(const DataCircle& second) 
	{
		return {(this->getPosition().x + second.getPosition().x)/2,(this->getPosition().y + second.getPosition().y)/2};
	}
	//���������� ���������� �����
	void setText(const std::string& text)
	{
		this->text.setString(text);
	};
	//���������� ������
	void setRadius(const float& r)
	{
		this->circle.setRadius(r);
		this->text.setCharacterSize((int)circle.getRadius() / 3);
	};
	//���������� ����� ������� �������������� � ����� �������
	void centrize() 
	{
		int w = this->circle.getGlobalBounds().width;
		int h = this->circle.getGlobalBounds().height;
		this->circle.setOrigin(sf::Vector2f(w / 2, h / 2));
	}

	//������������� draw
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

	//�������� �� ����������� ����
	void moveOnMouse(const Vector2f& mouse_pos) 
	{

		circle.setPosition(mouse_pos.x - dx, mouse_pos.y - dy);
	}
	//�������� ��������� ����� � �������� �������
	bool contains(const Vector2f& vect) 
	{
		return this->circle.getGlobalBounds().contains(vect);
	};
	bool contains(float x, float y)
	{
		return this->circle.getGlobalBounds().contains(x, y);
	};
	//�������� ����� �������
	std::string getString() const 
	{
		return this->text.getString();
	}
	//�������� �������
	Vector2f getPosition() const 
	{
		return this->circle.getPosition();
	}
	//�������� ������
	float getRadius() const
	{
		return this->circle.getRadius();
	}
	//���������� ������� ����
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
