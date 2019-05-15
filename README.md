# Installation

Using Ninja:

```
mkdir build
cd build
cmake -G Ninja -DCMAKE_INSTALL_PREFIX=<install_dir> ../src
ninja install
```

# Example of usage

Let's see an example using a file called *main.cc*:

```c++
#include <PerfQuirer.h>
#include <stdio.h>

void fun1()
{
  PERFQ_INSTRUMENT;
}

void fun2()
{
  PERFQ_INSTRUMENT;
}

void fun3()
{
  PERFQ_INSTRUMENT;

  for (unsigned i = 0; i < 20; i++)
  {
    fun2();
  }
}

int main(int argc, char *argv[])
{
  perfquirer::PerfQuirer::Start();

  for (unsigned i = 0; i < 99999; i++) {
    fun1();
    fun3();
  }

  perfquirer::PerfQuirer::Stop();

  printf("%s\n", perfquirer::PerfQuirer::AsJSON().c_str());

  perfquirer::PerfQuirer::ToFile("perfq.json");

  return 0;
}
```


Compile using *-DWITH_PERFQUIRER* and link with *-lperfquirer*:

```
g++ -O2 -o main main.cc -DWITH_PERFQUIRER -lperfquirer
```

This is an example of the output:

```
{"TOTALS" : {ticks : 222995910, percentage : 100.000%, exclusive-ticks : 12034712, exclusive-percentage : 5.397%, childs : [{"void fun1()" : {ticks : 4167712, percentage : 1.869%, exclusive-ticks : 4167712, exclusive-percentage : 1.869%, childs : []}}, {"void fun3()" : {ticks : 206793486, percentage : 92.734%, exclusive-ticks : 122569983, exclusive-percentage : 54.965%, childs : [{"void fun2()" : {ticks : 84223503, percentage : 37.769%, exclusive-ticks : 84223503, exclusive-percentage : 37.769%, childs : []}}]}}]}}
```

# PerfView

To print the output JSON file as a hierarchy in plain text use:

```
./perfview -t <output.json>
```

To navigate it graphically use:

```
./perfview -g <output.json>
```

