#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

class DataArrow : public Drawable
{
protected:
	//vector<Vertex> verts(2);
	Vector2f start;
	Vector2f end;
	Color color;
	Font font;
	mutable Text text;
	float r;
	float k;
public:
	bool show_arrow = true;
	bool show_text = true;
	DataArrow(const Vector2f& s, const Vector2f& end, const Color& c = Color::Black) 
	{
		r = 0;
		k = 10;
		font.loadFromFile("timesnewromanpsmt.ttf");
		this->text.setFont(font);
		this->text.setCharacterSize(20);
		this->text.setString("");
		this->text.setFillColor(c);
		this->text.setStyle(Text::Bold);
		this->start = start;
		this->end = end;
		this->color = c;
	};
	DataArrow() : DataArrow({ 0,0 }, {0,0}) {};
	//Установить отдоление стрелки от конца на величину R
	void setR(const float& r) 
	{
		this->r = r;
	}
	//Установить Цвет тексту
	void setTextColor(const Color& c) 
	{
		this->text.setFillColor(c);
	};
	//Установить строковое значение тексту
	void setText(const std::string& text) 
	{
		this->text.setString(text);
	};
	//Установить позицию начала
	void setStart(const Vector2f& vect) 
	{
		this->start = vect;
	};
	//Установить цвет
	void setColor(const Color& c) 
	{
		this->color = c;
	}
	//Установить позциию конца
	void setEnd(const Vector2f& vect)
	{
		this->end = vect;
	};
	//Узнать длину 
	float getLen() const
	{
		return sqrt(pow(start.x - end.x,2) + pow(start.y - end.y,2));
	}
	//Получить координаты начала и конеца
	Vector2f getStart() { return this->start; }
	Vector2f getEnd() { return this->end; }
	//имплементация draw
	virtual void draw(RenderTarget& window, RenderStates states = RenderStates::Default) const override 
	{
		
		
		vector<Vertex> verts(2);
		verts[0] = Vertex(start,this->color);
		verts[1] = Vertex(end, this->color);

		window.draw(&verts[0],2,Lines,states);

		//float k = (this->end.y - this->start.y) / (this->end.x - this->start.x);
		if (show_arrow)
		{
			Vector2f end = this->end;
			Vector2f v1((this->end.x - this->start.x) /this->getLen(), (this->end.y - this->start.y) /this->getLen());
			Vector2f v2( (-this->start.y + this->end.y) /this->getLen(), (this->start.x - this->end.x)/this->getLen());
			Vector2f v3((v1.x + v2.x)*k,(v1.y + v2.y)*k);
			Vector2f v4((v1.x - v2.x)*k, (v1.y - v2.y)*k);
			end = Vector2f(end.x - v1.x*r,end.y-v1.y*r);

			VertexArray v(Triangles,3);
			v[0] = Vertex({end.x ,end.y}, color);
			v[1] = Vertex({end.x - v3.x,end.y - v3.y}, color);
			v[2] = Vertex({end.x - v4.x,end.y - v4.y}, color);
			window.draw(v,states);
		}
		if (show_text)
		this->text.setPosition((this->start.x + this->end.x)/2 - 10, (this->start.y + this->end.y) / 2);
		window.draw(text,states);
	};
};

