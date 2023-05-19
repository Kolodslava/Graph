#include "Graph.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace Pz4_3;

std::vector<std::vector<int>> matrix = {
			{1, 5},
			{2, 3, 5},
			{3, 2, 4, 5, 11, 13},
			{4, 3, 11},
			{5, 1, 2, 3, 6, 7, 8, 9},
			{6, 5, 8, 12, 13},
			{7, 5, 8, 9},
			{8, 5, 6, 7, 9, 13, 14},
			{9, 5, 7, 8, 13, 15, 19},
			{10, 11, 17},
			{11, 3, 4, 10, 17},
			{12, 6},
			{13, 3, 6, 8, 9, 17, 23},
			{14, 8, 15, 18, 19},
			{15, 9, 14, 20},
			{16, 17},
			{17, 10, 11, 18, 22},
			{18, 14, 17, 19, 22, 23},
			{19, 14, 18, 20, 23},
			{20, 15, 19},
			{21, 22},
			{22, 17, 18, 21, 24},
			{23, 13, 18, 19, 24},
			{24, 22, 23},
};

void writeMatrixToFile(const std::vector<std::vector<int>>& matrix, const std::string& filename) {
	std::ofstream file(filename);
	if (file.is_open()) {
		for (const auto& row : matrix) {
			for (const auto& element : row) {
				file << element << " ";
			}
			file << std::endl;
		}
		file.close();
		std::cout << "Data successfully written to file." << std::endl;
	}
	else {
		std::cout << "Unable to open file for writing." << std::endl;
	}
}

std::vector<std::vector<int>> readMatrixFromFile(const std::string& filename) {
	std::vector<std::vector<int>> matrix;
	std::ifstream file(filename);
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			std::vector<int> row;
			std::istringstream iss(line);
			int value;
			while (iss >> value) {
				row.push_back(value);
			}
			matrix.push_back(row);
		}
		file.close();
		std::cout << "Data successfully read from file." << std::endl;
	}
	else {
		std::cout << "Unable to open file for reading." << std::endl;
	}
	return matrix;
}

int main(void) {
	std::string filename = "D:\\KPI\\вл\\ог 4.3\\Project\\Pz4_3\\Pz4_3\\Test\\list_graph_data.txt";
	writeMatrixToFile(matrix, filename);

	std::vector<std::vector<int>> matrix_test = readMatrixFromFile(filename);

	Graph graph(matrix_test);

	std::cout << graph.size() << "\n";

	std::vector<Vertex*> peripheralVertices = graph.getPeripheralVertices();
	std::vector<Vertex*> centerVertices = graph.getCenterVertices();

	int rad = graph.getRadius();
	int diam = graph.getDiameter();

	std::cout << "Radius: " << rad << "\n";
	std::cout << "Diameter: " << diam << "\n";

	std::cout << "Peripheral vertices: ";
	for (auto& v : peripheralVertices) {
		std::cout << v->getId() << " ";
	}
	std::cout << std::endl;

	std::cout << "Center vertices: ";
	for (auto& v : centerVertices) {
		std::cout << v->getId() << " ";
	}
	std::cout << std::endl;

	std::cin.get();

	return 0;
}