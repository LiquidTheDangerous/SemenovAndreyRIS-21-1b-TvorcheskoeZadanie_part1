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
	
	//Текст
	mutable Text text;
	//Шрифт
	Font font;
	//Цвет текущий
	Color active;
	//Цвет при нажатии
	Color pressed;
	//Главный цвет
	Color main_color;
	
	//Для установки и получения id кнопки
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
	//Установка id кнопки
	void setTypeId(const MenuEvent::ButtonType& type) 
	{
		this->type_id = type;
	};

	//Получение id кнопки
	MenuEvent::ButtonType getTypeId() const 
	{
		return this->type_id;
	}
	//Переключение цвета
	void switchColorToPressed()
	{
		this->active = this->pressed;
	};
	void switchColorToMain() 
	{
		this->active = this->main_color;
	}

	//Проверка вхождения
	bool contains(const Vector2f& point) 
	{
		return FloatRect(this->getPosition(), this->getScale()).contains(point);
	}

	std::string getText() const 
	{
		return this->text.getString();
	}
	//Установка текста кнопки
	void setText(const std::string& text) 
	{
		this->text.setString(text);
	}

	//Получение центра кнопки
	Vector2f getCentre() const
	{
		return Vector2f(this->getScale().x/2,this->getScale().y / 2);
	}

	// реализация метода draw, для отрисовки
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

