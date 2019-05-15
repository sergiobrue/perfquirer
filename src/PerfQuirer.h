#ifndef _PERF_QUIRER_H_
#define _PERF_QUIRER_H_

#include <string>

#ifdef _MSC_VER
#define __attribute__(x)
#endif

namespace perfquirer {

class TAnnotTable;

class PerfQuirer {
  friend class FuncInquirer;
public:
  static void Start() noexcept;
  static void Stop() noexcept;
  static std::string AsJSON() noexcept;
  static bool ToFile(const char* full_path_file);
private:
  static void EnterFunction(const char* func_name) noexcept __attribute__ ((hot));
  static void ExitFunction() noexcept __attribute__ ((hot));
  static void __CleanUp() noexcept;

  static thread_local TAnnotTable* GlobalTAnnotTable;
};

struct FuncInquirer {
  FuncInquirer(const char* func_name) { PerfQuirer::EnterFunction(func_name); }
  ~FuncInquirer() { PerfQuirer::ExitFunction(); }
};

} // ns perfquirer

#ifdef WITH_PERFQUIRER
#define PERFQ_INSTRUMENT \
  perfquirer::FuncInquirer ___fPerfInq_$$$__(__PRETTY_FUNCTION__);
#else
#define PERFQ_INSTRUMENT
#endif

#endif /* _PERF_QUIRER_H_ */
