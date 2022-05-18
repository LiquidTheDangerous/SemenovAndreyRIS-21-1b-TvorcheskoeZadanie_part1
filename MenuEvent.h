#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
struct MenuEvent
{
	enum class ButtonType 
	{
		SHOW_ADJ,
		RENAME,
		ADD,
		DEL,
		INSERT_EDGE,
		DELETE_EDGE,
		VOYAGER_TASK
	};
	ButtonType btn_code;
	enum class What
	{
		ButtonPressed,
		Wait,
		Chosen,
		Select_Pos,
		CarRiding,
		Nothing
	} what;
	sf::Vector2f pos;
	int index_first;
	int index_second;
	int rand_i;
	int rand_j;
	MenuEvent() : index_first(-1), index_second(-1)
	{
		this->what = What::Nothing;
	}
};

