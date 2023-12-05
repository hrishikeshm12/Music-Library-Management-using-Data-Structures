# Music Library Management using Data Structures 

![image](https://github.com/hrishikeshm12/Music-Management-using-Data-Structures/assets/65590350/d24d5987-6340-4d0b-9607-2c27a23ad78f)


![image](https://github.com/hrishikeshm12/Music-Management-using-Data-Structures/assets/65590350/80028d20-1210-4c64-a25f-6cc8aa40d138)


## Abstract

The Song Management System efficiently manages music records using advanced data structures like Trees, Linked Lists, and Queues. It offers features such as loading songs, creating playlists, and analyzing time complexity for various operations. This in-depth documentation outlines the project's architecture, algorithms, and analysis of data structures, providing a comprehensive understanding of its functionality.

## 1. Introduction

### 1.1 Background

With the growing complexity of music libraries, a robust system is needed for efficient song management. This project addresses the need for an advanced Song Management System using cutting-edge data structures.

### 1.2 Objectives

- Implement a system capable of handling a large pool of songs.
- Utilize Trees for efficient searching, Linked Lists for dynamic playlist operations, and Queues for playlist functionality.
- Analyze and compare time complexities for key operations.

## 2. System Architecture

### 2.1 Data Structures Used

- **Binary Trees:** Efficient for searching and sorting.
- **Linked Lists:** Dynamic playlist operations (search, insert, delete).
- **Queues:** Playlist functionality.

### 2.2 Flowchart

![image](https://github.com/hrishikeshm12/Music-Management-using-Data-Structures/assets/65590350/15a91674-b1c5-4c6c-883d-48ec212f3e30)


## 3. Implementation Details

### 3.1 Song Loading

The Spotify Developers API is employed to obtain a metadata CSV file containing details of around 100 songs. This data is parsed and simulated as local storage for song loading.

### 3.2 Linked List Operations

The Linked List structure is utilized for playlist operations. Functions include search, insert, and delete to provide dynamic playlist functionality based on user instructions.

### 3.3 Tree Operations

Binary Trees handle search, manual insertion, and deletion of songs. This structure is chosen for its efficiency in searching and sorting.

### 3.4 Queue Implementation

Queues are employed for playlist functionality, ensuring a first-in, first-out order for a seamless music playback experience.

## 4. Time Complexity Analysis
![image](https://github.com/hrishikeshm12/Music-Management-using-Data-Structures/assets/65590350/6b0a2c57-0b62-4d97-8959-488ddf887874)

![image](https://github.com/hrishikeshm12/Music-Management-using-Data-Structures/assets/65590350/54d4d753-249c-45ea-893c-da7bd2b5c47c)


### 4.1 Binary Trees

- **Search:** O(log N)
- **Insertion:** O(log N)
- **Deletion:** O(log N)

### 4.2 Linked Lists

- **Search:** O(n)
- **Insertion:** O(1) (at the beginning), O(n) (in the middle)
- **Deletion:** O(1) (at the beginning), O(n) (in the middle)

### 4.3 Queues

- **Enqueue (Insert):** O(1)
- **Dequeue (Delete):** O(1)

## 5. Operational Analysis

### 5.1 Insertion

- **Arrays (when small):** O(1)
- **Binary Trees:** O(log N)

### 5.2 Insertion in the Middle

- **Arrays:** O(n)
- **Binary Trees:** O(log N)

### 5.3 Updation

- **Arrays:** O(1)
- **Binary Trees:** O(log N)

### 5.4 Deletion

- **Arrays:** O(n) (in the middle), O(1) (at the end)
- **Binary Trees:** O(log N)

## 6. Conclusion

The choice of data structures significantly impacts the system's efficiency. Binary Trees offer efficient searching but may degrade in specific scenarios. Linked Lists are suitable for dynamic operations, while Queues ensure a seamless playlist experience.


