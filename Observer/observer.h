#pragma once
class PaintUpdatable {
 public:
  virtual void updateZone() = 0;
  virtual ~PaintUpdatable() {};
};
