#include<iostream>
#include<map>
#include<list>
#include<string>
#include<queue>

using namespace std;

template <typename T>
class MinHeap {
private:
    vector<T> heap; // The heap array
    map<T, int> indices; // Map to store the index of each element in the heap

    void heapifyUp(int index) { // Helper function to restore the heap property
        if (index == 0) return; // If the element is at the root, no need to heapify up
        int parent = (index - 1) / 2; // Parent index of the current element
        if (heap[parent] > heap[index]) { // If the parent is greater than the current element
            swap(heap[parent], heap[index]); // Swap the parent and the current element
            indices[heap[parent]] = parent; // Update the index of the parent
            indices[heap[index]] = index; // Update the index of the current element
            heapifyUp(parent); // Recursively heapify up the parent
        } 
    }

    void heapifyDown(int index) { // Helper function to restore the heap property
        int left = 2 * index + 1; // Left child index 
        int right = 2 * index + 2; // Right child index
        int smallest = index; // Assume the current element is the smallest
        if (left < heap.size() && heap[left] < heap[smallest]) { // If the left child is smaller than the current element
            smallest = left; // Update the smallest index
        }
        if (right < heap.size() && heap[right] < heap[smallest]) { // If the right child is smaller than the current element
            smallest = right; // Update the smallest index
        }
        if (smallest != index) { // If the current element is not the smallest
            swap(heap[index], heap[smallest]); // Swap the current element and the smallest element
            indices[heap[index]] = index; // Update the index of the current element
            indices[heap[smallest]] = smallest; // Update the index of the smallest element
            heapifyDown(smallest); // Recursively heapify down the smallest element
        }
    }

public:
    void insert(T element) { // Function to insert an element into the heap 
        heap.push_back(element); // Add the element to the end of the heap
        indices[element] = heap.size() - 1; // Update the index of the element
        heapifyUp(heap.size() - 1); // Restore the heap property
    }

    void decreaseKey(T element) {  // Function to decrease the key of an element in the heap
        heapifyUp(indices[element]); // Restore the heap property
    }

    void deleteKey(T element) { // Function to delete an element from the heap
        int index = indices[element]; // Get the index of the element
        swap(heap[index], heap[heap.size() - 1]); // Swap the element with the last element
        indices[heap[index]] = index; // Update the index of the element
        indices.erase(element); // Remove the element from the index map
        heap.pop_back(); // Remove the last element
        heapifyDown(index); // Restore the heap property
    }

    T extractMin() {
        T min = heap[0]; // Get the minimum element
        deleteKey(min); // Delete the minimum element
        return min; // Return the minimum element
    }

    bool empty() { // Function to check if the heap is empty
        return heap.empty(); // Return true if the heap is empty, false otherwise
    }
};