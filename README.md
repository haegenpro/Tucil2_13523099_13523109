# Quadtree Image Compression Program
## Tucil 2 IF2211 Strategi Algoritma

The Quadtree Image Compression Program provides a robust solution for reducing image file sizes using a quadtree-based approach. It works by recursively subdividing an image into smaller blocks based on color similarity and various error metrics—including Mean Absolute Deviation (MAD), Maximum Pixel Difference (MPD), Variance, Entropy, and Structural Similarity Index (SSIM). This standard functionality compresses the image efficiently while preserving essential visual details.

## Overview

In addition to its core compression capabilities, the program offers advanced bonus features for enhanced performance and user experience. These include:

- **Target Compression Percentage:** Users can specify a desired reduction in file size. The algorithm then employs a binary search method to adjust the quadtree threshold optimally, ensuring that the compressed image meets the targeted compression ratio.
- **GIF Visualization:** An animated GIF is generated to visually document the compression process. This feature provides a dynamic illustration of the quadtree's progressive subdivision and merging, offering valuable insights into how the algorithm refines the image.

Together, the standard and bonus features enable a balanced approach between achieving significant file size reduction and maintaining high image quality.

## Requirements & Installation

### Requirements

- **C++ Compiler:** A compiler supporting C++17 (e.g., GCC 7+, Clang 7+, or MSVC 2019 or later)
- **CMake:** (Optional) for building the project automatically
- **Additional Libraries:**
  - [stb_image](https://github.com/nothings/stb) for image processing
  - [stb_image_write](https://github.com/nothings/stb) for writing images to files
  - [gif](https://github.com/charlietangora/gif-h/blob/master/gif.h) for writing and reading GIF files

### Installation

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/username/quadtree-compression.git
   cd quadtree-compression
   ```

2. **Install Dependencies (if necessary):**

    Ensure that the stb_image and stb_image_write libraries are available.
    For Linux systems, install build essentials and CMake:
    ```bash
    sudo apt-get update
    sudo apt-get install build-essential cmake
    ```

## Compiling the Program

### Using CMake

1. **Create a Build Directory and Navigate Into It:**

    ```bash
    mkdir build
    cd build
    ```

2. **Generate Build Files Using CMake:**

    ```bash
    cmake ..
    ```

3. **Build the Program:**

    ```bash
    cmake --build .
    ```
    The compiled program will be located in the build directory.

### Using G++ Manually

If you prefer not to use CMake, compile manually with:

```bash
g++ -std=c++17 -O2 -o quadtree_compressor src/driver.cpp src/image.cpp src/ssim.cpp src/compressor.cpp src/quadtree.cpp -lm
```

Ensure that your directory structure matches the source file layout.

## Running and Using the Program

1. **Run the Program via Terminal:**

    ```bash
    ./quadtree_compressor
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

## Authors / Contributors

**Haegen Quinston**  
**haegenquinston@gmail.com**  
[![GitHub](https://img.shields.io/badge/GitHub-haegenpro-blue?style=flat&logo=github)](https://github.com/haegenpro)

**Daniel Pedrosa Wu**  
**13523099@std.stei.itb.ac.id**  
[![GitHub](https://img.shields.io/badge/GitHub-DanielDPW-blue?style=flat&logo=github)](https://github.com/DanielDPW)

## License

This project is distributed under the MIT License.