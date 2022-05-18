#pragma once


#include "PathFinder.h"
#include <list>
#include <vector>


class voyager_task
{
private:
	std::vector<std::vector<int>> adj_matrix;
	std::vector<int> shortest;
	int record;

	int start;

	void eval(PathFinder& p);
	std::vector<int> getNbrs(const int& ind);
public:

	voyager_task(const std::vector<std::vector<int>>& g,const int& size) : adj_matrix(size,std::vector<int>(size,0))
	{
		this->record = INT_MAX;
		for (int i = 0; i < size; ++i) 
		{
			for (int j = 0; j < size; ++j) 
			{
				this->adj_matrix[i][j] = g[i][j];
			}
		}
	};
	int getRecord() const;
	void sloveTask(const int& start_vert_ind);
	std::vector<int> getShortest();

};
int voyager_task::getRecord() const 
{
	return this->record;
}

void voyager_task::eval(PathFinder& p)
{
	//Условие завершения рекурсии
	if (p.allVisited())
	{
		if (!this->adj_matrix[p.currentVertex()][ p.startVertex()])
		{
			return;
		}

		vector<int> path_vect(p.pathList().begin(), p.pathList().end());

		//Вычисление длины пути
		int len = 0;
		int front_vert = path_vect.front();
		int back_vert = path_vect.back();
		len += this->adj_matrix[p.startVertex()][front_vert];
		len += this->adj_matrix[back_vert][p.startVertex()];
		for (int i = 0; i < path_vect.size() - 1; ++i)
		{
			len += this->adj_matrix[path_vect[i]][path_vect[i + 1]];
		};

		//Сравнение всех путей
		if (this->record > len) 
		{
			this->shortest = path_vect;
			this->record = len;
		}
		
		return;
	};

	int p_vert(p.currentVertex());
	std::vector<int> nbrs_ind = this->getNbrs(p_vert);

	//Обход соседей
	for (int& i : nbrs_ind) 
	{
		//Если сущность не была в следующей вершине
		if (!p.wasIn(i)) 
		{
			//Копирование
			PathFinder p_cpy(p);
			//Переход в на другую вершину
			p_cpy.next(i);
			//рекурсивныый вызов 
			eval(p_cpy);
		}
		 
	}

}

inline void voyager_task::sloveTask(const int& start_vert_ind)
{
	this->start = start_vert_ind;
	PathFinder p(start_vert_ind, this->adj_matrix.size());
	this->eval(p);
}

inline std::vector<int> voyager_task::getShortest()
{
	std::vector<int> res(this->shortest.size() + 2);
	for (int i = 0; i < this->shortest.size(); ++i)
	{
		res[i + 1] = this->shortest[i];
	};
	res[0] = this->start;
	res[res.size() - 1] = this->start;
	return res;
}

inline std::vector<int> voyager_task::getNbrs(const int& ind)
{
	std::list<int> nbrs;
	
	for (int j = 0; j < this->adj_matrix.size(); ++j) 
	{
		if (this->adj_matrix[ind][j]) 
		{
			nbrs.push_back(j);
		}
	}
	return std::vector<int>(nbrs.begin(),nbrs.end());	
}