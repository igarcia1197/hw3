#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

  /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> data;
  int m_ary;
  PComparator comp;

  // helper functions to maintain heap property
  void heapifyUp(int index);
  void heapifyDown(int index);
};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c) : m_ary(m), comp(c) {
  if(m < 2)
    throw std::invalid_argument("m must be at least 2");
}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap() {
  // nothing special needed here; vector cleans up itself
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item) {
  data.push_back(item);
  heapifyUp(data.size() - 1);
}

template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data[0];
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }
  // Replace the top with the last element and remove the last element
  data[0] = data.back();
  data.pop_back();
  if(!empty()){
    heapifyDown(0);
  }
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const {
  return data.empty();
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const {
  return data.size();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapifyUp(int index) {
  while(index > 0) {
    int parent = (index - 1) / m_ary;
    if(comp(data[index], data[parent])) {
      T temp = data[index];
      data[index] = data[parent];
      data[parent] = temp;
      index = parent;
    }
    else {
      break;
    }
  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapifyDown(int index) {
  int n = data.size();
  while(true) {
    int best = index;
    for (int i = 1; i <= m_ary; i++) {
      int child = m_ary * index + i;
      if(child < n && comp(data[child], data[best])) {
        best = child;
      }
    }
    if(best != index) {
      T temp = data[index];
      data[index] = data[best];
      data[best] = temp;
      index = best;
    }
    else {
      break;
    }
  }
}

#endif
