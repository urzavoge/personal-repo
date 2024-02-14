#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

template <typename T>
struct Point;

template <typename T>
struct Vector {
  Point<T> start;
  Point<T> end;

  Vector(T x_c, T y_c);
  Vector(const Point<T>& first, const Point<T>& second)
      : start(first), end(second) {}

  explicit Vector(const Point<T>& other) : start(0, 0), end(other) {}

  bool operator==(const Vector& other) const;
  void Norm();
  T DotProduct(const Vector& oth) const;
  T CrossProduct(const Vector& oth) const;
  T LenghtSq() const;

  Vector& operator+=(const Vector& oth);

  T GetX() const;
  T GetY() const;
};

template <typename T>
struct Point {
  T cord_x;
  T cord_y;

  Point() = default;
  Point(T fx, T fy) : cord_x(fx), cord_y(fy) {}

  Vector<T> operator-=(const Point& other) const {
    return Vector<T>(cord_x - other.cord_x, cord_y - other.cord_y);
  }

  explicit Point(const Vector<T>& oth)
      : cord_x(oth.end.cord_x - oth.start.cord_x),
        cord_y(oth.end.cord_y - oth.start.cord_y) {}

  bool operator==(const Point& oth) const {
    return (cord_x == oth.cord_x) && (cord_y == oth.cord_y);
  }

  bool operator!=(const Point& oth) const {
    return (cord_x != oth.cord_x) || (cord_y != oth.cord_y);
  }

  bool operator<(const Point& other) const {
    return cord_x < other.cord_x ||
           (cord_x == other.cord_x && cord_y < other.cord_y);
  }

  Point& operator+=(const Vector<T>& vect) {
    cord_x += (vect.end.cord_x - vect.start.cord_x);
    cord_y += (vect.end.cord_y - vect.start.cord_y);
    return *this;
  }

  Point& operator+=(const Point<T>& other) {
    return (*this) += Vector<T>(other);
  }
};

template <typename T>
Point<T> operator+(const Point<T>& first, const Point<T>& second) {
  Point<T> copy(first);
  return copy += second;
}

template <typename T>
T Vector<T>::GetX() const {
  return end.cord_x - start.cord_x;
}

template <typename T>
T Vector<T>::GetY() const {
  return end.cord_y - start.cord_y;
}

template <typename T>
T LenghtSq(const Point<T>& first, const Point<T>& second) {
  return (second - first).LenghtSq();
}

template <typename T>
Point<T> operator+(const Point<T>& point, const Vector<T>& vect) {
  Point<T> copy = point;
  return copy += vect;
}

template <typename T>
Vector<T> operator-(const Point<T>& first, const Point<T>& second) {
  Point<T> copy(first);
  return copy -= second;
}

template <typename T>
Vector<T>::Vector(T x_c, T y_c) : start{0, 0}, end{x_c, y_c} {}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& other) const {
  return Point(*this) == Point(other);
}

template <typename T>
void Vector<T>::Norm() {
  end.cord_x = end.cord_x - start.cord_x;
  end.cord_y = end.cord_y - start.cord_y;
  start.cord_x = 0;
  start.cord_y = 0;
}

template <typename T>
T DotProduct(const Vector<T>& first, const Vector<T>& second) {
  return (first.end.cord_x - first.start.cord_x) *
             (second.end.cord_x - second.start.cord_x) +
         (first.end.cord_y - first.start.cord_y) *
             (second.end.cord_y - second.start.cord_y);
}

template <typename T>
T CrossProduct(const Vector<T>& first, const Vector<T>& second) {
  return first.GetX() * second.GetY() - first.GetY() * second.GetX();
}

template <typename T>
T Vector<T>::LenghtSq() const {
  return (end.cord_x - start.cord_x) * (end.cord_x - start.cord_x) +
         (end.cord_y - start.cord_y) * (end.cord_y - start.cord_y);
}

template <typename T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& oth) {
  end.cord_x += (oth.end.cord_x - oth.start.cord_x);
  end.cord_y += (oth.end.cord_y - oth.start.cord_y);
  return *this;
}

template <typename T>
Vector<T> operator+(const Vector<T>& first, const Vector<T>& second) {
  Vector<T> vect(first);
  return vect += second;
}

template <typename T>
double DistLine(Point<T> start, Point<T> end, Point<T> point) {
  double square = static_cast<double>(
      std::abs(CrossProduct<T>(start - point, end - point)));
  if (LenghtSq(start, end) == 0) {
    return sqrt(static_cast<double>(LenghtSq(start, point)));
  }
  return square / sqrt(static_cast<double>(LenghtSq(start, end)));
}

template <typename T>
double DistRay(Point<T> start, Point<T> end, Point<T> point) {
  Vector<T> first = point - start;
  Vector<T> second = end - start;
  if (DotProduct(first, second) < 0) {
    return sqrt(static_cast<double>(first.LenghtSq()));
  }
  return DistLine(start, end, point);
}

template <typename T>
double DistSegment(Point<T> start, Point<T> end, Point<T> point) {
  Vector<T> first = point - start;
  Vector<T> second = point - end;
  Vector<T> base = end - start;

  if (DotProduct(first, base) >= 0 && DotProduct(second, start - end) >= 0) {
    return DistLine(start, end, point);
  }
  return static_cast<double>(
      sqrt(std::min(first.LenghtSq(), second.LenghtSq())));
}

template <typename T>
T ControlSum(Point<T> sta, Vector<T> vect, Point<T> poi) {
  vect.Norm();
  return vect.end.cord_x * poi.cord_y - vect.end.cord_y * poi.cord_x +
         vect.end.cord_y * sta.cord_x - vect.end.cord_x * sta.cord_y;
}

template <typename T>
bool AreIntersects(Point<T> st_f, Point<T> en_f, Point<T> st_s, Point<T> en_s) {
  T first = ControlSum(st_f, en_f - st_f, st_s);
  T second = ControlSum(st_f, en_f - st_f, en_s);
  T third = ControlSum(st_s, en_s - st_s, st_f);
  T fourth = ControlSum(st_s, en_s - st_s, en_f);
  if (first * second <= 0) {
    if (third * fourth <= 0) {
      if (first == 0 && second == 0 && third == 0 && fourth == 0) {
        if (DotProduct(st_f - st_s, en_f - st_s) > 0 &&
            DotProduct(st_s - st_f, en_s - st_f) > 0 &&
            DotProduct(st_f - en_s, en_f - en_s) > 0 &&
            DotProduct(st_s - en_f, en_s - en_f)) {
          return false;
        }
      }
      return true;
    }
  }
  return false;
}

template <typename T>
double Dist2Seg(Point<T> st_f, Point<T> en_f, Point<T> st_s, Point<T> en_s) {
  if (AreIntersects(st_f, en_f, st_s, en_s)) {
    return 0;
  }
  return std::min(DistSegment(st_f, en_f, st_s),
                  std::min(DistSegment(st_f, en_f, en_s),
                           std::min(DistSegment(st_s, en_s, st_f),
                                    DistSegment(st_s, en_s, en_f))));
}

template <typename T>
bool IsConvex(std::vector<Point<T>>& polygon) {
  size_t size = polygon.size();
  polygon.emplace_back(polygon[0]);
  polygon.emplace_back(polygon[1]);
  int64_t cross;
  size_t cnt = 0;
  while ((cross = CrossProduct(polygon[cnt + 1] - polygon[cnt],
                               polygon[cnt + 2] - polygon[cnt + 1])) == 0) {
    ++cnt;
    if (cnt == size) {
      return false;
    }
  }
  bool sign = (cross > 0);
  for (size_t i = 0; i < size; ++i) {
    cross = CrossProduct(polygon[i + 1] - polygon[i],
                         polygon[i + 2] - polygon[i + 1]);
    if (cross == 0) {
      if (DotProduct(polygon[i + 1] - polygon[i],
                     polygon[i + 2] - polygon[i + 1]) < 0) {
        return false;
      }
      continue;
    }
    bool new_sign = (cross > 0);
    if (new_sign ^ sign) {
      return false;
    }
  }
  return true;
}

template <typename T>
bool WeakIntersec(Point<T> bbbbb, Point<T> end, Point<T> aaaaa,
                  Point<T> second) {
  T cs1 = ControlSum(bbbbb, end - bbbbb, aaaaa);
  T cs2 = ControlSum(bbbbb, end - bbbbb, second);
  T cs3 = ControlSum(aaaaa, second - aaaaa, bbbbb);
  T cs4 = ControlSum(aaaaa, second - aaaaa, end);
  return (cs1 * cs2 < 0 && cs3 * cs4 < 0);
}

template <typename T>
bool IsOnASegment(Point<T> start, Point<T> end, Point<T> point) {
  if (ControlSum(start, end - start, point) != 0) {
    return false;
  }
  return std::min(start.cord_x, end.cord_x) <= point.cord_x &&
         point.cord_x <= std::max(start.cord_x, end.cord_x) &&
         std::min(start.cord_y, end.cord_y) <= point.cord_y &&
         point.cord_y <= std::max(start.cord_y, end.cord_y);
}

template <typename T>
bool IsInside(std::vector<Point<T>>& polygon, Point<T> monster, Point<T> fake) {
  int cnt = 0;
  Point<T> rrrrr = polygon.back();
  Point<T> cock(std::numeric_limits<T>::max(), std::numeric_limits<T>::min());
  size_t size = polygon.size();
  polygon.emplace_back(polygon[0]);
  for (size_t i = 0; i < size; ++i) {
    if (WeakIntersec(monster, fake, polygon[i], polygon[i + 1])) {
      ++cnt;
    }
    if (IsOnASegment(polygon[i], polygon[i + 1], monster)) {
      return true;
    }
    if (IsOnASegment(monster, fake, polygon[i])) {
      if (ControlSum(monster, fake - monster, rrrrr) *
              ControlSum(monster, fake - monster, polygon[i + 1]) <=
          0) {
        ++cnt;
      }
    }
    rrrrr = polygon[i];
  }
  return (cnt % 2 == 1);
}

template <typename T>
struct Circle {
  Point<T> centre;
  T radius;

  Circle() = default;
};

template <typename T>
void ConvexHull(std::vector<Point<T>>& polygon) {
  std::sort(
      polygon.begin(), polygon.end(), [](Point<T>& first, Point<T>& second) {
        return first.cord_x < second.cord_x ||
               (first.cord_x == second.cord_x && first.cord_y < second.cord_y);
      });
  polygon.erase(std::unique(polygon.begin(), polygon.end()), polygon.end());
  if (polygon.size() <= 2) {
    return;
  }
  Point<T> left = polygon[0];
  Point<T> right = polygon.back();
  std::vector<Point<T>> up_hull(1, left);
  std::vector<Point<T>> down_hull(1, left);
  for (auto& point : polygon) {
    if (point == right || CrossProduct(left - right, point - right) < 0) {
      while (up_hull.size() >= 2 &&
             CrossProduct(up_hull[up_hull.size() - 2] - point,
                          up_hull.back() - point) >= 0) {
        up_hull.pop_back();
      }
      up_hull.emplace_back(point);
    }
    if (point == right || CrossProduct(left - right, point - right) > 0) {
      while (down_hull.size() >= 2 &&
             CrossProduct(down_hull[down_hull.size() - 2] - point,
                          down_hull.back() - point) <= 0) {
        down_hull.pop_back();
      }
      down_hull.emplace_back(point);
    }
  }
  polygon.clear();
  for (auto it = up_hull.begin(); it != up_hull.end(); ++it) {
    polygon.emplace_back(*it);
  }
  for (auto it = down_hull.end() - 1; it != down_hull.begin() + 1;) {
    polygon.emplace_back(*(--it));
  }
}

template <typename T>
T DoubleSquare(std::vector<Point<T>>& polygon) {
  T sq = 0;
  for (size_t i = 1; i < polygon.size() - 1; ++i) {
    sq += std::abs(
        CrossProduct(polygon[i] - polygon[0], polygon[i + 1] - polygon[0]));
  }
  return sq;
}

template <typename T>
void MinkowskiSum(const std::vector<Point<T>>& first, size_t fir_left,
                  const std::vector<Point<T>>& second, size_t sec_left,
                  std::vector<Point<T>>& result) {
  size_t size1 = first.size();
  size_t size2 = second.size();
  if (size1 == 0 || size2 == 0) {
    return;
  }
  size_t ind1 = 0;
  size_t ind2 = 0;
  Point<T> sum = first[fir_left] + second[sec_left];
  result.emplace_back(sum);
  while (ind1 < size1 || ind2 < size2) {
    Vector<T> first_next =
        first[(fir_left + ind1 + 1) % size1] - first[(fir_left + ind1) % size1];
    Vector<T> second_next = second[(sec_left + ind2 + 1) % size2] -
                            second[(sec_left + ind2) % size2];
    if (CrossProduct(first_next, second_next) > 0) {
      sum += first_next;
      if (sum == result[0]) {
        return;
      }
      result.emplace_back(sum);
      ++ind1;
    } else if (CrossProduct(first_next, second_next) < 0) {
      sum += second_next;
      if (sum == result[0]) {
        return;
      }
      result.emplace_back(sum);
      ++ind2;
    } else {
      sum += second_next;
      sum += first_next;
      if (sum == result[0]) {
        return;
      }
      result.emplace_back(sum);
      ++ind2;
      ++ind1;
    }
  }
}

bool IsInsideConvex(const std::vector<Point<int64_t>>& polygon,
                    Point<int64_t> point) {
  size_t first = 0;
  size_t second = polygon.size();
  if (second == 0) {
    return false;
  }
  while (second - first > 1) {
    size_t mid = std::midpoint(first, second);
    Vector<int64_t> mid_vect = polygon[mid % polygon.size()] - polygon[0];
    Vector<int64_t> origin = point - polygon[0];
    if (CrossProduct(mid_vect, origin) > 0) {
      first = mid;
    } else if (CrossProduct(mid_vect, origin) < 0) {
      second = mid;
    } else {
      if (DotProduct(mid_vect, origin) < 0) {
        return false;
      }
      return origin.LenghtSq() <= mid_vect.LenghtSq();
    }
  }
  return CrossProduct(point - polygon[second % polygon.size()],
                      polygon[first] - polygon[second % polygon.size()]) >= 0;
}

void Solve(const std::vector<std::vector<Point<int64_t>>>& polygons,
           const std::vector<size_t>& lefts,
           std::vector<Point<int64_t>>& requests) {
  std::vector<Point<int64_t>> tmp_res{};
  std::vector<Point<int64_t>> res{};
  MinkowskiSum(polygons[0], lefts[0], polygons[1], lefts[1], tmp_res);
  MinkowskiSum(polygons[2], lefts[2], tmp_res, 0, res);
  for (auto& point : requests) {
    if (IsInsideConvex(res, point)) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t num;
  std::vector<std::vector<Point<int64_t>>> polygons(3);
  std::vector<size_t> lefts(3, 0);
  for (size_t j = 0; j < 3; ++j) {
    Point<int64_t> leftest(std::numeric_limits<int64_t>::max(),
                           std::numeric_limits<int64_t>::max());
    std::cin >> num;
    polygons[j].resize(num);
    for (size_t i = 0; i < num; ++i) {
      std::cin >> polygons[j][i].cord_x >> polygons[j][i].cord_y;
      if (polygons[j][i] < leftest) {
        leftest = polygons[j][i];
        lefts[j] = i;
      }
    }
  }
  std::cin >> num;
  std::vector<Point<int64_t>> requests(num);
  for (auto& point : requests) {
    std::cin >> point.cord_x >> point.cord_y;
    point.cord_y *= 3;
    point.cord_x *= 3;
  }
  Solve(polygons, lefts, requests);
  return 0;
}