Simple logger fro c++ and python

Also with support for tables and lists for more convenient output

```c++
#include <iostream>
#include "SomeLogger.h"

using namespace std;
using namespace SomeLogger;

int main() {
	Logger logger = Logger::Instance();
	logger.log(LoggerLevel::ERR, Color::Red, Color::Blue) << "TEST";

	logger.log(LoggerLevel::ERR, Color::Red, Color::Blue).logFormat(" WWW.FIRMCODES.COM \n %d", 9);

	List l;
	l << "TEST";
	l << "TEST";
	l << "TEST";
	l << "TEST";
	l << "TEST";
	l.print();

	Table t(5, 5);
	t.insert(1, 1, "!!!!");
	t.insert(1, 2, "!!!!");
	t.insert(1, 3, "!!!!");
	t.insert(4, 4, "!!!!");
	t[2][4] = TableElem("QWQFS");
	t.print();

	cout << t.get(2, 4);
	return 0;
}

```
```python
l=Logger()
l.log(Level.ERROR).lprint("WTF!!!!!!")

l = List()
l.insert(List.ElemList("TEST"))
l.insert(List.ElemList("TEST"))
l.insert(List.ElemList("TEST"))
l.insert(List.ElemList("TEST"))
l.insert(List.ElemList("TEST"))
l.lprint()

t = Table(5, 3);
t.insert(1, 1, "!!!!")
t.insert(2, 1, "!!!fsdf!")
t.insert(0, 1, "!22!")
t.insert(0, 0, "!")
t.tprint();

```