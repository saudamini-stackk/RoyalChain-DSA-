# RoyalChain-DSA
RoyalChain Copyright Management System
1. Project Title
   
RoyalChain – Intellectual Property Rights Ledger
A Data Structures and Algorithms (DSA) based copyright management system developed in C++ for managing digital licenses, royalty distribution, ownership verification, transaction processing, and storage optimization.

2. Problem Statement

RoyalChain is a digital copyright tracking system that registers media licenses, verifies ownership transfers, and manages royalty payment distribution among publishers, distributors, and artists.
The existing system faces the following challenges:
Large license registry causing inefficient indexing.
Difficulty in tracking and reversing copyright clearances.
Delays in processing transfer requests.
Slow verification of licensing keys.
Manual tracing of royalty payment routes.
Increasing storage requirements for media asset descriptions.
The objective is to design an optimized system using suitable Data Structures and Algorithms.

3. Objectives

Maintain an efficient license registry.
Track copyright approval and revocation history.
Process transfer requests in submission order.
Verify licenses quickly.
Rank media based on transaction volume.
Model royalty distribution networks.
Find minimum-cost royalty payment routes.
Reduce storage requirements for asset descriptions.

4. System Overview / Architecture
   
The system consists of the following modules:
License Registry
Stores and indexes license IDs using a B-Tree.
Revocation Log
Tracks approval and rollback operations using a Stack.
Transfer Request Manager
Processes ownership transfer requests using a Queue.
Verification Ledger
Verifies license ownership using a Hash Table.
Media Ranking Module
Ranks media assets based on transaction volume using Merge Sort.
Royalty Channel Network
Represents royalty distribution paths using a Graph.
Route Optimization Module
Uses Dijkstra’s Algorithm to determine the cheapest royalty payment route.
Storage Divider
Compresses asset descriptions using Run Length Encoding (RLE).

5. Data Structures and Algorithms Used
   
Requirement	Data Structure / Algorithm
License Registry : B-Tree
Revocation Log	: Stack
Transfer Requests :Queue
License Verification	: Hash Table
Media Ranking	: Merge Sort
Royalty Network	: Graph
Route Optimization	: Dijkstra Algorithm
Storage Divider	: Run Length Encoding

6. Implementation Approach

B-Tree :
Used for indexing licenses efficiently. Supports insertion and searching in logarithmic time.
Stack :
Stores copyright approval history. Supports rollback using LIFO principle.
Queue :
Stores transfer requests and processes them in FIFO order.
Hash Table :
Provides near O(1) average-time license verification.
Merge Sort :
Sorts media assets by transaction volume in descending order.
Graph :
Represents publishers, distributors, agencies, and artists as nodes connected by weighted edges.
Dijkstra Algorithm :
Finds the minimum-cost route for royalty distribution.
Run Length Encoding :
Compresses repetitive asset descriptions to reduce storage requirements.

7. Time and Space Complexity Analysis

Module	Time Complexity
B-Tree Search	- O(log n)
B-Tree Insert	- O(log n)
Stack Push	- O(1)
Stack Pop	- O(1)
Queue Enqueue	- O(1)
Queue Dequeue	- O(1)
Hash Table Lookup	- O(1) Average
Merge Sort	- O(n log n)
Dijkstra Algorithm	- O((V + E) log V)
RLE Compression	- O(n)

8. Execution Steps

Compile
g++ RoyalChain.cpp -o RoyalChain
Run
./RoyalChain

9. Sample Inputs and Outputs

Add License
Input -
1
101
Taylor
Universal
Output -
License Added Successfully

Verify License
Input -
12
101
Output -
License Verified
Artist : Taylor
Owner  : Universal

Add Approval
Input -
4
AuthorityA
Output -
Approval Added

Process Transfer Request
Input -
7
101
9
Output -
Processed License ID: 101

Compress Asset Description
Input -
15
AAAAABBBCC
Output -
Compressed : 5A3B2C

10. Screenshots
    
    Main Menu
    <img width="404" height="288" alt="Screenshot 2026-06-15 at 13 30 11" src="https://github.com/user-attachments/assets/d92e6331-96dc-4769-af7a-81a4bf6d9de1" />

   License Registration
   <img width="258" height="80" alt="Screenshot 2026-06-15 at 13 32 28" src="https://github.com/user-attachments/assets/834da13a-f82d-47ee-af6f-eb09e9004105" />

   License Verification
   <img width="265" height="106" alt="Screenshot 2026-06-15 at 13 33 10" src="https://github.com/user-attachments/assets/4d7c7f45-c776-4c45-99c0-ac0e226f5f33" />

  Approval History
<img width="265" height="90" alt="Screenshot 2026-06-15 at 13 35 36" src="https://github.com/user-attachments/assets/fa9a383b-4a53-4b4a-b034-49bb157c620b" />

 Transfer Request Processing
 <img width="224" height="58" alt="Screenshot 2026-06-15 at 13 36 46" src="https://github.com/user-attachments/assets/4d2eddac-7e13-42d6-9a2c-82ce25782fa1" />

  Media Ranking
  <img width="268" height="82" alt="Screenshot 2026-06-15 at 13 41 10" src="https://github.com/user-attachments/assets/f66b60ae-9d50-40b9-9af3-b39a17015c6e" />

 Royalty Route Calculation
 <img width="267" height="116" alt="Screenshot 2026-06-15 at 13 44 33" src="https://github.com/user-attachments/assets/41c368e3-9684-4547-b030-2bac7114f7a3" />

 Asset Description Compression
 <img width="272" height="92" alt="Screenshot 2026-06-15 at 13 46 52" src="https://github.com/user-attachments/assets/1c6b3fa9-86e3-4400-a28f-d272e2966a65" />

11. Results and Observations

The system successfully demonstrates the practical application of multiple Data Structures and Algorithms to solve a real-world copyright management problem.
Observations:
B-Tree improves registry indexing efficiency.
Stack simplifies revocation tracking.
Queue ensures fair request processing.
Hashing provides fast license verification.
Merge Sort efficiently ranks media.
Graph and Dijkstra optimize royalty routing.
RLE reduces storage for repetitive descriptions.

12. Conclusion

RoyalChain successfully integrates several core Data Structures and Algorithms into a unified copyright management system. The project demonstrates efficient storage, retrieval, processing, sorting, routing, and compression techniques while satisfying all requirements of the Intellectual Property Rights Ledger case study.
Future Enhancements :
Full License Object Storage in B-Tree
Graph Visualization
Database Integration
Huffman Coding for Advanced Compression
User Authentication System
File-Based Persistent Storage

Author
Saudamini Nayak
150096725073
B.Tech CSE (2025–2029)
ITM Skills University
