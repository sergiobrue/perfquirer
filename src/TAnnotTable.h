#ifndef _PERFQUIRER_TICKS_ANNOTATION_TABLE_H_
#define _PERFQUIRER_TICKS_ANNOTATION_TABLE_H_

#include "PerfQNode.h"

#include <string>

#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

namespace perfquirer {

class TAnnotTable {
  friend class PerfQuirer;

  TAnnotTable();
  ~TAnnotTable();

  TAnnotTable(const TAnnotTable&)            = delete;
  TAnnotTable(const TAnnotTable&&)           = delete;
  TAnnotTable& operator=(const TAnnotTable&) = delete;

  void Stop();
  std::string AsJSON();

  std::uint64_t RenderTicksWithoutWastedOnes(PerfQNode& node);
  std::string NodeAsJSON(const PerfQNode& node);

  void EnterFunction(const char* func_name) __attribute__ ((hot));
  void ExitFunction() __attribute__ ((hot));

  PerfQNode* root_;
  PerfQNode* current_node_;
  bool done_;
};

} // ns perfquirer

#include "TAnnotTable.inl"

#endif /* _PERFQUIRER_TICKS_ANNOTATION_TABLE_H_ */
