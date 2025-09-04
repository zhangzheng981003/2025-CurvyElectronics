#include <QMouseEvent>
#include <QLineEdit>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QtCore>
#include <QUrl>

#include "InteractiveViewerWidget.h"

InteractiveViewerWidget::InteractiveViewerWidget(QWidget* parent /* = 0 */)
	:MeshViewerWidget(parent)
{
	draw_new_mesh = false;
	clearSelectedData();
	kdTree = NULL;
}

InteractiveViewerWidget::InteractiveViewerWidget(QGLFormat& _fmt, QWidget* _parent)
:MeshViewerWidget(_fmt, _parent)
{
	draw_new_mesh = false;
	clearSelectedData();
	kdTree = NULL;
}

InteractiveViewerWidget::~InteractiveViewerWidget()
{
	if(kdTree) delete kdTree;

	if (dij_path) delete dij_path;

	if (seam_mesh_) delete seam_mesh_;
}

void InteractiveViewerWidget::setMouseMode(int mm)
{
	if(mouse_mode_ != T2_MODE)
	{
		mouse_mode_ = mm;
		if( TRANS != mouse_mode_ )
		{ buildIndex(); }
		emit setMouseMode_signal(mm);
	}
}

void InteractiveViewerWidget::mousePressEvent(QMouseEvent *_event)
{
	if(mouse_mode_ == TRANS)
	{
		MeshViewerWidget::mousePressEvent(_event);
	}
	updateGL();
}

void InteractiveViewerWidget::mouseMoveEvent(QMouseEvent *_event)
{
	if (mesh.n_vertices() != 0)
	{
		pick_point(_event->x(), _event->y());
		if (edit_mode_ == EditMode::SEAM_EDIT)
		{
			pick_vertex(_event->x(), _event->y());
			temp_end_v = VH(lastestVertex);
			if (start_v.size() != 0)
			{
				dij_path->ComputePath(start_v.back(), temp_end_v);
				temp_path = dij_path->return_path();
			}
		}
		else
		{
			MeshViewerWidget::mouseMoveEvent(_event);
		}
	}

	update();

	
}

void InteractiveViewerWidget::mouseReleaseEvent(QMouseEvent *_event)
{
	if (mesh.n_vertices() != 0)
	{
		if (edit_mode_ == EditMode::SEAM_EDIT && lastestVertex != -1)
		{
			temp_end_v = VH(lastestVertex);
			
			start_v.push_back(temp_end_v);
			path_he.push_back(temp_path);

			//lastestVertex = -1;
		}
		else
		{
			MeshViewerWidget::mouseReleaseEvent(_event);
		}
	}

	update();
}

void InteractiveViewerWidget::wheelEvent(QWheelEvent* _event)
{
	if(mouse_mode_ != N_MODE && mouse_mode_ != T2_MODE)
	{
		MeshViewerWidget::wheelEvent(_event);
	}
}

void InteractiveViewerWidget::dragEnterEvent(QDragEnterEvent* event)
{
	if( event->mimeData()->hasFormat("text/uri-list") )
	{
		event->acceptProposedAction();
	}
}

void InteractiveViewerWidget::dropEvent(QDropEvent* event)
{
	QList<QUrl> urls = event->mimeData()->urls();
	if( urls.isEmpty() )
		return;
	QString fileName = urls.first().toLocalFile();
	if (fileName.isEmpty())
		return;

	if (fileName.endsWith(".off") || fileName.endsWith(".obj") || fileName.endsWith(".stl") || fileName.endsWith(".ply"))
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

			MeshCut();
			ChooseModel(0);
			ParaPatch(0);

			setDrawMode(SOLID_SMOOTH);
			setMouseMode(TRANS);
		}
		else
		{
			emit(loadMeshOK(false, "No Mesh"));
		}
	}

}

void InteractiveViewerWidget::pick_vertex(int x,int y)
{
	int r = find_vertex_using_selected_point();
	lastestVertex = r;
	//printf("Select Vertex : %d\n", r);
	//std::vector<int>::iterator it;
	//if( (it = std::find(selectedVertex.begin(),selectedVertex.end(), r)) == selectedVertex.end() )
	//{
	//	selectedVertex.push_back(r);
	//}
	//else
	//{
	//	selectedVertex.erase(it);
	//}

	updateGL();
}
void InteractiveViewerWidget::pick_face(int x,int y)
{
	int desiredFace = find_face_using_selected_point();
	if(desiredFace < 0) return;
	lastestFace = desiredFace;
	printf("Select Face : %d\n", desiredFace);
	std::vector<int>::iterator it;
	if( (it = std::find(selectedFace.begin(),selectedFace.end(),desiredFace)) == selectedFace.end() )
	{
		selectedFace.push_back(desiredFace);
	}
	else
	{
		selectedFace.erase(it);
	}
	updateGL();
}
void InteractiveViewerWidget::pick_edge(int x,int y)
{
	int desiredEdge = find_edge_using_selected_point();
	if(desiredEdge < 0) return;
	lastestEdge = desiredEdge;
	printf("Select Edge : %d\n", desiredEdge);
	std::vector<int>::iterator it;
	if( (it = std::find(selectedEdge.begin(),selectedEdge.end(),desiredEdge)) == selectedEdge.end() )
	{
		selectedEdge.push_back(desiredEdge);
	}
	else
	{
		selectedEdge.erase(it);
	}
	updateGL();
}
void InteractiveViewerWidget::pick_point(int x,int y)
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	GLdouble winX = double(x);
	GLdouble winY = double( height() - y );
	GLfloat winZ = 0.0;
	glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, (GLdouble)winZ, &ModelViewMatrix[0], &ProjectionMatrix[0], viewport, &selectedPoint[0], &selectedPoint[1], &selectedPoint[2]);
}

void InteractiveViewerWidget::move_point_based_lastVertex(int x,int y)
{
	if(lastestVertex<0 || lastestVertex>=mesh.n_vertices())
	{
		return;
	}
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	GLdouble winX = 0.0;
	GLdouble winY = 0.0;
	GLdouble winZ = 0.0;
	OpenMesh::Vec3d p = mesh.point(mesh.vertex_handle(lastestVertex));
	gluProject(p[0], p[1], p[2],  &ModelViewMatrix[0], &ProjectionMatrix[0], viewport, &winX, &winY, &winZ);
	
	gluUnProject((GLdouble)(x), (GLdouble)( height() - y ), winZ,  &ModelViewMatrix[0], &ProjectionMatrix[0], viewport, &selectedPoint[0], &selectedPoint[1], &selectedPoint[2]);
}

int InteractiveViewerWidget::find_vertex_using_selected_point()
{
	ANNpoint tp = annAllocPt(3); tp[0] = selectedPoint[0]; tp[1] = selectedPoint[1]; tp[2] = selectedPoint[2];
	ANNidxArray nnIdx = new ANNidx[1]; ANNdistArray dists = new ANNdist[1];

	kdTree->annkSearch(tp, 1, nnIdx, dists);
	if (dists[0] > Radius)
	{
		nnIdx[0] = -1;
	}

	return nnIdx[0];
}

int InteractiveViewerWidget::find_face_using_selected_point()
{
	int rv = find_vertex_using_selected_point();
	Mesh::VertexFaceIter vf_it = mesh.vf_iter( mesh.vertex_handle(rv) );
	int desiredFace = -1; //double minLen = 10*radius();
	std::vector<OpenMesh::Vec3d> tri_p(3); int tri_count = 0;
	Mesh::Point resultP(selectedPoint[0],selectedPoint[1],selectedPoint[2]);
	for( vf_it; vf_it; ++vf_it )
	{
		tri_count = 0;
		for(Mesh::FaceVertexIter fv_it = mesh.fv_iter(vf_it.handle()); fv_it; ++fv_it)
		{
			tri_p[tri_count] = mesh.point(fv_it); ++tri_count;
		}
		if( check_in_triangle_face(tri_p, resultP) )
		{
			desiredFace = vf_it.handle().idx(); break;
		}
	}
	if(desiredFace < 0)
	{
		for(Mesh::FaceIter f_it = mesh.faces_begin(); f_it != mesh.faces_end(); ++f_it)
		{
			tri_count = 0;
			for(Mesh::FaceVertexIter fv_it = mesh.fv_iter(f_it.handle()); fv_it; ++fv_it)
			{
				tri_p[tri_count] = mesh.point(fv_it); ++tri_count;
			}
			if( check_in_triangle_face(tri_p, resultP) )
			{
				desiredFace = f_it.handle().idx(); break;
			}
		}
	}

	return  desiredFace;
}

int InteractiveViewerWidget::find_edge_using_selected_point()
{
	int desiredFace = find_face_using_selected_point(); if(desiredFace < 0) return -1;
	Mesh::FaceHandle fh = mesh.face_handle(desiredFace);
	double min_len= 1e30; int desiredEdge = -1;
	Mesh::Point resultP(selectedPoint[0],selectedPoint[1],selectedPoint[2]);
	for(Mesh::FaceHalfedgeIter fhe_it = mesh.fh_iter(fh); fhe_it; ++fhe_it)
	{
		OpenMesh::Vec3d s = mesh.point( mesh.from_vertex_handle(fhe_it) );
		OpenMesh::Vec3d e = mesh.point( mesh.to_vertex_handle(fhe_it) );
		double dis = OpenMesh::cross(resultP - s, resultP - e).norm() / (s - e).norm();
		if(dis < min_len){ min_len = dis; desiredEdge = mesh.edge_handle(fhe_it.handle()).idx(); }
	}
	
	return desiredEdge;
}

void InteractiveViewerWidget::buildIndex()
{
	if(mesh.n_vertices() == 0)
		return;

	Mesh::VertexIter v_it(mesh.vertices_begin());
	Mesh::VertexIter v_end(mesh.vertices_end());
	Mesh::Point p;
	unsigned nv = mesh.n_vertices();
	ANNpointArray dataPts = annAllocPts(nv, 3);
	int count = 0;
	for(; v_it != v_end; ++v_it)
	{
		p = mesh.point(v_it);
		dataPts[count][0] = p[0]; dataPts[count][1] = p[1]; dataPts[count][2] = p[2];
		++count;
	}

	if(kdTree) delete kdTree;
	kdTree = new ANNkd_tree(dataPts, nv, 3);
}

//with the first mesh
void InteractiveViewerWidget::draw_interactive_portion(int drawmode)
{
	glViewport ( 0,0, width(),height());
	glMatrixMode( GL_PROJECTION );
	glLoadMatrixd( &ProjectionMatrix[0] );
	glMatrixMode( GL_MODELVIEW );
	glLoadMatrixd( &ModelViewMatrix[0] );

	
	emit draw_from_out_signal();

	{
		//draw select vertex, face, edge.
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		glPointSize(1);

		switch(mouse_mode_)
		{
		case POINTPICK:
			draw_selected_point();
			break;
		case VERTEXPICK:
			draw_selected_vertex();
			break;
		case FACEPICK:
			draw_selected_face();
			break;
		case EDGEPICK:
			draw_selected_edge();
			break;
		default:
			draw_selected_vertex();
			draw_selected_face();
			draw_selected_edge();
			break;
		}
	}

	if(draw_new_mesh)
	{
		draw_scene_mesh(drawmode);
	}
}

//with the second mesh
void InteractiveViewerWidget::draw_interactive_portion_mesh2()
{
	return;
}

void InteractiveViewerWidget::draw_selected_point()
{
	glColor3f(1.0, 0.5, 0.0);
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex3d(selectedPoint[0],selectedPoint[1],selectedPoint[2]);
	glEnd();
	glPointSize(1);
}

void InteractiveViewerWidget::draw_selected_vertex()
{
	if( selectedVertex.size() > 0 )
	{
		Mesh::Point p;
		glColor3f(1.0, 0.5, 0.0);
		glPointSize(12);
		glBegin(GL_POINTS);
		for(unsigned int i=0;i<selectedVertex.size();++i)
		{
			p = mesh.point( mesh.vertex_handle(selectedVertex[i]) );
			glVertex3dv(p.data());
		}
		glEnd();
		glPointSize(1);
	}
}

void InteractiveViewerWidget::draw_selected_face()
{
	if( selectedFace.size() > 0 )
	{
		glColor3f(1.0, 0.5, 1.0);
		Mesh::Point p;
		Mesh::ConstFaceVertexIter fv_it;
		Mesh::FaceHandle f_handle;
		for( unsigned int i=0; i<selectedFace.size(); ++i )
		{
			f_handle = mesh.face_handle(selectedFace[i]);
			fv_it = mesh.fv_iter(f_handle);
			glBegin(GL_POLYGON);
			for( fv_it; fv_it; ++fv_it )
			{
				glVertex3dv(&mesh.point(fv_it)[0]);
			}
			glEnd();
		}
	}
}

void InteractiveViewerWidget::draw_selected_edge()
{
	if( selectedEdge.size() > 0)
	{
		glColor3f(1.0, 0.5, 1.0);
		Mesh::Point p1; Mesh::Point p2;
		Mesh::EdgeHandle e_handle;
		Mesh::HalfedgeHandle he_handle;
		for(unsigned int i=0;i<selectedEdge.size();++i)
		{
			e_handle = mesh.edge_handle(selectedEdge[i]);
			he_handle = mesh.halfedge_handle( e_handle, 0 );
			p1 = mesh.point( mesh.from_vertex_handle( he_handle ) );
			p2 = mesh.point( mesh.to_vertex_handle( he_handle ) );
			glBegin(GL_LINES);
			glVertex3dv( p1.data() );
			glVertex3dv( p2.data() );
			glEnd();
		}
	}
}

void InteractiveViewerWidget::draw_scene(int drawmode)
{
	//std::cout << 11 << std::endl;
	if (drawmode == SOLID_SMOOTH && mesh.n_faces() != 0)
	{
		const std::vector<bool>& seam_status = seam_mesh_->GetSeam();

		std::vector<GLfloat> matAmbient, matDiffuse, matSpecular;
		GLfloat matShininess;

		double color_value = 0.8;
		//double color_value = 1.0 * (i + 1) / (seg_num + 1);

		//QColor temp_color = color_map_.pixelColor(
		//color_value * color_map_.width(),
		//color_value * color_map_.height());

		//QColor temp_color = color_map_.pixelColor(
		//	color_value * color_map_.width(),
		//	color_value * color_map_.height());

		//matAmbient = { (float)1.0 * temp_color.red() / 255,
		//	(float)1.0 * temp_color.green() / 255,
		//	(float)1.0 * temp_color.blue() / 255, 1.0f };
		//matDiffuse = { (float)1.0 * temp_color.red() / 255,
		//	(float)1.0 * temp_color.green() / 255,
		//	(float)1.0 * temp_color.blue() / 255, 1.0f };
		//matSpecular = { (float)1.0 * temp_color.red() / 255,
		//	(float)1.0 * temp_color.green() / 255,
		//	(float)1.0 * temp_color.blue() / 255, 1.0f };

		matAmbient = { 0.9f, 0.667f, 0.0f, 1.0f };
		matDiffuse = { 0.9f, 0.749f, 0.251f, 1.0f };
		matSpecular = { 0.9f, 0.816f, 0.451f, 1.0f };
		matShininess = 50.0f;

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient.data());
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse.data());
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular.data());
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, matShininess);

		glEnable(GL_LIGHTING);

		Mesh cur_mesh;
		cut_mesh_->GetPatch(cur_patch_id, cur_mesh);
		cur_mesh.request_face_normals();
		cur_mesh.update_face_normals();
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.5f, 2.0f);
		glShadeModel(GL_FLAT);
		glColor3d(0.8, 0.8, 0.8);

		glBegin(GL_TRIANGLES);
		for (auto f_h : cur_mesh.faces()) 
		{
			glNormal3dv(cur_mesh.normal(f_h).data());
			for (auto v_h : cur_mesh.fv_range(f_h))
			{
				glVertex3dv(cur_mesh.point(v_h).data());
			}
		}
		glEnd();
		glDisable(GL_POLYGON_OFFSET_FILL);

		glDisable(GL_LIGHTING);
		glLineWidth(2.0);
		glColor3d(0.0, 0.0, 1.0);
		glBegin(GL_LINES);
		for (const EH& e_h : cur_mesh.edges())
		{
			if (!cur_mesh.is_boundary(e_h)) continue;
			
			auto heh = cur_mesh.halfedge_handle(e_h, 0);
			auto vh0 = cur_mesh.from_vertex_handle(heh);
			auto vh1 = cur_mesh.to_vertex_handle(heh);
			glVertex3dv(cur_mesh.point(vh0).data());
			glVertex3dv(cur_mesh.point(vh1).data());
		}
		glEnd();

		glLineWidth(0.5);
		glColor3d(0.0, 0.0, 0.0);
		glBegin(GL_LINES);
		for (const EH& e_h : cur_mesh.edges())
		{
			auto heh = cur_mesh.halfedge_handle(e_h, 0);
			auto vh0 = cur_mesh.from_vertex_handle(heh);
			auto vh1 = cur_mesh.to_vertex_handle(heh);
			glVertex3dv(cur_mesh.point(vh0).data());
			glVertex3dv(cur_mesh.point(vh1).data());
		}
		glEnd();


		matAmbient = { 0.8f, 0.8f, 0.8f, 1.0f };
		matDiffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
		matSpecular = { 0.8f, 0.8f, 0.8f, 1.0f };
		matShininess = 50.0f;

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient.data());
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse.data());
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular.data());
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, matShininess);
		
		glEnable(GL_LIGHTING);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.5f, 2.0f);
		glShadeModel(GL_FLAT);
		glColor3d(0.8, 0.8, 0.8);

		int cut_size = cut_mesh_->GetPatchNum();

		glBegin(GL_TRIANGLES);

		for (int i = 0; i < cut_size; i++)
		{
			if (i == cur_patch_id) continue;

			cut_mesh_->GetPatch(i, cur_mesh);
			cur_mesh.request_face_normals();
			cur_mesh.update_face_normals();

			for (auto f_h : cur_mesh.faces()) {
				glNormal3dv(cur_mesh.normal(f_h).data());
				for (auto v_h : cur_mesh.fv_range(f_h))
				{
					glVertex3dv(cur_mesh.point(v_h).data());
				}
			}
		}
		glEnd();
		glDisable(GL_POLYGON_OFFSET_FILL);

		glDisable(GL_LIGHTING);

		//glLineWidth(3);
		//glColor3d(0.0, 0.0, 0.0);
		//glBegin(GL_LINES);
		//for (const EH&e_h:mesh.edges())
		//{
		//	if (!seam_status[e_h.idx()]) continue;

		//	auto heh = mesh.halfedge_handle(e_h, 0);
		//	auto vh0 = mesh.from_vertex_handle(heh);
		//	auto vh1 = mesh.to_vertex_handle(heh);
		//	glNormal3dv(mesh.normal(vh0).data());
		//	glVertex3dv(mesh.point(vh0).data());
		//	glNormal3dv(mesh.normal(vh1).data());
		//	glVertex3dv(mesh.point(vh1).data());
		//}
		//glEnd();

		const std::vector<std::vector<int>>&
			add_record = cut_mesh_->GetAddRecord();

		glLineWidth(3);
		glColor3d(0.0, 0.0, 0.0);
		glBegin(GL_LINES);

		for (const auto& single_path:add_record)
		{
			for (int e_id:single_path)
			{
				HEH he_h = mesh.halfedge_handle(EH(e_id), 0);
				auto vh0 = mesh.from_vertex_handle(he_h);
				auto vh1 = mesh.to_vertex_handle(he_h);
				glNormal3dv(mesh.normal(vh0).data());
				glVertex3dv(mesh.point(vh0).data());
				glNormal3dv(mesh.normal(vh1).data());
				glVertex3dv(mesh.point(vh1).data());
			}
		}

		for (const auto& single_path : path_he)
		{
			for (const HEH& he_h : single_path)
			{
				auto vh0 = mesh.from_vertex_handle(he_h);
				auto vh1 = mesh.to_vertex_handle(he_h);
				glNormal3dv(mesh.normal(vh0).data());
				glVertex3dv(mesh.point(vh0).data());
				glNormal3dv(mesh.normal(vh1).data());
				glVertex3dv(mesh.point(vh1).data());
			}
		}
		for (const HEH& he_h : temp_path)
		{
			auto vh0 = mesh.from_vertex_handle(he_h);
			auto vh1 = mesh.to_vertex_handle(he_h);
			glNormal3dv(mesh.normal(vh0).data());
			glVertex3dv(mesh.point(vh0).data());
			glNormal3dv(mesh.normal(vh1).data());
			glVertex3dv(mesh.point(vh1).data());
		}
		glEnd();

		glPointSize(8);
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_POINTS);
		for (const VH& v_h : start_v)
		{
			glNormal3dv(mesh.normal(v_h).data());
			glVertex3dv(mesh.point(v_h).data());
		}
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POINTS);
		if (temp_end_v.is_valid())
		{
			glNormal3dv(mesh.normal(temp_end_v).data());
			glVertex3dv(mesh.point(temp_end_v).data());
		}

		glEnd();
	}
	else
	{
		MeshViewerWidget::draw_scene(drawmode);
	}
}

void InteractiveViewerWidget::render_text_slot(OpenMesh::Vec3d pos, QString str)
{
	/*GLdouble  winX, winY, winZ;
	GLint     viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	gluProject(pos[0],pos[1],pos[2],&ModelViewMatrix[0][0],&ProjectionMatrix[0][0],viewport,&winX,&winY,&winZ);
	int x = (long)winX;
	int y = viewport[3]-(long)winY;
	render_text(x,y,str);*/
	render_text(pos[0],pos[1],pos[2],str);
}

void InteractiveViewerWidget::LoadColorMap()
{
	color_map_ = QImage(QString("Texture/colorbar.bmp")).mirrored();
}

void InteractiveViewerWidget::initializeGL(void)
{
	LoadColorMap();

	QGLViewerWidget::initializeGL();
}