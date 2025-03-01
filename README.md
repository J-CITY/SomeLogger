# Simple logger for `C++` and `Python`

Also it support tables and lists for more beautiful output

## Usage in `C++`

```c++
#include <iostream>
#include "SomeLogger.h"

using namespace std;
using namespace SomeLogger;

int main() {
	Logger logger = Logger::Instance();

	// PRINT_LINE and PRINT_LINE_STR - define for print code line

	// stream
	logger.log(LoggerLevel::ERR, Color::Red, Color::Blue) << 
		PRINT_LINE_STR << " TEST" << Endl();
	// format output
	logger.log(LoggerLevel::ERR, Color::Red, Color::Blue)
		.logFormat("Data: %d - %d", 42, PRINT_LINE).endl();

	// print containers
	std::map<std::string, int> m = {
		{"one", 1},
		{"two", 2},
		{"three", 3},
	};
	std::vector<int> v = { 0,1,2 };

	logger << m << Endl();
	logger << v << Endl();

	// print list
	List l;
	l << "TEST";
	l << "TEST";
	l << "TEST";
	l << "TEST";
	l << "TEST";
	l.print();
	//or
	logger << l << Endl();

	// print table
	Table t(5, 5);
	t.insert(1, 1, "!!!!");
	t.insert(1, 2, "!!!!");
	t.insert(1, 3, "!!!!");
	t.insert(4, 4, "!!!!");
	t[2][4] = TableElem("QWQFS");
	t.print();
	// or
	logger << t << Endl();

	return 0;
}
```

## Usage in `Python`

```python
l=Logger()
l.log(Level.ERROR).lprint("TEST")

# print list
l = List()
l.insert(List.ElemList("TEST"))
l.insert(List.ElemList("TEST"))
l.insert(List.ElemList("TEST"))
l.insert(List.ElemList("TEST"))
l.insert(List.ElemList("TEST"))
l.lprint()

# print table
t = Table(5, 3)
t.insert(1, 1, "!!!!")
t.insert(2, 1, "!!!fsdf!")
t.insert(0, 1, "!22!")
t.insert(0, 0, "!")
t.tprint()
```