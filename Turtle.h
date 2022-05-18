#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <iostream>



class Turtle : public sf::Drawable
{
private:
	
	bool is_move = true;
	bool is_visible = true;
	bool move_with_drawing = true;
	float speed = 1;
	mutable int cur_index_pos = 0;

	mutable sf::Vector2f current_pos;
	mutable sf::Vector2f start_pos;
	mutable sf::Vector2f end_pos;
	mutable sf::Vector2f S;
	std::vector<sf::Vector2f> positions;

	mutable sf::Shape* obj;
	
	//����������� �������, ������������ ������� ��������� ����� �������
	static float DistancePow2(const sf::Vector2f& start, const sf::Vector2f& end) 
	{
		return pow(start.x - end.x, 2) + pow(start.y - end.y, 2);
	};
	//����������� ������� �����������, ��������� ����� �������
	static float Distance(const sf::Vector2f& start, const sf::Vector2f& end)
	{
		return sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
	};

	//��������� ���-�������
	static  sf::Vector2f normalized(const sf::Vector2f& start, const sf::Vector2f& end) 
	{
		float D = Distance(start, end);
		return sf::Vector2f((end.x - start.x) / D, (end.y - start.y) / D);
	}
	//���������� ������ ������� ����
	void setStart(const sf::Vector2f& start) const
	{
		
		this->current_pos = start;
		this->start_pos = start;
	};
	//���������� ����� ������� ����
	//��� ��������� ����� �������, ����������� ���� ��������
	void setEnd(const sf::Vector2f& end) const
	{
		this->end_pos = end;
		this->S = normalized(this->start_pos, this->end_pos);
		if (S.y >= 0 && S.x >= 0) 
		{
			this->obj->setRotation(180-asin(this->S.x) * 180 / 3.1415926535897932f);
		}
		else if (S.y <= 0 && S.x <= 0)
		{

			this->obj->setRotation(90 - acos(this->S.x) * 180 / 3.1415926535897932f);
		}
		else 
		{
			if (this->S.x < 0) 
			{
				this->obj->setRotation(90 + acos(this->S.x)*180/3.1415926535897932f);
			}
			else 
			{
				this->obj->setRotation(asin(this->S.x)*180/3.1415926535897932f);
			}
		}
	};

public:
	Turtle()
	{
	};

	//�������� ������� ������� �����
	sf::Vector2f getCurrentPos() const
	{
		return this->current_pos;
	};

	//�������� ������ ������� �������
	int getCurrentIndex() const 
	{
		return this->cur_index_pos;
	}
	//���������� ������ ������� �������
	void setCurIndex(const int& index) 
	{
		this->cur_index_pos = index;
	}
	//��������� �������� ��������
	void setSpeed(const float& speed) 
	{
		this->speed = speed;
	}
	//������ �������� - �������, ������� ����� ������, ������ - ��, ��� ������ ������������
	Turtle(const std::vector<sf::Vector2f>& positions, sf::Shape* shape) : Turtle()
	{
		if (positions.size() >= 2) 
		{
			this->setStart(positions[0]);
			this->setEnd(positions[1]);
			this->positions = positions;
			this->obj = shape;
		}
	};

	//���������� �������
	void setPositions(const std::vector<Vector2f>& vect) 
	{
		if (vect.size() >= 2) 
		{
			this->positions = vect;
			this->setStart(vect[0]);
			this->setEnd(vect[1]);
		}
	
	};
	//����� ��
	bool isVisible() const
	{
		return this->is_visible;
	};
	//��������� �����, ������� ������ ������������ �� ��������
	void setSprite(sf::Shape* obj) 
	{
		this->obj = obj;
	};
	//����������� ����� move
	void go()
	{
		this->is_move = true;
	};
	void stop() 
	{
		this->is_move = false;
	}

	//������
	void hide()
	{
		if (is_visible)
			this->is_visible = false;
	};
	//��������
	void show()
	{
		if (!is_visible)
			this->is_visible = true;
	};
	//���������� ���� ��������
	void setMove(const bool& set)
	{
		this->is_move= set;
	};
	//���������� ���� ���������
	void setVisible(const bool& set) 
	{
		this->is_visible = set;
	};
	void drawWithMoving(const bool& set)
	{
		this->move_with_drawing = set;
	};


	//����� ��� �����������
	//�� ���� �������� ����� - ����� ��� ��������� ��������
	bool move(const float& time = 1) const
	{
		if (this->is_move)
		{
			if (DistancePow2(this->current_pos, this->end_pos) >= 100)
			{
				this->current_pos.x += this->S.x*time*this->speed;
				this->current_pos.y += this->S.y*time*this->speed;
				this->obj->setPosition(this->current_pos);
				return false;
			}
			else
			{
				if (this->cur_index_pos + 2 < this->positions.size()) 
				{
					this->setStart(positions[this->cur_index_pos + 1]);
					this->setEnd(positions[this->cur_index_pos + 2]);
					this->obj->setPosition(this->current_pos);
				}
					++this->cur_index_pos;
			}
		}
		return true;
	}
	//������������� ������ draw, ��� ��������� �������, ������� ���������� � �������� RenderTarget ������������ ��� ������� ����� ������
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const override
	{
		if (this->is_visible)
		{
			if (this->move_with_drawing) 
			{
				this->move();
			}
			window.draw(*this->obj,states);
		};
	};




};

