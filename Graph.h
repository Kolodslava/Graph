
#include <vector>
#include <queue>
#include <unordered_map>

namespace Pz4_3 {

    class Vertex {
    public:
        // Constructor/Destructor
        Vertex();
        Vertex(int id);
        ~Vertex();

        // Get/Set Methods

        int getId() const;
        const std::vector<Vertex*>& getNeighbors() const;
        void addNeighbor(Vertex*);

    private:
        int m_id;
        std::vector<Vertex*> list_neighbors;
    };

    class Graph {
    public:
        // Constructor/Destructor
        Graph();
        Graph(const std::vector<std::vector<int>>&);
        ~Graph();

        // Get/Set Methods

        const std::vector<Vertex*>& getVec() const;
        size_t size();

        // Calculate Parameters Graph Methods

        int getEccentricity(Vertex*);
        int getRadius();
        int getDiameter();
        std::vector<Vertex*> getPeripheralVertices();
        std::vector<Vertex*> getCenterVertices();

    private:
        std::vector<Vertex*> m_vec;
    };

}