#include "Graph.h"

namespace Pz4_3 {

	// CLASS VERTEX RELEASE
	Vertex::Vertex() {
		this->m_id = NULL;
	}

	Vertex::Vertex(int id) {
		this->m_id = id;
	}

	Vertex::~Vertex() {}
	int Vertex::getId() const {
		return this->m_id;
	}
	const std::vector<Vertex*>& Vertex::getNeighbors() const {
		return this->list_neighbors;
	}
	void Vertex::addNeighbor(Vertex* neighbor) {
		this->list_neighbors.push_back(neighbor);
	}

	//CLASS GRAPH RELEASE
	Graph::Graph() {}

	Graph::Graph(const std::vector<std::vector<int>>& matrix) {
		for (auto& list : matrix) {
			Vertex* v = new Vertex(list[0]);
			m_vec.push_back(v);
		}
		for (auto& list : matrix) {
			Vertex* v1 = m_vec[list[0] - 1];
			for (size_t i = 1; i < list.size(); i++) {
				Vertex* v2 = m_vec[list[i] - 1];
				v1->addNeighbor(v2);
			}
		}
	}

	Graph::~Graph() {
		for (auto& v : m_vec) {
			delete v;
		}
	}

	size_t Graph::size() {
		return m_vec.size();
	}

	int Graph::getEccentricity(Vertex* v) {
		std::unordered_map<Vertex*, int> dist;
		std::queue<Vertex*> q;
		for (auto& vertex : m_vec) {
			dist[vertex] = -1;
		}
		dist[v] = 0;

		q.push(v);

		while (!q.empty()) {
			Vertex* u = q.front();
			q.pop();
			for (auto& neighbor : u->getNeighbors()) {
				if (dist[neighbor] == -1) {
					dist[neighbor] = dist[u] + 1;
					q.push(neighbor);
				}
			}
		}
		int max_dist = -1;
		for (auto& d : dist) {
			if (d.second > max_dist) {
				max_dist = d.second;
			}
		}
		return max_dist;
	}

	int Graph::getRadius() {
		int radius = INT_MAX;
		for (auto& v : m_vec) {
			int eccentricity = getEccentricity(v);
			if (eccentricity < radius) {
				radius = eccentricity;
			}
		}
		return radius;
	}

	int Graph::getDiameter() {
		std::vector<std::vector<int>> dist(size(), std::vector<int>(size(), INT_MAX));
		for (int i = 0; i < size(); i++) {
			for (auto& neighbor : m_vec[i]->getNeighbors()) {
				dist[i][neighbor->getId() - 1] = 1;
				dist[neighbor->getId() - 1][i] = 1;
			}
		}
		for (int k = 0; k < size(); k++) {
			for (int i = 0; i < size(); i++) {
				for (int j = 0; j < size(); j++) {
					if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][j] > dist[i][k] + dist[k][j]) {
						dist[i][j] = dist[i][k] + dist[k][j];
					}
				}
			}
		}
		int diameter = 0;
		for (int i = 0; i < size(); i++) {
			for (int j = 0; j < size(); j++) {
				if (dist[i][j] != INT_MAX && dist[i][j] > diameter) {
					diameter = dist[i][j];
				}
			}
		}
		return diameter;
	}

	std::vector<Vertex*> Graph::getPeripheralVertices() {
		std::vector<Vertex*> peripheralVertices;
		int diameter = getDiameter();
		for (auto& v : m_vec) {
			if (getEccentricity(v) == diameter || 
					(v->getNeighbors().empty() && diameter == 1)) {
				peripheralVertices.push_back(v);
			}
		}
		return peripheralVertices;
	}

	std::vector<Vertex*> Graph::getCenterVertices() {
		std::vector<Vertex*> centerVertices;
		int radius = getRadius();
		for (auto& v : m_vec) {
			if (getEccentricity(v) == radius) {
				centerVertices.push_back(v);
			}
		}
		return centerVertices;
	}

	const std::vector<Vertex*>& Graph::getVec() const { 
		return m_vec; 
	}

}