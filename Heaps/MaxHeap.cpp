#include<iostream>
#include<map>
#include<list>
#include<string>
#include<queue>

using namespace std;

template <typename T>
class MaxHeap {
private:
    vector<T> heap; // The heap array
    map<T, int> indices; // Map to store the index of each element in the heap

    void heapifyUp(int index) { // Helper function to restore the heap property
        if (index == 0) return; // If the element is at the root, no need to heapify up
        int parent = (index - 1) / 2; // Parent index of the current element
        if (heap[parent] < heap[index]) { // If the parent is less than the current element
            swap(heap[parent], heap[index]); // Swap the parent and the current element
            indices[heap[parent]] = parent; // Update the index of the parent
            indices[heap[index]] = index; // Update the index of the current element
            heapifyUp(parent); // Recursively heapify up the parent
        } 
    }

    void heapifyDown(int index) { // Helper function to restore the heap property
        int left = 2 * index + 1; // Left child index 
        int right = 2 * index + 2; // Right child index
        int largest = index; // Assume the current element is the largest
        if (left < heap.size() && heap[left] > heap[largest]) { // If the left child is greater than the current element
            largest = left; // Update the largest index
        }
        if (right < heap.size() && heap[right] > heap[largest]) { // If the right child is greater than the current element
            largest = right; // Update the largest index
        }
        if (largest != index) { // If the current element is not the largest
            swap(heap[index], heap[largest]); // Swap the current element and the largest element
            indices[heap[index]] = index; // Update the index of the current element
            indices[heap[largest]] = largest; // Update the index of the largest element
            heapifyDown(largest); // Recursively heapify down the largest element
        }
    }

public:
    void insert(T element) { // Function to insert an element into the heap 
        heap.push_back(element); // Add the element to the end of the heap
        indices[element] = heap.size() - 1; // Update the index of the element
        heapifyUp(heap.size() - 1); // Restore the heap property
    }

    void increaseKey(T element) {  // Function to increase the key of an element in the heap
        heapifyUp(indices[element]); // Restore the heap property
    }

    void deleteKey(T element) { // Function to delete an element from the heap
        int index = indices[element]; // Get the index of the element
        swap(heap[index], heap[heap.size() - 1]); // Swap the element with the last element
        indices[heap[index]] = index; // Update the index of the element
        indices.erase(element); // Remove the element from the index map
        heap.pop_back(); // Remove the last element
    }

    T extractMax() { // Function to extract the maximum element from the heap
        T maxElement = heap[0]; // Get the maximum element
        indices.erase(maxElement); // Remove the maximum element from the index map
        swap(heap[0], heap[heap.size() - 1]); // Swap the maximum element with the last element
        indices[heap[0]] = 0; // Update the index of the maximum element
        heap.pop_back(); // Remove the maximum element
        heapifyDown(0); // Restore the heap property
        return maxElement; // Return the maximum element
    }

    T getMax() { // Function to get the maximum element from the heap
        return heap[0]; // Return the maximum element
    }

    bool empty() { // Function to check if the heap is empty
        return heap.empty(); // Return true if the heap is empty, false otherwise
    }
};