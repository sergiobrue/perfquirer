// -*- mode: c++ -*-

namespace perfquirer {

inline void TAnnotTable::EnterFunction(const char* func_name)
{
  const auto ticks_start = __rdtsc();
  PerfQNode* child_node = nullptr;

  for (auto node : current_node_->child_nodes)
  {
    if (node->func_name == func_name)
    {
      child_node = node;
      break;
    }
  }

  if (!child_node)
  {
    child_node = new PerfQNode(current_node_, func_name);
    current_node_->child_nodes.push_back(child_node);
  }

  current_node_= child_node;
  current_node_->wasted_ticks += (__rdtsc()-ticks_start);
  current_node_->enter_ticks   = __rdtsc();
}


inline void TAnnotTable::ExitFunction()
{
  const std::uint64_t enter_ticks = current_node_->enter_ticks;
  current_node_->ticks += (__rdtsc()-enter_ticks);
  current_node_ = const_cast<PerfQNode*>(current_node_->parent_node);
}


} // ns perfquirer
