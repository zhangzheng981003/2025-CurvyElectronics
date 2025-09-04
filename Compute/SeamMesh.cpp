#include "SeamMesh.h"

SeamMesh::SeamMesh(Mesh& mesh)
	:mesh_(mesh)
{
	seam_status_ = std::vector<bool>(mesh_.n_edges(), false);

	SeamToIdx();
}

void SeamMesh::ReadSeam(const std::string& file_name)
{
	std::ifstream seam_file(file_name);
	int id_0, id_1;
	while (seam_file >> id_0 >> id_1)
	{
		VH v_0 = mesh_.vertex_handle(id_0);
		VH v_1 = mesh_.vertex_handle(id_1);
		HEH he_h = mesh_.find_halfedge(v_0, v_1);
		EH e_h = mesh_.edge_handle(he_h);

		seam_status_[e_h.idx()] = true;
	}
	seam_file.close();

	SeamToIdx();
}

void SeamMesh::SetSeam(const std::vector<bool>& seam)
{
	seam_status_ = seam;

	SeamToIdx();
}

void SeamMesh::SeamToIdx()
{
	seg_id_.assign(mesh_.n_faces(), -1);
	seg_num_ = 0;

	int start_idx = -1;
	for (int i = 0; i < mesh_.n_faces(); i++)
	{
		if (seg_id_[i] != -1) continue;

		start_idx = i;

		std::vector<int> f_stack;
		f_stack.push_back(start_idx);
		do
		{
			int top_idx = f_stack.back(); f_stack.pop_back();
			seg_id_[top_idx] = seg_num_;

			for (HEH fh_h : mesh_.fh_range(mesh_.face_handle(top_idx)))
			{
				FH oppo_f_h = mesh_.opposite_face_handle(fh_h);

				if (!mesh_.is_valid_handle(oppo_f_h)) continue;
				if (seg_id_[oppo_f_h.idx()] != -1) continue;

				int adj_e_idx = mesh_.edge_handle(fh_h).idx();
				if (!seam_status_[adj_e_idx])
				{
					f_stack.push_back(oppo_f_h.idx());
				}
			}
		} while (f_stack.size() != 0);

		++seg_num_;
	}
}

std::vector<bool>& SeamMesh::GetSeam()
{
	return seam_status_;
}

std::vector<int> SeamMesh::ReturnSegIdx()
{
	return seg_id_;
}

int SeamMesh::ReturnSegNum()
{
	return seg_num_;
}

Mesh SeamMesh::ReturnMesh()
{
	return mesh_;
}

std::vector<bool> SeamMesh::ReturnSeam()
{
	return seam_status_;
}

void SeamMesh::OutputMesh(const std::string& file_name)
{
	MeshTools::WriteMesh(mesh_, file_name, 12);
}

void SeamMesh::OutputSeam(const std::string& file_name)
{
	std::ofstream seam_cout(file_name);
	for (size_t i = 0; i < mesh_.n_edges(); i++)
	{
		if (seam_status_[i])
		{
			EH e_h = mesh_.edge_handle(i);
			HEH he_h = mesh_.halfedge_handle(e_h, 0);

			int idx_0 = mesh_.to_vertex_handle(he_h).idx();
			int idx_1 = mesh_.from_vertex_handle(he_h).idx();

			seam_cout << std::min(idx_0, idx_1) << " " << std::max(idx_0, idx_1) << std::endl;
		}
	}
	seam_cout.close();
}