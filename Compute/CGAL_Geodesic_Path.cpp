#include "CGAL_Geodesic_Path.h"

CGAL_Geodesic_Path::CGAL_Geodesic_Path(const Mesh& mesh)
    : mesh_(mesh)
{
    build_cgal_mesh();
}

void CGAL_Geodesic_Path::build_cgal_mesh()
{
    vmap_.reserve(mesh_.n_vertices());
    for (const VH& v : mesh_.vertices())
    {
        const auto& p = mesh_.point(v);
        vmap_.push_back(cgal_mesh_.add_vertex(Point_3(p[0], p[1], p[2])));
    }

    for (const FH& f : mesh_.faces())
    {
        std::vector<SurfaceMesh::Vertex_index> face;
        for (auto fv_it = mesh_.cfv_iter(f); fv_it.is_valid(); ++fv_it)
        {
            face.push_back(vmap_[fv_it->idx()]);
        }
        if (face.size() == 3)
            cgal_mesh_.add_face(face);
    }
}

void CGAL_Geodesic_Path::ComputePath(const VH& start, const VH& end)
{
    path_points_.clear();

    typedef CGAL::Surface_mesh_shortest_path_traits<Kernel, SurfaceMesh> Traits;
    typedef CGAL::Surface_mesh_shortest_path<Traits> Shortest_path;
    Shortest_path shortest_paths(cgal_mesh_);

    shortest_paths.add_source_point(vmap_[start.idx()]);

    std::list<Point_3> points;
    shortest_paths.shortest_path_points_to_source_points(vmap_[end.idx()], std::back_inserter(points));

    for (const Point_3& p : points)
    {
        path_points_.push_back(OpenMesh::Vec3d(p.x(), p.y(), p.z()));
    }
}

