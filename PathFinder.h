#pragma once
#include <list>
#include <vector>
#include <bitset>


class PathFinder
{
private:
	int start_vertex;
	int current_vertex;
	std::list<int> path;
	std::vector<bool> visited_verts;

public:
	PathFinder(const int& start_vert, const int& amount);
	PathFinder(const PathFinder& p);

	//получение позиции начала
	int& startVertex();
	//прлучение текущей позиции
	int& currentVertex();
	//Все ли были посещены
	bool allVisited() const;
	//Был ли в некоторой вершине

	bool wasIn(const int& v) const;
	//Переход к следующей
	void next(const int& v);
	//Получить путь
	std::list<int>& pathList();
};

inline PathFinder::PathFinder(const int& start_vert, const int& amount) : visited_verts(amount, false)
{
	this->current_vertex = start_vert;
	this->start_vertex = start_vert;
	this->visited_verts[this->start_vertex] = true;
}

inline PathFinder::PathFinder(const PathFinder& p)
{
	this->start_vertex = p.start_vertex;
	this->current_vertex = p.current_vertex;
	this->path = p.path;
	this->visited_verts = p.visited_verts;
}

inline int& PathFinder::startVertex()
{
	return this->start_vertex;
}

inline int& PathFinder::currentVertex()
{
	return this->current_vertex;
}

inline bool PathFinder::allVisited() const
{
	for (bool i : this->visited_verts) 
	{
		if (i == false)
		{
			return false;
		}
	}
	return true;
}

bool PathFinder::wasIn(const int& v) const
{
	return this->visited_verts[v];
}

inline void PathFinder::next(const int& v)
{
	if (v >= this->visited_verts.size()) 
	{
		return;
	}
	this->current_vertex = v;
	this->path.push_back(v);
	this->visited_verts[v] = true;
}

inline std::list<int>& PathFinder::pathList()
{
	return this->path;
}
