#include "lab.h"

#include <QButtonGroup>
#include <QKeyEvent>
#include <QPainter>
#include <QColor>

#include "Mouse/brush.h"
#include "Mouse/cursor.h"
#include "Mouse/shapeCreator.h"
#include "PaintBox/paintbox.h"
#include "User/user.h"
#include "colorchanger.h"
#include "paintBoxPresenter.h"

Lab::Lab(QWidget *parent) : QMainWindow(parent) {
  ui.setupUi(this);

  connect(ui.brushSizeSlider, SIGNAL(valueChanged(int)),
          SLOT(brushSizeSliderValueChanged(int)));
  connect(ui.chooseMouseBtn, SIGNAL(clicked()), SLOT(cursorChoosed()));
  connect(ui.chooseBrushBtn, SIGNAL(clicked()), SLOT(brushChoosed()));

  connect(ui.lineButton, SIGNAL(clicked()), SLOT(shapeChoosed()));
  connect(ui.rectButton, SIGNAL(clicked()), SLOT(shapeChoosed()));
  connect(ui.ellipseButton, SIGNAL(clicked()), SLOT(shapeChoosed()));
  connect(ui.triangleButton, SIGNAL(clicked()), SLOT(shapeChoosed()));

  connect(ui.colorButton, SIGNAL(clicked()), SLOT(changeColor()));

  toolsGroup_ = new QButtonGroup(this);
  toolsGroup_->setExclusive(true);

  toolsGroup_->addButton(ui.chooseBrushBtn, 0);
  toolsGroup_->addButton(ui.chooseMouseBtn, 1);
  toolsGroup_->addButton(ui.lineButton, 2);
  toolsGroup_->addButton(ui.rectButton, 3);
  toolsGroup_->addButton(ui.ellipseButton, 4);
  toolsGroup_->addButton(ui.triangleButton, 5);

  setUpPaintBox();

  colorChanged(User::getInstance()->Color);
} // TODO: group

Lab::~Lab() {
  if (paintBoxPresenter_) delete paintBoxPresenter_;
  if (paintBox_) delete paintBox_;
  if (brush_) delete brush_;
  if (cursor_) delete cursor_;
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
    User::getInstance()->ShapeCreatorType = ShapeType::Line;
  } else if (sName == "rectButton") {
    User::getInstance()->ShapeCreatorType = ShapeType::Rect;
  } else if (sName == "ellipseButton") {
    User::getInstance()->ShapeCreatorType = ShapeType::Ellipse;
  } else if (sName == "triangleButton") {
    User::getInstance()->ShapeCreatorType = ShapeType::Triangle;
  }

  paintBoxPresenter_->setMouseType(shapeCreator_);
}

void Lab::changeColor() {
  ColorChanger *cc = new ColorChanger();
  connect(cc, SIGNAL(closed(QColor)), SLOT(changeColorClosed(QColor)));
  cc->show();
  this->setEnabled(false);
}

void Lab::changeColorClosed(QColor color) {
  this->setEnabled(true);
  colorChanged(color);
}

void Lab::takeSelectionsColor(QColor color) {
  
}
