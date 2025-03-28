#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/* class PixelMatrix {
    int rows, cols;
    vector<vector<vector<int>>> matrix;
    public:
        PixelMatrix() {
            rows = 0;
            cols = 0;
        }
        PixelMatrix(const PixelMatrix &pm) {
            rows = pm.rows;
            cols = pm.cols;
            matrix = pm.matrix;
        }
        PixelMatrix(int rows, int cols) {
            this->rows = rows;
            this->cols = cols;
            matrix.resize(rows, vector<vector<int>>(cols, vector<int>(3, 0)));
        }
        int getCols() {
            return cols;
        }
        int getRows() {
            return rows;
        }
        int getPixel(int row, int col, int channel) {
            return matrix[row][col][channel];
        }
        void setPixel(int row, int col, int r, int g, int b) {
            matrix[row][col][0] = r;
            matrix[row][col][1] = g;
            matrix[row][col][2] = b;
        }
        void invertColors() {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    for (int k = 0; k < 3; k++) {
                        matrix[i][j][k] = 255 - matrix[i][j][k];
                    }
                }
            }
        }
        void grayscale() {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    int avg = (matrix[i][j][0] + matrix[i][j][1] + matrix[i][j][2]) / 3;
                    matrix[i][j][0] = avg;
                    matrix[i][j][1] = avg;
                    matrix[i][j][2] = avg;
                }
            }
        }
        void flipHorizontal() {
            for (int i = 0; i < rows; i++) {
                reverse(matrix[i].begin(), matrix[i].end());
            }
        }
        void flipVertical() {
            reverse(matrix.begin(), matrix.end());
        }
        void print() {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    cout << matrix[i][j][0] << " " << matrix[i][j][1] << " " << matrix[i][j][2] << " ";
                }
                cout << endl;
            }
        }
};
*/