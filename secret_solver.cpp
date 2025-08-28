#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <sstream>

using namespace std;

// Function to convert a string from given base to decimal
long long convertToDecimal(const string& value, int base) {
    long long result = 0;
    long long power = 1;
    
    // Process from right to left
    for (int i = value.length() - 1; i >= 0; i--) {
        char digit = value[i];
        int digitValue;
        
        if (digit >= '0' && digit <= '9') {
            digitValue = digit - '0';
        } else if (digit >= 'a' && digit <= 'z') {
            digitValue = digit - 'a' + 10;
        } else if (digit >= 'A' && digit <= 'Z') {
            digitValue = digit - 'A' + 10;
        }
        
        result += digitValue * power;
        power *= base;
    }
    
    return result;
}

// Function to perform Lagrange interpolation and find constant term
double lagrangeInterpolation(const vector<pair<int, long long>>& points, int x) {
    double result = 0;
    int n = points.size();
    
    for (int i = 0; i < n; i++) {
        double term = points[i].second; // yi
        
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= (double)(x - points[j].first) / (points[i].first - points[j].first);
            }
        }
        
        result += term;
    }
    
    return result;
}

// Alternative implementation using integer arithmetic for better precision
long long lagrangeInterpolationInteger(const vector<pair<int, long long>>& points) {
    // Calculate f(0) using Lagrange interpolation
    long long result = 0;
    int n = points.size();
    
    for (int i = 0; i < n; i++) {
        long long numerator = points[i].second;
        long long denominator = 1;
        
        for (int j = 0; j < n; j++) {
            if (i != j) {
                numerator *= (0 - points[j].first);
                denominator *= (points[i].first - points[j].first);
            }
        }
        
        result += numerator / denominator;
    }
    
    return result;
}

int main() {
    // Test Case 1
    cout << "=== Test Case 1 ===" << endl;
    vector<pair<int, long long>> points1;
    
    // Manually decode the values from test case 1
    points1.push_back({1, convertToDecimal("4", 10)});      // (1, 4)
    points1.push_back({2, convertToDecimal("111", 2)});     // (2, 7)
    points1.push_back({3, convertToDecimal("12", 10)});     // (3, 12)
    points1.push_back({6, convertToDecimal("213", 4)});     // (6, 39)
    
    cout << "Decoded points:" << endl;
    for (const auto& point : points1) {
        cout << "(" << point.first << ", " << point.second << ")" << endl;
    }
    
    // Use first 3 points (k=3)
    vector<pair<int, long long>> selectedPoints1(points1.begin(), points1.begin() + 3);
    long long secret1 = lagrangeInterpolationInteger(selectedPoints1);
    cout << "Secret for test case 1: " << secret1 << endl;
    
    cout << "\n=== Test Case 2 ===" << endl;
    vector<pair<int, long long>> points2;
    
    // Manually decode the values from test case 2
    points2.push_back({1, convertToDecimal("13444211440455345511", 6)});
    points2.push_back({2, convertToDecimal("aed7015a346d63", 15)});
    points2.push_back({3, convertToDecimal("6aeeb69631c227c", 15)});
    points2.push_back({4, convertToDecimal("e1b5e05623d881f", 16)});
    points2.push_back({5, convertToDecimal("316034514573652620673", 8)});
    points2.push_back({6, convertToDecimal("2122212201122002221120200210011020220200", 3)});
    points2.push_back({7, convertToDecimal("20120221122211000100210021102001201112121", 3)});
    
    cout << "Decoded points (first 7):" << endl;
    for (const auto& point : points2) {
        cout << "(" << point.first << ", " << point.second << ")" << endl;
    }
    
    // Use first 7 points (k=7)
    long long secret2 = lagrangeInterpolationInteger(points2);
    cout << "Secret for test case 2: " << secret2 << endl;
    
    return 0;
}