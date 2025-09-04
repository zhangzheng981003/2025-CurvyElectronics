#pragma once
#include <fstream>
#include "../MeshViewer/MeshDefinition.h"

class SeamMesh
{
public:
	SeamMesh(Mesh& mesh);

	void ReadSeam(const std::string&); // file with v_0 and v_1
	void SetSeam(const std::vector<bool>& seam);

	std::vector<bool>& GetSeam();
	std::vector<int> ReturnSegIdx();
	int ReturnSegNum();
	Mesh ReturnMesh();

	std::vector<bool> ReturnSeam();

	void OutputMesh(const std::string&);
	void OutputSeam(const std::string&);

private:
	void SeamToIdx();

private:
	Mesh& mesh_;

	std::vector<bool> seam_status_;

	std::vector<int> seg_id_;

	int seg_num_;
};

