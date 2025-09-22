/*
2-D Maxima Finding Algorithm (Divide and Conquer Approach)

Overview:
-----------
This algorithm efficiently finds all maximal points in a set of 2D points.
A point (x1, y1) is said to dominate another point (x2, y2) if x1 > x2 and y1 > y2.
Maximal points are those not dominated by any other point in the set.

Algorithm Steps:
-----------------
1. **Divide**:
    - Sort all points by their x-coordinate.
    - Split the set into two equal halves using a vertical line:
      - Left subset (SL): points to the left of the line.
      - Right subset (SR): points to the right of the line.

2. **Conquer**:
    - Recursively find maximal points in SL (call this ML).
    - Recursively find maximal points in SR (call this MR).

3. **Combine**:
    - All maximal points in MR are guaranteed to be maximal in the whole set,
      because no point in SL can dominate any point in SR (all x-coordinates in SL are smaller).
    - For ML, a point may be dominated by a point in SR if its y-coordinate is less than
      the maximum y-coordinate in SR.
    - Find the highest y-value (y_max_R) among all points in SR.
    - Filter ML: keep only those points whose y-value is at least y_max_R.
    - The final set of maximal points is the union of MR and the filtered ML.

Complexity:
-------------
- The algorithm runs in O(n log n) time, which is much faster than the naive O(n^2) approach.

Summary:
----------
- Sort points by x.
- Recursively find maxima in left and right halves.
- Combine by filtering left maxima using the highest y in the right half.
- Return the union as the set of maximal points.
*/


#include <iostream>
#include <vector>
#include <algorithm> // For std::sort
#include <climits>   // For INT_MIN
using namespace std;

// A simple structure to represent a 2D point
struct Point {
    int x, y;
};

// A helper function to print a vector of points
void printPoints(const vector<Point>& points) {
    for (const auto& p : points) {
        cout << "(" << p.x << ", " << p.y << ") ";
    }
    cout << endl;
}

// The recursive function that implements the divide-and-conquer logic
vector<Point> findMaximaRecursive(vector<Point>& points, int start, int end) {
    // Base Case: If there is only one point, it is maximal by definition
    if (start == end) {
        return {{points[start]}};
    }

    // === 1. DIVIDE ===
    // Find the middle index to split the points into two halves
    int mid = start + (end - start) / 2;

    // === 2. CONQUER ===
    // Recursively find the maximal points in the left and right halves
    vector<Point> maximaLeft = findMaximaRecursive(points, start, mid);
    vector<Point> maximaRight = findMaximaRecursive(points, mid + 1, end);

    // === 3. COMBINE ===
    // Find the largest y-value in the entire right subset (S_R)
    int maxY_in_SR = INT_MIN;
    for (int i = mid + 1; i <= end; ++i) {
        if (points[i].y > maxY_in_SR) {
            maxY_in_SR = points[i].y;
        }
    }

    // The final result will contain all maximal points from the right half (M_R)
    vector<Point> finalMaxima = maximaRight;

    // Now, filter the maximal points from the left half (M_L).
    // A point from M_L is only a true maximum if its y-value is greater
    // than the highest y-value in the entire right set S_R.
    for (const auto& p : maximaLeft) {
        if (p.y > maxY_in_SR) {
            finalMaxima.push_back(p);
        }
    }

    return finalMaxima;
}

// Main function to start the process
vector<Point> findMaxima(vector<Point>& points) {
    if (points.empty()) {
        return {};
    }

    // Step 0: Sort the points based on their x-coordinate.
    // This is a crucial prerequisite for the divide-and-conquer logic to work.
    sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        return a.x < b.x;
    });

    return findMaximaRecursive(points, 0, points.size() - 1);
}

int main() {
    // Example from the previous explanation
    vector<Point> points = {
        {1, 8}, {2, 5}, {3, 9}, {4, 7}, {5, 3},
        {6, 6}, {7, 2}, {8, 4}
    };

    cout << "Original points:" << endl;
    printPoints(points);

    vector<Point> maximalPoints = findMaxima(points);

    cout << "\nMaximal points found:" << endl;
    printPoints(maximalPoints);

    return 0;
}