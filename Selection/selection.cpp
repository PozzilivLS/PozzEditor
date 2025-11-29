#include "selection.h"

#include <QBrush>
#include <QEvent>
#include <QPoint>
#include <QSize>
#include <map>

#include "Shape/shape.h"

void Selection::addElement(Shape * const& el) {
  Storage<Shape *>::addElement(el);
  updateRelativeInfo();
}

void Selection::removeElement(Shape * const& el) {
  Storage<Shape *>::removeElement(el);
  updateRelativeInfo();
}

void Selection::removeElementByIndex(const int index) {
  Storage<Shape *>::removeElementByIndex(index);
  updateRelativeInfo();
}

void Selection::clear() {
  Storage<Shape *>::clear();
  updateRelativeInfo();
}

void Selection::draw(QPainter& painter) const {
  if (Storage<Shape *>::size() == 0) {
    return;
  }

  QRect r = getArea();

  QPoint vertexes[4]{r.topLeft(), r.topRight(), r.bottomRight(),
                     r.bottomLeft()};
  QPoint edges[4]{(r.topLeft() + r.topRight()) / 2,
                  (r.topRight() + r.bottomRight()) / 2,
                  (r.bottomRight() + r.bottomLeft()) / 2,
                  (r.bottomLeft() + r.topLeft()) / 2};

  QPoint alpha(-4, -4);
  QSize pivotSize(8, 8);
  QRect* pivots = new QRect[8]{
      QRect(vertexes[0] + alpha, pivotSize),
      QRect(vertexes[1] + alpha, pivotSize),
      QRect(vertexes[2] + alpha, pivotSize),
      QRect(vertexes[3] + alpha, pivotSize),
      QRect(edges[0] + alpha, pivotSize),
      QRect(edges[1] + alpha, pivotSize),
      QRect(edges[2] + alpha, pivotSize),
      QRect(edges[3] + alpha, pivotSize),
  };

  painter.drawRect(r);

  QBrush b(Qt::white);
  painter.setBrush(b);

  painter.drawRects(pivots, 8);

  delete pivots;
}

QRect Selection::getArea() const {
  if (Storage<Shape *>::size() == 0) {
    return QRect();
  }

  QRect r(at(0)->getBounds());

  for (int i = 1; i < Storage<Shape *>::size(); i++) {
    r = r.united(at(i)->getBounds());
  }
  return r;
}

bool Selection::hasObjectInPoint(QPoint point) const {
  for (const auto& obj : data_) {
    if (obj->hasPointIn(point)) {
      return true;
    }
  }
  return false;
}

Selection::MousePosState Selection::checkMousePos(QPoint pos) {
  auto r = abstractLastRect_.isNull() ? getArea() : abstractLastRect_;

  QPoint vertexAlpha(-4, -4);
  QSize pivotSize(8, 8);
  QRect vertexBPivots[2]{QRect(r.topLeft() + vertexAlpha, pivotSize),
                         QRect(r.bottomRight() + vertexAlpha, pivotSize)};

  QRect vertexFPivots[2]{QRect(r.topRight() + vertexAlpha, pivotSize),
                         QRect(r.bottomLeft() + vertexAlpha, pivotSize)};

  QRect horEdges[2]{
      QRect(r.topLeft() + QPoint(4, -4), QSize(r.size().width() - 8, 8)),
      QRect(r.bottomLeft() + QPoint(4, -4), QSize(r.size().width() - 8, 8))};

  QRect verEdges[2]{
      QRect(r.topRight() + QPoint(-4, 4), QSize(8, r.size().height() - 8)),
      QRect(r.topLeft() + QPoint(-4, 4), QSize(8, r.size().height() - 8))};

  std::vector<std::pair<QRect, Selection::ResizePositions>> positions{
      {vertexBPivots[0], Selection::ResizePositions::LeftUp},
      {horEdges[0], Selection::ResizePositions::Up},
      {vertexFPivots[0], Selection::ResizePositions::RightUp},
      {verEdges[0], Selection::ResizePositions::Right},
      {vertexBPivots[1], Selection::ResizePositions::RightDown},
      {horEdges[1], Selection::ResizePositions::Down},
      {vertexFPivots[1], Selection::ResizePositions::LeftDown},
      {verEdges[1], Selection::ResizePositions::Left}};  // TODO: говнокод

  for (int i = 0; i < 2; i++) {
    if (vertexBPivots[i].contains(pos)) {
      currentResizePos_ = positions[i * 4].second;
      return (r.height() * r.width() > 0) ? Selection::MousePosState::BCorner
                                          : Selection::MousePosState::FCorner;
    }
  }
  for (int i = 0; i < 2; i++) {
    if (vertexFPivots[i].contains(pos)) {
      currentResizePos_ = positions[2 + i * 4].second;
      return (r.height() * r.width() > 0) ? Selection::MousePosState::FCorner
                                          : Selection::MousePosState::BCorner;
    }
  }

  for (int i = 0; i < 2; i++) {
    if (horEdges[i].contains(pos)) {
      currentResizePos_ = positions[1 + i * 4].second;
      return Selection::MousePosState::HorEdge;
    }
  }
  for (int i = 0; i < 2; i++) {
    if (verEdges[i].contains(pos)) {
      currentResizePos_ = positions[3 + i * 4].second;
      return Selection::MousePosState::VerEdge;
    }
  }

  return Selection::MousePosState::None;
}

void Selection::moveSelections(int diffX, int diffY) {
  for (const auto& obj : *this) {
    obj->move(obj->getPos().x() + diffX, obj->getPos().y() + diffY);
  }
  abstractLastRect_.moveTo(abstractLastRect_.topLeft() + QPoint(diffX, diffY));
}

void Selection::resizeSelections(int diffX, int diffY) {
  QPoint positionDiff(0, 0);
  QSize sizeDiff(0, 0);

  switch (currentResizePos_) {
    case Selection::ResizePositions::LeftUp:
      positionDiff = QPoint(diffX, diffY);
      sizeDiff = QSize(-diffX, -diffY);
      break;
    case Selection::ResizePositions::Up:
      positionDiff = QPoint(0, diffY);
      sizeDiff = QSize(0, -diffY);
      break;
    case Selection::ResizePositions::RightUp:
      positionDiff = QPoint(0, diffY);
      sizeDiff = QSize(diffX, -diffY);
      break;
    case Selection::ResizePositions::Right:
      positionDiff = QPoint(0, 0);
      sizeDiff = QSize(diffX, 0);
      break;
    case Selection::ResizePositions::RightDown:
      positionDiff = QPoint(0, 0);
      sizeDiff = QSize(diffX, diffY);
      break;
    case Selection::ResizePositions::Down:
      positionDiff = QPoint(0, 0);
      sizeDiff = QSize(0, diffY);
      break;
    case Selection::ResizePositions::LeftDown:
      positionDiff = QPoint(diffX, 0);
      sizeDiff = QSize(-diffX, diffY);
      break;
    case Selection::ResizePositions::Left:
      positionDiff = QPoint(diffX, 0);
      sizeDiff = QSize(-diffX, 0);
      break;
    case Selection::ResizePositions::None:
      break;
    default:
      break;
  }

  QRect allArea = abstractLastRect_.isNull() ? getArea() : abstractLastRect_;

  QRect newArea = allArea;
  newArea.moveTo(newArea.topLeft() + positionDiff);
  newArea.setSize(newArea.size() + sizeDiff);

  abstractLastRect_ = newArea;

  for (auto& obj : *this) {
    QPointF objRelativePos = relativeInfo_[obj].first;
    QSizeF objRelativeSize = relativeInfo_[obj].second;

    obj->resize(newArea.width() * objRelativeSize.width(),
                newArea.height() * objRelativeSize.height());
    obj->move(
        newArea.topLeft().x() + objRelativePos.x() * newArea.width(),
        newArea.topLeft().y() + objRelativePos.y() * newArea.height());
  }
}

void Selection::updateRelativeInfo() {
  relativeInfo_.clear();

  QRect allArea = getArea();
  abstractLastRect_ = QRect();

  for (auto& obj : *this) {
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
