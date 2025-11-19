#include "group.h"
#include "QDebug"

Group::Group(Storage<Shape *> storage) : objects_(storage) {
  QRect b = getBounds();

  pos_ = b.topLeft();
  size_ = b.size();

  updateRelativeInfo();
}

Group::~Group() {
  for (auto &object : objects_) {
    delete object;
  }
}

void Group::move(int x, int y) {
  pos_ = QPoint(x, y);

  for (auto &object : objects_) {
    QPointF objRelativePos = relativeInfo_[object].first;

    object->move(pos_.x() + objRelativePos.x() * size_.width(),
                 pos_.y() + objRelativePos.y() * size_.height());
  }
}

void Group::resize(int x, int y) {
  size_ = QSize(x, y);

  for (auto &obj : objects_) {
    QSizeF objRelativeSize = relativeInfo_[obj].second;

    obj->resize(size_.width() * objRelativeSize.width(),
                size_.height() * objRelativeSize.height());
  }
}

void Group::changeColor(QColor color) {
  color_ = color;

  for (auto &object : objects_) {
    object->changeColor(color);
  }
}

QRect Group::getBounds() const {
  if (objects_.size() == 0) {
    return QRect();
  }
  QRect r(objects_[0]->getBounds());

  for (int i = 1; i < objects_.size(); i++) {
    r = r.united(objects_[i]->getBounds());
  }
  return r;
}

bool Group::hasPointIn(QPoint point) const {
  for (const auto &obj : objects_) {
    if (obj->hasPointIn(point)) {
      return true;
    }
  }
  return false;
}

void Group::draw(QPainter& painter) const {
  for (const auto &obj : objects_) {
    obj->draw(painter);
  }
}

Storage<Shape *> &Group::getAllObjToUngroup() { return objects_; }

void Group::updateRelativeInfo() {
  relativeInfo_.clear();

  QRect allArea = getBounds();

  for (auto &obj : objects_) {
    QPointF objRelativePos(
        static_cast<double>(obj->getPos().x() - allArea.topLeft().x()) /
            allArea.width(),
        static_cast<double>(obj->getPos().y() - allArea.topLeft().y()) /
            allArea.height());

    QSizeF objRelativeSize(
        static_cast<double>(obj->getSize().width()) / allArea.width(),
        static_cast<double>(obj->getSize().height()) / allArea.height());

    relativeInfo_[obj] = std::make_pair(objRelativePos, objRelativeSize);
  }
}