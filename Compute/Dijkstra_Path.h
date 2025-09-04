#pragma once
#include <queue>
#include <vector>
#include <iostream>
#include "..\MeshViewer\MeshDefinition.h"

typedef OpenMesh::EdgeHandle EH;
typedef OpenMesh::FaceHandle FH;
typedef OpenMesh::HalfedgeHandle HEH;
typedef OpenMesh::VertexHandle VH;

struct Node {
	VH v_h;

	int version;

	double dist_;

	bool operator<(const Node& n)const {
		return dist_ > n.dist_;
	}
};

class Dijkstra_Path
{
public:
	Dijkstra_Path(const Mesh& mesh)
		:mesh_(mesh)
	{
		e_status_.resize(mesh_.n_edges(), true);

		ComputeDefaultWeight();
	}

	~Dijkstra_Path();

	void ComputePath(VH& start, VH& end);

	void SetEdgeStatus(const std::vector<int>& true_e);

	void SetEdgeWeight(std::vector<double> e_weight) {
		e_weight_ = e_weight;
	}

	std::vector<HEH> return_path();

private:
	void ComputeDefaultWeight();

private:
	const Mesh& mesh_;

	std::vector<bool> e_status_;

	std::vector<HEH> path_;

	std::vector<double> e_weight_;
};

