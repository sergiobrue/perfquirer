#include "PerfQuirer.h"
#include "TAnnotTable.h"

#include <iostream>
#include <fstream>

namespace perfquirer {

thread_local TAnnotTable* PerfQuirer::GlobalTAnnotTable = nullptr;


void PerfQuirer::Start() noexcept
{
  delete GlobalTAnnotTable;
  GlobalTAnnotTable = new TAnnotTable;
  atexit(PerfQuirer::__CleanUp);
}


void PerfQuirer::Stop() noexcept
{
  GlobalTAnnotTable->Stop();
}


std::string PerfQuirer::AsJSON() noexcept
{
  return GlobalTAnnotTable->AsJSON();
}


bool PerfQuirer::ToFile(const char* full_path_file)
{
  std::ofstream out_file(full_path_file);

  if (out_file.is_open())
  {
    out_file << AsJSON() << std::endl;
    return true;
  }

  std::cerr << __PRETTY_FUNCTION__
            << "Error: Cannot open/write to " << full_path_file;
  return false;
}


void PerfQuirer::EnterFunction(const char* func_name) noexcept
{
  GlobalTAnnotTable->EnterFunction(func_name);
}


void PerfQuirer::ExitFunction() noexcept
{
  GlobalTAnnotTable->ExitFunction();
}


void PerfQuirer::__CleanUp() noexcept
{
  delete GlobalTAnnotTable;
  GlobalTAnnotTable = nullptr;
}

} // ns perfquirer

