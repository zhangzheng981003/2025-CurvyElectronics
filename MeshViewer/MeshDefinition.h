#ifndef MESHDEFINITION_H
#define MESHDEFINITION_H
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Geometry/VectorT.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
//#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

struct MeshTraits : public OpenMesh::DefaultTraits
{
	typedef OpenMesh::Vec3d Point;
	typedef OpenMesh::Vec3d Normal;

	VertexAttributes(OpenMesh::Attributes::Status);
	FaceAttributes(OpenMesh::Attributes::Status);
	EdgeAttributes(OpenMesh::Attributes::Status);
	HalfedgeAttributes(OpenMesh::Attributes::Status);
};

typedef OpenMesh::TriMesh_ArrayKernelT<MeshTraits> Mesh;
//typedef OpenMesh::PolyMesh_ArrayKernelT<MeshTraits> Mesh;

bool is_flip_ok_openmesh(Mesh::EdgeHandle& eh, Mesh& mesh_);//just copy the code from openmesh
bool flip_openmesh(Mesh::EdgeHandle& eh, Mesh& mesh_);

bool check_in_triangle_face(const std::vector<OpenMesh::Vec3d>& tri, const OpenMesh::Vec3d& p);

typedef OpenMesh::FaceHandle FH;
typedef OpenMesh::HalfedgeHandle HEH;
typedef OpenMesh::EdgeHandle EH;
typedef OpenMesh::VertexHandle VH;

class MeshTools
{
public:
	static bool ReadMesh(Mesh& mesh, const std::string& filename);
	static bool ReadOBJ(Mesh& mesh, const std::string& filename);
	//static bool ReadOFF(Mesh & mesh, const std::string & filename);
	static bool WriteMesh(const Mesh& mesh, const std::string& filename, const std::streamsize& precision = 6);
	static bool WriteOBJ(const Mesh& mesh, const std::string& filename, const std::streamsize& precision = 6);
	static double Area(const Mesh& mesh);
	static double AverageEdgeLength(const Mesh& mesh);
	static bool HasBoundary(const Mesh& mesh);
	static bool HasOneComponent(const Mesh& mesh);
	static int Genus(const Mesh& mesh);
	static void BoundingBox(const Mesh& mesh, Mesh::Point& bmax, Mesh::Point& bmin);
	static void Reassign(const Mesh& mesh1, Mesh& mesh2);
	static void ComputeGaussianCurvature(const Mesh& mesh, std::vector<double>& v_gauss, const bool& bound_remove = true);
};


#endif