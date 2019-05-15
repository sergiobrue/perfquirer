#ifndef _PERFQUIRER_PERF_Q_NODE_H_
#define _PERFQUIRER_PERF_Q_NODE_H_

#include <vector>
#include <cstdint>

namespace perfquirer {

class PerfQNode;

using PerfQNodeVec = std::vector<PerfQNode*>;

struct PerfQNode {
  PerfQNode(PerfQNode* iparent_node, const char* ifunc_name);
  ~PerfQNode();

  PerfQNode*  parent_node;
  const char* func_name;

  std::uint64_t ticks;
  std::uint64_t wasted_ticks;
  std::uint64_t enter_ticks;
  std::uint64_t exclusive_ticks;

  PerfQNodeVec child_nodes;
};


inline PerfQNode::PerfQNode(PerfQNode* iparent_node, const char* ifunc_name)
  : parent_node(iparent_node)
  , func_name(ifunc_name)
  , ticks(0)
  , wasted_ticks(0)
  , enter_ticks(0)
  , exclusive_ticks(0)
{}


inline PerfQNode::~PerfQNode()
{
  for (auto child : child_nodes)
  {
    delete child;
  }
}


} // ns perfquirer



#endif /* _PERFQUIRER_PERF_Q_NODE_H_ */
