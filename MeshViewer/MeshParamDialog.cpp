#include "MeshParamDialog.h"
#include <QApplication>
#include <QDesktopWidget>

#include "Common\CommonDefinitions.h"

MeshParamDialog::MeshParamDialog(QWidget* parent /* = 0 */)
	:QDialog(parent)
{
	initDialog();
}

MeshParamDialog::~MeshParamDialog()
{
}

void MeshParamDialog::initDialog()
{
	CreateCutMeshBox();
	CreateViewPatchBox();
	createWidget();
	createLayout();
}

void MeshParamDialog::createWidget()
{
	create_Basic_Operation_Information_Widget();
}

void MeshParamDialog::createLayout()
{
	tabWidget = new QTabWidget();
	tabWidget->addTab(view_BOI, "QP");

	QGridLayout *layout = new QGridLayout();
	layout->addWidget(tabWidget, 0, 0, 1, 1);
	setLayout(layout);
}

void MeshParamDialog::create_Basic_Operation_Information_Widget()
{
	print_info = new QPushButton("Print Information");
	leftLabel_BOI = new QLabel("");

	QVBoxLayout* mainLayout = new QVBoxLayout();
	mainLayout->addWidget(print_info); 
	mainLayout->addWidget(cut_mesh_box_);
	mainLayout->addWidget(view_patch_box_);

	mainLayout->addStretch();

	mainLayout->addWidget(leftLabel_BOI);

	Basic_Operation_And_Information = new QWidget();
	Basic_Operation_And_Information->setLayout(mainLayout);

	view_BOI = new QScrollArea;
	view_BOI->setFocusPolicy(Qt::NoFocus);
	view_BOI->setFrameStyle(QFrame::NoFrame);
	view_BOI->setWidget(Basic_Operation_And_Information);
	view_BOI->setWidgetResizable(true);

	connect(print_info, SIGNAL(clicked()), SIGNAL(print_info_signal()));
}

void MeshParamDialog::CreateCutMeshBox(void)
{
	cut_mesh_box_ = new QGroupBox("Cut Mesh");

        rb_non_edit_ = new QRadioButton(tr("Non"));
        connect(rb_non_edit_, SIGNAL(clicked()), SIGNAL(NoEditSignal()));

        rb_seam_edit_ = new QRadioButton(tr("Dijkstra Edit"));
        connect(rb_seam_edit_, SIGNAL(clicked()), SIGNAL(SeamEditSignal()));

        rb_geodesic_edit_ = new QRadioButton(tr("Geodesic Edit"));
        connect(rb_geodesic_edit_, SIGNAL(clicked()), SIGNAL(GeodesicEditSignal()));

        QButtonGroup* bg_show_ = new QButtonGroup();
        bg_show_->setExclusive(true);
        rb_non_edit_->setChecked(true);
        bg_show_->addButton(rb_non_edit_);
        bg_show_->addButton(rb_seam_edit_);
        bg_show_->addButton(rb_geodesic_edit_);

	QPushButton* pb_add = new QPushButton(tr("Add"));
	connect(pb_add, SIGNAL(clicked()), SIGNAL(AddSeamSignal()));

	QPushButton* pb_undo = new QPushButton(tr("Undo"));
	connect(pb_undo, SIGNAL(clicked()), SIGNAL(UndoSeamSignal()));

	QPushButton* pb_cut = new QPushButton(tr("Mesh Cut"));
	connect(pb_cut, SIGNAL(clicked()), SIGNAL(MeshCutSignal()));

        QGridLayout* layout_field = new QGridLayout();
        layout_field->addWidget(rb_non_edit_, 0, 0, 1, 1);
        layout_field->addWidget(rb_seam_edit_, 0, 1, 1, 1);
        layout_field->addWidget(rb_geodesic_edit_, 0, 2, 1, 1);
        layout_field->addWidget(pb_undo, 1, 0, 1, 1);
        layout_field->addWidget(pb_add, 1, 1, 1, 1);
        layout_field->addWidget(pb_cut, 2, 0, 1, 3);

	cut_mesh_box_->setLayout(layout_field);
}

void MeshParamDialog::CreateViewPatchBox(void)
{
	view_patch_box_ = new QGroupBox("View Patch");

	sb_iters_ = new QSpinBox();
	sb_iters_->setRange(0, 200);
	sb_iters_->setSingleStep(1);
	sb_iters_->setValue(0);
	connect(sb_iters_, SIGNAL(valueChanged(int)), SIGNAL(ChooseModelSignal(int)));

	//rb_seam_edit_ = new QRadioButton(tr("Edit"));
	//connect(rb_seam_edit_, SIGNAL(clicked()), SIGNAL(SeamEditSignal()));

	//QButtonGroup* bg_show_ = new QButtonGroup();
	//bg_show_->setExclusive(true);
	//rb_non_edit_->setChecked(true);
	//bg_show_->addButton(rb_non_edit_);
	//bg_show_->addButton(rb_seam_edit_);

	//QPushButton* pb_add = new QPushButton(tr("Add"));
	//connect(pb_add, SIGNAL(clicked()), SIGNAL(AddSeamSignal()));

	//QPushButton* pb_undo = new QPushButton(tr("Undo"));
	//connect(pb_undo, SIGNAL(clicked()), SIGNAL(UndoSeamSignal()));

	//QPushButton* pb_cut = new QPushButton(tr("Mesh Cut"));
	//connect(pb_cut, SIGNAL(clicked()), SIGNAL(MeshCutSignal()));

	QVBoxLayout* layout_field = new QVBoxLayout();
	layout_field->addWidget(sb_iters_);

	view_patch_box_->setLayout(layout_field);
}
