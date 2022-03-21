/* ***************************************************************************

Główny plik systemu testowego, dzięki któremu można łatwo przetestować
dany ADT za pomocą testów opracowanych przez wiele osób. Każda z nich
dostarcza odrębny plik z opracowanymi przez nią testami sprawdzającymi
poprawność działania tego ADT.

Załóżmy, że testy dla Set<T> są w plikach set_palacz.cpp, set_nowak.cpp,
set_kowalski.cpp itd. Pliki zawierają instrukcje dodające zdefiniowane
w nich testy do centralnego rejestru (patrz set_palacz.cpp). Tu w głównym
pliku mamy zaś kod uruchamiający wszystkie zarejestrowane testy.

Wszystkie pliki są kompilowane jednym poleceniem:

g++ -std=c++14 -pedantic -Wall set_*.cpp runner.cpp -lcppunit -o set_tests

*************************************************************************** */

#include <cppunit/TextTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

int main()
{
    CppUnit::TextTestRunner runner;

    auto & registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());

    bool success = runner.run();
    return static_cast<int>(! success);
}
