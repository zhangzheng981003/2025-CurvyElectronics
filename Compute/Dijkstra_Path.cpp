#include "Dijkstra_Path.h"

Dijkstra_Path::~Dijkstra_Path()
{
}

void Dijkstra_Path::ComputePath(VH & start, VH & end)
{
	std::priority_queue<Node> Q;

	std::vector<int> forward_he_(mesh_.n_vertices(), -1);
	std::vector<int> version_(mesh_.n_vertices(), 0);
	std::vector<double> dist_(mesh_.n_vertices());

	for (const VH& v_h:mesh_.vertices())
	{
		dist_[v_h.idx()] = DBL_MAX;
	}

	// 1
	for (HEH voh : mesh_.voh_range(start))
	{
		if (!e_status_[mesh_.edge_handle(voh).idx()])
		{
			continue;
		}

		VH v_h = mesh_.to_vertex_handle(voh);

		// property
		forward_he_[v_h.idx()] = voh.idx();
		version_[v_h.idx()] += 1;
		dist_[v_h.idx()] = e_weight_[mesh_.edge_handle(voh).idx()];	

		// Node 
		Node temp_node;
		temp_node.v_h = v_h;
		temp_node.version = version_[v_h.idx()];
		temp_node.dist_ = dist_[v_h.idx()];
		Q.push(temp_node);
	}

	// 2
	while (!Q.empty()) {
		// 2.1
		Node temp_P = Q.top();
		Q.pop();

		// 2.2
		VH p = temp_P.v_h;
		if (version_[p.idx()] != temp_P.version) continue;

		// 2.3
		if (p == end) break;

		// 2.4
		double temp_dist = dist_[p.idx()];
		VH vv_h;
		double new_dist;
		for (HEH voh : mesh_.voh_range(p)) {

			if (!e_status_[mesh_.edge_handle(voh).idx()])
			{
				continue;
			}

			vv_h = mesh_.to_vertex_handle(voh);
			new_dist = temp_dist + e_weight_[mesh_.edge_handle(voh).idx()];
			if (dist_[vv_h.idx()] > new_dist)
			{
				// property
				forward_he_[vv_h.idx()] = voh.idx();
				version_[vv_h.idx()] += 1;
				dist_[vv_h.idx()] = new_dist;
				
				Node temp_node;
				temp_node.v_h = vv_h;
				temp_node.version = version_[vv_h.idx()];
				temp_node.dist_ = dist_[vv_h.idx()];
				Q.push(temp_node);

			}

		}
	}

	path_.clear();
	VH v_h = end;
	HEH he_h;
	do
	{
		int he_idx = forward_he_[v_h.idx()];
	
		if (he_idx == -1)
		{
			path_.clear();
			return;
		}

		he_h = mesh_.halfedge_handle(he_idx);
		path_.insert(path_.begin(), he_h);
		v_h = mesh_.from_vertex_handle(he_h);
	} while (v_h != start);

}

void Dijkstra_Path::SetEdgeStatus(const std::vector<int>& true_e)
{
	e_status_.clear();
	e_status_.resize(mesh_.n_edges(), false);
	for (size_t i : true_e)
	{
		e_status_[i] = true;
	}
}

std::vector<HEH> Dijkstra_Path::return_path()
{
	return path_;
}

void Dijkstra_Path::ComputeDefaultWeight()
{
	e_weight_ = std::vector<double>(mesh_.n_edges(), 0);

	for (const EH& e_h : mesh_.edges())
	{
		if (mesh_.is_boundary(e_h))
		{
			e_weight_[e_h.idx()] = DBL_EPSILON;
		}
		else
		{
			e_weight_[e_h.idx()] = mesh_.calc_edge_length(e_h);
		}
	}
}
