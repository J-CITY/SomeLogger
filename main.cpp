#include <iostream>

#include "someLogger.h"

using namespace std;
using namespace SomeLogger;

int main() {
	Logger logger = Logger::Instance();

	logger.log(LoggerLevel::ERR, Color::Red, Color::Blue) << PRINT_LINE_STR << " TEST" << Endl();


	logger.log(LoggerLevel::ERR, Color::Red, Color::Blue).logFormat(" QWERTYU  %d wwa %d", 1321, PRINT_LINE).endl();


	std::map<std::string, int> m = {
		{"one", 1},
		{"two", 2},
		{"three", 3},
	};
	std::vector<int> v = { 0,1,2 };

	logger << m << Endl();
	logger << v << Endl();

	//cout << "\033[1;31mbold red text\033[0m\n";
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
