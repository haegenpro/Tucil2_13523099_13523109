# DPW Quadtree Program
## Tucil 2 IF2211 Strategi Algoritma

DPW Quadtree Program is an image compressor that uses a quadtree-based approach. It works by continuously subdividing an image into smaller blocks based on color similarity and various error metrics—including Mean Absolute Deviation (MAD), Maximum Pixel Difference (MPD), Variance, Entropy, and Structural Similarity Index (SSIM). This standard functionality compresses the image efficiently while preserving essential visual details.

## Overview

In addition to its core compression capabilities, the program offers advanced bonus features for enhanced performance and user experience, including:

- **Target Compression Percentage:** Users can specify a desired reduction in file size. The algorithm then employs a binary search method to adjust the quadtree threshold optimally, ensuring that the compressed image meets the targeted compression ratio.
- **GIF Visualization:** An animated GIF is generated to visually document the compression process. This feature provides a dynamic illustration of the quadtree's progressive subdivision and merging, offering valuable insights into how the algorithm refines the image.

## Requirements & Installation

### Requirements

- **GNU C++ Compiler version 9+:** A compiler supporting C++17 

### Installation

1. **Clone the Repository:**

```bash
git clone https://github.com/haegenpro/Tucil2_13523099_13523109.git
cd Tucil2_13523099_13523109
```

2. **Change to src directory**
```bash
cd src
```

3. **Compile the Program**

```bash
g++ -o ../bin/dpw_quadtree_program  error_measurement/*.cpp image/*.cpp pixel/*.cpp quadtree/*.cpp dpw_quadtree_program.cpp compressor/*.cpp -std=c++17 -O2    
```

4. **Run the Program**

```bash
cd ../bin
./dpw_quadtree_program 
```

Ensure that your directory structure matches the source file layout.
<br> If you are experiencing issues with compiling, feel free to use the provided executable in the bin directory

## Using the Program

1. **Run the Program via Terminal:**

    ```bash
    ./dpw_quadtree_compressor
    ```

2. **Follow the Interactive Prompts:**

    a. **Enter the file path of the image to be compressed.**  
    b. **Choose an error measurement method (e.g., SSIM, MAD, etc.).**  
    c. **Provide a threshold value and minimum block size.**  
    d. **Specify a target compression ratio (e.g., 0.3 for a 30% reduction in file size).**  
    e. **Enter the output file path for the compressed image.**  
    f. **Optionally, provide a GIF output file path to see the compression animation.**  
    g. **Output: The program displays information such as execution time, original and compressed file sizes, and the achieved compression percentage.**  

3. **Example Output:**

    ```bash
    Enter input file path: original_image.png
    Enter threshold: 0.05
    Enter minimum block size: 4
    Enter target compression ratio: 0.3
    Enter output file path: compressed_image.png
    Enter GIF file path: animation.gif
    Time taken for compression: 1.23 seconds
    Initial image size: 2048000 bytes
    Compressed image size: 512000 bytes
    Compression percentage: 75%
    Depth of QuadTree: 6
    Image saved to: compressed_image.png
    GIF saved to: animation.gif
    ```

## Project Status
| No | Poin                                                 | Ya | Tidak |
|----|------------------------------------------------------|:--:|:-----:|
| 1  | Program berhasil dikompilasi tanpa kesalahan        | ✓  |       |
| 2  | Program berhasil dijalankan                         | ✓  |       |
| 3  | Program berhasil melakukan kompresi gambar sesuai parameter yang ditentukan  | ✓  |       |
| 4  | Mengimplementasi seluruh metode perhitungan error wajib  | ✓  |       |
| 5  | [Bonus] Implementasi persentase kompresi sebagai parameter tambahan      | ✓  |       |
| 6  | [Bonus] Implementasi Structural Similarity Index (SSIM) sebagai metode pengukuran error | ✓  |       |
| 7  | [Bonus] Output berupa GIF Visualisasi Proses pembentukan Quadtree dalam Kompresi Gambar  | ✓  |       |
| 8  | Program dan laporan dibuat (kelompok) sendiri   | ✓   |    |

## Authors / Contributors

**Haegen Quinston**  
**haegenquinston@gmail.com**  
[![GitHub](https://img.shields.io/badge/GitHub-haegenpro-blue?style=flat&logo=github)](https://github.com/haegenpro)

**Daniel Pedrosa Wu**  
**13523099@std.stei.itb.ac.id**  
[![GitHub](https://img.shields.io/badge/GitHub-DanielDPW-blue?style=flat&logo=github)](https://github.com/DanielDPW)

## License

This project is distributed under the MIT License.