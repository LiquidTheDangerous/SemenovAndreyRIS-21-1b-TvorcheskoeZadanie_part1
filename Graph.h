#include <iostream>
#include <vector>
#include <queue>

#include <algorithm>

#include <iomanip>
#include <SFML/Graphics.hpp>

#include "Btn.h"
#include "DataArrow.h"
#include "Data_Circle.h"
#include "MenuEvent.h"
#include "matrix_app.h"
#include "Turtle.h"

#include "voyager_task.h"

using std::vector;
using std::cout;
using std::endl;
using std::queue;
using std::fill;

#pragma once
template <class T>
class Graph 
{
private:
	//Вектор вершин
	vector<T> vertexList;

	//Матрица смежности
	vector<vector<int>> adjMatrix;

	//Размер вектора вершин и матрицы смежности
	int maxSize;

	queue<T> VertsQueue;

	vector<int> labelList;

public:

	Graph(const int& size);

	Graph() : Graph(20) {};

	Graph(const Graph<T>&) = default;

	//Выводит матрицу смежности
	void showAdj();

	std::vector<std::vector<int>> getAdj() const
	{
		return this->adjMatrix;
	}

	//true, если граф пустой
	bool isEmpty();

	//true, если граф полный
	bool isFull();

	//Возвращает позицию вершины в списке вершин
	int GetVertPos(const T&);

	//Возвращает количество вершин
	int GetAmountVerts();

	//Добавляет вершину
	bool insertVertex(const T&);

	//Количество ребер для неориентированного графа
	int GetAmountEdges();

	//получить вес
	int GetWeight(const T&, const T&);

	int getWeightInd(const int&, const int&);

	void eraseVertex(const T& vert);

	void eraseEdge(const T& vert,const T& vert2);

	void InsertEdge(const T& vertex1, const T& vertex2, const int& weight = 1);


	std::vector<T> GetNbrs(const T&);

	std::vector<int> getNbrsInd(const int& vert_index);

	void Print();

	std::vector<T> getVertexList() const;

	void DrawGraph();

	void StartApplication();

	void BFS(T& startVertex, bool* visitedVerts);
	void DFS(T& startVertex, bool* visitedVerts);
	void Dijkstra(T& startVertex);
	bool AllVisited(vector<bool>& visitedVerts);
	void FillLabels(T& startVertex);


	static double to_rad(const double& d)
	{
		return d * 3.1415926535897932 / 180;
	}
	static vector<Vector2f> getPolyCircleVertPos(const Vector2f& pos, const int& radius, const int& n)
	{
		vector<Vector2f> result(n);
		for (int i = 0; i < n; ++i)
		{

			double angle = to_rad((360 / double(n)) * double(i));
			result[i] = Vector2f(pos.x + radius * cos(angle), pos.y + radius * sin(angle));
		}
		return result;
	};
	std::pair<std::vector<int>,int> slove_task(const int& start) 
	{
		voyager_task task(this->adjMatrix, this->vertexList.size());
		task.sloveTask(start);
		return std::pair<vector<int>,int>(task.getShortest(),task.getRecord());
	};
	std::pair<std::vector<sf::Vector2f>,std::string> get_positions_voyager(const std::pair<std::vector<int>, int>& index_positions,const int& start,const std::vector<DataCircle*>& circles)
	{
		std::string info = "path : ";
		if (index_positions.first.size()) 
		{
			info += this->vertexList[index_positions.first.front()];
			for (int i = 1; i < index_positions.first.size(); ++i) 
			{
				info += "-" + this->vertexList[index_positions.first[i]];
			}
			//info += std::to_string(index_positions.back());
		}
		else
		{
			return std::pair<std::vector<sf::Vector2f>, std::string>(std::vector<sf::Vector2f>(),"Can't find");
		}
		info += "\na.e. : " + std::to_string(index_positions.second);
		std::vector<sf::Vector2f> positions(index_positions.first.size());
		for (int i = 0; i < index_positions.first.size(); ++i) 
		{
			positions[i] = circles[index_positions.first[i]]->getPosition();
		}


		return std::pair<std::vector<sf::Vector2f>,std::string>(positions,info);
	};
	  
};	
template <class T>
int Graph<T>::getWeightInd(const int& i, const int& j) 
{
	return this->adjMatrix[i][j];
};


template <class T>
std::vector<int> Graph<T>::getNbrsInd(const int& vert_index) 
{
	std::vector<int> nbrs_ind;
	for (int j = 0; j < this->adjMatrix.size(); ++j) 
	{
		if (this->adjMatrix[vert_index][j]) 
		{
			nbrs_ind.push_back(j);
		}
	}
	return nbrs_ind;
	
};

template <class T>
void Graph<T>::eraseEdge(const T& vert, const T& vert2) 
{
	int p1 = this->GetVertPos(vert);
	int p2 = this->GetVertPos(vert2);
	if (p1 != -1 && p2 != -1) 
	{
		this->adjMatrix[p1][p2] = 0;
	}
};

template <class T>
void Graph<T>::eraseVertex(const T& vert) 
{
	int pos = this->GetVertPos(vert);
	if ( pos != -1) 
	{
		for (int i = 0; i < this->vertexList.size(); ++i) 
		{
			this->adjMatrix[i].erase(this->adjMatrix[i].begin() + pos);
		}
		this->adjMatrix.erase(this->adjMatrix.begin() + pos);
		this->vertexList.erase(this->vertexList.begin() + pos);
	}
};



template<class T>
inline std::vector<T> Graph<T>::getVertexList() const
{
	return this->vertexList;
}


void Graph<string>::StartApplication() 
{
	setlocale(LC_ALL, "Russian");

	srand(time(NULL));

	Font font;
	font.loadFromFile("timesnewromanpsmt.ttf");

	Text Msg("", font, 30);
	Msg.setPosition(500,100);
	Msg.setFillColor(Color::White);
	

	Text input("", font, 30);
	input.setPosition(700, 100);
	input.setFillColor(Color::White);

	Image star_sky;
	star_sky.loadFromFile("star_sky_h.jpg");

	Texture star_sky_texture;
	star_sky_texture.loadFromImage(star_sky);
	Sprite star_sky_sprite(star_sky_texture, sf::IntRect(0,0,2070,1440));


	Image planets_img;
	planets_img.loadFromFile("planets.png");

	Texture planets_texture;
	planets_texture.loadFromImage(planets_img);

	Image graph_img;
	graph_img.loadFromFile("nodes_3.png");

	Image table_img;
	table_img.loadFromFile("table_icon.png");

	matrix_app matr;
	matr.setIcon(840,828,table_img.getPixelsPtr());
	matr.setAdjMatrix(&this->adjMatrix);
	matr.setVerts(&this->vertexList);
	matr.setWidth(96);
	matr.setHeight(64);

	Image car_img;
	car_img.loadFromFile("x_wing.png");

	Texture car_tex;
	car_tex.loadFromImage(car_img);

	Image circle_mark_img;
	circle_mark_img.loadFromFile("mark_rebel(1).png");

	Texture circle_mark_texture;
	circle_mark_texture.loadFromImage(circle_mark_img);

	RectangleShape mark_(sf::Vector2f(800,800));
	mark_.setOrigin(400, 400);
	mark_.scale(sf::Vector2f(0.125, 0.125));
	mark_.setTexture(&circle_mark_texture);

	sf::RectangleShape car_shape(sf::Vector2f(1857,1982));

	car_shape.scale(sf::Vector2f(0.0625, 0.0625));
	car_shape.setTexture(&car_tex);
	car_shape.setOrigin(sf::Vector2f(1857 / 2, 1982 / 2));
	Turtle car_voyager;
	car_voyager.setSprite(&car_shape);
	car_voyager.setVisible(false);
	car_voyager.drawWithMoving(false);
	car_voyager.setSpeed(3);


	RenderWindow win(VideoMode(1200, 800), "Graph");
	win.setIcon(512,512,graph_img.getPixelsPtr());

	win.setFramerateLimit(60);
	View view(Vector2f(600, 400), Vector2f(1200, 800));
	win.setView(view);

	vector<Vector2f> circle_pos = getPolyCircleVertPos({600,400}, 400 - 120, this->vertexList.size());
	vector<DataCircle*> circles(this->vertexList.size());

	DataArrow arrow;
	arrow.setColor(Color::White);
	arrow.setTextColor(Color::White);
	std::vector<int> positions_ind;

	//Интерактивная вершина
	DataCircle interactiv;
	interactiv.id = -1;
	interactiv.visible = false;
	interactiv.setText("");
	interactiv.setPosition(0, 0);
	interactiv.setRadius(60);
	interactiv.centrize();
	interactiv.setDefaultColor(Color::White);
	interactiv.switchColorToMain();
	interactiv.setMarkShape(&mark_);



	for (int i = 0; i < circles.size(); ++i)
	{
		circles[i] = new DataCircle();
		circles[i]->id = i;
		circles[i]->setText(this->vertexList[i]);
		circles[i]->setPosition(circle_pos[i].x, circle_pos[i].y);
		circles[i]->setRadius(60);
		circles[i]->centrize();
		circles[i]->setTexture(planets_texture);
		circles[i]->setTextureRect(sf::IntRect(270 * (rand() % 6), 270 * (rand() % 6), 270, 270));
		circles[i]->setDefaultColor(Color::White);
		circles[i]->switchColorToMain();
		circles[i]->setMarkShape(&mark_);
		
	};

	Btn button_show_adj({ 1200 - 150 - 20,400 - 20 - 300 }, { 150,40 }, "Show adjMatrix");
	Btn button_rename_vertex({ 1200 - 150 - 20,400 - 20 - 200 }, {150,40},"Rename vertex");
	Btn button_delete_vertex({1200 - 150 - 20, 400 - 20 - 100}, {150,40},"Delete vertex");
	Btn button_add_vertex({1200 - 150 - 20,400 - 20}, {150,40},"Add vertex");
	Btn button_insert_edge({ 1200 - 150 - 20, 400 - 20 + 100 }, {150,40},"Insert edge");
	Btn button_delete_edge({ 1200 - 150 - 20,400 - 20 + 200 }, {150,40},"Delete edge");
	Btn button_voyager_task({ 1200 - 150 - 20,400 - 20 + 300 }, { 150,40 }, "Voyager task");
	button_add_vertex.setTypeId(MenuEvent::ButtonType::ADD);
	button_delete_vertex.setTypeId(MenuEvent::ButtonType::DEL);
	button_insert_edge.setTypeId(MenuEvent::ButtonType::INSERT_EDGE);
	button_delete_edge.setTypeId(MenuEvent::ButtonType::DELETE_EDGE);
	button_rename_vertex.setTypeId(MenuEvent::ButtonType::RENAME);
	button_show_adj.setTypeId(MenuEvent::ButtonType::SHOW_ADJ);
	button_voyager_task.setTypeId(MenuEvent::ButtonType::VOYAGER_TASK);
	std::vector<Btn*> buttons{&button_show_adj,&button_rename_vertex,&button_delete_vertex,&button_add_vertex,&button_insert_edge,&button_delete_edge,&button_voyager_task};

	sf::Clock clock;
	std::string str;
	while (win.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		Event event;
		static MenuEvent MEvent;

		Vector2i mouse_pos_2 = Mouse::getPosition(win);
		
		Vector2f mouse_pos = win.mapPixelToCoords(mouse_pos_2);
		static float dx(0);
		static float dy(0);


		/*Цикл обработки событий*/
		while (win.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{

				win.close();

				
			}
			//Действия при изменении размеров окна
			else if (event.type == sf::Event::Resized) 
			{

				float w = static_cast<float>(event.size.width);
				float h = static_cast<float>(event.size.height);
				view.setCenter({w/2,h/2});
				view.setSize({w,h});
				win.setView(view);
				
					
				for (int i = -3, c = 0; i <= 3; ++i) 
				{
					buttons[c++]->setPosition(w- 150 - 20,h/2 + 100*i);
				}
				
				Msg.setPosition({ w / 2 - 100,h / 8 });
				input.setPosition({ w / 2 + 100,h / 8 });
			}
			
			//Проверка нажатия на кнопку
			if (event.type == Event::MouseButtonPressed)
			{
				if (MEvent.what != MenuEvent::What::Wait)
				{
					if (event.key.code == Mouse::Left)
					{
						for (Btn*& button : buttons)
						{
							if (button->contains(Vector2f(mouse_pos_2.x, mouse_pos_2.y)))
							{
								button->switchColorToPressed();
								MEvent.what = MenuEvent::What::ButtonPressed;
								MEvent.btn_code = button->getTypeId();
							}
						}
					}
				}
				
				//Завершение выбора позиции для вершины 
				if (event.key.code == Mouse::Left
					&& MEvent.what == MenuEvent::What::Select_Pos)
				{
						Msg.setString("Input name: ");
						MEvent.what = MenuEvent::What::Wait;
						MEvent.pos = mouse_pos;
						interactiv.setPosition(MEvent.pos.x, MEvent.pos.y);
				}
			}
			if (event.type == Event::MouseButtonReleased ) 
			{
				if (event.key.code == Mouse::Left)
				for (Btn* button : buttons) 
				{
					if (button->contains(Vector2f(mouse_pos_2.x, mouse_pos_2.y)))
					{
						button->switchColorToMain();
					}
				}
			}

			//Обработка событий ввода текста
			if (event.type == Event::TextEntered)
			{
				if (MEvent.what == MenuEvent::What::Wait)
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
						input.setString(str);
					}
				}
			};
			//Завершение ввода текста
			if (event.type == Event::KeyPressed) 
			{
				if (event.key.code == Keyboard::Enter)
				{
					if (MEvent.what == MenuEvent::What::Wait)
					{
						if (MEvent.btn_code == MenuEvent::ButtonType::ADD)
						{
							if (this->insertVertex(str))
							{
								circles.push_back(new DataCircle());
								circles.back()->id = (int) circles.size() - 1;
								circles.back()->setText(str);
								circles.back()->setPosition(MEvent.pos.x, MEvent.pos.y);
								circles.back()->setRadius(60);
								circles.back()->centrize();
								circles.back()->setMarkShape(&mark_);
								circles.back()->setTexture(planets_texture);
								circles.back()->setTextureRect(sf::IntRect(MEvent.rand_i, MEvent.rand_j, 270, 270));
								circles.back()->setDefaultColor(Color::White);
								circles.back()->switchColorToMain();
								interactiv.visible = false;
								this->vertexList.back() = str;

							}
						}

						else if (MEvent.btn_code == MenuEvent::ButtonType::INSERT_EDGE)
						{
							this->InsertEdge(circles[MEvent.index_first]->getString(), circles[MEvent.index_second]->getString(), atoi(str.c_str()));
						}
						else if (MEvent.btn_code == MenuEvent::ButtonType::RENAME)
						{
							if (this->GetVertPos(str) == -1)
							{
								this->vertexList[MEvent.index_first] = str;
								circles[MEvent.index_first]->setText(str);

							}
						}

						if (MEvent.index_first != -1)
						{
							circles[MEvent.index_first]->switchColorToMain();
						}
						if (MEvent.index_second != -1)
						{
							circles[MEvent.index_second]->switchColorToMain();
						}


						input.setString("");
						Msg.setString("");
						str = "";
						MEvent.what = MenuEvent::What::Nothing;
						MEvent.index_first = -1;
						MEvent.index_second = -1;

					}
				}
				//Очистка меток по нажатию на пробел
				else if (event.key.code == Keyboard::Space) 
				{
					if (MEvent.what != MenuEvent::What::CarRiding) 
					{
						
						for (int i = 0; i < circles.size(); ++i)
						{
							circles[i]->markt = false;
						}
						Msg.setString("");
						MEvent.what = MenuEvent::What::Nothing;
					}
				}

				

			}
			//Преемещение вершин мышкой
			for (int i = 0; i < circles.size(); ++i) 
			{
				DataCircle*& c = circles[i];
				if (MEvent.what != MenuEvent::What::Chosen) 
				{
					if (MEvent.what != MenuEvent::What::CarRiding) 
					{
						c->handleMouseEvent(event, mouse_pos);
						if (c->moving)
						{
							c->moveOnMouse(mouse_pos);
						}
					}
				}
				else
				{
					//Выбор вершин, соохранение их индексов
					if (MEvent.btn_code == MenuEvent::ButtonType::INSERT_EDGE || MEvent.btn_code == MenuEvent::ButtonType::DELETE_EDGE  
					 || MEvent.btn_code == MenuEvent::ButtonType::RENAME      || MEvent.btn_code == MenuEvent::ButtonType::DEL
					||  MEvent.btn_code == MenuEvent::ButtonType::VOYAGER_TASK)
					{
						if (MEvent.index_first == -1)
						{
							MEvent.index_first = c->handleMouseEvent(event, mouse_pos);
							c->moving = false;
							if (MEvent.index_first != -1) 
							{
								circles[MEvent.index_first]->switchColorToSelected();
							}
						}
						else if (MEvent.index_second == -1) 
						{
							MEvent.index_second = c->handleMouseEvent(event,mouse_pos);
							c->moving = false;
							if (MEvent.index_second!= -1)
							{
								circles[MEvent.index_second]->switchColorToSelected();
							}
						}
					}
				}
			}


			//Обработка событий меню
			switch (MEvent.what)
			{
			case MenuEvent::What::ButtonPressed:
				if (MEvent.btn_code == MenuEvent::ButtonType::ADD)
				{
					Msg.setString("Choose a position: ");
					interactiv.visible = true;
					MEvent.rand_i = 270 * (rand() % 6);
					MEvent.rand_j = 270 * (rand() % 6);
					interactiv.setTexture(planets_texture);
					interactiv.setTextureRect(sf::IntRect(MEvent.rand_i, MEvent.rand_j, 270, 270));
					MEvent.what = MenuEvent::What::Select_Pos;
				}
				else if (MEvent.btn_code == MenuEvent::ButtonType::DEL || MEvent.btn_code == MenuEvent::ButtonType::RENAME)
				{
					Msg.setString("Select vertex: ");
					MEvent.what = MenuEvent::What::Chosen;
				}
				else if (MEvent.btn_code == MenuEvent::ButtonType::INSERT_EDGE || MEvent.btn_code == MenuEvent::ButtonType::DELETE_EDGE)
				{
					Msg.setString("Select 2 vertex: ");
					MEvent.what = MenuEvent::What::Chosen;
				}
				else if (MEvent.btn_code == MenuEvent::ButtonType::SHOW_ADJ)
				{
					//win.;
					MEvent.what = MenuEvent::What::Nothing;
					win.setActive(false);

					matr.showWindow();
					win.setActive(true);
					if (matr.is_renamed())
					{
						for (int i = 0; i < circles.size(); ++i) 
						{
							circles[i]->setText(this->vertexList[i]);
						}

						matr.setUnRenamed();
					}

				}
				else if (MEvent.btn_code == MenuEvent::ButtonType::VOYAGER_TASK)
				{
					car_voyager.setCurIndex(0);
					Msg.setString("Select start vertex:");
					MEvent.what = MenuEvent::What::Chosen;
				};
				break;
				
			case MenuEvent::What::Chosen:
				if (MEvent.btn_code == MenuEvent::ButtonType::DEL) 
				{
					if (MEvent.index_first != -1) 
					{
						this->eraseVertex(circles[MEvent.index_first]->getString());
						delete circles[MEvent.index_first];
						circles.erase( circles.begin() + MEvent.index_first);
						for (int i = 0; i < circles.size(); ++i) 
						{
							circles[i]->id = i;
						}

						Msg.setString("");
						MEvent.what = MenuEvent::What::Nothing;
						MEvent.index_first = -1;
					}
				}
				else if (MEvent.btn_code == MenuEvent::ButtonType::RENAME) 
				{
					if (MEvent.index_first != -1) 
					{
						Msg.setString("Input name: ");
						MEvent.what = MenuEvent::What::Wait;
					}
				}
				else if (MEvent.btn_code == MenuEvent::ButtonType::INSERT_EDGE)
				{
					if (MEvent.index_first != -1 && MEvent.index_second != -1)
					{
						MEvent.what = MenuEvent::What::Wait;
						Msg.setString("Input weight:");
					}
				}
				else if (MEvent.btn_code == MenuEvent::ButtonType::DELETE_EDGE) 
				{
					if (MEvent.index_first != -1 && MEvent.index_second != -1) 
					{
						circles[MEvent.index_first]->switchColorToMain();
						circles[MEvent.index_second]->switchColorToMain();
						this->eraseEdge(circles[MEvent.index_first]->getString(), circles[MEvent.index_second]->getString());
						Msg.setString("");
						MEvent.what = MenuEvent::What::Nothing;
						MEvent.index_first = -1;
						MEvent.index_second = -1;
					}
				}
				else if (MEvent.btn_code == MenuEvent::ButtonType::VOYAGER_TASK) 
				{
					if (MEvent.index_first != -1) 
					{
						std::pair<std::vector<int>,int> res = slove_task(MEvent.index_first);
						positions_ind = res.first;
						if (positions_ind.size() > 2) 
						{
							std::pair<std::vector<sf::Vector2f>, std::string> r = get_positions_voyager(res,MEvent.index_first, circles);
							car_voyager.setPositions(r.first);
							car_voyager.setVisible(true);
							Msg.setString(r.second);
							MEvent.what = MenuEvent::What::CarRiding;
						}
							circles[MEvent.index_first]->switchColorToMain();
							MEvent.index_first = -1;
							MEvent.index_second = -1;
					}
				}

				break;
			default:
				break;
			}
		}


		//отрисовка звездного полотна
		win.clear(sf::Color::White);
		win.draw(star_sky_sprite);


		//Интерактивное добавление ребра
		if (MEvent.what == MenuEvent::What::Chosen)
		{
			if (MEvent.btn_code == MenuEvent::ButtonType::INSERT_EDGE)
			{
				if (MEvent.index_first != -1)
				{
					if (MEvent.index_second == -1)
					{
						arrow.setStart(circles[MEvent.index_first]->getPosition());
						arrow.setEnd(mouse_pos);
						arrow.setText("");
						arrow.setR(0);
						win.draw(arrow);
					}
				}
			}
		}
		else if (MEvent.what == MenuEvent::What::Wait)
		{
			if (MEvent.btn_code == MenuEvent::ButtonType::INSERT_EDGE)
			{
				if (MEvent.index_first != -1
					&& MEvent.index_second != -1)
				{
					arrow.setStart(circles[MEvent.index_first]->getPosition());
					arrow.setText("");
					arrow.setR(55);
					arrow.setEnd(circles[MEvent.index_second]->getPosition());
					win.draw(arrow);
				}
			}
		};

		//Интерактивоное добавление вершины
		if (MEvent.what == MenuEvent::What::Select_Pos) 
		{
			if (MEvent.btn_code == MenuEvent::ButtonType::ADD) 
			{
				interactiv.setPosition(mouse_pos.x, mouse_pos.y);
				win.draw(interactiv);
			}
		}
		else if (MEvent.what == MenuEvent::What::Wait) 
		{
			win.draw(interactiv);
		}


		//Отрисовка ребер
		for (int i = 0; i < this->vertexList.size(); ++i) 
		{
			for (int j = 0; j < this->vertexList.size(); ++j) 
			{

				if (this->adjMatrix[i][j]) 
				{
					if (this->adjMatrix[j][i]) 
					{
						arrow.setStart(circles[i]->getPosition());
						arrow.setEnd(circles[i]->getMid(*circles[j]));
						arrow.setR(0);
						arrow.setText(std::to_string(this->adjMatrix[i][j]));
						win.draw(arrow);
					}
					else
					{
						arrow.setStart(circles[i]->getPosition());
						arrow.setEnd(circles[j]->getPosition());
						arrow.setR(55);
						arrow.setText(std::to_string(this->adjMatrix[i][j]));
						win.draw(arrow);
					}
				}
			}
		}

		//Отрисовка вершин
		for (DataCircle* i : circles)
		{
			win.draw(*i);
		}

		//Отрисовка текса
		for (Btn* button : buttons) 
		{
			win.draw(*button);
		}

		//Отрисовка сообщения
		if (Msg.getString().getSize() != 0)
		{
			win.draw(Msg);
		};
		//Отрисовка вводимого тектса
		if (input.getString().getSize() != 0)
		{
			win.draw(input);
		};

		//Отрисовка анимации перемещения Звездного корабля 
		if (car_voyager.isVisible()) 
		{

			car_voyager.move(time/8000);
			if (car_voyager.getCurrentIndex() > circles.size()) 
			{

				car_voyager.setVisible(false);
				MEvent.what = MenuEvent::What::Nothing;
			}
			else
			{
				if (car_voyager.getCurrentIndex() < circles.size()) 
				{
					circles[positions_ind[car_voyager.getCurrentIndex()]]->markt = true;
				}
			
			}

			win.draw(car_voyager);
		}


		win.display();
	}

	//Выгрузка вершин
	for (int i = 0; i < circles.size(); ++i) 
	{
		delete circles[i];
	}




};

template <class T>
void Graph<T>::FillLabels(T& startVertex) 
{
	//Заполнение меток расстояния
	for (int i = 0, size = vertexList.size(); i < size; ++i)
		labelList[i] = 1000000;
	int pos = GetVertPos(startVertex);
	labelList[pos] = 0;
};


template <class T>
bool Graph<T>::AllVisited(vector<bool>& visitedVerts)
{
	//Проверяет, все ли ноды были посещены
	bool flag = true;
	for (int i = 0; i < this->vertexList.size(); i++)
		if (visitedVerts[i] != true)
			flag = false;
	return flag;
};



template <class T>
void Graph<T>::Dijkstra(T& startVertex) 
{
	for (int i = 0; i < vertexList.size(); i++)
		for (int j = 0; j < vertexList.size(); j++)
			if (adjMatrix[i][j] < 0) 
				return;

	if (GetVertPos(startVertex) == -1)
		return;

	vector<bool> visitedVerts(vertexList.size());
	fill(visitedVerts.begin(), visitedVerts.end(), false);

	this->FillLabels(startVertex);
	T curSrc = startVertex;
	vector<T> neighbors;

	while (!this->AllVisited(visitedVerts))
	{
		neighbors = this->GetNbrs(curSrc);
		int startLabel = labelList[GetVertPos(curSrc)];

		//Самый близкий сосед
		T* minNeighbor_ptr = nullptr;
		int minW = 1000000;

		for (int i = 0; i < neighbors.size(); ++i)
		{
			int weight = this->GetWeight(curSrc, neighbors[i]);
			int nIndex = this->GetVertPos(neighbors[i]);
			int nextLabel = labelList[nIndex];
			
			if (startLabel + weight < nextLabel)
			{
				labelList[nIndex] = startLabel + weight;
			};
			if (!visitedVerts[nIndex] && minW > labelList[nIndex])
			{
				minW = labelList[nIndex];
				minNeighbor_ptr = &neighbors[i];
			};
		};

		visitedVerts[GetVertPos(curSrc)] = true;
		if (minNeighbor_ptr != nullptr)
		{
			curSrc = *minNeighbor_ptr;
		};
	};


	/* Вывод результата работы алгоритма на экран */
	for (int i = 0; i < GetVertPos(startVertex); ++i)
	{
		cout << "Кратчайшее расстояние от вершины " << startVertex
			<< " до вершины " << vertexList[i] << " равно "
			<< labelList[GetVertPos(vertexList[i])] << endl;
	};

	for (int i = GetVertPos(startVertex) + 1; i < vertexList.size(); ++i)
	{
		cout << "Кратчайшее расстояние от вершины " << startVertex
			<< " до вершины " << vertexList[i] << " равно "
			<< labelList[GetVertPos(vertexList[i])] << endl;
	};


};



template<class T>
void Graph<T>::BFS(T& startVertex, bool* visitedVerts) {
	//Условие истино только при первом вызове функции
	if (visitedVerts[this->GetVertPos(startVertex)] == false) { 
		this->VertsQueue.push(startVertex); 
		cout << "Вершина " << startVertex << " обработана" << endl; 
		visitedVerts[this->GetVertPos(startVertex)] = true;
	}
	std::vector<T> neighbors = this->GetNbrs(startVertex); 
	this->VertsQueue.pop();
	for (int i = 0; i < neighbors.size(); ++i) {
		if (!visitedVerts[this->GetVertPos(neighbors[i])]) 
		{
			this->VertsQueue.push(neighbors[i]); 
								
			visitedVerts[this->GetVertPos(neighbors[i])] = true;
			cout << "Вершина " << neighbors[i] << " обработана" << endl;
		}
	}
	if (this->VertsQueue.empty())
	{
		return;
	};
	BFS(VertsQueue.front(),visitedVerts);
}

template<class T>
inline Graph<T>::Graph(const int& size)
{
	this->labelList = vector<int>(size);
	this->maxSize = size;
	this->adjMatrix = vector<vector<int>>(size, vector<int>(size));
	for (int i = 0; i < this->maxSize; ++i)
	{
		for (int j = 0; j < this->maxSize; ++j)
		{
			this->adjMatrix[i][j] = 0;
		};
	};
};



template<class T>
inline void Graph<T>::showAdj()
{
	for (int i = 0; i < this->maxSize; ++i)
	{
		for (int j = 0; j < this->maxSize; ++j)
		{
			cout << this->adjMatrix[i][j] << ' ';
		};
		cout << endl;
	}
};

template<class T>
inline bool Graph<T>::isEmpty()
{
	return this->vertexList.size() == 0;
};




template<class T>
inline bool Graph<T>::isFull()
{
	return this->vertexList.size() == this->maxSize;
};




template<class T>
inline int Graph<T>::GetVertPos(const T& v)
{
	for (int i = 0; i < this->vertexList.size(); ++i)
	{
		if (this->vertexList[i] == v)
		{
			return i;
		}
	}
	return -1;
};





template<class T>
inline int Graph<T>::GetAmountVerts()
{
	return this->vertexList.size();
};






template<class T>
inline bool Graph<T>::insertVertex(const T& vert)
{
	if (this->isFull())
	{
		cout << "Невозможно добвать вершину." << endl;
		return false;
	};
	if (this->GetVertPos(vert) == -1) 
	{
		this->vertexList.push_back(vert);
		return true;
	}
	return false;
};





template<class T>
int Graph<T>::GetAmountEdges()
{
	int amount = 0;
	if (!this->IsEmpty())
	{
		for (int i = 0; i < this->vertexList.size(); ++i)
		{
			for (int j = 0; j < this->vertexList.size(); ++j)
			{
				if (this->adjMatrix[i][j] != 0)
				{
					amount++;
				}
			}
		}
	}
	return amount;
};




template<class T>
inline int Graph<T>::GetWeight(const T& v1, const T& v2)
{
	if (this->isEmpty())
	{
		return 0;
	};

	int v1_p = this->GetVertPos(v1);
	int v2_p = this->GetVertPos(v2);

	if (v1_p == -1 || v2_p == -1)
	{
		cout << "Одного из узлов в графе не существует." << endl;
		return 0;
	};

	return this->adjMatrix[v1_p][v2_p];
};



template<class T>
void Graph<T>::DFS(T& startVertex, bool* visitedVerts) 
{
	cout << "Вершина " << startVertex << " посещена" << endl; 
	visitedVerts[this->GetVertPos(startVertex)] = true; 
	std::vector<T> neighbors = this->GetNbrs(startVertex);
	for (int i = 0; i < neighbors.size(); ++i)
	{
		if (!visitedVerts[this->GetVertPos(neighbors[i])])
		{
			this->DFS(neighbors[i], visitedVerts);
		};
	};
}

template<class T>
std::vector<T> Graph<T>::GetNbrs(const T& vertex) {
	std::vector<T> nbrsList; // создание списка соседей
	int pos = this->GetVertPos(vertex); /* вычисление позиции vertex в матрице смежности */
	if (pos != -1)
	{ /* проверка, что vertex есть в матрице смежности */
		for (int i = 0; i < this->vertexList.size(); ++i)
		{
			if (this->adjMatrix[pos][i] != 0)
			{
				nbrsList.push_back(this->vertexList[i]);
			}
		}
	}
	return nbrsList; // возврат списка соседей
};




template<class T>
void Graph<T>::InsertEdge(const T& vertex1, const T& vertex2,const int& weight) {
	if (GetVertPos(vertex1) != (-1) && this->GetVertPos(vertex2) != (-1)) {
		int vertPos1 = GetVertPos(vertex1);
		int vertPos2 = GetVertPos(vertex2);

		if (this->adjMatrix[vertPos1][vertPos2] != 0)
		{
			cout << "Ребро между вершинами уже есть" << endl;
			return;
		}
		else
		{
			this->adjMatrix[vertPos1][vertPos2] = weight;
		}
	}
	else
	{
		cout << "Обеих вершин (или одной из них) нет в графе " << endl;
		return;
	}
};



template<class T>
void Graph<T>::Print() {
	if (!this->isEmpty()) 
	{
		cout << "Матрица смежности графа: " << endl;

		cout << "-  ";
		for (int i = 0; i < vertexList.size(); ++i) 
		{
			cout << setw(3) << vertexList[i] << "  ";
		}
		cout << endl;

		for (int i = 0; i < this->vertexList.size(); ++i) {
			cout << this->vertexList[i] << " ";
			for (int j = 0; j < this->vertexList.size(); ++j) {
				cout << " " <<setw(3) << this->adjMatrix[i][j] << " ";
			}
			cout << endl;
		}
	}
	else {
		cout << "Граф пуст " << endl;
	}
}

