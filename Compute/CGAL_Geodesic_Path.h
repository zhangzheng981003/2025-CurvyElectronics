#pragma once

#include <vector>
#include <list>
#include "../MeshViewer/MeshDefinition.h"

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Surface_mesh_shortest_path.h>

class CGAL_Geodesic_Path
{
public:
    CGAL_Geodesic_Path(const Mesh& mesh);
    ~CGAL_Geodesic_Path() = default;

    void ComputePath(const VH& start, const VH& end);

    std::vector<OpenMesh::Vec3d> return_path() const { return path_points_; }

private:
    typedef CGAL::Simple_cartesian<double> Kernel;
    typedef Kernel::Point_3 Point_3;
    typedef CGAL::Surface_mesh<Point_3> SurfaceMesh;

    void build_cgal_mesh();

    const Mesh& mesh_;
    SurfaceMesh cgal_mesh_;
    std::vector<SurfaceMesh::Vertex_index> vmap_;
    std::vector<OpenMesh::Vec3d> path_points_;
};