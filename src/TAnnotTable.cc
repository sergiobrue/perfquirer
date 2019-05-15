#include "TAnnotTable.h"

namespace perfquirer {

TAnnotTable::TAnnotTable()
  : root_(new PerfQNode(nullptr, "TOTALS"))
  , current_node_(root_)
  , done_(false)
{
  root_->enter_ticks = __rdtsc();
}


TAnnotTable::~TAnnotTable()
{
  delete root_;
}


void TAnnotTable::Stop()
{
  root_->ticks = __rdtsc() - root_->enter_ticks;
  done_ = true;
  RenderTicksWithoutWastedOnes(*root_);
}


std::uint64_t TAnnotTable::RenderTicksWithoutWastedOnes(PerfQNode& node)
{
  std::uint64_t wasted_ticks_in_childs = 0;
  std::uint64_t non_wasted_ticks_in_childs = 0;

  for (auto child : node.child_nodes)
  {
    const std::uint64_t wasted_current_child = RenderTicksWithoutWastedOnes(*child);
    wasted_ticks_in_childs += wasted_current_child;
    non_wasted_ticks_in_childs += child->ticks;
  }

  node.ticks -= wasted_ticks_in_childs;
  node.exclusive_ticks = node.ticks - non_wasted_ticks_in_childs;

  return node.wasted_ticks + wasted_ticks_in_childs;
}


std::string TAnnotTable::AsJSON()
{
  return done_?NodeAsJSON(*root_):"Error: Please call Stop() before rendering as JSON";
}


std::string TAnnotTable::NodeAsJSON(const PerfQNode& node)
{
  static constexpr size_t MAX_NUM_STR_LEN = __builtin_log2(UINTMAX_MAX)+2;
  char ticks_str[MAX_NUM_STR_LEN];
  sprintf(ticks_str, "%ju", uintmax_t(node.ticks));

  char perc_str[sizeof("100.000")];
  sprintf(perc_str, "%.3f", (double(node.ticks)/root_->ticks)*100.);

  char exclusive_ticks_str[MAX_NUM_STR_LEN];
  sprintf(exclusive_ticks_str, "%ju", uintmax_t(node.exclusive_ticks));

  char exclusive_perc_str[sizeof("100.000")];
  sprintf(exclusive_perc_str, "%.3f", (double(node.exclusive_ticks)/root_->ticks)*100.);

  std::string ret_str = std::string("{\"") + node.func_name
    + "\" : {\"ticks\" : "                + ticks_str
    +     ", \"percentage\" : "           + perc_str
    +     ", \"exclusive-ticks\" : "      + exclusive_ticks_str
    +     ", \"exclusive-percentage\" : " + exclusive_perc_str
    +     ", \"childs\" : [";

  for (auto child : node.child_nodes)
  {
    ret_str += NodeAsJSON(*child)
      +((child!=node.child_nodes[node.child_nodes.size()-1])?", ":"");
  }

  return ret_str + "]}}";
}


} // ns perfquirer
