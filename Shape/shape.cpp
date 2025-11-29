#include "shape.h"

#include <QPainter>
#include <chrono>

Shape::~Shape() { notifyAllArrowsAboutDelete(); }

Shape::Shape(QPoint coordinates, QSize size, QColor color)
    : pos_(coordinates), size_(size), color_(color) {
  generateId();
}

QColor Shape::getColor() const { return color_; }

void Shape::move(int x, int y) {
  notifyFromArrowsAboutMove(x - pos_.x(), y - pos_.y());
  pos_ = QPoint(x, y);
}

void Shape::resize(int x, int y) {
  size_.setWidth(x);
  size_.setHeight(y);
}

void Shape::changeColor(QColor color) { color_ = color; }

QSize Shape::getSize() const { return size_; }

QPoint Shape::getPos() const { return pos_; }

QPoint Shape::getCentralPos() const {
  return pos_ + QPoint(size_.width() / 2, size_.height() / 2);
}

QRect Shape::getBounds() const { return QRect(pos_, size_); }

void Shape::save(FILE* file) {
  fprintf_s(file, "%s %d %d %d %d %d %d %d %d\n", type(), id_, pos_.x(), pos_.y(),
            size_.width(), size_.height(), color_.red(), color_.green(),
            color_.blue());
}

void Shape::load(FILE* file) {
  int id, xPos, yPos, xSize, ySize, redC, greenC, blueC;

  fscanf_s(file, "%d %d %d %d %d %d %d %d\n", &id, &xPos, &yPos, &xSize, &ySize, &redC,
           &greenC, &blueC);

  id_ = id;
  pos_ = QPoint(xPos, yPos);
  size_ = QSize(xSize, ySize);
  color_ = QColor(redC, greenC, blueC);
}

int Shape::getId() { return id_; }

void Shape::addToArrow(Arrow* arrow) { toArrows_.addElement(arrow); }

void Shape::removeToArrow(Arrow* arrow) {
  if (arrow) toArrows_.removeElement(arrow);
}

void Shape::addFromArrow(Arrow* arrow) { fromArrows_.addElement(arrow); }

void Shape::removeFromArrow(Arrow* arrow) {
  if (arrow) fromArrows_.removeElement(arrow);
}

void Shape::notifyFromArrowsAboutMove(int xDiff, int yDiff) {
  for (auto& arrow : fromArrows_) {
    arrow->moved(xDiff, yDiff);
  }
}

void Shape::notifyAllArrowsAboutDelete() {
  Storage<Arrow*> arrowsToDel;

  for (auto& arrow : fromArrows_) {
    arrowsToDel.addElement(arrow);
  }
  for (auto& arrow : toArrows_) {
    arrowsToDel.addElement(arrow);
  }

  for (auto& arrow : arrowsToDel) {
    arrow->deleted(this);
  }
  fromArrows_.clear();
  toArrows_.clear();
}

void Shape::generateId() {
  auto now = std::chrono::system_clock::now();
  auto duration = now.time_since_epoch();
  auto milliseconds =
      std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

  id_ = (milliseconds % 100000 + pos_.x() + pos_.y() + size_.width() +
         size_.height() + color_.red() + color_.green() + color_.blue()) %
        100000;
}
