#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <functional>
#include "MenuEvent.h"

using namespace std;
using namespace sf;

class Btn : public Drawable, public Transformable
{
private:
	
	//�����
	mutable Text text;
	//�����
	Font font;
	//���� �������
	Color active;
	//���� ��� �������
	Color pressed;
	//������� ����
	Color main_color;
	
	//��� ��������� � ��������� id ������
	MenuEvent::ButtonType type_id;


public:

	bool muted_sound = false;
	Btn(const Vector2f& pos, const Vector2f& scale,const std::string& str= "")
	{

		this->setPosition(pos);
		this->setScale(scale);
		this->font.loadFromFile("timesnewromanpsmt.ttf");
		this->text.setFont(this->font);
		this->text.setFillColor(Color::Yellow);
		this->text.setPosition(pos);
		this->text.setString(str);
		this->text.setCharacterSize(20);
		
		this->main_color = sf::Color(112, 9, 97);
		this->pressed = sf::Color(184, 13, 87);
		this->active = this->main_color;
	}
	//��������� id ������
	void setTypeId(const MenuEvent::ButtonType& type) 
	{
		this->type_id = type;
	};

	//��������� id ������
	MenuEvent::ButtonType getTypeId() const 
	{
		return this->type_id;
	}
	//������������ �����
	void switchColorToPressed()
	{
		this->active = this->pressed;
	};
	void switchColorToMain() 
	{
		this->active = this->main_color;
	}

	//�������� ���������
	bool contains(const Vector2f& point) 
	{
		return FloatRect(this->getPosition(), this->getScale()).contains(point);
	}

	std::string getText() const 
	{
		return this->text.getString();
	}
	//��������� ������ ������
	void setText(const std::string& text) 
	{
		this->text.setString(text);
	}

	//��������� ������ ������
	Vector2f getCentre() const
	{
		return Vector2f(this->getScale().x/2,this->getScale().y / 2);
	}

	// ���������� ������ draw, ��� ���������
	virtual void draw(RenderTarget& window, RenderStates states = RenderStates::Default) const override 
	{
		RectangleShape rect(this->getScale());
		rect.setFillColor(active);
		rect.setPosition(this->getPosition());
		rect.setOutlineThickness(1);
		rect.setOutlineColor(Color::Black);
		this->text.setPosition({ this->getPosition().x + this->getCentre().x - this->text.getString().getSize()*3 - this->text.getCharacterSize() ,this->getPosition().y + this->text.getCharacterSize()/4});
		window.draw(rect);
		window.draw(this->text);
	};

};

