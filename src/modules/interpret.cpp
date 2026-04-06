#include "interpret.hpp"
#include "../utils/printer.hpp"

Interpreter::Interpreter(const Node &root, size_t memorySize)
    : m_root(root), m_memory(memorySize, 0), m_ptr(0) {}

Interpreter::~Interpreter() {}

void Interpreter::execute() {
  for (const Node &node : m_root.children) {
    executeNode(node);
  }
}

void Interpreter::executeNode(const Node &node) {
  switch (node.type) {
  case NodeType::IncrPtr:
    m_ptr+=node.delta;
    break;
  case NodeType::DecrPtr:
    m_ptr-=node.delta;
    break;
  case NodeType::IncrByte:
    m_memory[m_ptr]+=node.delta;
    break;
  case NodeType::DecrByte:
    m_memory[m_ptr]-=node.delta;
    break;
  case NodeType::Output:
    std::cout << static_cast<char>(m_memory[m_ptr]);
    break;
  case NodeType::Input:
    m_memory[m_ptr] = std::cin.get();
    break;
  case NodeType::Loop:
    executeLoop(node); // handle loops recursively
    break;
  default:
    break;
  }

  if (m_ptr < 0 || m_ptr >= m_memory.size()) {
    throw std::runtime_error("Pointer out of bounds");
  }
}

void Interpreter::executeLoop(const Node &node) {
  while (m_memory[m_ptr] != 0) {
    for (const Node &child : node.children) {
      executeNode(child);
    }
  }
}

