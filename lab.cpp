#include "lab.h"

#include <QButtonGroup>
#include <QKeyEvent>
#include <QPainter>
#include <QColor>
#include <QColorDialog>

#include "Mouse/brush.h"
#include "Mouse/cursor.h"
#include "Mouse/shapeCreator.h"
#include "Mouse/arrowsManager.h"
#include "PaintBox/paintbox.h"
#include "User/user.h"
#include "colorchanger.h"
#include "PaintBox/paintBoxPresenter.h"

#include "Hierarchy/hierarchy.h"

Lab::Lab(QWidget *parent) : QMainWindow(parent) {
  ui.setupUi(this);

  connect(ui.brushSizeSlider, SIGNAL(valueChanged(int)),
          SLOT(brushSizeSliderValueChanged(int)));
  connect(ui.chooseMouseBtn, SIGNAL(clicked()), SLOT(cursorChoosed()));
  connect(ui.chooseBrushBtn, SIGNAL(clicked()), SLOT(brushChoosed()));
  connect(ui.arrowsBtn, SIGNAL(clicked()), SLOT(arrowChoosed()));

  connect(ui.lineButton, SIGNAL(clicked()), SLOT(shapeChoosed()));
  connect(ui.rectButton, SIGNAL(clicked()), SLOT(shapeChoosed()));
  connect(ui.ellipseButton, SIGNAL(clicked()), SLOT(shapeChoosed()));
  connect(ui.triangleButton, SIGNAL(clicked()), SLOT(shapeChoosed()));

  connect(ui.colorButton, SIGNAL(clicked()), SLOT(changeColor()));

  connect(ui.openFileAction, SIGNAL(triggered()), SLOT(openFile()));
  connect(ui.saveFileAction, SIGNAL(triggered()), SLOT(saveFile()));

  toolsGroup_ = new QButtonGroup(this);
  toolsGroup_->setExclusive(true);

  toolsGroup_->addButton(ui.chooseBrushBtn, 0);
  toolsGroup_->addButton(ui.chooseMouseBtn, 1);
  toolsGroup_->addButton(ui.lineButton, 2);
  toolsGroup_->addButton(ui.rectButton, 3);
  toolsGroup_->addButton(ui.ellipseButton, 4);
  toolsGroup_->addButton(ui.triangleButton, 5);
  toolsGroup_->addButton(ui.arrowsBtn, 6);

  setUpPaintBox();

  colorChanged(User::getInstance()->Color);

  hierarchy_ = new Hierarchy(ui.tree);
  paintBoxPresenter_->linkHierarchyAndModel(hierarchy_);
} // TODO: group

Lab::~Lab() {
  if (paintBoxPresenter_) delete paintBoxPresenter_;
  if (paintBox_) delete paintBox_;
  if (brush_) delete brush_;
  if (cursor_) delete cursor_;
  if (arrowsManager_) delete arrowsManager_;
  if (hierarchy_) delete hierarchy_;
}

void Lab::setUpPaintBox() {
  paintBoxPresenter_ = new PaintBoxPresenter();
  paintBox_ = new PaintBox();

  paintBoxPresenter_->subscribeView(paintBox_);

  paintBox_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  ui.centralWidget->layout()->addWidget(paintBox_);

  paintBox_->show();

  brush_ = new Brush();
  cursor_ = new Cursor();
  shapeCreator_ = new ShapeCreator();
  arrowsManager_ = new ArrowsManager();
  paintBoxPresenter_->setMouseType(cursor_);
}

void Lab::colorChanged(QColor color) {
  QPalette palette;
  palette.setColor(QPalette::Window, color);
  ui.colorPresenter->setPalette(palette);

  if (!paintBoxPresenter_->tryChangeColor(color)) {
    User::getInstance()->Color = color;
  }
}

void Lab::brushSizeSliderValueChanged(int value) {
  User::getInstance()->BrushSize = value;
}

void Lab::cursorChoosed() { paintBoxPresenter_->setMouseType(cursor_); }

void Lab::brushChoosed() { paintBoxPresenter_->setMouseType(brush_); }

void Lab::shapeChoosed() {
  QString sName = sender()->objectName();
  if (sName == "lineButton") {
    User::getInstance()->ShapeCreatorType = "Line";
  } else if (sName == "rectButton") {
    User::getInstance()->ShapeCreatorType = "Rect";
  } else if (sName == "ellipseButton") {
    User::getInstance()->ShapeCreatorType = "Ellipse";
  } else if (sName == "triangleButton") {
    User::getInstance()->ShapeCreatorType = "Triangle";
  }

  paintBoxPresenter_->setMouseType(shapeCreator_);
}

void Lab::changeColor() {
  QColor c = QColorDialog::getColor();
  colorChanged(c);
}

void Lab::arrowChoosed() { paintBoxPresenter_->setMouseType(arrowsManager_); }

void Lab::openFile() { paintBoxPresenter_->openFile(); }

void Lab::saveFile() { paintBoxPresenter_->saveFile(); }
