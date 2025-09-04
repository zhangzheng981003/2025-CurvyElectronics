#ifndef INTERACTIVE_VIEWER_WIDGET
#define INTERACTIVE_VIEWER_WIDGET

#include "MeshViewerWidget.h"
#include "ANN\ANN.h"
#include "Compute\Dijkstra_Path.h"
#include "Compute\CGAL_Geodesic_Path.h"
#include "Compute\CutMesh.h"
#include "Compute\SeamMesh.h"
#include <io.h>

struct Line {
	double x1;
	double y1;
	double x2;
	double y2;
};

class InteractiveViewerWidget : public MeshViewerWidget
{
	Q_OBJECT
public:
	InteractiveViewerWidget(QWidget* parent = 0);
	InteractiveViewerWidget(QGLFormat& _fmt, QWidget* _parent);
	~InteractiveViewerWidget();

	bool openMesh(const char* filename)
	{
		bool read_status = MeshViewerWidget::openMesh(filename);

		if (mesh.n_vertices() != 0)
		{
			buildIndex();
			
			if (dij_path) delete dij_path;
			dij_path = new Dijkstra_Path(mesh);
                        if (geo_path) delete geo_path;
                        geo_path = new CGAL_Geodesic_Path(mesh);
			
			if (seam_mesh_) delete seam_mesh_;
			seam_mesh_ = new SeamMesh(mesh);

			if (cut_mesh_) delete cut_mesh_;
			cut_mesh_ = new CutMesh(mesh);

			start_v.clear();
			path_he.clear();
			temp_path.clear();
			temp_end_v = VH(-1);
                        geo_path_points.clear();
                        temp_geo_path.clear();
		}

		return read_status;
	}

	void LoadMeshMesh(const QString& fileName)
	{
		//obj文件的目录
		fileDirPath = fileName.toStdString();
		fileDirPath = fileDirPath.substr(0, fileDirPath.find_last_of("//"));
		std::string mesh_name = fileName.toStdString().substr(fileName.toStdString().find_last_of("//"), fileName.toStdString().length());
		mesh_name = mesh_name.substr(1, mesh_name.find_last_of(".") - 1);
		for (int i = 0; i < fileDirPath.size(); i++)
		{
			if (fileDirPath[i] == '/')
				fileDirPath[i] = '\\';
		}

		std::string patch_path = "Patches\\Patches";

		if (_access((patch_path).c_str(), 0) != -1)//不存在
		{
			std::string cmd = "rmdir /Q /S " + patch_path;
			system(cmd.c_str());
			while (_access((patch_path).c_str(), 0) != -1)
			{
				std::cout << "删除中" << std::endl;
				//等待删除完成
			}
		}
		//新建文件夹
		std::string cmd = "mkdir " + patch_path;
		system(cmd.c_str());
		cmd = "mkdir " + patch_path + "\\Patch_Para";
		system(cmd.c_str());

		if (openMesh(fileName.toLocal8Bit()))
		{
			emit(loadMeshOK(true, fileName));
			//setDrawMode(FLAT_POINTS);

			setDrawMode(WIRE_FRAME);
			setMouseMode(TRANS);
		}
		else
		{
			emit(loadMeshOK(false, "No Mesh"));
		}
	}

	void LoadSegSeg(const QString& filename)
	{
		std::string seg_file = filename.toStdString();
		if (_access(seg_file.c_str(), 0) != -1)//不存在
		{
			OpenSeg(seg_file);
			MeshCut();
			ChooseModel(0);
			ParaPatch(0);
			std::cout << "seg load" << std::endl;
		}
		else std::cout << "seg文件: " + seg_file + " 读入失败" << std::endl;
		setDrawMode(SOLID_SMOOTH);
		setMouseMode(TRANS);
	}


	void Update()
	{
		update();
	}

	void clearSelectedData()
	{
		selectedVertex.clear();
		selectedFace.clear();
		selectedEdge.clear();
	};

	virtual void clearAllMesh()
	{
		draw_new_mesh = false;
		clearSelectedData();
		MeshViewerWidget::clearAllMesh();
	}

	void setDrawNewMesh(bool draw_new_mesh_)
	{
		draw_new_mesh = draw_new_mesh_;
		updateGL();
	}

	void set_mesh_ref(Mesh& mesh_)
	{
		clearAllMesh();
		mesh = mesh_;
		initMesh(); 
		setDrawMode(FLAT_POINTS);
		setMouseMode(TRANS);
	};

	void edit_undo_viewer()
	{
		--mesh_vector_index;
		mesh = mesh_vector[mesh_vector_index];
		emit set_edit_redo_enable_viewer_signal( true );
		if(mesh_vector_index == 0)
		{
			emit set_edit_undo_enable_viewer_signal( false );
		}
		updateGL();
	}
	void edit_redo_viewer()
	{
		++mesh_vector_index;
		mesh = mesh_vector[mesh_vector_index];
		emit set_edit_undo_enable_viewer_signal( true );
		if(mesh_vector_index == mesh_vector.size() - 1)
		{
			emit set_edit_redo_enable_viewer_signal( false );
		}
		updateGL();
	}

	void OpenSeg(const std::string& filename) {
		std::ifstream seg_file(filename);
		seam_mesh_->ReadSeam(filename);

		const std::vector<bool>& seam_status = seam_mesh_->GetSeam();
		std::vector<int> e_ids(0);
		for (size_t i = 0; i < seam_status.size(); i++)
		{
			if (seam_status[i]) e_ids.push_back(i);
		}
		cut_mesh_->AddNewSeam(e_ids);
	}

	bool ChooseModel(int patch_id)
	{
		cur_patch_id = patch_id;

		if (patch_id < 0 || patch_id > genus_remove_status.size()-1)
		{
			std::cout << "====================================" << std::endl;
			std::cout << "Out of patch size!" << std::endl;
			return false;
		}

		if (genus_remove_status[patch_id])
		{
			std::cout << "====================================" << std::endl;
			std::cout << "High Genus!" << std::endl;
			update();
			return false;
		}
		
		update();
		return true;
	}

	bool ParaPatch(int patch_id)
	{
		if (patch_show_status)
		{
			struct stat buffer;

			std::string final_name = "Patches/Patches/Patch_Para/seg_"
				+ std::to_string(patch_id) + "_comp_para_result.obj";

			std::cout << "====================================" << std::endl;

			std::cout << final_name << std::endl;

			if (stat(final_name.c_str(), &buffer) == 0)
			{
				Mesh temp_mesh;
				bool read_status = MeshTools::ReadMesh(temp_mesh, final_name);

				mesh = temp_mesh;

				if (read_status)
				{
					initMesh();
					update();

					bool in_status = is_intersection(mesh);

					if (in_status)
					{
						std::cout << "Self-intersection!" << std::endl;
						return true;
					}
					else
					{
						std::cout << "Fine!!!" << std::endl;
						return true;
					}
				}
				else 
				{
					std::cout << "NaN!" << std::endl;
					return false;
				}

			}
			else
			{
				std::cout << "No Parameterization!" << std::endl;
				return false;
			}
		}
	}

signals:
	void mouse_press_signal(Mesh::Point P);
	void mouse_move_signal(OpenMesh::Vec3d xy);
	void mouse_release_signal(Mesh::Point  P);
	void draw_from_out_signal();

	void setMouseMode_signal(int);

	void set_edit_undo_enable_viewer_signal(bool);
	void set_edit_redo_enable_viewer_signal(bool);

	void ResetEditSignal();

public slots:
	void render_text_slot(OpenMesh::Vec3d pos, QString str);
	void set_t2_mouse_mode(int tm)
	{
		t2_mode_ = tm;
	}

	void NoEdit()
	{
		std::cout << "No edit!" << std::endl;
		edit_mode_ = EditMode::NON_EDIT;
	}

	void SeamEdit()
        {
                std::cout << "Seam edit!" << std::endl;
                edit_mode_ = EditMode::SEAM_EDIT;
        }

        void GeodesicEdit()
        {
                std::cout << "Geodesic edit!" << std::endl;
                edit_mode_ = EditMode::GEODESIC_EDIT;
        }

	void AddSeam()
	{
		std::cout << "Add Seam!" << std::endl;

		if (path_he.size()!= 0)
		{
			std::vector<int> add_e(0);
			for (const auto& temp_path_vector : path_he)
			{
				for (const HEH& he_h : temp_path_vector)
				{
					add_e.push_back(mesh.edge_handle(he_h).idx());
				}
			}
			cut_mesh_->AddNewSeam(add_e);

			start_v.clear();
			path_he.clear();
			temp_path.clear();
			temp_end_v = VH(-1);
		}

		NoEdit();
		emit(ResetEditSignal());

		update();
	}

        void UndoSeam()
        {
                std::cout << "Undo Seam Edit!" << std::endl;

                if (edit_mode_ == EditMode::NON_EDIT)
                {
                        cut_mesh_->UndoAdd();

                        start_v.clear();
                        path_he.clear();
                        temp_path.clear();
                        temp_end_v = VH(-1);
                        geo_path_points.clear();
                        temp_geo_path.clear();
                }
                else if (edit_mode_ == EditMode::SEAM_EDIT)
                {
                        if (path_he.size() > 0)
                        {
                                path_he.pop_back();
                                start_v.pop_back();

                                temp_path.clear();
                                temp_end_v = VH(-1);
                        }
                        else if (start_v.size() > 0)
                        {
                                start_v.pop_back();

                                temp_path.clear();
                                temp_end_v = VH(-1);
                        }
                }
                else if (edit_mode_ == EditMode::GEODESIC_EDIT)
                {
                        if (geo_path_points.size() > 0)
                        {
                                geo_path_points.pop_back();
                                start_v.pop_back();

                                temp_geo_path.clear();
                                temp_end_v = VH(-1);
                        }
                        else if (start_v.size() > 0)
                        {
                                start_v.pop_back();

                                temp_geo_path.clear();
                                temp_end_v = VH(-1);
                        }
                }

                update();
        }
	void MeshCut()
	{
		std::cout << "Mesh Cut!" << std::endl;

		QDir dir(QString::fromStdString("Patches/Patches"));
		if (!dir.exists()) {
			return;
		}
		dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
		QFileInfoList fileList = dir.entryInfoList();
		foreach(QFileInfo file, fileList) {
			if (file.isFile()) {
				bool isDelete = file.dir().remove(file.fileName());
			}
		}

		cut_mesh_->Compute();

		int cut_num = cut_mesh_->GetPatchNum();
		if (cut_num > 2)
		{
			seam_mesh_->SetSeam(cut_mesh_->GetSeam());
			update();
		}

		seam_mesh_->OutputSeam("seam.txt");

		// generate patch
		int patch_num = cut_mesh_->GetPatchNum();
		genus_remove_status.clear();
		genus_remove_status.resize(patch_num);
		// is_high_genus
		for (size_t i = 0; i < patch_num; i++)
		{
			std::string final_name = "Patches/Patches/seg_"
				+ std::to_string(i) + ".obj";

			Mesh temp_mesh;
			bool read_status = MeshTools::ReadMesh(temp_mesh, final_name);

			bool genus_status = is_high_genus(temp_mesh);

			if (genus_status)
			{
				genus_remove_status[i] = true;
				remove(final_name.c_str());
			}
		}

		// parameterization
		Click_to_BPE(fileDirPath);
	}

	void Click_to_BPE(std::string fileDirPath)
	{
		if (0)
		{
			std::vector<std::string> NeededFile = { "BPE.exe","libiomp5md.dll","mkl_avx2.dll","mkl_core.dll","mkl_def.dll","mkl_intel_thread.dll","run.bat" };
			bool file_all_exist = true;
			for (int i = 0; i < NeededFile.size(); i++)
			{
				//std::string fname = fileDirPath + "\\" + NeededFile[i];
				std::string fname = "Patches/" + NeededFile[i];
				if (_access(fname.c_str(), 0) == -1) {
					std::cout << "dll" << NeededFile[i] << std::endl;
					file_all_exist = false;
				}
			}

			if (!file_all_exist) return;
			std::string cmd = "cd Patches & run.bat";
			system(cmd.c_str());
		}
	}

public:
	enum { TRANS, POINTPICK, VERTEXPICK, EDGEPICK, FACEPICK, EDGECOLLAPSE, EDGEFLIP, EDGESPLIT , MOVE, T2_MODE, N_MODE };
	void setMouseMode(int mm);
	int mouseMode() const { return mouse_mode_; }

protected:
	virtual void mousePressEvent(QMouseEvent *_event);
	virtual void mouseReleaseEvent(QMouseEvent *_event);
	virtual void mouseMoveEvent(QMouseEvent *_event);
	virtual void wheelEvent(QWheelEvent* _event);
	int mouse_mode_;
	int t2_mode_;

	bool is_high_genus(Mesh& mesh)
	{
		int count = 0;
		std::vector<int> is_visit(mesh.n_halfedges(), -1);
		for (auto he : mesh.halfedges())
		{
			if (mesh.is_boundary(he) && (is_visit[he.idx()] < 0))
			{
				count++;
				is_visit[he.idx()] = 1;
				while (true)
				{
					auto hhe = mesh.next_halfedge_handle(he);
					if (mesh.is_boundary(hhe) && (is_visit[hhe.idx()] < 0))
					{
						is_visit[hhe.idx()] = 1;
						he = hhe;
					}
					else
					{
						break;
					}
				}
			}
		}
		//std::cout << "boundary count : " << count << std::endl;
		return (count > 1);
	}

	bool intersection(const Line& l1, const Line& l2)
	{
		//快速排斥实验
		if ((l1.x1 > l1.x2 ? l1.x1 : l1.x2) < (l2.x1 < l2.x2 ? l2.x1 : l2.x2) ||
			(l1.y1 > l1.y2 ? l1.y1 : l1.y2) < (l2.y1 < l2.y2 ? l2.y1 : l2.y2) ||
			(l2.x1 > l2.x2 ? l2.x1 : l2.x2) < (l1.x1 < l1.x2 ? l1.x1 : l1.x2) ||
			(l2.y1 > l2.y2 ? l2.y1 : l2.y2) < (l1.y1 < l1.y2 ? l1.y1 : l1.y2))
		{
			return false;
		}
		//跨立实验
		if ((((l1.x1 - l2.x1) * (l2.y2 - l2.y1) - (l1.y1 - l2.y1) * (l2.x2 - l2.x1)) *
			((l1.x2 - l2.x1) * (l2.y2 - l2.y1) - (l1.y2 - l2.y1) * (l2.x2 - l2.x1))) > 0 ||
			(((l2.x1 - l1.x1) * (l1.y2 - l1.y1) - (l2.y1 - l1.y1) * (l1.x2 - l1.x1)) *
				((l2.x2 - l1.x1) * (l1.y2 - l1.y1) - (l2.y2 - l1.y1) * (l1.x2 - l1.x1))) > 0)
		{
			return false;
		}
		return true;
	}

	bool is_intersection(Mesh& mesh)
	{
		for (size_t i = 0; i < mesh.n_edges() - 1; i++)
		{
			if (mesh.is_boundary(mesh.edge_handle(i)))
			{
				auto e1 = mesh.edge_handle(i);
				for (int j = i + 1; j < mesh.n_edges(); j++)
				{
					if (mesh.is_boundary(mesh.edge_handle(j)))
					{
						auto e2 = mesh.edge_handle(j);
						auto v11 = mesh.from_vertex_handle(mesh.halfedge_handle(e1, 0));
						auto v12 = mesh.to_vertex_handle(mesh.halfedge_handle(e1, 0));
						auto v21 = mesh.from_vertex_handle(mesh.halfedge_handle(e2, 0));
						auto v22 = mesh.to_vertex_handle(mesh.halfedge_handle(e2, 0));

						if (v11.idx() != v21.idx() && v11.idx() != v22.idx() && v12.idx() != v21.idx() && v12.idx() != v22.idx())
						{
							Line l1, l2;
							l1.x1 = mesh.point(v11)[0];
							l1.x2 = mesh.point(v12)[0];
							l1.y1 = mesh.point(v11)[1];
							l1.y2 = mesh.point(v12)[1];

							l2.x1 = mesh.point(v21)[0];
							l2.x2 = mesh.point(v22)[0];
							l2.y1 = mesh.point(v21)[1];
							l2.y2 = mesh.point(v22)[1];
							bool is_in = intersection(l1, l2);
							if (is_in)
							{
								//std::cout << l1.x1 << std::endl;
								//std::cout << l1.x2 << std::endl;
								//std::cout << l1.y1 << std::endl;
								//std::cout << l1.y2 << std::endl;
								//std::cout << l2.x1 << std::endl;
								//std::cout << l2.x2 << std::endl;
								//std::cout << l2.y1 << std::endl;
								//std::cout << l2.y2 << std::endl;

								//std::cout << "false" << std::endl;
								return is_in;
							}
						}


					}
				}
			}

		}
		//std::cout << "ok" << std::endl;
		return false;
	}

protected:
	void pick_vertex(int x,int y);
	void pick_face(int x,int y);
	void pick_edge(int x,int y);
	void pick_point(int x,int y);
	void move_point_based_lastVertex(int x,int y);

	int find_vertex_using_selected_point();
	int find_face_using_selected_point();
	int find_edge_using_selected_point();

	void buildIndex();
	ANNkd_tree* kdTree;

	void draw_interactive_portion(int drawmode);
	void draw_interactive_portion_mesh2();
	void draw_selected_point();
	void draw_selected_vertex();
	void draw_selected_face();
	void draw_selected_edge();
	virtual void draw_scene(int drawmode);
	bool draw_new_mesh;

protected:
	double selectedPoint[3];
	std::vector<int> selectedVertex;
	int lastestVertex = -1;
	std::vector<int> selectedFace;
	int lastestFace;
	std::vector<int> selectedEdge;
	int lastestEdge;

protected:
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);

	void initializeGL(void);
	void LoadColorMap();

public:
	bool patch_show_status = false;
private:
	std::string fileDirPath = "";

	enum class EditMode {NON_EDIT, SEAM_EDIT, GEODESIC_EDIT};
	EditMode edit_mode_ = EditMode::NON_EDIT;

	std::vector<OpenMesh::VertexHandle> start_v;
	std::vector<std::vector<OpenMesh::HalfedgeHandle>> path_he;
	OpenMesh::VertexHandle temp_end_v;
	std::vector<OpenMesh::HalfedgeHandle> temp_path;

	Dijkstra_Path* dij_path = NULL;
        std::vector<std::vector<OpenMesh::Vec3d>> geo_path_points;
        std::vector<OpenMesh::Vec3d> temp_geo_path;
        CGAL_Geodesic_Path* geo_path = NULL;

	int cur_patch_id = 0;

	// colormap
	QImage color_map_;
	SeamMesh* seam_mesh_ = NULL;
	CutMesh* cut_mesh_ = NULL;

	std::string batch_measure_path;
	std::vector<std::string> folder_name; // genus 0
	std::vector<bool> patch_status;

	std::vector<bool> genus_remove_status;
};

#endif
