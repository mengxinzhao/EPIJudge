#include <tuple>
#include <stdlib.h>

#include "test_framework/test_utils_serialization_traits.h"

struct Rectangle {
  int x, y, width, height;
};

Rectangle IntersectRectangle(const Rectangle& R1, const Rectangle& R2) {
  // Implement this placeholder.
  // sanity check
  if (R1.width < 0 || R1.height < 0 || R2.height < 0 || R2.width < 0)
    return {-1, -1, -1, -1};
  int top = 0;
  int left = 0;
  int width = 0;
  int height = 0;
  // check if there is intersection at all
  // coordinate system is computer x,y system
  if ( (abs(std::max(R1.x+R1.width, R2.x+ R2.width) - std::min(R1.x, R2.x )) <= R1.width + R2.width) &&
          (abs(std::max(R1.y + R1.height, R2.y + R2.height) - std::min(R1.y,R2.y)) <= R1.height + R2.height)) {
      left = std::max(R1.x, R2.x);
      top =  std::max(R1.y, R2.y);
      width = std::min(R1.x + R1.width, R2.x + R2.width) - left;
      height = std::min(R1.y + R1.height, R2.y + R2.height) - top;
      return {left,top,width,height};
  }
  else
    return {0, 0, -1, -1};
}

bool operator==(const Rectangle& r1, const Rectangle& r2) {
  return std::tie(r1.x, r1.y, r1.width, r1.height) ==
         std::tie(r2.x, r2.y, r2.width, r2.height);
}

template <>
struct SerializationTraits<Rectangle>
    : UserSerTraits<Rectangle, int, int, int, int> {};

std::ostream& operator<<(std::ostream& out, const Rectangle& r) {
  return EpiPrint(out, std::make_tuple(r.x, r.y, r.width, r.height));
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"R1", "R2"};
  generic_test_main(argc, argv, param_names, "rectangle_intersection.tsv",
                    &IntersectRectangle);
  return 0;
}
