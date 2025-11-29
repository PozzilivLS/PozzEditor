#include "chunk.h"

#include <ObjectFactory/objectFactory.h>

#include <QBitmap>
#include <QDebug>
#include <QPoint>

Chunk::Chunk(QColor color) : Shape(QPoint(), QSize(), color) {}

Chunk::~Chunk() {
  for (auto& obj : data_) {
    delete obj;
  }
  // Shape::~Shape();
}

void Chunk::addElement(Ellipse* const& el) {
  Storage::addElement(el);

  QPoint luPoint = el->getPos();
  QPoint rdPoint =
      el->getPos() + QPoint(el->getSize().width(), el->getSize().height());

  if (size() == 1) {
    pos_ = el->getPos();
    size_ = el->getSize();
  }

  QRect rect(pos_, size_);
  rect = rect.united(QRect(luPoint, rdPoint));
  pos_ = rect.topLeft();
  size_ = rect.size();
}

void Chunk::resize(int x, int y) {
  if (!isFixed_ && fixedCache_.size().width() > 0 &&
      fixedCache_.size().height() > 0) {
    return;
  }

  size_ = QSize(x, y);

  cache_ = fixedCache_.transformed(
      QTransform().scale((float)size_.width() / fixedCache_.size().width(),
                         (float)size_.height() / fixedCache_.size().height()));
}

bool Chunk::hasPointIn(QPoint point) const {
  QRect rect(pos_, size_);
  if (!rect.contains(point)) {
    return false;
  }
  return isCircleInPoint(point);
}

bool Chunk::isCircleInPoint(QPoint point) const {
  if (size() == 0) {
    return false;
  }

  auto sqrMagnitude = [](QPoint a, QPoint b) {
    QPoint c = a - b;
    return c.x() * c.x() + c.y() * c.y();
  };

  point -= pos_;

  point.setX(point.x() / (size_.width() / (float)fixedCache_.size().width()));
  point.setY(point.y() / (size_.height() / (float)fixedCache_.size().height()));

  int rad = data_[0]->getSize().height() / 2;
  for (const auto& circle : data_) {
    if (sqrMagnitude(point, circle->getCentralPos()) <= rad * rad) {
      return true;
    }
  }  // TODO: incaps?

  return false;
}

void Chunk::draw(QPainter& painter) const {
  if (!isFixed()) {
    painter.setBrush(color_);
    for (const auto& obj : *this) {
      obj->draw(painter);
    }
    return;
  }

  QPoint p(pos_.x() + (size_.width() < 0 ? size_.width() : 0),
           pos_.y() + (size_.height() < 0 ? size_.height() : 0));

  painter.drawPixmap(p, cache_);
}

void Chunk::changeColor(QColor color) {
  color_ = color;
  for (const auto& el : data_) {
    el->changeColor(color);
  }

  QPainter p(&fixedCache_);

  p.setCompositionMode(QPainter::CompositionMode_SourceIn);
  p.fillRect(fixedCache_.rect(), color);

  p.end();

  cache_ = fixedCache_.transformed(
      QTransform().scale((float)size_.width() / fixedCache_.size().width(),
                         (float)size_.height() / fixedCache_.size().height()));
}

QPixmap& Chunk::getPixmap() { return cache_; }

const QPixmap& Chunk::getPixmap() const { return cache_; }

bool Chunk::isFixed() const { return isFixed_; }

void Chunk::setFixed() {
  cache_ = QPixmap(size_);
  mask_ = QBitmap(cache_.size());
  mask_.clear();
  cache_.setMask(mask_);

  QPainter chunkPainter(&const_cast<QPixmap&>(cache_));
  QBrush br(color_);
  chunkPainter.setBrush(br);
  chunkPainter.setPen(color_);
  for (const auto& obj : *this) {
    obj->move(obj->getPos().x() - pos_.x(), obj->getPos().y() - pos_.y());
    obj->draw(chunkPainter);
  }

  fixedCache_ = cache_;
  isFixed_ = true;
}

void Chunk::save(FILE* file) {
  Shape::save(file);

  fprintf_s(file, "%d\n", size());

  for (const auto& obj : data_) {
    obj->save(file);
  }
}
     
void Chunk::load(FILE* file) {
  int id, xPos, yPos, xSize, ySize, redC, greenC, blueC;

  fscanf_s(file, "%d %d %d %d %d %d %d %d\n", &id, &xPos, &yPos, &xSize, &ySize, &redC,
           &greenC, &blueC);
  id_ = id;
  int size;

  fscanf_s(file, "%d\n", &size);

  qDebug() << pos_;

  for (int i = 0; i < size; i++) {
    char type[128];
    fscanf_s(file, "%s", type, (unsigned)_countof(type));

    Shape * newObj = ObjectFactory::getInstance()->createObj(type);
    if (!newObj) continue;

    newObj->load(file);

    addElement(static_cast<Ellipse*>(newObj));
  }

  setFixed();

  changeColor(QColor(redC, greenC, blueC));
  move(xPos, yPos);
  resize(xSize, ySize);
}
