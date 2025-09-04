#ifndef MESHPROCESSING_MESHPARAMDIALOG_H
#define MESHPROCESSING_MESHPARAMDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtWidgets>

class MeshParamDialog : public QDialog
{
	Q_OBJECT
public:
	MeshParamDialog(QWidget* parent=0);
	~MeshParamDialog();

	QSize sizeHint()
	{
		QRect rect = QApplication::desktop()->screenGeometry();
		return QSize( int( rect.width()*0.15), rect.height() );
	}
	QSpinBox* sb_iters_;

private:
	QTabWidget* tabWidget;

signals:
        void print_info_signal();

        void NoEditSignal();
        void SeamEditSignal();
        void GeodesicEditSignal();
        void AddSeamSignal();
        void UndoSeamSignal();
        void MeshCutSignal();

	void ChooseModelSignal(int);
	
private:
	QWidget* Basic_Operation_And_Information;
	QScrollArea *view_BOI;

	QLabel* leftLabel_BOI;
	QPushButton* print_info;

private:
	void create_Basic_Operation_Information_Widget();


public slots:
	void ResetEdit() {
		rb_non_edit_->setChecked(true);
	}

private:
	void initDialog();
	void createWidget();
	void createLayout();

        void CreateCutMeshBox(void);
        QGroupBox* cut_mesh_box_;
        QRadioButton* rb_non_edit_;
        QRadioButton* rb_seam_edit_;
        QRadioButton* rb_geodesic_edit_;

	void CreateViewPatchBox(void);
	QGroupBox* view_patch_box_;

};

#endif
